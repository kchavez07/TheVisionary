#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class Rasterizer
 * @brief Administra el estado de rasterización en Direct3D 11.
 *
 * @details
 * Encapsula la creación, configuración y destrucción del
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
     * @brief Inicializa el estado de rasterización.
     * @param device Dispositivo Direct3D donde se creará el estado.
     * @return HRESULT que indica éxito o error de la operación.
     */
    HRESULT init(Device device);

    /** @brief Actualiza parámetros internos si es necesario. */
    void update();

    /**
     * @brief Aplica el estado de rasterización al contexto de dispositivo.
     * @param deviceContext Contexto de dispositivo donde aplicar el estado.
     */
    void render(DeviceContext& deviceContext);

    /** @brief Libera los recursos asociados. */
    void destroy();

private:
    /** @brief Puntero al estado de rasterización de Direct3D 11. */
    ID3D11RasterizerState* m_rasterizerState = nullptr;
};
