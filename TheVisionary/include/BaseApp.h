#pragma once
#include "Prerequisites.h"
#include "Window.h"

/**
 * @file BaseApp.h
 * @class BaseApp
 * @brief Clase base para una aplicación de motor gráfico con DirectX.
 *
 * Esta clase define el ciclo de vida de la aplicación:
 * inicialización, actualización, renderizado y destrucción.
 * También gestiona la ventana principal y ejecuta el bucle principal del programa.
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
     * @brief Inicializa la aplicación.
     *
     * Este método puede usarse para crear dispositivos, cargar recursos
     * o preparar subsistemas del motor. Actualmente no está implementado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT init();

    /**
     * @brief Actualiza la lógica de la aplicación por frame.
     *
     * Aquí se puede controlar la lógica del juego, animaciones, físicas, etc.
     */
    void update();

    /**
     * @brief Renderiza el contenido de la aplicación por frame.
     *
     * Este método se encarga de dibujar los elementos visuales en pantalla.
     */
    void render();

    /**
     * @brief Libera los recursos utilizados por la aplicación.
     *
     * Este método debe llamarse antes de cerrar la app para evitar fugas de memoria.
     */
    void destroy();

    /**
     * @brief Lanza la aplicación (punto de entrada principal).
     *
     * Se encarga de iniciar la ventana principal y correr el loop principal.
     * @param hInstance Instancia del programa (WinMain).
     * @param hPrevInstance Instancia anterior (no utilizada).
     * @param lpCmdLine Argumentos desde línea de comandos.
     * @param nCmdShow Modo de visualización de la ventana.
     * @param wndproc Función de callback para eventos de Windows.
     * @return int Código de salida de la aplicación.
     */
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    /**
     * @brief Objeto que representa la ventana principal de la aplicación.
     */
    Window m_window;
};
