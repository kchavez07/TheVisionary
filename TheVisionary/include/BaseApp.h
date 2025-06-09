#pragma once
#include "Prerequisites.h"
#include "Window.h"

/**
 * @file BaseApp.h
 * @class BaseApp
 * @brief Clase base para una aplicaci�n de motor gr�fico con DirectX.
 *
 * Esta clase define el ciclo de vida de la aplicaci�n:
 * inicializaci�n, actualizaci�n, renderizado y destrucci�n.
 * Tambi�n gestiona la ventana principal y ejecuta el bucle principal del programa.
 */
class BaseApp {
public:
    /**
     * @brief Constructor por defecto.
     */
    BaseApp() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~BaseApp() = default;

    /**
     * @brief Inicializa la aplicaci�n.
     *
     * Este m�todo puede usarse para crear dispositivos, cargar recursos
     * o preparar subsistemas del motor. Actualmente no est� implementado.
     * @return HRESULT C�digo de �xito o error.
     */
    HRESULT init();

    /**
     * @brief Actualiza la l�gica de la aplicaci�n por frame.
     *
     * Aqu� se puede controlar la l�gica del juego, animaciones, f�sicas, etc.
     */
    void update();

    /**
     * @brief Renderiza el contenido de la aplicaci�n por frame.
     *
     * Este m�todo se encarga de dibujar los elementos visuales en pantalla.
     */
    void render();

    /**
     * @brief Libera los recursos utilizados por la aplicaci�n.
     *
     * Este m�todo debe llamarse antes de cerrar la app para evitar fugas de memoria.
     */
    void destroy();

    /**
     * @brief Lanza la aplicaci�n (punto de entrada principal).
     *
     * Se encarga de iniciar la ventana principal y correr el loop principal.
     * @param hInstance Instancia del programa (WinMain).
     * @param hPrevInstance Instancia anterior (no utilizada).
     * @param lpCmdLine Argumentos desde l�nea de comandos.
     * @param nCmdShow Modo de visualizaci�n de la ventana.
     * @param wndproc Funci�n de callback para eventos de Windows.
     * @return int C�digo de salida de la aplicaci�n.
     */
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    /**
     * @brief Objeto que representa la ventana principal de la aplicaci�n.
     */
    Window m_window;
};
