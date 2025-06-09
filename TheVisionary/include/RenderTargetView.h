#pragma once
#include "Prerequisites.h"

// =====================================================
// RenderTargetView.h
// Clase encargada de gestionar una Render Target View,
// que es una interfaz que nos permite dibujar sobre
// texturas o buffers de pantalla en DirectX 11.
//
// Un Render Target View (RTV) se enlaza al pipeline
// gr�fico para ser el destino de la renderizaci�n.
// =====================================================

// Forward Declarations para evitar includes innecesarios
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

class RenderTargetView {
public:
    RenderTargetView() = default;
    ~RenderTargetView() = default;

    // =====================================================
    // M�TODO: init (desde textura de backbuffer)
    // Crea una RTV usando una textura ya existente (por ejemplo, el backbuffer).
    // Format define el tipo de datos (formato de color) de la vista.
    // =====================================================
    HRESULT init(Device& device, Texture& backBuffer, DXGI_FORMAT Format);

    // =====================================================
    // M�TODO: init (desde textura cualquiera)
    // Permite especificar una dimensi�n de vista (2D, array, etc.).
    // �til para configuraciones m�s complejas que solo el backbuffer.
    // =====================================================
    HRESULT init(Device& device,
        Texture& inTex,
        D3D11_RTV_DIMENSION ViewDimension,
        DXGI_FORMAT Format);

    // =====================================================
    // M�TODO: update
    // Usualmente llamado por frame si se requiere actualizar el recurso.
    // (Vac�o por ahora, pero definido por convenci�n del motor).
    // =====================================================
    void update();

    // =====================================================
    // M�TODO: render (con DepthStencil)
    // Enlaza esta RTV y un DepthStencilView al pipeline de render.
    // Limpia la vista con un color antes de dibujar (ClearColor).
    // =====================================================
    void render(DeviceContext& deviceContext,
        DepthStencilView& depthStencilView,
        unsigned int numViews,
        const float ClearColor[4]);

    // =====================================================
    // M�TODO: render (solo RTV)
    // Enlaza esta RTV al pipeline sin limpiar ni usar DepthStencil.
    // =====================================================
    void render(DeviceContext& deviceContext,
        unsigned int numViews);

    // =====================================================
    // M�TODO: destroy
    // Libera la memoria del recurso interno (m_renderTargetView).
    // Siempre que se use COM en DirectX es buena pr�ctica liberar recursos.
    // =====================================================
    void destroy();

private:
    // Puntero a la vista de renderizado creada con DirectX 11
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
