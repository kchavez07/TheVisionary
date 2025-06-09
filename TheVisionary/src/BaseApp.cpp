#include "BaseApp.h"

// ===================================================
// M�TODO: init()
// Inicializa la aplicaci�n. Se utiliza para preparar
// recursos, cargar texturas, inicializar dispositivos, etc.
// En este punto a�n no est� implementado, pero es �til dejarlo
// declarado para seguir el flujo completo de la app.
// ===================================================
HRESULT BaseApp::init() {
    return E_NOTIMPL; // E_NOTIMPL = Not Implemented
}

// ===================================================
// M�TODO: update()
// Se llama cada frame para actualizar la l�gica de la app.
// Aqu� se suelen poner c�lculos de movimiento, l�gica de IA,
// f�sicas, animaciones, etc.
// De momento est� vac�o ya que a�n no hay l�gica definida.
// ===================================================
void BaseApp::update() {
    // TODO: Agregar l�gica por frame aqu�
}

// ===================================================
// M�TODO: render()
// Es llamado despu�s de update() en cada frame.
// Su responsabilidad es dibujar la escena o interfaz gr�fica
// utilizando DirectX. Por ahora no hay nada para dibujar.
// ===================================================
void BaseApp::render() {
    // TODO: Agregar llamadas de renderizado aqu�
}

// ===================================================
// M�TODO: destroy()
// Se ejecuta al final del ciclo de vida de la aplicaci�n.
// Su funci�n es liberar memoria o recursos (texturas, buffers, etc.)
// que hayan sido asignados din�micamente.
// ===================================================
void BaseApp::destroy() {
    // TODO: Agregar limpieza de recursos cuando existan
}

// ===================================================
// M�TODO: run()
// Este es el punto principal de ejecuci�n de la aplicaci�n.
// Su tarea ser� inicializar la ventana (y otros m�dulos), iniciar
// el bucle principal (loop de juego) y gestionar eventos.
// Los par�metros vienen del sistema operativo (WinMain).
// ===================================================
int BaseApp::run(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow,
    WNDPROC wndproc) {
    // TODO: Inicializar ventana, swapchain, bucle principal, etc.
    return 0;
}
