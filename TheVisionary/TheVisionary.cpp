#include <windows.h>
#include "BaseApp.h"
#include "UserInterface.h"

// ImGui
#include "imgui.h"
#include "imgui_impl_win32.h"

// Reenvío de Win32 a ImGui
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Declaración adelantada
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
    // 1) Deja que ImGui procese primero. Si lo consume, salimos.
    if (ImGui::GetCurrentContext() &&
        ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    {
        return true; // clave para drag/inputs
    }

    // 2) Tu manejo normal
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
