#include "RenderTargetView.h"
#include "Device.h"
#include "Texture.h"
#include "DeviceContext.h"
#include "DepthStencilView.h"

// =====================================================
// MÉTODO: init (con backBuffer)
// Inicializa un RenderTargetView usando como textura el backbuffer.
// Este método es común cuando se desea renderizar directo a pantalla.
// =====================================================
HRESULT
RenderTargetView::init(Device& device, Texture& backBuffer, DXGI_FORMAT Format) {
    if (!device.m_device) {
        ERROR("RenderTargetView", "init", "Device is nullptr.");
        return E_POINTER;
    }
    if (!backBuffer.m_texture) {
        ERROR("RenderTargetView", "init", "Texture is nullptr.");
        return E_POINTER;
    }
    if (Format == DXGI_FORMAT_UNKNOWN) {
        ERROR("RenderTargetView", "init", "Format is DXGI_FORMAT_UNKNOWN.");
        return E_INVALIDARG;
    }

    // Configura la descripción de la RTV para backbuffer con MSAA
    D3D11_RENDER_TARGET_VIEW_DESC desc;
    memset(&desc, 0, sizeof(desc));
    desc.Format = Format;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS; // MSAA por defecto

    // Crea la RTV desde la textura del backbuffer
    HRESULT hr = device.m_device->CreateRenderTargetView(backBuffer.m_texture,
        &desc,
        &m_renderTargetView);
    if (FAILED(hr)) {
        ERROR("RenderTargetView", "init",
            ("Failed to create render target view. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

// =====================================================
// MÉTODO: init (con cualquier textura y configuración)
// Permite especificar la dimensión de vista (2D, MSAA, Array, etc.)
// Ideal para vistas personalizadas o múltiples objetivos de render.
// =====================================================
HRESULT
RenderTargetView::init(Device& device,
    Texture& inTex,
    D3D11_RTV_DIMENSION ViewDimension,
    DXGI_FORMAT Format) {
    if (!device.m_device) {
        ERROR("RenderTargetView", "init", "Device is nullptr.");
        return E_POINTER;
    }
    if (!inTex.m_texture) {
        ERROR("RenderTargetView", "init", "Texture is nullptr.");
        return E_POINTER;
    }
    if (Format == DXGI_FORMAT_UNKNOWN) {
        ERROR("RenderTargetView", "init", "Format is DXGI_FORMAT_UNKNOWN.");
        return E_INVALIDARG;
    }

    // Configura la descripción de la RTV
    D3D11_RENDER_TARGET_VIEW_DESC desc;
    memset(&desc, 0, sizeof(desc));
    desc.Format = Format;
    desc.ViewDimension = ViewDimension;

    // Crea la RTV desde la textura personalizada
    HRESULT hr = device.m_device->CreateRenderTargetView(inTex.m_texture,
        &desc,
        &m_renderTargetView);
    if (FAILED(hr)) {
        ERROR("RenderTargetView", "init",
            ("Failed to create render target view. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

// =====================================================
// MÉTODO: render (con DepthStencil)
// Este método enlaza esta RTV y también un DepthStencilView
// al pipeline gráfico. Además limpia el color inicial del buffer.
// =====================================================
void
RenderTargetView::render(DeviceContext& deviceContext,
    DepthStencilView& depthStencilView,
    unsigned int numViews,
    const float ClearColor[4]) {
    if (!deviceContext.m_deviceContext) {
        ERROR("RenderTargetView", "render", "DeviceContext is nullptr.");
        return;
    }
    if (!m_renderTargetView) {
        ERROR("RenderTargetView", "render", "RenderTargetView is nullptr.");
        return;
    }

    // Limpia el color del render target con el valor recibido
    deviceContext.m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);

    // Asigna tanto el render target como el depth stencil al pipeline
    deviceContext.m_deviceContext->OMSetRenderTargets(numViews,
        &m_renderTargetView,
        depthStencilView.m_depthStencilView);
}

// =====================================================
// MÉTODO: render (sin DepthStencil)
// Método más simple que solo enlaza la RTV (sin limpiar color ni usar stencil).
// Útil para ciertos efectos gráficos o pasos de postprocesamiento.
// =====================================================
void
RenderTargetView::render(DeviceContext& deviceContext, unsigned int numViews) {
    if (!deviceContext.m_deviceContext) {
        ERROR("RenderTargetView", "render", "DeviceContext is nullptr.");
        return;
    }
    if (!m_renderTargetView) {
        ERROR("RenderTargetView", "render", "RenderTargetView is nullptr.");
        return;
    }

    // Asigna únicamente la RTV al pipeline
    deviceContext.m_deviceContext->OMSetRenderTargets(numViews,
        &m_renderTargetView,
        nullptr);
}

// =====================================================
// MÉTODO: destroy()
// Libera la memoria asociada a la RTV. Siempre usar esto
// al cerrar el programa o cambiar de escena.
// =====================================================
void
RenderTargetView::destroy() {
    SAFE_RELEASE(m_renderTargetView);
}
