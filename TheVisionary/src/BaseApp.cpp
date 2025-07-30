/**
 * @file BaseApp.cpp
 * @brief Implementación de la clase BaseApp
 */

#include "BaseApp.h"
#include "UserInterface.h"

 // Declaración adelantada del procedimiento de ventana
extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int BaseApp::run(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow,
    WNDPROC wndproc)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(m_window.init(hInstance, nCmdShow, wndproc)))
        return 0;

    if (FAILED(init()))
    {
        destroy();
        return 0;
    }

    // Bucle principal de mensajes
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            update();
            render();
        }
    }

    destroy();
    return static_cast<int>(msg.wParam);
}

HRESULT BaseApp::init()
{
    HRESULT hr = S_OK;

    // === Inicializar SwapChain ===
    hr = m_swapChain.init(m_device, m_deviceContext, m_backBuffer, m_window);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize SwapChain. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Render Target View ===
    hr = m_renderTargetView.init(m_device, m_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize RenderTargetView. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Depth Stencil Texture ===
    hr = m_depthStencil.init(
        m_device,
        m_window.m_width,
        m_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL,
        4,
        0
    );
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize DepthStencil. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Depth Stencil View ===
    hr = m_depthStencilView.init(m_device, m_depthStencil, DXGI_FORMAT_D24_UNORM_S8_UINT);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize DepthStencilView. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Viewport ===
    hr = m_viewport.init(m_window);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Viewport. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Input Layout ===
    std::vector<D3D11_INPUT_ELEMENT_DESC> Layout;

    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);

    // === Shader Program ===
    hr = m_shaderProgram.init(m_device, "TheVisionary.fx", Layout);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize ShaderProgram. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }
    // === Vértices e índices del cubo ===
    SimpleVertex vertices[] = {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
    };

    unsigned int indices[] = {
        3,1,0, 2,1,3,
        6,4,5, 7,4,6,
        11,9,8, 10,9,11,
        14,12,13, 15,12,14,
        19,17,16, 18,17,19,
        22,20,21, 23,20,22
    };

    for (int i = 0; i < 24; ++i) m_cubeMesh.m_vertex.push_back(vertices[i]);
    for (int i = 0; i < 36; ++i) m_cubeMesh.m_index.push_back(indices[i]);

    // === Vertex Buffer ===
    hr = m_vertexBuffer.init(m_device, m_cubeMesh, D3D11_BIND_VERTEX_BUFFER);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize VertexBuffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Index Buffer ===
    hr = m_indexBuffer.init(m_device, m_cubeMesh, D3D11_BIND_INDEX_BUFFER);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize IndexBuffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Constant Buffers ===
    hr = m_neverChanges.init(m_device, sizeof(CBNeverChanges));
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize NeverChanges Buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    hr = m_changeOnResize.init(m_device, sizeof(CBChangeOnResize));
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize ChangeOnResize Buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    hr = m_changeEveryFrame.init(m_device, sizeof(CBChangesEveryFrame));
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize ChangesEveryFrame Buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Cargar Textura ===
    hr = D3DX11CreateShaderResourceViewFromFile(m_device.m_device, "seafloor.dds", NULL, NULL, &m_textureRV, NULL);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to load texture 'seafloor.dds'. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Sampler State ===
    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = m_device.CreateSamplerState(&sampDesc, &m_samplerLinear);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to create SamplerState. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Configurar cámara (View Matrix) ===
    XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f); // Posición de la cámara
    XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);   // Hacia dónde mira
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);   // Vector arriba

    m_view = XMMatrixLookAtLH(Eye, At, Up);
    m_cbNeverChanges.mView = XMMatrixTranspose(m_view);

    // === Configurar proyección (Projection Matrix) ===
    m_projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, m_window.m_width / (FLOAT)m_window.m_height, 0.01f, 100.0f);
    m_cbChangesOnResize.mProjection = XMMatrixTranspose(m_projection);

    // === Crear geometría del plano (suelo) ===
    SimpleVertex planeVertices[] =
    {
        { XMFLOAT3(-20.0f, 0.0f, -20.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(20.0f, 0.0f, -20.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(20.0f, 0.0f,  20.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-20.0f, 0.0f,  20.0f), XMFLOAT2(0.0f, 1.0f) },
    };

    WORD planeIndices[] =
    {
        0, 2, 1,
        0, 3, 2
    };

    m_planeIndexCount = 6;

    // Guardar datos en el MeshComponent
    for (int i = 0; i < 4; i++) {
        m_planeMesh.m_vertex.push_back(planeVertices[i]);
    }

    for (int i = 0; i < 6; i++) {
        m_planeMesh.m_index.push_back(planeIndices[i]);
    }

    // Inicializar vertex buffer del plano
    hr = m_planeVertexBuffer.init(m_device, m_planeMesh, D3D11_BIND_VERTEX_BUFFER);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize PlaneVertexBuffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // Inicializar index buffer del plano
    hr = m_planeIndexBuffer.init(m_device, m_planeMesh, D3D11_BIND_INDEX_BUFFER);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize PlaneIndexBuffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // Inicializar constant buffer para el plano
    hr = m_constPlane.init(m_device, sizeof(CBChangesEveryFrame));
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Plane Constant Buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Compilar pixel shader para sombra ===
    hr = m_shaderShadow.CreateShader(m_device, PIXEL_SHADER, "TheVisionary.fx");
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow Shader. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Crear constant buffer para sombra ===
    hr = m_constShadow.init(m_device, sizeof(CBChangesEveryFrame));
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow Constant Buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Crear estado de blending para sombra ===
    hr = m_shadowBlendState.init(m_device);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow Blend State. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Crear estado de depth stencil para sombra ===
    hr = m_shadowDepthStencilState.init(m_device, true, false);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow DepthStencil State. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Compilar pixel shader para sombra ===
    hr = m_shaderShadow.CreateShader(m_device, PIXEL_SHADER, "TheVisionary.fx");
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow Shader. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Crear constant buffer para sombra ===
    hr = m_constShadow.init(m_device, sizeof(CBChangesEveryFrame));
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow Constant Buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Crear estado de blending para sombra ===
    hr = m_shadowBlendState.init(m_device);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow Blend State. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // === Crear estado de depth stencil para sombra ===
    hr = m_shadowDepthStencilState.init(m_device, true, false);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", ("Failed to initialize Shadow DepthStencil State. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    m_deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // === Inicializar Interfaz de Usuario (ImGui) ===
    HWND hwnd = m_window.getHWND();
    m_userInterface.init(hwnd, m_device.m_device, m_deviceContext.m_deviceContext);

    // === Crear estado rasterizado sólido ===
    D3D11_RASTERIZER_DESC descSolid = {};
    descSolid.FillMode = D3D11_FILL_SOLID;
    descSolid.CullMode = D3D11_CULL_BACK;
    descSolid.DepthClipEnable = TRUE;

    hr = m_device.m_device->CreateRasterizerState(&descSolid, &m_rasterStateDefault);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", "Failed to create solid rasterizer state.");
        return hr;
    }

    // === Crear estado rasterizado en wireframe ===
    D3D11_RASTERIZER_DESC descWireframe = {};
    descWireframe.FillMode = D3D11_FILL_WIREFRAME;
    descWireframe.CullMode = D3D11_CULL_NONE;
    descWireframe.DepthClipEnable = TRUE;

    hr = m_device.m_device->CreateRasterizerState(&descWireframe, &m_rasterStateWireframe);
    if (FAILED(hr)) {
        ERROR("BaseApp", "init", "Failed to create wireframe rasterizer state.");
        return hr;
    }

    return S_OK;

}


