#include "Viewport.h"
#include "Window.h"
#include "DeviceContext.h"

// ========================================================
// MÉTODO: init(const Window& window)
// Inicializa el viewport usando las dimensiones actuales de la ventana.
// Esto es útil cuando queremos que el dibujo ocurra en toda el área visible.
// ========================================================
HRESULT
Viewport::init(const Window& window) {
	// Validamos si la ventana fue creada correctamente
	if (!window.m_hWnd) {
		ERROR("Viewport", "init", "Window handle (m_hWnd) is nullptr");
		return E_POINTER;
	}
	if (window.m_width == 0 || window.m_height == 0) {
		ERROR("Viewport", "init", "Window dimensions are zero.");
		return E_INVALIDARG;
	}

	// Asignamos los valores del viewport según el tamaño de la ventana
	m_viewport.Width = static_cast<float>(window.m_width);
	m_viewport.Height = static_cast<float>(window.m_height);
	m_viewport.MinDepth = 0.0f;  // Z-buffer mínimo
	m_viewport.MaxDepth = 1.0f;  // Z-buffer máximo
	m_viewport.TopLeftX = 0;     // Comienza desde la esquina superior izquierda
	m_viewport.TopLeftY = 0;

	return S_OK;
}

// ========================================================
// MÉTODO: init(unsigned int width, unsigned int height)
// Variante del método de inicialización que recibe tamaño directamente,
// útil para viewports personalizados (ej: mini-mapas, cámaras secundarias, etc.)
// ========================================================
HRESULT
Viewport::init(unsigned int width, unsigned int height) {
	if (width == 0 || height == 0) {
		ERROR("Viewport", "init", "Window dimensions are zero.");
		return E_INVALIDARG;
	}

	m_viewport.Width = static_cast<float>(width);
	m_viewport.Height = static_cast<float>(height);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;

	return S_OK;
}

// ========================================================
// MÉTODO: render(DeviceContext& deviceContext)
// Este método activa el viewport en el pipeline gráfico, es decir,
// le indica a DirectX en qué región de la pantalla debe dibujar.
// ========================================================
void
Viewport::render(DeviceContext& deviceContext) {
	// Validamos que exista un contexto válido
	if (!deviceContext.m_deviceContext) {
		ERROR("Viewport", "render", "Device context is not set.");
		return;
	}

	// Activamos este viewport (solo uno en este caso)
	deviceContext.RSSetViewports(1, &m_viewport);
}
