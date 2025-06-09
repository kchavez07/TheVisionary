#include "BaseApp.h"

// ===================================================
// MÉTODO: init()
// Inicializa la aplicación. Se utiliza para preparar
// recursos, cargar texturas, inicializar dispositivos, etc.
// En este punto aún no está implementado, pero es útil dejarlo
// declarado para seguir el flujo completo de la app.
// ===================================================
HRESULT BaseApp::init() {
    return E_NOTIMPL; // E_NOTIMPL = Not Implemented
}

// ===================================================
// MÉTODO: update()
// Se llama cada frame para actualizar la lógica de la app.
// Aquí se suelen poner cálculos de movimiento, lógica de IA,
// físicas, animaciones, etc.
// De momento está vacío ya que aún no hay lógica definida.
// ===================================================
void BaseApp::update() {
    // TODO: Agregar lógica por frame aquí
}

// ===================================================
// MÉTODO: render()
// Es llamado después de update() en cada frame.
// Su responsabilidad es dibujar la escena o interfaz gráfica
// utilizando DirectX. Por ahora no hay nada para dibujar.
// ===================================================
void BaseApp::render() {
    // TODO: Agregar llamadas de renderizado aquí
}

// ===================================================
// MÉTODO: destroy()
// Se ejecuta al final del ciclo de vida de la aplicación.
// Su función es liberar memoria o recursos (texturas, buffers, etc.)
// que hayan sido asignados dinámicamente.
// ===================================================
void BaseApp::destroy() {
    // TODO: Agregar limpieza de recursos cuando existan
}

// ===================================================
// MÉTODO: run()
// Este es el punto principal de ejecución de la aplicación.
// Su tarea será inicializar la ventana (y otros módulos), iniciar
// el bucle principal (loop de juego) y gestionar eventos.
// Los parámetros vienen del sistema operativo (WinMain).
// ===================================================
int BaseApp::run(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow,
    WNDPROC wndproc) {
    // TODO: Inicializar ventana, swapchain, bucle principal, etc.
    return 0;
}
