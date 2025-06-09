#pragma once
#include "Prerequisites.h"

/**
 * @file Window.h
 * @class Window
 * @brief Clase encargada de crear y manejar la ventana principal del motor gráfico usando WinAPI.
 *
 * Esta clase encapsula la creación, actualización y destrucción de la ventana.
 * También proporciona acceso a las dimensiones del área de cliente y al handle (HWND).
 */
class Window {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	Window() = default;

	/**
	 * @brief Destructor por defecto.
	 */
	~Window() = default;

	/**
	 * @brief Inicializa y crea la ventana de Windows.
	 *
	 * @param hInstance Instancia del programa proporcionada por WinMain.
	 * @param nCmdShow Bandera que indica cómo se debe mostrar la ventana (normal, minimizada, etc.).
	 * @param wndproc Función de callback para el procesamiento de mensajes (eventos) del sistema.
	 * @return HRESULT Código de resultado de éxito o error.
	 */
	HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

	/**
	 * @brief Método de actualización por frame (actualmente vacío).
	 *
	 * Se puede utilizar más adelante para lógica personalizada o polling de eventos.
	 */
	void update();

	/**
	 * @brief Método de renderizado asociado a la ventana (actualmente no implementado).
	 *
	 * Nota: El renderizado principal se realiza desde el contexto gráfico (DeviceContext).
	 */
	void render();

	/**
	 * @brief Libera recursos asociados a la ventana.
	 *
	 * Es recomendable llamarlo antes de cerrar la aplicación para evitar fugas.
	 */
	void destroy();

	/**
	 * @brief Handle (identificador) de la ventana WinAPI.
	 *
	 * Este valor es requerido por casi todas las funciones relacionadas con ventanas en Win32.
	 */
	HWND m_hWnd = nullptr;

	/**
	 * @brief Ancho del área cliente (interior) de la ventana.
	 */
	unsigned int m_width;

	/**
	 * @brief Alto del área cliente (interior) de la ventana.
	 */
	unsigned int m_height;

private:
	/**
	 * @brief Instancia de la aplicación WinAPI.
	 *
	 * Es provista por WinMain y necesaria para funciones como CreateWindow o LoadIcon.
	 */
	HINSTANCE m_hInst = nullptr;

	/**
	 * @brief Rectángulo que representa las dimensiones internas de la ventana.
	 */
	RECT m_rect;

	/**
	 * @brief Nombre o título que se muestra en la barra de la ventana.
	 */
	std::string m_windowName = "The Visionary Engine";
};