void BaseApp::update()
{
    // === Actualizar tiempo ===
    static float t = 0.0f;
    if (m_swapChain.m_driverType == D3D_DRIVER_TYPE_REFERENCE) {
        t += (float)XM_PI * 0.0125f;
    }
    else {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
        if (dwTimeStart == 0) dwTimeStart = dwTimeCur;
        t = (dwTimeCur - dwTimeStart) / 1000.0f;
    }

    // === Actualizar matrices de cámara y transformaciones ===
    m_cbNeverChanges.mView = XMMatrixTranspose(m_view);
    m_neverChanges.update(m_deviceContext, nullptr, 0, nullptr, &m_cbNeverChanges, 0, 0);

    m_cbChangesOnResize.mProjection = XMMatrixTranspose(m_projection);
    m_changeOnResize.update(m_deviceContext, nullptr, 0, nullptr, &m_cbChangesOnResize, 0, 0);

    XMMATRIX cubeScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
    XMMATRIX cubeRot = XMMatrixRotationY(t);
    XMMATRIX cubeTrans = XMMatrixTranslation(0.0f, 2.0f, 0.0f);
    m_world = cubeTrans * cubeRot * cubeScale;

    m_meshColor = {
        (sinf(t * 1.0f) + 1.0f) * 0.5f,
        (cosf(t * 3.0f) + 1.0f) * 0.5f,
        (sinf(t * 5.0f) + 1.0f) * 0.5f,
        1.0f
    };

    XMMATRIX planeTrans = XMMatrixTranslation(0.0f, -5.0f, 0.0f);
    m_planeWorld = planeTrans;

    m_cbPlane.mWorld = XMMatrixTranspose(m_planeWorld);
    m_cbPlane.vMeshColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
    m_constPlane.update(m_deviceContext, nullptr, 0, nullptr, &m_cbPlane, 0, 0);

    m_cb.mWorld = XMMatrixTranspose(m_world);
    m_cb.vMeshColor = m_meshColor;
    m_changeEveryFrame.update(m_deviceContext, nullptr, 0, nullptr, &m_cb, 0, 0);

    float dot = m_lightPos.y;
    XMMATRIX shadowMat = XMMATRIX(
        dot, -m_lightPos.x, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -m_lightPos.z, dot, 0.0f,
        0.0f, -1.0f, 0.0f, dot
    );
    XMMATRIX shadowWorld = m_world * shadowMat;

    m_cbShadow.mWorld = XMMatrixTranspose(shadowWorld);
    m_cbShadow.vMeshColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f);
    m_constShadow.update(m_deviceContext, nullptr, 0, nullptr, &m_cbShadow, 0, 0);

    m_userInterface.update();

}



