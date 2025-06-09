#pragma once
#include "Prerequisites.h"
#include "Window.h"

// ===========================================================
// CLASE: BaseApp
// Clase base para una aplicaci�n de motor gr�fico con DirectX.
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
    // M�TODO: init()
    // Inicializa la aplicaci�n. En esta etapa se pueden cargar
    // recursos, crear dispositivos, inicializar subsistemas, etc.
    // Por ahora est� definido pero no implementado (ver .cpp).
    // =======================================================
    HRESULT init();

    // =======================================================
    // M�TODO: update()
    // M�todo de actualizaci�n l�gica. Se ejecuta cada frame
    // para actualizar el estado de la aplicaci�n o del juego.
    // =======================================================
    void update();

    // =======================================================
    // M�TODO: render()
    // M�todo que se encarga del renderizado. Aqu� se dibuja
    // todo lo que se deba mostrar en pantalla cada frame.
    // =======================================================
    void render();

    // =======================================================
    // M�TODO: destroy()
    // Libera todos los recursos utilizados por la aplicaci�n.
    // Es llamado antes de cerrar la aplicaci�n.
    // =======================================================
    void destroy();

    // =======================================================
    // M�TODO: run()
    // Lanza la aplicaci�n. Este m�todo funciona como el punto
    // de entrada personalizado que gestiona la ventana y el loop principal.
    // Par�metros:
    // - hInstance: instancia del programa
    // - hPrevInstance: (no se usa, compatibilidad)
    // - lpCmdLine: argumentos desde l�nea de comandos
    // - nCmdShow: c�mo se mostrar� la ventana
    // - wndproc: funci�n para manejar eventos de Windows
    // =======================================================
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    // Objeto que representa la ventana principal de la aplicaci�n
    Window m_window;
};
