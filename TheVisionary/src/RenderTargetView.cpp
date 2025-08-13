#include "RenderTargetView.h"
#include "Device.h"
#include "Texture.h"
#include "DeviceContext.h"
#include "DepthStencilView.h"

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

    // Lee el desc del back-buffer para decidir 2D vs 2DMS y el formato real
    D3D11_TEXTURE2D_DESC texDesc{};
    backBuffer.m_texture->GetDesc(&texDesc);

    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
    // Si te pasan UNKNOWN, infiere del recurso
    rtvDesc.Format = (Format == DXGI_FORMAT_UNKNOWN) ? texDesc.Format : Format;

    // **FIX**: si el backbuffer tiene MSAA, usar TEXTURE2DMS
    if (texDesc.SampleDesc.Count > 1) {
        rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
    }
    else {
        rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        rtvDesc.Texture2D.MipSlice = 0;
    }

    // Crear RTV
    HRESULT hr = device.m_device->CreateRenderTargetView(backBuffer.m_texture, &rtvDesc, &m_renderTargetView);
    if (FAILED(hr)) {
        // Plan B: deja que D3D infiera todo (suele funcionar con el back-buffer)
        hr = device.m_device->CreateRenderTargetView(backBuffer.m_texture, nullptr, &m_renderTargetView);
        if (FAILED(hr)) {
            ERROR("RenderTargetView", "init",
                ("Failed to create RTV. HRESULT: " + std::to_string(hr)).c_str());
            return hr;
        }
    }

    return S_OK;
}

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

    // Si te pasan UNKNOWN aquí, infiere del recurso
    D3D11_TEXTURE2D_DESC texDesc{};
    inTex.m_texture->GetDesc(&texDesc);

    D3D11_RENDER_TARGET_VIEW_DESC desc{};
    desc.Format = (Format == DXGI_FORMAT_UNKNOWN) ? texDesc.Format : Format;
    desc.ViewDimension = ViewDimension;

    if (desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE2D) {
        desc.Texture2D.MipSlice = 0;
    }
    else if (desc.ViewDimension == D3D11_RTV_DIMENSION_TEXTURE2DARRAY) {
        desc.Texture2DArray.MipSlice = 0;
        desc.Texture2DArray.FirstArraySlice = 0;
        desc.Texture2DArray.ArraySize = 1;
    } // agrega otros casos si los usas

    HRESULT hr = device.m_device->CreateRenderTargetView(inTex.m_texture, &desc, &m_renderTargetView);
    if (FAILED(hr)) {
        ERROR("RenderTargetView", "init",
            ("Failed to create RTV. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }
    return S_OK;
}

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

    ID3D11RenderTargetView* rtv = m_renderTargetView;
    ID3D11DepthStencilView* dsv = depthStencilView.m_depthStencilView;

    // Liga RTV/DSV y limpia
    deviceContext.m_deviceContext->OMSetRenderTargets(numViews, &rtv, dsv);
    deviceContext.m_deviceContext->ClearRenderTargetView(rtv, ClearColor);
    if (dsv) {
        deviceContext.m_deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }
}

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
    ID3D11RenderTargetView* rtv = m_renderTargetView;
    deviceContext.m_deviceContext->OMSetRenderTargets(numViews, &rtv, nullptr);
}

void
RenderTargetView::destroy() {
    SAFE_RELEASE(m_renderTargetView);
}
