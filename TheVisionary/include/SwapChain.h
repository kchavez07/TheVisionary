#pragma once
#include "Prerequisites.h"

// Forward declarations para evitar incluir headers innecesarios
class Device;
class DeviceContext;
class Window;
class Texture;

// ============================================================================
// Clase SwapChain
// Encargada de manejar el mecanismo de presentación de imágenes en pantalla.
// Una "swap chain" (cadena de intercambio) permite tener múltiples buffers
// para dibujar en uno mientras otro se muestra, evitando parpadeos.
// Esta clase también configura MSAA (antialiasing) y se conecta al backbuffer.
// ============================================================================
class SwapChain {
public:
    // Constructor y destructor por defecto
    SwapChain() = default;
    ~SwapChain() = default;

    // ==========================================================
    // MÉTODO: init()
    // Inicializa la swap chain junto con el dispositivo y el backbuffer.
    // Configura MSAA y obtiene acceso a interfaces de DXGI.
    // ==========================================================
    HRESULT init(Device& device,
        DeviceContext& deviceContext,
        Texture& backBuffer,
        Window window);

    // Placeholder para actualizaciones futuras
    void update();

    // Placeholder para lógica de render interna si es necesaria
    void render();

    // Libera todos los recursos asociados a la swap chain y sus interfaces DXGI
    void destroy();

    // ==========================================================
    // MÉTODO: present()
    // Presenta el buffer actual en pantalla (swap front <-> back).
    // Es el paso final del render loop.
    // ==========================================================
    void present();

public:
    // ==========================================================
    // Puntero a la swap chain de DXGI
    // Esta cadena permite manejar los buffers de presentación.
    // ==========================================================
    IDXGISwapChain* m_swapChain = nullptr;

    // Tipo de driver utilizado (hardware, WARP o referencia)
    D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
    // ==========================================================
    // Nivel de características de DirectX soportado por el hardware
    // ==========================================================
    D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

    // ==========================================================
    // Configuración de anti-aliasing (MSAA)
    //
    // sampleCount: número de muestras por píxel (típicamente 4 para 4xMSAA)
    // qualityLevels: calidad permitida por el hardware para ese número de muestras
    //
    // El MSAA ayuda a suavizar los bordes en objetos 3D.
    // ==========================================================
    unsigned int m_sampleCount;
    unsigned int m_qualityLevels;

    // ==========================================================
    // Interfaces internas de DXGI
    // Estas se obtienen a partir del dispositivo para crear la swap chain
    // ==========================================================
    IDXGIDevice* m_dxgiDevice = nullptr;
    IDXGIAdapter* m_dxgiAdapter = nullptr;
    IDXGIFactory* m_dxgiFactory = nullptr;
};
