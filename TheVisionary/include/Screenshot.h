#pragma once
#include "Prerequisites.h"
#include "UserInterface.h"

class Window;
class SwapChain;
class Texture;

/**
 * @class Screenshot
 * @brief Gestiona la captura de pantallas del contenido renderizado.
 *
 * @details
 * Proporciona funciones para capturar la imagen del back buffer
 * y mostrar opciones relacionadas en la interfaz de usuario.
 */
class Screenshot {
public:
    /** @brief Constructor por defecto. */
    Screenshot() = default;

    /** @brief Destructor por defecto. */
    ~Screenshot() = default;

    /**
     * @brief Captura una imagen del contenido actual del back buffer.
     * @param window Referencia a la ventana activa.
     * @param swapChain Cadena de intercambio asociada.
     * @param backBuffer Textura del back buffer a capturar.
     */
    void captureScreenshot(Window window, SwapChain swapChain, Texture& backBuffer);

    /**
     * @brief Dibuja la interfaz de usuario para la captura de pantalla.
     * @param window Referencia a la ventana activa.
     * @param swapChain Cadena de intercambio asociada.
     * @param backBuffer Textura del back buffer a mostrar o capturar.
     */
    void ui(Window window, SwapChain swapChain, Texture& backBuffer);
};
