#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/**
 * @class RenderTargetView
 * @brief Encapsula la creación, gestión y uso de vistas de renderizado (RTV) en Direct3D 11.
 *
 * @details
 * Un Render Target View (RTV) es la interfaz que permite a Direct3D escribir
 * en una textura como destino de renderizado. Esta clase administra la inicialización,
 * limpieza y enlace de dicha vista al pipeline gráfico.
 *
 * @note Parte del motor gráfico The Visionary.
 */
class RenderTargetView {
public:
    RenderTargetView() = default;  ///< Constructor por defecto.
    ~RenderTargetView() = default; ///< Destructor por defecto.

    /**
     * @brief Inicializa la vista de render a partir del back buffer.
     * @param device Referencia al dispositivo Direct3D.
     * @param backBuffer Textura que actúa como back buffer.
     * @param Format Formato de píxel a utilizar.
     * @return HRESULT con el estado de la operación.
     */
    HRESULT init(Device& device, Texture& backBuffer, DXGI_FORMAT Format);

    /**
     * @brief Inicializa la vista de render para una textura específica.
     * @param device Referencia al dispositivo Direct3D.
     * @param inTex Textura de entrada.
     * @param ViewDimension Dimensión de la vista RTV.
     * @param Format Formato de píxel a utilizar.
     * @return HRESULT con el estado de la operación.
     */
    HRESULT init(Device& device,
        Texture& inTex,
        D3D11_RTV_DIMENSION ViewDimension,
        DXGI_FORMAT Format);

    /**
     * @brief Actualiza el estado del Render Target View.
     */
    void update();

    /**
     * @brief Renderiza limpiando y estableciendo el RTV junto al Depth Stencil.
     * @param deviceContext Contexto del dispositivo.
     * @param depthStencilView Vista de profundidad asociada.
     * @param numViews Número de vistas a enlazar.
     * @param ClearColor Color con el que se limpiará el RTV.
     */
    void render(DeviceContext& deviceContext,
        DepthStencilView& depthStencilView,
        unsigned int numViews,
        const float ClearColor[4]);

    /**
     * @brief Renderiza estableciendo únicamente el RTV sin limpieza de color.
     * @param deviceContext Contexto del dispositivo.
     * @param numViews Número de vistas a enlazar.
     */
    void render(DeviceContext& deviceContext,
        unsigned int numViews);

    /**
     * @brief Libera los recursos asociados al Render Target View.
     */
    void destroy();

private:
    ID3D11RenderTargetView* m_renderTargetView = nullptr; ///< Puntero a la vista de render D3D11.
};
