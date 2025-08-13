#include "UserInterface.h"
#include "imgui_internal.h"
#include "Screenshot.h"
#include "Window.h"
#include "SwapChain.h"
#include "Texture.h"
#include "MeshComponent.h"
#include "ECS\\Actor.h"

UserInterface::UserInterface() {}
UserInterface::~UserInterface() {}

void UserInterface::init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Entrada y docking
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // <<< Clave para poder arrastrar desde cualquier parte de la ventana
    io.ConfigWindowsMoveFromTitleBarOnly = false;

    ImGui::StyleColorsDark();
    GameMakerStyle();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, deviceContext);

    toolTipData();
    selectedActorIndex = 0;

    m_imguiInitialized = true;
}

void UserInterface::update() {
    // Frame ImGui
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Dockspace “global” para un layout más predecible (opcional pero recomendable)
    ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_PassthruCentralNode);

    // Siempre visibles
    ToolBar();
    closeApp();
}

void UserInterface::render() {
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void UserInterface::destroy()
{
    if (!m_imguiInitialized || ImGui::GetCurrentContext() == nullptr)
        return;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    m_imguiInitialized = false;
}

void UserInterface::vec3Control(const std::string& label, float* values, float resetValue, float columnWidth) {
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize)) values[0] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize)) values[1] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize)) values[2] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values[2], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::Columns(1);

    ImGui::PopID();
}

void UserInterface::menuBar(Window window, SwapChain swapChain, Texture& backBuffer) {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New", "Ctrl+N");
            ImGui::MenuItem("Open", "Ctrl+O");
            ImGui::MenuItem("Save", "Ctrl+S");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::MenuItem("Copy", "Ctrl+C");
            ImGui::MenuItem("Paste", "Ctrl+V");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Capture screenshot"))
        {
            // Screenshot sc; sc.captureScreenshot(window, swapChain, backBuffer);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void UserInterface::Renderer(Window window, ID3D11ShaderResourceView* renderTexture) {
    bool Stage = true;
    // No forzamos pos cada frame para no “clavar” la ventana
    ImGui::Begin("Renderer", &Stage);
    ImTextureID texId = (ImTextureID)renderTexture;
    ImGui::Image(texId, ImVec2(window.m_width / 2.0f, window.m_height / 2.0f));
    ImGui::End();
}

void UserInterface::inspectorGeneral(EU::TSharedPointer<Actor> actor) {
    ImGui::Begin("Inspector");

    bool isStatic = false;
    ImGui::Checkbox("##Static", &isStatic);
    ImGui::SameLine();

    char objectName[128] = "Cube";
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() * 0.6f);
    ImGui::InputText("##ObjectName", &actor->getName()[0], IM_ARRAYSIZE(objectName));
    ImGui::SameLine();

    if (ImGui::Button("Icon")) {
        // icon action
    }

    ImGui::Separator();

    const char* tags[] = { "Untagged", "Player", "Enemy", "Environment" };
    static int currentTag = 0;
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() * 0.5f);
    ImGui::Combo("Tag", &currentTag, tags, IM_ARRAYSIZE(tags));
    ImGui::SameLine();

    const char* layers[] = { "Default", "TransparentFX", "Ignore Raycast", "Water", "UI" };
    static int currentLayer = 0;
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() * 0.5f);
    ImGui::Combo("Layer", &currentLayer, layers, IM_ARRAYSIZE(layers));

    ImGui::Separator();
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
        inspectorContainer(actor);
    }
    ImGui::End();
}

void UserInterface::inspectorContainer(EU::TSharedPointer<Actor> actor) {
    vec3Control("Position", const_cast<float*>(actor->getComponent<Transform>()->getPosition().data()));
    vec3Control("Rotation", const_cast<float*>(actor->getComponent<Transform>()->getRotation().data()));
    vec3Control("Scale", const_cast<float*>(actor->getComponent<Transform>()->getScale().data()));
}

void UserInterface::output() {
    bool Stage = true;
    ImGui::Begin("Output", &Stage);
    ImGui::End();
}

void UserInterface::darkStyle() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.04f, 0.04f, 0.04f, 0.04f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);

    for (int i = 0; i < ImGuiCol_COUNT; ++i) {
        colors[i].x += 0.015f; colors[i].y += 0.025f; colors[i].z += 0.020f;
    }
}

void UserInterface::greyStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
    colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
    colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style.PopupRounding = 3;
    style.WindowPadding = ImVec2(4, 4);
    style.FramePadding = ImVec2(6, 4);
    style.ItemSpacing = ImVec2(6, 2);
    style.ScrollbarSize = 18;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 2;
    style.WindowRounding = 3;
    style.ChildRounding = 3;
    style.FrameRounding = 3;
    style.ScrollbarRounding = 2;
    style.GrabRounding = 3;
    style.TabBorderSize = 2;
    style.TabRounding = 3;

    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

