#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class InputLayout
 * @brief Define el formato de los datos de v�rtice para el Input Assembler de Direct3D 11.
 *
 * @details
 * El Input Layout describe c�mo se interpretan los datos de v�rtice
 * en la etapa de ensamblado de entrada del pipeline gr�fico.
 * Se crea a partir de una lista de descriptores y el bytecode del vertex shader.
 *
 * @note Parte del motor gr�fico The Visionary.
 */
class InputLayout {
public:
    InputLayout() = default;  ///< Constructor por defecto.
    ~InputLayout() = default; ///< Destructor por defecto.

    /**
     * @brief Inicializa el Input Layout.
     * @param device Dispositivo de Direct3D usado para la creaci�n.
     * @param Layout Vector con descriptores de elementos de entrada.
     * @param VertexShaderData Bytecode del Vertex Shader asociado.
     * @return HRESULT con el estado de la operaci�n.
     */
    HRESULT init(Device& device,
        std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
        ID3DBlob* VertexShaderData);

    /**
     * @brief Actualiza el estado interno del Input Layout (si es necesario).
     */
    void update();

    /**
     * @brief Asigna este Input Layout al pipeline de renderizado.
     * @param deviceContext Contexto del dispositivo donde se aplicar�.
     */
    void render(DeviceContext& deviceContext);

    /**
     * @brief Libera los recursos asociados al Input Layout.
     */
    void destroy();

public:
    ID3D11InputLayout* m_inputLayout = nullptr; ///< Puntero a la interfaz de Input Layout.
};
