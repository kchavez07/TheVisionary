#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class DepthStencilState
 * @brief Gestiona el estado de profundidad y stencil en Direct3D 11.
 *
 * @details
 * Controla las pruebas de profundidad y stencil durante el renderizado
 * en el motor The Visionary.
 */
class DepthStencilState {
public:
    /**
     * @brief Constructor por defecto.
     */
    DepthStencilState() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~DepthStencilState() = default;

    /**
     * @brief Inicializa el estado de profundidad y stencil.
     * @param device Dispositivo de Direct3D para crear el estado.
     * @param enableDepth Activa/desactiva la prueba de profundidad.
     * @param enableStencil Activa/desactiva la prueba de stencil.
     * @return HRESULT que indica éxito o fallo.
     */
    HRESULT init(Device& device, bool enableDepth = true, bool enableStencil = false);

    /**
     * @brief Actualiza parámetros internos (actualmente sin implementación).
     */
    void update();

    /**
     * @brief Aplica el estado de profundidad y stencil al contexto de render.
     * @param deviceContext Contexto de dispositivo de render.
     * @param stencilRef Valor de referencia para la prueba de stencil.
     * @param reset Si es true, restablece el estado por defecto.
     */
    void render(DeviceContext& deviceContext, unsigned int stencilRef = 0, bool reset = false);

    /**
     * @brief Libera los recursos asociados al estado de profundidad y stencil.
     */
    void destroy();

private:
    ID3D11DepthStencilState* m_depthStencilState = nullptr; ///< Puntero al estado de profundidad/stencil de Direct3D.
};
