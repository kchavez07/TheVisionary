#pragma once
#include "Prerequisites.h"
#include "imgui.h"
#include <imgui_internal.h>
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

class Window;
class SwapChain;
class Texture;
class Actor;
class ModelComponent;

/**
 * @class UserInterface
 * @brief Gestiona y renderiza la interfaz gráfica (ImGui) del motor The Visionary.
 *
 * @details
 * Controla menús, paneles, estilos y utilidades gráficas
 * para la edición y depuración en tiempo real.
 */
class UserInterface {
public:
    /**
     * @brief Constructor por defecto.
     */
    UserInterface();

    /**
     * @brief Destructor por defecto.
     */
    ~UserInterface();

    /**
     * @brief Aplica el estilo visual "Neon Red".
     */
    void NeonRedStyle();

    /**
     * @brief Inicializa ImGui con ventana y dispositivo de render.
     * @param window Puntero a la ventana Win32.
     * @param device Dispositivo de Direct3D.
     * @param deviceContext Contexto de dispositivo de Direct3D.
     */
    void init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

    /**
     * @brief Actualiza la lógica de la interfaz.
     */
    void update();

    /**
     * @brief Renderiza la interfaz en pantalla.
     */
    void render();

    /**
     * @brief Libera recursos de ImGui.
     */
    void destroy();

    /**
     * @brief Control para modificar un vector3 con sliders.
     * @param label Etiqueta del control.
     * @param values Puntero a los valores (x, y, z).
     * @param resetValues Valor de reinicio.
     * @param columnWidth Ancho de la columna de la etiqueta.
     */
    void vec3Control(const std::string& label,
        float* values,
        float resetValues = 0.0f,
        float columnWidth = 100.0f);

    /**
     * @brief Muestra la barra de menú principal.
     */
    void menuBar(Window window, SwapChain swapChain, Texture& backBuffer);

    /**
     * @brief Renderiza la ventana de vista previa del render.
     */
    void Renderer(Window window, ID3D11ShaderResourceView* renderTexture);

    /**
     * @brief Inspector de propiedades generales de un actor.
     */
    void inspectorGeneral(EU::TSharedPointer<Actor> actor);

    /**
     * @brief Inspector para componentes de tipo contenedor.
     */
    void inspectorContainer(EU::TSharedPointer<Actor> actor);

    /**
     * @brief Muestra la ventana de salida/log.
     */
    void output();

    /** @brief Aplica estilo oscuro. */
    void darkStyle();

    /** @brief Aplica estilo gris. */
    void greyStyle();

    /** @brief Aplica estilo tipo GameMaker. */
    void GameMakerStyle();

    /** @brief Aplica estilo tipo Visual Studio. */
    void visualStudioStyle();

    /**
     * @brief Muestra un tooltip con ícono.
     */
    void ToolTip(std::string icon, std::string tip);

    /**
     * @brief Muestra un tooltip simple.
     */
    void ToolTip(std::string tip);

    /**
     * @brief Configura datos de tooltips.
     */
    void toolTipData();

    /**
     * @brief Renderiza la barra de herramientas.
     */
    void ToolBar();

    /**
     * @brief Solicita el cierre de la aplicación.
     */
    void closeApp();

    /**
     * @brief Renderiza una ventana transparente a pantalla completa.
     */
    void RenderFullScreenTransparentWindow();

    /**
     * @brief Muestra el outliner de actores.
     */
    void outliner(const std::vector<EU::TSharedPointer<Actor>>& actors);

public:
    int selectedActorIndex = -1; ///< Índice del actor seleccionado.

private:
    bool checkboxValue = true;
    bool checkboxValue2 = false;
    std::vector<const char*> m_objectsNames; ///< Lista de nombres de objetos.
    std::vector<const char*> m_tooltips;     ///< Lista de tooltips.

    bool show_exit_popup = false;
    bool m_imguiInitialized = false; ///< Indica si ImGui fue inicializado.
};