void BaseApp::render()
{
    m_deviceContext.m_deviceContext->RSSetState(
        g_wireframeMode ? m_rasterStateWireframe : m_rasterStateDefault
    );

    // Limpiar con color dinámico de fondo
    m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, g_clearColor);

    // === Preparar render target y estados iniciales ===
    m_renderTargetView.render(m_deviceContext, m_depthStencilView, 1, m_clearColor);
    m_viewport.render(m_deviceContext);
    m_depthStencilView.render(m_deviceContext);
    m_shaderProgram.render(m_deviceContext);

    // === Buffers de cámara ===
    m_neverChanges.render(m_deviceContext, 0, 1);
    m_changeOnResize.render(m_deviceContext, 1, 1);

    // === Render del plano ===
    m_planeVertexBuffer.render(m_deviceContext, 0, 1);
    m_planeIndexBuffer.render(m_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
    m_constPlane.render(m_deviceContext, 2, 1);
    m_constPlane.render(m_deviceContext, 2, 1, true);
    m_deviceContext.PSSetShaderResources(0, 1, &m_textureRV);
    m_deviceContext.PSSetSamplers(0, 1, &m_samplerLinear);
    m_deviceContext.DrawIndexed(static_cast<UINT>(m_planeMesh.m_index.size()), 0, 0);

    // === Render del cubo ===
    m_vertexBuffer.render(m_deviceContext, 0, 1);
    m_indexBuffer.render(m_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
    m_changeEveryFrame.render(m_deviceContext, 2, 1);
    m_changeEveryFrame.render(m_deviceContext, 2, 1, true);
    m_deviceContext.PSSetShaderResources(0, 1, &m_textureRV);
    m_deviceContext.PSSetSamplers(0, 1, &m_samplerLinear);
    m_deviceContext.DrawIndexed(static_cast<UINT>(m_cubeMesh.m_index.size()), 0, 0);

    // === Render de la sombra del cubo ===
    m_shaderShadow.render(m_deviceContext, PIXEL_SHADER);
    m_shadowBlendState.render(m_deviceContext, m_blendFactor, 0xffffffff);
    m_shadowDepthStencilState.render(m_deviceContext, 0);
    m_vertexBuffer.render(m_deviceContext, 0, 1);
    m_indexBuffer.render(m_deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);
    m_constShadow.render(m_deviceContext, 2, 1, true);
    m_deviceContext.DrawIndexed(static_cast<UINT>(m_cubeMesh.m_index.size()), 0, 0);

    // === Restaurar estados ===
    m_shadowBlendState.render(m_deviceContext, m_blendFactor, 0xffffffff, true);
    m_shadowDepthStencilState.render(m_deviceContext, 0, true);

    // === Presentar frame final ===
    m_userInterface.render();
    m_swapChain.present();
}


void BaseApp::destroy()
{
    m_deviceContext.clearState();

    // === Destruir estados ===
    m_shadowBlendState.destroy();
    m_shadowDepthStencilState.destroy();

    // === Destruir shaders ===
    m_shaderShadow.destroy();
    m_shaderProgram.destroy();

    // === Destruir buffers ===
    m_planeVertexBuffer.destroy();
    m_planeIndexBuffer.destroy();
    m_constPlane.destroy();
    m_constShadow.destroy();
    m_neverChanges.destroy();
    m_changeOnResize.destroy();
    m_changeEveryFrame.destroy();
    m_vertexBuffer.destroy();
    m_indexBuffer.destroy();

    // === Liberar texturas y muestreo ===
    if (m_samplerLinear) {
        m_samplerLinear->Release();
        m_samplerLinear = nullptr;
    }
    if (m_textureRV) {
        m_textureRV->Release();
        m_textureRV = nullptr;
    }

    // === Destruir sistema de render ===
    m_depthStencil.destroy();
    m_depthStencilView.destroy();
    m_renderTargetView.destroy();
    m_swapChain.destroy();

    // === Liberar device context y device ===
    if (m_deviceContext.m_deviceContext) {
        m_deviceContext.m_deviceContext->Release();
        m_deviceContext.m_deviceContext = nullptr;
    }

    if (m_device.m_device) {
        m_device.m_device->Release();
        m_device.m_device = nullptr;
    }

    if (m_rasterStateWireframe) {
        m_rasterStateWireframe->Release();
        m_rasterStateWireframe = nullptr;
    }
    if (m_rasterStateDefault) {
        m_rasterStateDefault->Release();
        m_rasterStateDefault = nullptr;
    }

}