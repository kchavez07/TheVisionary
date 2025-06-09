#pragma once
#include "Prerequisites.h"

// Forward declarations para evitar dependencias circulares o inclusiones innecesarias
class Device;
class DeviceContext;
class Window;
class Texture;

/**
 * @class SwapChain
 * @brief Maneja la presentaci�n de im�genes en pantalla mediante buffers intercambiables.
 *
 * La clase SwapChain representa la cadena de intercambio (backbuffer y frontbuffer),
 * utilizada para renderizar en un buffer mientras se muestra el otro. Tambi�n configura
 * caracter�sticas como MSAA (antialiasing) y obtiene interfaces internas de DXGI.
 */
class SwapChain {
public:
     /**
      * @brief Constructor por defecto.
      */
    SwapChain() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~SwapChain() = default;

    /**
     * @brief Inicializa la swap chain y sus interfaces relacionadas.
     *
     * @param device Referencia al dispositivo de Direct3D.
     * @param deviceContext Contexto del dispositivo.
     * @param backBuffer Textura que actuar� como backbuffer.
     * @param window Ventana donde se mostrar� el contenido.
     * @return HRESULT C�digo de �xito o error.
     */
    HRESULT init(Device& device,
        DeviceContext& deviceContext,
        Texture& backBuffer,
        Window window);

    /**
     * @brief M�todo de actualizaci�n. Placeholder para l�gica futura.
     */
    void update();

    /**
     * @brief M�todo de render. Placeholder para l�gica futura.
     */
    void render();

    /**
     * @brief Libera todos los recursos e interfaces de DXGI utilizados.
     */
    void destroy();

    /**
     * @brief Presenta el contenido renderizado en pantalla (swap buffers).
     */
    void present();

    /** =======================
     *  ATRIBUTOS P�BLICOS
     *  ======================= */

     /**
      * @brief Puntero principal a la cadena de intercambio de DXGI.
      *
      * Utilizado para presentar el contenido en la ventana.
      */
    IDXGISwapChain* m_swapChain = nullptr;

    /**
     * @brief Tipo de driver seleccionado para el dispositivo (hardware, WARP, referencia).
     */
    D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
     /**
      * @brief Nivel de caracter�sticas de DirectX soportado por el dispositivo.
      */
    D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

    /**
     * @brief N�mero de muestras para MSAA (antialiasing).
     *
     * Mejora visual al suavizar bordes en objetos renderizados.
     */
    unsigned int m_sampleCount;

    /**
     * @brief N�mero de niveles de calidad disponibles para MSAA seg�n el hardware.
     */
    unsigned int m_qualityLevels;

    /**
     * @brief Interfaces internas de DXGI necesarias para crear la swap chain.
     *
     * Se obtienen a trav�s del dispositivo.
     */
    IDXGIDevice* m_dxgiDevice = nullptr;
    IDXGIAdapter* m_dxgiAdapter = nullptr;
    IDXGIFactory* m_dxgiFactory = nullptr;
};
