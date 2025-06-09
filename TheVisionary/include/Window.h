#pragma once
#include "Prerequisites.h"

/**
 * @file Window.h
 * @class Window
 * @brief Clase encargada de crear y manejar la ventana principal del motor gr�fico usando WinAPI.
 *
 * Esta clase encapsula la creaci�n, actualizaci�n y destrucci�n de la ventana.
 * Tambi�n proporciona acceso a las dimensiones del �rea de cliente y al handle (HWND).
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
	 * @param nCmdShow Bandera que indica c�mo se debe mostrar la ventana (normal, minimizada, etc.).
	 * @param wndproc Funci�n de callback para el procesamiento de mensajes (eventos) del sistema.
	 * @return HRESULT C�digo de resultado de �xito o error.
	 */
	HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

	/**
	 * @brief M�todo de actualizaci�n por frame (actualmente vac�o).
	 *
	 * Se puede utilizar m�s adelante para l�gica personalizada o polling de eventos.
	 */
	void update();

	/**
	 * @brief M�todo de renderizado asociado a la ventana (actualmente no implementado).
	 *
	 * Nota: El renderizado principal se realiza desde el contexto gr�fico (DeviceContext).
	 */
	void render();

	/**
	 * @brief Libera recursos asociados a la ventana.
	 *
	 * Es recomendable llamarlo antes de cerrar la aplicaci�n para evitar fugas.
	 */
	void destroy();

	/**
	 * @brief Handle (identificador) de la ventana WinAPI.
	 *
	 * Este valor es requerido por casi todas las funciones relacionadas con ventanas en Win32.
	 */
	HWND m_hWnd = nullptr;

	/**
	 * @brief Ancho del �rea cliente (interior) de la ventana.
	 */
	unsigned int m_width;

	/**
	 * @brief Alto del �rea cliente (interior) de la ventana.
	 */
	unsigned int m_height;

private:
	/**
	 * @brief Instancia de la aplicaci�n WinAPI.
	 *
	 * Es provista por WinMain y necesaria para funciones como CreateWindow o LoadIcon.
	 */
	HINSTANCE m_hInst = nullptr;

	/**
	 * @brief Rect�ngulo que representa las dimensiones internas de la ventana.
	 */
	RECT m_rect;

	/**
	 * @brief Nombre o t�tulo que se muestra en la barra de la ventana.
	 */
	std::string m_windowName = "The Visionary Engine";
};
