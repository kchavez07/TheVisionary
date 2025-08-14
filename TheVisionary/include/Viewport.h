#pragma once
#include "Prerequisites.h"

class Window;
class DeviceContext;

/**
 * @class Viewport
 * @brief Representa un área de renderizado en la pantalla para Direct3D 11.
 *
 * @details
 * El viewport define la porción de la superficie de renderizado donde se dibujará
 * la escena. Puede inicializarse a partir de las dimensiones de una ventana
 * o de valores personalizados.
 *
 * @note Parte del motor gráfico The Visionary.
 */
class Viewport {
public:
    Viewport() = default;  ///< Constructor por defecto.
    ~Viewport() = default; ///< Destructor por defecto.

    /**
     * @brief Inicializa el viewport usando las dimensiones de una ventana.
     * @param window Referencia a la ventana asociada.
     * @return HRESULT con el estado de la operación.
     */
    HRESULT init(const Window& window);

    /**
     * @brief Inicializa el viewport con dimensiones personalizadas.
     * @param width Ancho en píxeles.
     * @param height Alto en píxeles.
     * @return HRESULT con el estado de la operación.
     */
    HRESULT init(unsigned int width, unsigned int height);

    /**
     * @brief Actualiza el estado interno del viewport (si es necesario).
     */
    void update();

    /**
     * @brief Configura este viewport en el pipeline de renderizado.
     * @param deviceContext Contexto del dispositivo donde se aplicará.
     */
    void render(DeviceContext& deviceContext);

    /**
     * @brief Libera recursos asociados al viewport.
     */
    void destroy();

public:
    D3D11_VIEWPORT m_viewport; ///< Estructura de configuración del viewport de Direct3D.
};
