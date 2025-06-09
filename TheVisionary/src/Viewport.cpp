#include "Viewport.h"
#include "Window.h"
#include "DeviceContext.h"

// ========================================================
// M�TODO: init(const Window& window)
// Inicializa el viewport usando las dimensiones actuales de la ventana.
// Esto es �til cuando queremos que el dibujo ocurra en toda el �rea visible.
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

	// Asignamos los valores del viewport seg�n el tama�o de la ventana
	m_viewport.Width = static_cast<float>(window.m_width);
	m_viewport.Height = static_cast<float>(window.m_height);
	m_viewport.MinDepth = 0.0f;  // Z-buffer m�nimo
	m_viewport.MaxDepth = 1.0f;  // Z-buffer m�ximo
	m_viewport.TopLeftX = 0;     // Comienza desde la esquina superior izquierda
	m_viewport.TopLeftY = 0;

	return S_OK;
}

// ========================================================
// M�TODO: init(unsigned int width, unsigned int height)
// Variante del m�todo de inicializaci�n que recibe tama�o directamente,
// �til para viewports personalizados (ej: mini-mapas, c�maras secundarias, etc.)
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
// M�TODO: render(DeviceContext& deviceContext)
// Este m�todo activa el viewport en el pipeline gr�fico, es decir,
// le indica a DirectX en qu� regi�n de la pantalla debe dibujar.
// ========================================================
void
Viewport::render(DeviceContext& deviceContext) {
	// Validamos que exista un contexto v�lido
	if (!deviceContext.m_deviceContext) {
		ERROR("Viewport", "render", "Device context is not set.");
		return;
	}

	// Activamos este viewport (solo uno en este caso)
	deviceContext.RSSetViewports(1, &m_viewport);
}