void UserInterface::GameMakerStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 1.0f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.WindowRounding = 0.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.FrameRounding = 0.0f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 14.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.TabBorderSize = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Left;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    // Colores (igual a tu versión)
    style.Colors[ImGuiCol_Text] = ImVec4(0.83137256f, 0.84705883f, 0.87843138f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.83137256f, 0.84705883f, 0.87843138f, 0.50196081f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.17254902f, 0.19215686f, 0.23529412f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.15879828f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.17254902f, 0.19215686f, 0.23529412f, 1.0f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.20392157f, 0.23137255f, 0.28235295f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 0.50196081f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 0.25098041f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 1.0f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.019607844f, 0.019607844f, 0.019607844f, 0.0f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.53333336f, 0.53333336f, 0.53333336f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.33333334f, 0.33333334f, 0.33333334f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.23921569f, 0.52156866f, 0.87843138f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25882354f, 0.58823532f, 0.98039216f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.35294118f, 0.41254902f, 0.44176471f, 0.50196081f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.15294118f, 0.17254902f, 0.21176471f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.15294118f, 0.17254902f, 0.21176471f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 0.25098041f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 1.0f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.427451f, 0.427451f, 0.49803922f, 0.5f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.098039217f, 0.40000001f, 0.74901962f, 0.77999997f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.098039217f, 0.40000001f, 0.74901962f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 0.25098041f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 1.0f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.15294118f, 0.17254902f, 0.21176471f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 0.25098041f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.15294118f, 0.17254902f, 0.21176471f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.30980393f, 0.62352943f, 0.93333334f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.60784316f, 0.60784316f, 0.60784316f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.42745098f, 0.34901962f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.89803922f, 0.69803923f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.60000002f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20392157f, 0.23137255f, 0.28235295f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.20392157f, 0.23137255f, 0.28235295f, 0.50214589f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1, 1, 1, 0.0386f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20392157f, 0.23137255f, 0.28235295f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.9f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.25882354f, 0.58823532f, 0.97647059f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.20392157f, 0.23137255f, 0.28235295f, 0.75294119f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 0.75294119f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10588235f, 0.11372549f, 0.13725491f, 0.75294119f);
}

