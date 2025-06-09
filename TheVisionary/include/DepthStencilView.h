#pragma once
#include "Prerequisites.h"

/// @file DepthStencilView.h
/// @brief Clase que administra una vista de profundidad y stencil (DepthStencilView) para DirectX 11.
///
/// Esta clase permite definir un buffer de profundidad (z-buffer) y una m�scara de stencil
/// que se utilizan en el pipeline gr�fico para determinar qu� p�xeles deben renderizarse,
/// en funci�n de su profundidad o reglas de m�scara.

// Forward declarations para evitar dependencias circulares
class Device;
class DeviceContext;
class Texture;

/// @class DepthStencilView
/// @brief Representa una vista de profundidad y stencil para Direct3D 11.
///
/// La DepthStencilView se usa com�nmente junto con el RenderTargetView
/// para habilitar el z-buffering y operaciones de stencil en la escena.
class DepthStencilView {
public:
	/// @brief Constructor por defecto.
	DepthStencilView() = default;

	/// @brief Destructor por defecto.
	~DepthStencilView() = default;

	/**
	 * @brief Inicializa la vista de profundidad y stencil a partir de una textura.
	 *
	 * @param device Referencia al dispositivo de DirectX.
	 * @param depthStencil Textura sobre la que se crear� la vista de profundidad/stencil.
	 * @param format Formato de la vista, usualmente DXGI_FORMAT_D24_UNORM_S8_UINT.
	 * @return HRESULT indicando el estado del proceso (S_OK si fue exitoso).
	 */
	HRESULT init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

	/**
	 * @brief M�todo de actualizaci�n por cuadro (vac�o por ahora).
	 */
	void update();

	/**
	 * @brief Limpia y activa la DepthStencilView en el pipeline.
	 *
	 * @param deviceContext Contexto del dispositivo utilizado para emitir comandos de render.
	 */
	void render(DeviceContext& deviceContext);

	/**
	 * @brief Libera los recursos asociados a la DepthStencilView.
	 */
	void destroy();

public:
	/**
	 * @brief Puntero a la interfaz ID3D11DepthStencilView de DirectX.
	 */
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
};
