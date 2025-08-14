/**
 * @file DepthStencilView.cpp
 * @brief Creación y enlace de Depth Stencil Views (DSV) al pipeline.
 */

#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

HRESULT
DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format) {
    if (!device.m_device) {
        ERROR("DepthStencilView", "init", "Device is null.");
        return E_POINTER;
    }
    if (!depthStencil.m_texture) {
        ERROR("DepthStencilView", "init", "Texture is null.");
        return E_POINTER;
    }

    // Lee el desc de la textura para decidir formato y dimensión
    D3D11_TEXTURE2D_DESC texDesc{};
    depthStencil.m_texture->GetDesc(&texDesc);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
    dsvDesc.Format = (format == DXGI_FORMAT_UNKNOWN) ? texDesc.Format : format;

    if (texDesc.SampleDesc.Count > 1) {
        // MSAA -> usar TEXTURE2DMS
        dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
    }
    else {
        dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        dsvDesc.Texture2D.MipSlice = 0;
    }

    HRESULT hr = device.m_device->CreateDepthStencilView(
        depthStencil.m_texture,
        &dsvDesc,
        &m_depthStencilView
    );

    if (FAILED(hr)) {
        ERROR("DepthStencilView", "init",
            ("Failed to create depth stencil view. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

void
DepthStencilView::render(DeviceContext& deviceContext) {
    if (!deviceContext.m_deviceContext) {
        ERROR("DepthStencilView", "render", "Device context is null.");
        return;
    }
    if (!m_depthStencilView) {
        ERROR("DepthStencilView", "render", "DepthStencilView is null.");
        return;
    }

    // Limpia profundidad y stencil
    deviceContext.m_deviceContext->ClearDepthStencilView(
        m_depthStencilView,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
        1.0f,
        0
    );
}

void
DepthStencilView::destroy() {
    SAFE_RELEASE(m_depthStencilView);
}
