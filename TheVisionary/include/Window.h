#pragma once
#include "Prerequisites.h"

// ===========================================================
// CLASE: Window
// Esta clase se encarga de crear y manejar la ventana principal
// del motor gr�fico, utilizando las funciones de la WinAPI.
// Tambi�n guarda las dimensiones y el nombre de la ventana.
// ===========================================================
class Window {
public:
	// Constructor por defecto
	Window() = default;

	// Destructor por defecto
	~Window() = default;

	// =======================================================
	// M�TODO: init()
	// Inicializa y crea la ventana de Windows usando WinAPI.
	// Recibe:
	// - hInstance: instancia del programa (la da WinMain)
	// - nCmdShow: modo de visualizaci�n de la ventana (normal, minimizada, etc.)
	// - wndproc: funci�n de callback para manejar los mensajes de Windows (eventos)
	// =======================================================
	HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

	// =======================================================
	// M�TODO: update()
	// M�todo de actualizaci�n por frame (a�n sin l�gica).
	// Podr�a usarse para procesar eventos personalizados.
	// =======================================================
	void update();

	// =======================================================
	// M�TODO: render()
	// M�todo para l�gica de renderizado (no se usa directamente
	// porque DX11 dibuja con el contexto de dispositivo).
	// =======================================================
	void render();

	// =======================================================
	// M�TODO: destroy()
	// Libera los recursos asociados a la ventana.
	// Es una buena pr�ctica llamarlo antes de cerrar la app.
	// =======================================================
	void destroy();

public:
	// Handle (identificador) de la ventana WinAPI
	// Este valor es requerido por casi todas las funciones de Win32.
	HWND m_hWnd = nullptr;

	// Ancho y alto del �rea visible de la ventana (cliente)
	unsigned int m_width;
	unsigned int m_height;

private:
	// Instancia del programa (WinMain la proporciona)
	// Necesaria para varias llamadas a funciones WinAPI.
	HINSTANCE m_hInst = nullptr;

	// Estructura RECT con las dimensiones de la ventana.
	RECT m_rect;

	// Nombre de la ventana (aparece en la barra de t�tulo)
	std::string m_windowName = "The Visionary Engine";
};
