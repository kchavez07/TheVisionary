#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class SamplerState
 * @brief Administra el estado de muestreo de texturas en Direct3D 11.
 *
 * @details
 * Encapsula la creación, configuración y destrucción del
 * ID3D11SamplerState, definiendo cómo se leen las texturas en los shaders.
 */
class SamplerState {
public:
    /** @brief Constructor por defecto. */
    SamplerState() = default;

    /** @brief Destructor por defecto. */
    ~SamplerState() = default;

    /**
     * @brief Inicializa el estado de muestreo.
     * @param device Dispositivo Direct3D donde se creará el estado.
     * @return HRESULT que indica éxito o error de la operación.
     */
    HRESULT init(Device& device);

    /** @brief Actualiza parámetros internos si es necesario. */
    void update();

    /**
     * @brief Aplica el estado de muestreo al contexto de dispositivo.
     * @param deviceContext Contexto de dispositivo donde aplicar el estado.
     * @param StartSlot Primer slot de muestreador en el shader.
     * @param NumSamplers Número de muestreadores a asignar.
     */
    void render(DeviceContext& deviceContext,
        unsigned int StartSlot,
        unsigned int NumSamplers);

    /** @brief Libera los recursos asociados. */
    void destroy();

public:
    /** @brief Puntero al estado de muestreo de Direct3D 11. */
    ID3D11SamplerState* m_sampler = nullptr;
};
