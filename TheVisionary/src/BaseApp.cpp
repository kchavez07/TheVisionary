/**
 * @file BaseApp.cpp
 * @brief Bucle principal, inicialización de DX11 y orquestación del render.
 */

#include "BaseApp.h"
#include "ECS/Transform.h"
#include "imgui.h"

// Color de limpieza
static const float kClear[4] = { 0.0f, 0.125f, 0.30f, 1.0f };

HRESULT BaseApp::init()
{
    HRESULT hr = S_OK;

    // 1) SwapChain + Device + Context + BackBuffer  (sin MSAA para evitar mismatches)
    hr = m_swapChain.init(m_device, m_deviceContext, m_backBuffer, m_window);
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to initialize SwapChain. hr=" + std::to_string(hr)).c_str());
        return hr;
    }

    // 2) RenderTargetView sobre el backbuffer
    hr = m_renderTargetView.init(m_device, m_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to initialize RenderTargetView. hr=" + std::to_string(hr)).c_str());
        return hr;
    }

    // 3) DepthStencil (textura + view) con sampleCount=1 (igual al swapchain)
    hr = m_depthStencil.init(
        m_device,
        m_window.m_width,
        m_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL,
        1,      // <- IMPORTANT: igual que swapchain
        0
    );
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to initialize DepthStencil texture. hr=" + std::to_string(hr)).c_str());
        return hr;
    }

    hr = m_depthStencilView.init(m_device, m_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to initialize DepthStencilView. hr=" + std::to_string(hr)).c_str());
        return hr;
    }

    // 4) Viewport
    hr = m_viewport.init(m_window);
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to initialize Viewport. hr=" + std::to_string(hr)).c_str());
        return hr;
    }

    // 5) InputLayout (POSITION, TEXCOORD)
    std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
    {
        D3D11_INPUT_ELEMENT_DESC pos{};
        pos.SemanticName = "POSITION";
        pos.SemanticIndex = 0;
        pos.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        pos.InputSlot = 0;
        pos.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        pos.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        pos.InstanceDataStepRate = 0;
        layout.push_back(pos);

        D3D11_INPUT_ELEMENT_DESC uv{};
        uv.SemanticName = "TEXCOORD";
        uv.SemanticIndex = 0;
        uv.Format = DXGI_FORMAT_R32G32_FLOAT;
        uv.InputSlot = 0;
        uv.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        uv.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        uv.InstanceDataStepRate = 0;
        layout.push_back(uv);
    }

    // --- 6) Shaders (.fx) ---
    hr = m_shaderProgram.init(m_device, "TheVisionary.fx", layout);  // <- usa aquí el .fx real en tu bin
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to initialize ShaderProgram. hr=" + std::to_string(hr)).c_str());
        return hr;
    }

    // --- 7) Constant Buffers (cámara) ---
    hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to create CB NeverChanges. hr=" + std::to_string(hr)).c_str());
        return hr;
    }
    hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
    if (FAILED(hr)) {
        ERROR("Main", "InitDevice", ("Failed to create CB ChangeOnResize. hr=" + std::to_string(hr)).c_str());
        return hr;
    }

    // --- 8) Matrices de cámara ---
    {
        XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
        XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

        m_View = XMMatrixLookAtLH(Eye, At, Up);
        cbNeverChanges.mView = XMMatrixTranspose(m_View);

        m_Projection = XMMatrixPerspectiveFovLH(
            XM_PIDIV4,
            m_window.m_width / (FLOAT)m_window.m_height,
            0.01f, 100.0f
        );
        cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
    }

    // --- 9) Actor: Ninja (FBX) ---
    {
        auto ninja = EU::MakeShared<Actor>(m_device);
        if (ninja.isNull()) {
            ERROR("Main", "InitDevice", "Failed to create Ninja Actor.");
            return E_FAIL;
        }

        const std::string kFBX = "ModelsFBX\\NinjaObscurity\\Ninja of Obscurity v02.fbx";
        if (!m_modelLoader.LoadFBXModel(kFBX) || m_modelLoader.meshes.empty()) {
            ERROR("Main", "InitDevice", ("Failed to load Ninja FBX: " + kFBX).c_str());
            return E_FAIL;
        }

        // Malla(s)
        ninja->setMesh(m_device, m_modelLoader.meshes);

        // Textura principal (intenta PNG y luego DDS)
        Texture ninjaSkin;
        HRESULT th = ninjaSkin.init(m_device, "ModelsFBX\\NinjaObscurity\\ninja_skin_02", PNG);
        if (FAILED(th)) {
            th = ninjaSkin.init(m_device, "ModelsFBX\\NinjaObscurity\\ninja_skin_02", DDS);
        }

        std::vector<Texture> ninjaTex;
        if (SUCCEEDED(th)) {
            ninjaTex.push_back(ninjaSkin);
        }
        else {
            // Fallback a textura por defecto
            Texture fallback;
            if (SUCCEEDED(fallback.init(m_device, "Textures\\Default", DDS)) ||
                SUCCEEDED(fallback.init(m_device, "Textures\\Default", PNG))) {
                ninjaTex.push_back(fallback);
            }
        }
        ninja->setTextures(ninjaTex);

        // Transform (FBX suele venir grande)
        ninja->getComponent<Transform>()->setTransform(
            EU::Vector3(0.0f, 0.0f, 0.0f),    // pos
            EU::Vector3(0.0f, 0.0f, 0.0f),    // rot
            EU::Vector3(0.01f, 0.01f, 0.01f)  // scale
        );
        ninja->setCastShadow(false);

        m_actors.push_back(ninja);
    }

    // 10) ACTOR: Plano simple (suelo con Lava.png)
    {
        const float kSize = 20.0f;  // mitad del tamaño del plano
        const float kTiling = 6.0f;   // repetición de la textura en U/V

        m_APlane = EU::MakeShared<Actor>(m_device);
        if (m_APlane.isNull()) {
            ERROR("Main", "InitDevice", "Failed to create Plane Actor.");
            return E_FAIL;
        }

        // Malla del plano (UVs preparados para tiling)
        SimpleVertex planeVertices[] =
        {
            { XMFLOAT3(-kSize, 0.0f, -kSize), XMFLOAT2(0.0f,    0.0f) },
            { XMFLOAT3(kSize, 0.0f, -kSize), XMFLOAT2(kTiling, 0.0f) },
            { XMFLOAT3(kSize, 0.0f,  kSize), XMFLOAT2(kTiling, kTiling) },
            { XMFLOAT3(-kSize, 0.0f,  kSize), XMFLOAT2(0.0f,    kTiling) },
        };
        WORD planeIndices[] = { 0,2,1, 0,3,2 };

        planeMesh.m_vertex.assign(std::begin(planeVertices), std::end(planeVertices));
        planeMesh.m_index.assign(std::begin(planeIndices), std::end(planeIndices));
        planeMesh.m_numVertex = 4;
        planeMesh.m_numIndex = 6;

        std::vector<MeshComponent> planeMeshes{ planeMesh };
        m_APlane->setMesh(m_device, planeMeshes);

        // *** Textura del piso: ModelsFBX\NinjaObscurity\Lava.png ***
        HRESULT hr = m_PlaneTexture.init(m_device, "ModelsFBX\\NinjaObscurity\\Lava", PNG);
        if (FAILED(hr)) {
            // Fallback si no se encuentra la Lava
            if (FAILED(m_PlaneTexture.init(m_device, "Textures\\Default", DDS)))
                m_PlaneTexture.init(m_device, "Textures\\Default", PNG);
        }

        std::vector<Texture> planeTextures{ m_PlaneTexture };
        m_APlane->setTextures(planeTextures);

        // Transform (ajusta Y si tu escena usa -5.0f como suelo)
        m_APlane->getComponent<Transform>()->setTransform(
            EU::Vector3(0.0f, -5.0f, 0.0f),   // posición
            EU::Vector3(0.0f, 0.0f, 0.0f),   // rotación
            EU::Vector3(1.0f, 1.0f, 1.0f)    // escala
        );

        m_APlane->setCastShadow(false);
        m_APlane->setReceiveShadow(true);

        m_actors.push_back(m_APlane);
    }

    // --- 11) Luz ---
    m_LightPos = XMFLOAT4(2.0f, 4.0f, -2.0f, 1.0f);

    // --- 12) ImGui (al final del init gráfico) ---
    m_userInterface.init(
        m_window.m_hWnd,
        m_device.m_device,
        m_deviceContext.m_deviceContext
    );

    return S_OK;

    // --- 10) Actor: Plano simple ---
    {
        m_APlane = EU::MakeShared<Actor>(m_device);
        if (m_APlane.isNull()) {
            ERROR("Main", "InitDevice", "Failed to create Plane Actor.");
            return E_FAIL;
        }

        SimpleVertex planeVertices[] =
        {
            { XMFLOAT3(-20.0f, 0.0f, -20.0f), XMFLOAT2(0.0f, 0.0f) },
            { XMFLOAT3(20.0f, 0.0f, -20.0f), XMFLOAT2(1.0f, 0.0f) },
            { XMFLOAT3(20.0f, 0.0f,  20.0f), XMFLOAT2(1.0f, 1.0f) },
            { XMFLOAT3(-20.0f, 0.0f,  20.0f), XMFLOAT2(0.0f, 1.0f) },
        };
        WORD planeIndices[] = { 0,2,1, 0,3,2 };

        planeMesh.m_vertex.assign(planeVertices, planeVertices + 4);
        planeMesh.m_index.assign(planeIndices, planeIndices + 6);
        planeMesh.m_numVertex = 4;
        planeMesh.m_numIndex = 6;

        // Textura del plano (Default)
        hr = m_PlaneTexture.init(m_device, "Textures\\Default", DDS);
        if (FAILED(hr)) hr = m_PlaneTexture.init(m_device, "Textures\\Default", PNG);

        std::vector<MeshComponent> planeMeshes{ planeMesh };
        std::vector<Texture>      planeTextures{ m_PlaneTexture };

        m_APlane->setMesh(m_device, planeMeshes);
        m_APlane->setTextures(planeTextures);
        m_APlane->getComponent<Transform>()->setTransform(
            EU::Vector3(0.0f, -5.0f, 0.0f),
            EU::Vector3(0.0f, 0.0f, 0.0f),
            EU::Vector3(1.0f, 1.0f, 1.0f)
        );
        m_APlane->setCastShadow(false);
        m_actors.push_back(m_APlane);
    }

    // --- 11) Luz ---
    m_LightPos = XMFLOAT4(2.0f, 4.0f, -2.0f, 1.0f);

    // --- 12) ImGui (al final del init gráfico) ---
    m_userInterface.init(
        m_window.m_hWnd,
        m_device.m_device,
        m_deviceContext.m_deviceContext
    );

    return S_OK;

}

