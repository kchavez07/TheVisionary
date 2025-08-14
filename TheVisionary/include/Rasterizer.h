#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class Rasterizer
 * @brief Administra el estado de rasterizaci�n en Direct3D 11.
 *
 * @details
 * Encapsula la creaci�n, configuraci�n y destrucci�n del
 * ID3D11RasterizerState, controlando aspectos como el cull mode
 * y el fill mode durante el renderizado.
 */
class Rasterizer {
public:
    /** @brief Constructor por defecto. */
    Rasterizer() = default;

    /** @brief Destructor por defecto. */
    ~Rasterizer() = default;

    /**
     * @brief Inicializa el estado de rasterizaci�n.
     * @param device Dispositivo Direct3D donde se crear� el estado.
     * @return HRESULT que indica �xito o error de la operaci�n.
     */
    HRESULT init(Device device);

    /** @brief Actualiza par�metros internos si es necesario. */
    void update();

    /**
     * @brief Aplica el estado de rasterizaci�n al contexto de dispositivo.
     * @param deviceContext Contexto de dispositivo donde aplicar el estado.
     */
    void render(DeviceContext& deviceContext);

    /** @brief Libera los recursos asociados. */
    void destroy();

private:
    /** @brief Puntero al estado de rasterizaci�n de Direct3D 11. */
    ID3D11RasterizerState* m_rasterizerState = nullptr;
};
