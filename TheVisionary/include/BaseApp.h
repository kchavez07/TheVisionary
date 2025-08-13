#pragma once
#include "Prerequisites.h"

#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "MeshComponent.h"
#include "ModelLoader.h"
#include "UserInterface.h"
#include "ECS/Actor.h"

#include <vector>

/**
 * Base de la app: crea dispositivo, swapchain, RTV/DSV, viewport, shaders,
 * buffers de cámara y carga un plano + el modelo Ninja (FBX).
 * Requiere que el Working Directory sea $(ProjectDir)\bin.
 */
class BaseApp {
public:
    BaseApp() = default;
    ~BaseApp() = default;

    HRESULT init();
    void    update();
    void    render();
    void    destroy();

    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    // --- Core DX11 ---
    Window          m_window;
    Device          m_device;
    DeviceContext   m_deviceContext;
    SwapChain       m_swapChain;

    // BackBuffer + RTV
    Texture         m_backBuffer;
    RenderTargetView m_renderTargetView;

    // Depth/Stencil
    Texture          m_depthStencil;
    DepthStencilView m_depthStencilView;

    // Viewport y Shaders
    Viewport       m_viewport;
    ShaderProgram  m_shaderProgram;

    // CBuffers de cámara
    Buffer         m_neverChanges;      // slot b0
    Buffer         m_changeOnResize;    // slot b1
    CBNeverChanges cbNeverChanges{};
    CBChangeOnResize cbChangesOnResize{};

    // Matrices de cámara
    XMMATRIX       m_View;
    XMMATRIX       m_Projection;

    // Color de limpieza
    float          ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };

    // Luz simple (si tu .fx la usa)
    XMFLOAT4       m_LightPos{ 2.0f, 4.0f, -2.0f, 1.0f };

    // Recursos de utilería
    ModelLoader    m_modelLoader;

    // Plano de referencia
    MeshComponent  planeMesh;
    Texture        m_PlaneTexture;
    EU::TSharedPointer<Actor> m_APlane;

    // Interfaz e inventario de actores (incluye Ninja)
    UserInterface  m_userInterface;
    std::vector<EU::TSharedPointer<Actor>> m_actors;

    // Parámetros opcionales de cámara orbital (si los usas en update())
    float   m_camYawDeg = 0.0f;
    float   m_camPitchDeg = 15.0f;
    float   m_camDistance = 10.0f;
    XMFLOAT3 m_camTarget = XMFLOAT3(0.0f, -5.0f, 0.0f);
};