void UserInterface::visualStudioStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    const ImVec4 discord_purple = ImVec4(0.447f, 0.227f, 0.635f, 1.000f);
    const ImVec4 discord_darker_purple = ImVec4(0.337f, 0.157f, 0.486f, 1.000f);
    const ImVec4 discord_light_gray = ImVec4(0.741f, 0.765f, 0.780f, 1.000f);
    const ImVec4 discord_darker_gray = ImVec4(0.169f, 0.188f, 0.204f, 1.000f);
    const ImVec4 discord_blue = ImVec4(0.192f, 0.545f, 0.906f, 1.000f);
    const ImVec4 discord_green = ImVec4(0.129f, 0.694f, 0.403f, 1.000f);
    const ImVec4 discord_light_blue = ImVec4(0.29f, 0.56f, 0.89f, 1.00f);
    const ImVec4 discord_dark_gray = ImVec4(0.16f, 0.18f, 0.21f, 1.00f);

    colors[ImGuiCol_Text] = discord_light_gray;
    colors[ImGuiCol_TextDisabled] = discord_darker_gray;
    colors[ImGuiCol_WindowBg] = discord_purple;
    colors[ImGuiCol_ChildBg] = discord_purple;
    colors[ImGuiCol_PopupBg] = discord_purple;
    colors[ImGuiCol_Border] = discord_darker_gray;
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_FrameBg] = discord_darker_purple;
    colors[ImGuiCol_FrameBgHovered] = discord_blue;
    colors[ImGuiCol_FrameBgActive] = discord_blue;
    colors[ImGuiCol_TitleBg] = discord_darker_purple;
    colors[ImGuiCol_TitleBgActive] = discord_blue;
    colors[ImGuiCol_TitleBgCollapsed] = discord_darker_gray;
    colors[ImGuiCol_MenuBarBg] = discord_darker_purple;
    colors[ImGuiCol_ScrollbarBg] = discord_darker_purple;
    colors[ImGuiCol_ScrollbarGrab] = discord_light_gray;
    colors[ImGuiCol_ScrollbarGrabHovered] = discord_darker_gray;
    colors[ImGuiCol_ScrollbarGrabActive] = discord_blue;
    colors[ImGuiCol_CheckMark] = discord_green;
    colors[ImGuiCol_SliderGrab] = discord_green;
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_Button] = discord_green;
    colors[ImGuiCol_ButtonHovered] = discord_blue;
    colors[ImGuiCol_ButtonActive] = ImVec4(0.05f, 0.11f, 0.19f, 1.00f);
    colors[ImGuiCol_Header] = discord_green;
    colors[ImGuiCol_HeaderHovered] = discord_blue;
    colors[ImGuiCol_HeaderActive] = ImVec4(0.05f, 0.11f, 0.19f, 1.00f);
    colors[ImGuiCol_Separator] = discord_darker_gray;
    colors[ImGuiCol_SeparatorHovered] = discord_blue;
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.05f, 0.11f, 0.19f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = discord_light_gray;
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.36f, 0.39f, 0.44f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.36f, 0.39f, 0.44f, 1.00f);
    colors[ImGuiCol_Tab] = discord_dark_gray;
    colors[ImGuiCol_TabHovered] = ImVec4(0.05f, 0.11f, 0.19f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.05f, 0.11f, 0.19f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = discord_darker_gray;
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.36f, 0.39f, 0.44f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.36f, 0.39f, 0.44f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = discord_dark_gray;
    colors[ImGuiCol_PlotLines] = ImVec4(0.36f, 0.39f, 0.44f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = discord_light_blue;
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.36f, 0.39f, 0.44f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = discord_light_blue;
    colors[ImGuiCol_TextSelectedBg] = discord_light_blue;
    colors[ImGuiCol_DragDropTarget] = discord_light_blue;
    colors[ImGuiCol_NavHighlight] = discord_light_blue;
    colors[ImGuiCol_NavWindowingHighlight] = discord_light_blue;
    colors[ImGuiCol_NavWindowingDimBg] = discord_darker_gray;
    colors[ImGuiCol_ModalWindowDimBg] = discord_darker_gray;
}

void UserInterface::ToolTip(std::string icon, std::string tip) {
    ImGui::SameLine();
    ImGui::Text("%s", icon.c_str());
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("%s", tip.c_str());
    }
}

void UserInterface::ToolTip(std::string tip) {
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(tip.c_str());
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void UserInterface::toolTipData() {
    m_tooltips.push_back(
        "You can change the current GameObject that is active to be used in the Inspector.\n"
        "\nNOTE:\n* WIP – some things might not work correctly.\n");
    m_tooltips.push_back(
        "You can change the drawing state of the GameObject by activating or deactivating the checkbox.\n"
        "\nNOTE:\n* WIP – some things might not work correctly.\n");
}

void UserInterface::ToolBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("New");
            ImGui::MenuItem("Open");
            ImGui::MenuItem("Save");
            if (ImGui::MenuItem("Exit")) {
                show_exit_popup = true;
                ImGui::OpenPopup("Exit?");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::MenuItem("Undo");
            ImGui::MenuItem("Redo");
            ImGui::MenuItem("Cut");
            ImGui::MenuItem("Copy");
            ImGui::MenuItem("Paste");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools")) {
            ImGui::MenuItem("Options");
            ImGui::MenuItem("Settings");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void UserInterface::closeApp() {
    if (show_exit_popup) {
        ImGui::OpenPopup("Exit?");
        show_exit_popup = false;
    }

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Exit?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Estas a punto de salir de la aplicacion.\nEstas seguro?\n\n");
        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0))) {
            exit(0);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void UserInterface::RenderFullScreenTransparentWindow() {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.0f);

    // Importantísimo: que no “coma” el ratón ni tape ventanas
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoInputs;

    ImGui::Begin("FullScreenTransparentWindow", nullptr, window_flags);
    ImGui::End();
}

void UserInterface::outliner(const std::vector<EU::TSharedPointer<Actor>>& actors) {
    ImGui::Begin("Hierarchy");

    static ImGuiTextFilter filter;
    filter.Draw("Search...", 180.0f);
    ImGui::Separator();

    for (int i = 0; i < (int)actors.size(); ++i) {
        const auto& actor = actors[i];
        std::string actorName = actor ? actor->getName() : "Unnamed Actor";
        if (!filter.PassFilter(actorName.c_str()))
            continue;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        if (selectedActorIndex == i) flags |= ImGuiTreeNodeFlags_Selected;

        bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)i, flags, "%s", actorName.c_str());
        if (ImGui::IsItemClicked())
            selectedActorIndex = i;

        if (nodeOpen) {
            ImGui::TreePop();
        }
    }

    ImGui::End();
}
