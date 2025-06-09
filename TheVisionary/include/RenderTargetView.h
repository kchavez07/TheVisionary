#pragma once
#include "Prerequisites.h"

/// @file RenderTargetView.h
/// @brief Clase encargada de gestionar una Render Target View (RTV) para DirectX 11.
/// 
/// Un Render Target View permite que una textura pueda ser utilizada como objetivo de renderizado,
/// es decir, donde se dibujan los gráficos en pantalla o en memoria.
/// Esta clase encapsula la creación, vinculación y destrucción de una RTV.

/// Forward declarations para evitar dependencias innecesarias
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/// @class RenderTargetView
/// @brief Encapsula una vista de renderizado (RTV) para DirectX 11.
/// 
/// Esta clase se utiliza para representar una textura sobre la cual se puede dibujar.
/// Puede ser una textura del backbuffer o una textura personalizada (off-screen).
class RenderTargetView {
public:
    /// Constructor por defecto
    RenderTargetView() = default;

    /// Destructor por defecto
    ~RenderTargetView() = default;

    /// @brief Crea una RTV desde una textura que representa el backbuffer.
    /// @param device Referencia al objeto Device.
    /// @param backBuffer Textura del backbuffer.
    /// @param Format Formato del recurso (por ejemplo, DXGI_FORMAT_R8G8B8A8_UNORM).
    /// @return HRESULT indicando éxito o error del proceso.
    HRESULT init(Device& device, Texture& backBuffer, DXGI_FORMAT Format);

    /// @brief Crea una RTV desde cualquier textura personalizada.
    /// @param device Referencia al objeto Device.
    /// @param inTex Textura de entrada.
    /// @param ViewDimension Dimensión de la vista (2D, array, etc.).
    /// @param Format Formato del recurso.
    /// @return HRESULT indicando éxito o error del proceso.
    HRESULT init(Device& device,
        Texture& inTex,
        D3D11_RTV_DIMENSION ViewDimension,
        DXGI_FORMAT Format);

    /// @brief Método placeholder para actualizaciones de estado de la RTV.
    void update();

    /// @brief Enlaza esta RTV y un DepthStencilView al pipeline, y limpia la vista.
    /// @param deviceContext Contexto del dispositivo.
    /// @param depthStencilView Referencia a una vista de stencil/profundidad.
    /// @param numViews Número de vistas de renderizado (normalmente 1).
    /// @param ClearColor Color RGBA con el que se limpia la RTV.
    void render(DeviceContext& deviceContext,
        DepthStencilView& depthStencilView,
        unsigned int numViews,
        const float ClearColor[4]);

    /// @brief Enlaza la RTV sin usar DepthStencil ni limpiar.
    /// @param deviceContext Contexto del dispositivo.
    /// @param numViews Número de vistas de renderizado (normalmente 1).
    void render(DeviceContext& deviceContext,
        unsigned int numViews);

    /// @brief Libera los recursos asociados a la RTV.
    void destroy();

public:
    /// @brief Puntero interno al recurso RenderTargetView de DirectX.
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
