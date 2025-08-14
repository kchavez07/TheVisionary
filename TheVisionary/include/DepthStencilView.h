#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class Texture;

/**
 * @class DepthStencilView
 * @brief Encapsula la creaci�n y uso de vistas de profundidad y stencil (DSV) en Direct3D 11.
 *
 * @details
 * Un Depth Stencil View (DSV) permite a Direct3D escribir y leer datos
 * de profundidad y stencil durante el renderizado. Esta clase administra
 * su inicializaci�n, enlace y liberaci�n de recursos.
 *
 * @note Parte del motor gr�fico The Visionary.
 */
class DepthStencilView {
public:
    DepthStencilView() = default;  ///< Constructor por defecto.
    ~DepthStencilView() = default; ///< Destructor por defecto.

    /**
     * @brief Inicializa la vista de profundidad/stencil a partir de una textura.
     * @param device Referencia al dispositivo Direct3D.
     * @param depthStencil Textura que actuar� como buffer de profundidad.
     * @param format Formato de p�xel del DSV.
     * @return HRESULT con el estado de la operaci�n.
     */
    HRESULT init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

    /**
     * @brief Actualiza el estado interno del DSV (si es necesario).
     */
    void update();

    /**
     * @brief Enlaza la vista de profundidad al pipeline gr�fico.
     * @param deviceContext Contexto del dispositivo.
     */
    void render(DeviceContext& deviceContext);

    /**
     * @brief Libera los recursos asociados al DSV.
     */
    void destroy();

public:
    ID3D11DepthStencilView* m_depthStencilView = nullptr; ///< Puntero a la vista DSV de Direct3D.
};
