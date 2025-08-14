#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class BlendState
 * @brief Gestiona el estado de blending en Direct3D 11.
 *
 * @details
 * Permite configurar y aplicar operaciones de mezcla (transparencia, alfa, etc.)
 * durante el renderizado en el motor The Visionary.
 */
class BlendState {
public:
    /**
     * @brief Constructor por defecto.
     */
    BlendState() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~BlendState() = default;

    /**
     * @brief Inicializa el estado de blending.
     * @param device Dispositivo de Direct3D para crear el estado.
     * @return HRESULT que indica éxito o fallo.
     */
    HRESULT init(Device& device);

    /**
     * @brief Actualiza parámetros internos (actualmente sin implementación).
     */
    void update() {};

    /**
     * @brief Aplica el estado de blending al contexto de render.
     * @param deviceContext Contexto de dispositivo de render.
     * @param blendFactor Factores de mezcla RGBA.
     * @param sampleMask Máscara de muestreo.
     * @param reset Si es true, restablece el estado por defecto.
     */
    void render(DeviceContext& deviceContext,
        float* blendFactor = nullptr,
        unsigned int sampleMask = 0xffffffff,
        bool reset = false);

    /**
     * @brief Libera los recursos asociados al estado de blending.
     */
    void destroy();

private:
    ID3D11BlendState* m_blendState = nullptr; ///< Puntero al estado de blending de Direct3D.
};
