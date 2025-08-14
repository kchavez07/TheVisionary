/**
 * @file SwapChain.h
 * @brief Encapsula la creación y gestión del swap chain.
 */

#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class Window;
class Texture;

/**
 * @class SwapChain
 * @brief Maneja el intercambio de buffers (front/back) y la configuración de MSAA.
 */
class SwapChain {
public:
    /** Constructor por defecto. */
    SwapChain() = default;
    /** Destructor por defecto. */
    ~SwapChain() = default;

    /**
     * @brief Inicializa el swap chain.
     * @param device Dispositivo Direct3D 11.
     * @param deviceContext Contexto de dispositivo.
     * @param backBuffer Textura de back buffer.
     * @param window Ventana asociada.
     * @return HRESULT indicando el resultado.
     */
    HRESULT init(Device& device,
        DeviceContext& deviceContext,
        Texture& backBuffer,
        Window window);

    /** Actualiza el estado del swap chain. */
    void update();

    /** Renderiza el contenido del swap chain. */
    void render();

    /** Libera los recursos del swap chain. */
    void destroy();

    /** Presenta el back buffer en pantalla. */
    void present();

public:
    IDXGISwapChain* m_swapChain = nullptr; ///< Puntero al swap chain.
    D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL; ///< Tipo de driver utilizado.

private:
    D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0; ///< Nivel de características de D3D.

    unsigned int m_sampleCount;   ///< Número de muestras para MSAA.
    unsigned int m_qualityLevels; ///< Niveles de calidad para MSAA.

    // Punteros a interfaces DXGI
    IDXGIDevice* m_dxgiDevice = nullptr; ///< Dispositivo DXGI.
    IDXGIAdapter* m_dxgiAdapter = nullptr; ///< Adaptador DXGI.
    IDXGIFactory* m_dxgiFactory = nullptr; ///< Fábrica DXGI.
};
