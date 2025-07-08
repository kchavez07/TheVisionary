/**
 * @file DeviceContext.cpp
 * @brief Implementación de la clase DeviceContext.
 */

#include "DeviceContext.h"

void DeviceContext::init() {
    // (En este caso no se necesita inicialización adicional)
}

void DeviceContext::update() {
    // Lógica por frame (si aplica en el futuro)
}

void DeviceContext::render() {
    // Comandos de render por frame (si aplica en el futuro)
}

void DeviceContext::destroy() {
    clearState();
    release();
}

void DeviceContext::clearState() {
    if (m_deviceContext) {
        m_deviceContext->ClearState();
    }
}

void DeviceContext::release() {
    if (m_deviceContext) {
        m_deviceContext->Release();
        m_deviceContext = nullptr;
    }
}

void DeviceContext::RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports) {
    if (NumViewports > 0 && pViewports != nullptr && m_deviceContext) {
        m_deviceContext->RSSetViewports(NumViewports, pViewports);
    }
    else {
        ERROR("DeviceContext", "RSSetViewports", "Viewport inválido o sin contexto.");
    }
}

void DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
    unsigned int ClearFlags,
    float Depth,
    UINT8 Stencil) {
    if (!m_deviceContext || !pDepthStencilView) {
        ERROR("DeviceContext", "ClearDepthStencilView", "Contexto o depth view nulo.");
        return;
    }
    m_deviceContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
    const float ColorRGBA[4]) {
    if (!m_deviceContext || !pRenderTargetView) {
        ERROR("DeviceContext", "ClearRenderTargetView", "Contexto o render target nulo.");
        return;
    }
    m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void DeviceContext::OMSetRenderTargets(unsigned int NumViews,
    ID3D11RenderTargetView* const* ppRenderTargetViews,
    ID3D11DepthStencilView* pDepthStencilView) {
    if (m_deviceContext) {
        m_deviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
    }
}

void DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology) {
    if (m_deviceContext) {
        m_deviceContext->IASetPrimitiveTopology(topology);
    }
}

void DeviceContext::PSSetShaderResources(UINT startSlot,
    UINT numViews,
    ID3D11ShaderResourceView* const* ppSRVs) {
    if (m_deviceContext) {
        m_deviceContext->PSSetShaderResources(startSlot, numViews, ppSRVs);
    }
}

void DeviceContext::PSSetSamplers(UINT startSlot,
    UINT numSamplers,
    ID3D11SamplerState* const* ppSamplers) {
    if (m_deviceContext) {
        m_deviceContext->PSSetSamplers(startSlot, numSamplers, ppSamplers);
    }
}

void DeviceContext::DrawIndexed(UINT indexCount,
    UINT startIndexLocation,
    INT baseVertexLocation) {
    if (m_deviceContext) {
        m_deviceContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
    }
}
