/**
 * @file BaseApp.h
 * @brief Clase principal de la aplicación.
 */

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
  * @class BaseApp
  * @brief Inicializa y gestiona el núcleo de DirectX 11, la escena y la interfaz.
  *
  * Crea dispositivo, swapchain, RTV/DSV, viewport, shaders, buffers de cámara
  * y carga recursos iniciales como un plano y el modelo Ninja.
  */
class BaseApp {
public:
    /** Constructor por defecto. */
    BaseApp() = default;
    /** Destructor por defecto. */
    ~BaseApp() = default;

    /** Inicializa el motor y sus recursos. */
    HRESULT init();
    /** Actualiza la lógica por cuadro. */
    void update();
    /** Renderiza la escena. */
    void render();
    /** Libera los recursos. */
    void destroy();

    /**
     * @brief Ejecuta el ciclo principal de la aplicación.
     * @param hInstance Instancia de la aplicación.
     * @param hPrevInstance Instancia previa (no usada).
     * @param lpCmdLine Argumentos de línea de comandos.
     * @param nCmdShow Estado inicial de la ventana.
     * @param wndproc Procedimiento de ventana.
     * @return Código de salida.
     */
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    // --- Core DX11 ---
    Window          m_window;            ///< Ventana principal.
    Device          m_device;            ///< Dispositivo DirectX 11.
    DeviceContext   m_deviceContext;     ///< Contexto de dispositivo.
    SwapChain       m_swapChain;         ///< Intercambio de buffers.

    // BackBuffer + RTV
    Texture         m_backBuffer;        ///< Textura de back buffer.
    RenderTargetView m_renderTargetView; ///< Vista de renderizado.

    // Depth/Stencil
    Texture          m_depthStencil;     ///< Textura de profundidad/stencil.
    DepthStencilView m_depthStencilView; ///< Vista de profundidad/stencil.

    // Viewport y Shaders
    Viewport       m_viewport;           ///< Viewport principal.
    ShaderProgram  m_shaderProgram;      ///< Programa de shaders.

    // CBuffers de cámara
    Buffer         m_neverChanges;       ///< Buffer constante slot b0.
    Buffer         m_changeOnResize;     ///< Buffer constante slot b1.
    CBNeverChanges cbNeverChanges{};     ///< Datos que casi no cambian.
    CBChangeOnResize cbChangesOnResize{};///< Datos que cambian al redimensionar.

    // Matrices de cámara
    XMMATRIX       m_View;               ///< Matriz de vista.
    XMMATRIX       m_Projection;         ///< Matriz de proyección.

    // Color de limpieza
    float          ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };

    // Luz simple
    XMFLOAT4       m_LightPos{ 2.0f, 4.0f, -2.0f, 1.0f };

    // Recursos
    ModelLoader    m_modelLoader;        ///< Cargador de modelos.

    // Plano de referencia
    MeshComponent  planeMesh;            ///< Malla del plano.
    Texture        m_PlaneTexture;       ///< Textura del plano.
    EU::TSharedPointer<Actor> m_APlane;  ///< Actor del plano.

    // Interfaz y actores
    UserInterface  m_userInterface;      ///< Interfaz de usuario.
    std::vector<EU::TSharedPointer<Actor>> m_actors; ///< Lista de actores.

    // Parámetros opcionales de cámara orbital
    float   m_camYawDeg = 0.0f;
    float   m_camPitchDeg = 15.0f;
    float   m_camDistance = 10.0f;
    XMFLOAT3 m_camTarget = XMFLOAT3(0.0f, -5.0f, 0.0f);
};
