#pragma once
#include "Prerequisites.h"
#include "Window.h"

// ===========================================================
// CLASE: BaseApp
// Clase base para una aplicación de motor gráfico con DirectX.
// Sirve como punto de partida para instanciar y controlar el ciclo
// de vida de la app (inicio, bucle de juego, cierre).
// ===========================================================
class BaseApp {
public:
    // Constructor por defecto
    BaseApp() = default;

    // Destructor por defecto
    ~BaseApp() = default;

    // =======================================================
    // MÉTODO: init()
    // Inicializa la aplicación. En esta etapa se pueden cargar
    // recursos, crear dispositivos, inicializar subsistemas, etc.
    // Por ahora está definido pero no implementado (ver .cpp).
    // =======================================================
    HRESULT init();

    // =======================================================
    // MÉTODO: update()
    // Método de actualización lógica. Se ejecuta cada frame
    // para actualizar el estado de la aplicación o del juego.
    // =======================================================
    void update();

    // =======================================================
    // MÉTODO: render()
    // Método que se encarga del renderizado. Aquí se dibuja
    // todo lo que se deba mostrar en pantalla cada frame.
    // =======================================================
    void render();

    // =======================================================
    // MÉTODO: destroy()
    // Libera todos los recursos utilizados por la aplicación.
    // Es llamado antes de cerrar la aplicación.
    // =======================================================
    void destroy();

    // =======================================================
    // MÉTODO: run()
    // Lanza la aplicación. Este método funciona como el punto
    // de entrada personalizado que gestiona la ventana y el loop principal.
    // Parámetros:
    // - hInstance: instancia del programa
    // - hPrevInstance: (no se usa, compatibilidad)
    // - lpCmdLine: argumentos desde línea de comandos
    // - nCmdShow: cómo se mostrará la ventana
    // - wndproc: función para manejar eventos de Windows
    // =======================================================
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    // Objeto que representa la ventana principal de la aplicación
    Window m_window;
};
