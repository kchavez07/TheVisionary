#pragma once
#include "Prerequisites.h"

/**
 * @file RenderTargetView.h
 * @brief Declaraci�n de la clase RenderTargetView.
 *
 * Esta clase encapsula la creaci�n, uso y destrucci�n de una
 * Render Target View (RTV) en DirectX 11. Una RTV permite que una
 * textura act�e como objetivo de renderizado, ya sea el backbuffer
 * o una textura personalizada.
 */

 // Forward declarations para evitar dependencias innecesarias
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/**
 * @class RenderTargetView
 * @brief Vista de renderizado que permite a DirectX dibujar sobre una textura.
 *
 * Esta clase gestiona una ID3D11RenderTargetView, que puede usarse
 * como destino de dibujo en el pipeline gr�fico.
 */
class RenderTargetView {
public:
    /**
     * @brief Constructor por defecto.
     */
    RenderTargetView() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~RenderTargetView() = default;

    /**
     * @brief Inicializa la RTV usando el backbuffer de la swap chain.
     *
     * @param device Dispositivo de Direct3D.
     * @param backBuffer Textura asociada al backbuffer.
     * @param Format Formato de color de la vista.
     * @return HRESULT C�digo de �xito o error.
     */
    HRESULT init(Device& device, Texture& backBuffer, DXGI_FORMAT Format);

    /**
     * @brief Inicializa la RTV a partir de una textura personalizada.
     *
     * @param device Dispositivo de Direct3D.
     * @param inTex Textura fuente.
     * @param ViewDimension Tipo de vista (por ejemplo: 2D, MSAA, array).
     * @param Format Formato de color de la vista.
     * @return HRESULT C�digo de �xito o error.
     */
    HRESULT init(Device& device,
        Texture& inTex,
        D3D11_RTV_DIMENSION ViewDimension,
        DXGI_FORMAT Format);

    /**
     * @brief M�todo de actualizaci�n (actualmente no implementado).
     */
    void update();

    /**
     * @brief Enlaza esta RTV al pipeline gr�fico junto con una vista de profundidad.
     *
     * Tambi�n limpia el color inicial del render target.
     *
     * @param deviceContext Contexto del dispositivo.
     * @param depthStencilView Vista de profundidad/stencil asociada.
     * @param numViews N�mero de vistas de render (usualmente 1).
     * @param ClearColor Color RGBA con el que se limpia la vista.
     */
    void render(DeviceContext& deviceContext,
        DepthStencilView& depthStencilView,
        unsigned int numViews,
        const float ClearColor[4]);

    /**
     * @brief Enlaza solo la RTV al pipeline, sin usar DepthStencil ni limpiar.
     *
     * @param deviceContext Contexto del dispositivo.
     * @param numViews N�mero de vistas de render (usualmente 1).
     */
    void render(DeviceContext& deviceContext,
        unsigned int numViews);

    /**
     * @brief Libera la memoria ocupada por la RTV.
     */
    void destroy();

public:
    /**
     * @brief Puntero al recurso interno de DirectX para render target view.
     */
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
