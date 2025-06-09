#pragma once
#include "Prerequisites.h"

/// @file Viewport.h
/// @brief Define el �rea de renderizado (viewport) en DirectX 11.
///
/// El viewport indica en qu� parte del render target (pantalla, textura)
/// se debe dibujar. Es esencial para ajustar resoluci�n, splitscreen, editores, etc.

/// Forward declarations para evitar dependencias circulares innecesarias.
class Window;
class DeviceContext;

/// @class Viewport
/// @brief Representa un viewport de Direct3D 11, que delimita el �rea visible de dibujo.
class Viewport {
public:
	/// Constructor por defecto
	Viewport() = default;

	/// Destructor por defecto
	~Viewport() = default;

	/// @brief Inicializa el viewport usando las dimensiones de una ventana.
	/// @param window Referencia a una instancia de Window.
	/// @return HRESULT indicando si la operaci�n fue exitosa (S_OK).
	HRESULT init(const Window& window);

	/// @brief Inicializa el viewport con dimensiones espec�ficas.
	/// @param width Ancho del viewport.
	/// @param height Alto del viewport.
	/// @return HRESULT indicando si la operaci�n fue exitosa (S_OK).
	HRESULT init(unsigned int width, unsigned int height);

	/// @brief M�todo de actualizaci�n (por ahora sin uso).
	void update();

	/// @brief Establece este viewport como activo en el pipeline gr�fico.
	/// @param deviceContext Contexto de dispositivo en el que se aplicar� el viewport.
	void render(DeviceContext& deviceContext);

	/// @brief Libera recursos asociados al viewport (actualmente no necesario).
	void destroy();

public:
	/// @brief Estructura de viewport de Direct3D 11.
	/// Contiene informaci�n de tama�o, profundidad y posici�n del �rea visible.
	D3D11_VIEWPORT m_viewport;
};
