#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "Buffer.h"
#include "MeshComponent.h"

/**
 * @file BaseApp.h
 * @class BaseApp
 * @brief Clase base para una aplicaci�n de motor gr�fico con DirectX.
 *
 * Esta clase define el ciclo de vida de la aplicaci�n:
 * inicializaci�n, actualizaci�n, renderizado y destrucci�n.
 * Tambi�n gestiona la ventana principal y ejecuta el bucle principal del programa.
 */
class BaseApp {
public:
    BaseApp() = default;
    ~BaseApp() = default;

    HRESULT init();
    void update();
    void render();
    void destroy();

    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    // === Subsistemas principales ===
    Window m_window;
    Device m_device;
    SwapChain m_swapChain;
    DeviceContext m_deviceContext;
    Texture m_backBuffer;
    RenderTargetView m_renderTargetView;
    Texture m_depthStencil;
    DepthStencilView m_depthStencilView;
    Viewport m_viewport;

    // === Shaders y estados ===
    ShaderProgram m_shaderProgram;
    ShaderProgram m_shaderShadow;
    BlendState m_shadowBlendState;
    DepthStencilState m_shadowDepthStencilState;

    // === Buffers ===
    Buffer m_neverChanges;
    Buffer m_changeOnResize;
    Buffer m_vertexBuffer;
    Buffer m_indexBuffer;
    Buffer m_changeEveryFrame;
    Buffer m_constShadow;
    Buffer m_planeVertexBuffer;
    Buffer m_planeIndexBuffer;
    Buffer m_constPlane;

    // === Geometr�a ===
    MeshComponent m_cubeMesh;
    MeshComponent m_planeMesh;

    // === Texturas y muestreo ===
    ID3D11ShaderResourceView* m_textureRV = nullptr;
    ID3D11SamplerState* m_samplerLinear = nullptr;

    // === Transformaciones y c�mara ===
    XMMATRIX m_world;
    XMMATRIX m_planeWorld;
    XMMATRIX m_view;
    XMMATRIX m_projection;

    // === Constantes y configuraci�n visual ===
    XMFLOAT4 m_meshColor = { 0.7f, 0.7f, 0.7f, 1.0f };
    XMFLOAT4 m_lightPos = { 2.0f, 4.0f, -2.0f, 1.0f };
    UINT m_planeIndexCount = 0;
    float m_clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    float m_blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };

    // === Const Buffers de aplicaci�n ===
    CBNeverChanges m_cbNeverChanges;
    CBChangeOnResize m_cbChangesOnResize;
    CBChangesEveryFrame m_cb;
    CBChangesEveryFrame m_cbPlane;
    CBChangesEveryFrame m_cbShadow;
};
