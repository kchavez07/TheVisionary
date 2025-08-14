/**
 * @file Window.h
 * @brief Declaración de la clase Window para gestión básica de ventana Win32.
 */

#pragma once
#include "Prerequisites.h"

 /**
  * @class Window
  * @brief Administra la ventana principal: creación, bucle de actualización, render y destrucción.
  */
class Window {
public:
    /** Constructor por defecto. */
    Window() = default;

    /** Destructor por defecto. */
    ~Window() = default;

    /**
     * @brief Inicializa y crea la ventana Win32.
     * @param hInstance Instancia de la aplicación.
     * @param nCmdShow Modo de visualización de la ventana (SW_SHOW, etc.).
     * @param wndproc Procedimiento de ventana (callback Win32).
     * @return HRESULT de la operación (S_OK si tuvo éxito).
     */
    HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

    /** @brief Actualiza el estado de la ventana (procesamiento por cuadro). */
    void update();

    /** @brief Realiza el render asociado a la ventana (por cuadro). */
    void render();

    /** @brief Libera recursos asociados y destruye la ventana. */
    void destroy();

public:
    HWND m_hWnd = nullptr;           ///< Handle de la ventana Win32.
    unsigned int m_width;            ///< Ancho actual de la ventana (px).
    unsigned int m_height;           ///< Alto actual de la ventana (px).

private:
    HINSTANCE m_hInst = nullptr;     ///< Instancia de la aplicación.
    RECT m_rect;                     ///< Rect de cliente/ventana.
    std::string m_windowName = "The Visionary Engine"; ///< Título/nombre de la ventana.
};