void BaseApp::update()
{
    // --- UI frame ---
    m_userInterface.update();

    // Inspector + Outliner (tal cual lo tenías)
    if (!m_actors.empty())
    {
        if (m_userInterface.selectedActorIndex < 0 ||
            m_userInterface.selectedActorIndex >= (int)m_actors.size())
        {
            m_userInterface.selectedActorIndex = 0;
        }
        m_userInterface.inspectorGeneral(m_actors[m_userInterface.selectedActorIndex]);
    }
    m_userInterface.outliner(m_actors);

    // --- Tiempo ---
    static float t = 0.0f;
    static DWORD t0 = 0;
    DWORD tNow = GetTickCount();
    if (t0 == 0) t0 = tNow;
    t = (tNow - t0) / 1000.0f;

    // ----------------------------------------------------
    // CONTROLES DE CÁMARA (RMB orbitar, rueda zoom, MMB pan)
    // ----------------------------------------------------
    {
        ImGuiIO& io = ImGui::GetIO();
        bool uiCapturaMouse = io.WantCaptureMouse;

        static bool orbitando = false, paneando = false;
        static POINT ultimo{};

        if (!uiCapturaMouse)
        {
            // ORBIT (RMB)
            if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
            {
                POINT p; GetCursorPos(&p);
                if (!orbitando) { orbitando = true; ultimo = p; }
                float dx = float(p.x - ultimo.x);
                float dy = float(p.y - ultimo.y);
                m_camYawDeg += dx * 0.25f;
                m_camPitchDeg -= dy * 0.25f;
                m_camPitchDeg = std::clamp(m_camPitchDeg, -89.0f, 89.0f);
                ultimo = p;
            }
            else orbitando = false;

            // ZOOM (rueda)
            if (io.MouseWheel != 0.0f)
            {
                m_camDistance *= (io.MouseWheel > 0 ? 0.9f : 1.1f);
                m_camDistance = std::clamp(m_camDistance, 2.0f, 50.0f);
            }

            // PAN (MMB)
            if (GetAsyncKeyState(VK_MBUTTON) & 0x8000)
            {
                POINT p; GetCursorPos(&p);
                if (!paneando) { paneando = true; ultimo = p; }
                float dx = float(p.x - ultimo.x);
                float dy = float(p.y - ultimo.y);
                ultimo = p;

                float yaw = XMConvertToRadians(m_camYawDeg);
                float pitch = XMConvertToRadians(m_camPitchDeg);

                XMVECTOR forward = XMVectorSet(sinf(yaw) * cosf(pitch), sinf(pitch),
                    cosf(yaw) * cosf(pitch), 0);
                XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMVectorSet(0, 1, 0, 0), forward));
                XMVECTOR up = XMVectorSet(0, 1, 0, 0);

                float panSpeed = m_camDistance * 0.0025f;
                XMVECTOR delta = -dx * panSpeed * right + dy * panSpeed * up;

                m_camTarget.x += XMVectorGetX(delta);
                m_camTarget.y += XMVectorGetY(delta);
                m_camTarget.z += XMVectorGetZ(delta);
            }
            else paneando = false;
        }

        // Recalcular la vista (m_View) con yaw/pitch/distancia/target
        {
            float yaw = XMConvertToRadians(m_camYawDeg);
            float pitch = XMConvertToRadians(m_camPitchDeg);
            float cy = cosf(yaw), sy = sinf(yaw);
            float cp = cosf(pitch), sp = sinf(pitch);

            XMVECTOR eye = XMVectorSet(m_camTarget.x + sy * cp * m_camDistance,
                m_camTarget.y + sp * m_camDistance,
                m_camTarget.z + cy * cp * m_camDistance, 1.0f);
            XMVECTOR at = XMVectorSet(m_camTarget.x, m_camTarget.y, m_camTarget.z, 1.0f);
            XMVECTOR up = XMVectorSet(0, 1, 0, 0);

            m_View = XMMatrixLookAtLH(eye, at, up);
        }
    }
    // ----------------------------------------------------

    // --- Subir cbuffers de cámara (igual que lo tenías) ---
    cbNeverChanges.mView = XMMatrixTranspose(m_View);
    m_neverChanges.update(m_deviceContext, nullptr, 0, nullptr, &cbNeverChanges, 0, 0);

    cbChangesOnResize.mProjection = XMMatrixTranspose(m_Projection);
    m_changeOnResize.update(m_deviceContext, nullptr, 0, nullptr, &cbChangesOnResize, 0, 0);

    // --- Actores ---
    for (auto& a : m_actors)
        if (!a.isNull())
            a->update(t, m_deviceContext);
}


