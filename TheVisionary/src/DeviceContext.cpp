#include "DeviceContext.h"

// ===============================================
// MÉTODO: RSSetViewports
// Configura el área de la pantalla donde se renderiza la escena.
// Este método es crucial para que DirectX sepa en qué parte del viewport dibujar.
// ===============================================
void
DeviceContext::RSSetViewports(unsigned int NumViewports,
	const D3D11_VIEWPORT* pViewports) {
	if (NumViewports > 0 && pViewports != nullptr) {
		// Aplica el viewport al contexto
		m_deviceContext->RSSetViewports(NumViewports, pViewports);
	}
	else {
		// Reporta error si los parámetros son inválidos
		ERROR("DeviceContext", "RSSetViewports", "pViewports is nullptr or NumViewports is 0");
	}
}

// ===============================================
// MÉTODO: ClearDepthStencilView
// Limpia el buffer de profundidad y/o stencil antes de renderizar un nuevo frame.
// Esto asegura que la escena no tenga residuos del frame anterior.
// ===============================================
void
DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
	unsigned int ClearFlags,
	float Depth,
	UINT8 Stencil) {
	if (!m_deviceContext || !pDepthStencilView) {
		ERROR("DeviceContext", "ClearDepthStencilView", "Device context or depth stencil view is null.");
		return;
	}
	m_deviceContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

// ===============================================
// MÉTODO: ClearRenderTargetView
// Limpia el render target (usualmente el backbuffer) con un color definido.
// Se suele usar al inicio del ciclo de renderizado de cada frame.
// ===============================================
void
DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
	const float ColorRGBA[4]) {
	if (!m_deviceContext || !pRenderTargetView) {
		ERROR("DeviceContext", "ClearRenderTargetView", "Device context or render target view is null.");
		return;
	}
	m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}
