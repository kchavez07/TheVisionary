#include "UserInterface.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// === Definiciones de variables globales ===
bool g_enableRotation = true;
bool g_wireframeMode = false;
float g_clearColor[3] = { 0.0f, 0.125f, 0.3f };


// Inicializa ImGui con el HWND y los dispositivos de DirectX
void UserInterface::init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
{
    // Crear contexto de ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    setupStyle(); // Aplica un estilo personalizado

    // Inicializar backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, context);
}

// Comienza un nuevo frame de ImGui y dibuja la interfaz
void UserInterface::update()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // === Ventana de configuración de render ===
    ImGui::Begin("Opciones de Renderizado");

    ImGui::Checkbox("Rotar cubo", &g_enableRotation);
    ImGui::Checkbox("Modo Wireframe", &g_wireframeMode);
    ImGui::ColorEdit3("Color de fondo", g_clearColor);

    ImGui::End();

    ImGui::EndFrame();
}

// Renderiza la interfaz ya preparada
void UserInterface::render()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

// Libera recursos de ImGui
void UserInterface::destroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// Establece estilo visual de ImGui
void UserInterface::setupStyle()
{
    ImGui::StyleColorsDark();
}
