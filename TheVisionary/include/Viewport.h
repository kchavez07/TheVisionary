#pragma once
#include "Prerequisites.h"

/// @file Viewport.h
/// @brief Define el área de renderizado (viewport) en DirectX 11.
///
/// El viewport indica en qué parte del render target (pantalla, textura)
/// se debe dibujar. Es esencial para ajustar resolución, splitscreen, editores, etc.

/// Forward declarations para evitar dependencias circulares innecesarias.
class Window;
class DeviceContext;

/// @class Viewport
/// @brief Representa un viewport de Direct3D 11, que delimita el área visible de dibujo.
class Viewport {
public:
	/// Constructor por defecto
	Viewport() = default;

	/// Destructor por defecto
	~Viewport() = default;

	/// @brief Inicializa el viewport usando las dimensiones de una ventana.
	/// @param window Referencia a una instancia de Window.
	/// @return HRESULT indicando si la operación fue exitosa (S_OK).
	HRESULT init(const Window& window);

	/// @brief Inicializa el viewport con dimensiones específicas.
	/// @param width Ancho del viewport.
	/// @param height Alto del viewport.
	/// @return HRESULT indicando si la operación fue exitosa (S_OK).
	HRESULT init(unsigned int width, unsigned int height);

	/// @brief Método de actualización (por ahora sin uso).
	void update();

	/// @brief Establece este viewport como activo en el pipeline gráfico.
	/// @param deviceContext Contexto de dispositivo en el que se aplicará el viewport.
	void render(DeviceContext& deviceContext);

	/// @brief Libera recursos asociados al viewport (actualmente no necesario).
	void destroy();

public:
	/// @brief Estructura de viewport de Direct3D 11.
	/// Contiene información de tamaño, profundidad y posición del área visible.
	D3D11_VIEWPORT m_viewport;
};
