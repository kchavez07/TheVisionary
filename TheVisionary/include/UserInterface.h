#pragma once

#include "imgui.h"
#include <d3d11.h>
#include <Windows.h>

/**
 * @brief Encapsula la l�gica de la interfaz gr�fica con ImGui.
 */
class UserInterface {
public:
    void init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context);
    void update();
    void render();
    void destroy();

private:
    void setupStyle();
};
