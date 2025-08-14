/**
 * @file The Visionary Engine.cpp
 * @brief Punto de entrada Win32 y reenvío de mensajes a ImGui para The Visionary Engine.
 *
 * Inicializa el motor a través de BaseApp::run y enruta mensajes Win32,
 * dando prioridad a ImGui_ImplWin32_WndProcHandler para el manejo de entradas.
 */

#include <windows.h>
#include "BaseApp.h"
#include "UserInterface.h"

 // ImGui
#include "imgui.h"
#include "imgui_impl_win32.h"

// Reenvío de eventos Win32 → ImGui (externo, provisto por el backend de ImGui)
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Declaración adelantada del procedimiento de ventana
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Punto de entrada
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    BaseApp app;
    return app.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}

// Procedimiento de ventana
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 1) Permitir que ImGui procese primero; si lo consume, retornar inmediatamente.
    if (ImGui::GetCurrentContext() &&
        ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    {
        return true; // Importante para drag y manejo de inputs
    }

    // 2) Manejo normal de mensajes
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return 0;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