void BaseApp::render() {
    // Limpiar y bind RTV/DSV
    m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, kClear);
    m_viewport.render(m_deviceContext);
    m_depthStencilView.render(m_deviceContext);

    // Pipeline
    m_shaderProgram.render(m_deviceContext);

    // Constantes
    m_neverChanges.render(m_deviceContext, 0, 1);
    m_changeOnResize.render(m_deviceContext, 1, 1);

    // Dibujo de actores
    for (auto& a : m_actors) if (!a.isNull()) a->render(m_deviceContext);

    // UI + Present
    m_userInterface.render();
    m_swapChain.present();
}

void BaseApp::destroy() {
    // Cierra ImGui correctamente (evita Live Objects)
    m_userInterface.destroy();

    if (m_deviceContext.m_deviceContext)
        m_deviceContext.m_deviceContext->ClearState();

    for (auto& a : m_actors) if (!a.isNull()) a->destroy();
    m_actors.clear();

    m_neverChanges.destroy();
    m_changeOnResize.destroy();
    m_shaderProgram.destroy();
    m_depthStencil.destroy();
    m_depthStencilView.destroy();
    m_renderTargetView.destroy();
    m_swapChain.destroy();

    if (m_deviceContext.m_deviceContext) m_deviceContext.m_deviceContext->Release();
    if (m_device.m_device)               m_device.m_device->Release();
}

int BaseApp::run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndproc) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
        return 0;

    if (FAILED(init())) {
        destroy();
        return 0;
    }

    MSG msg = { 0 };
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            update();
            render();
        }
    }

    destroy();
    return (int)msg.wParam;
}
