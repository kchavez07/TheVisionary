#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

/**
 * @class ShaderProgram
 * @brief Encapsula un programa de shaders (Vertex y Pixel) y su Input Layout.
 *
 * @details
 * Administra la carga, compilaci�n, creaci�n y uso de shaders de Direct3D 11.
 * Tambi�n se encarga de inicializar el Input Layout necesario para el ensamblado de v�rtices.
 *
 * @note Parte del motor gr�fico The Visionary.
 */
class ShaderProgram {
public:
    ShaderProgram() = default;  ///< Constructor por defecto.
    ~ShaderProgram() = default; ///< Destructor por defecto.

    /**
     * @brief Inicializa el programa de shaders a partir de un archivo y un layout de entrada.
     * @param device Dispositivo Direct3D para la creaci�n de recursos.
     * @param fileName Nombre del archivo que contiene los shaders.
     * @param Layout Descriptores del formato de v�rtices.
     * @return HRESULT con el estado de la operaci�n.
     */
    HRESULT init(Device& device,
        const std::string& fileName,
        std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    /**
     * @brief Actualiza el estado del programa de shaders.
     */
    void update();

    /**
     * @brief Aplica el programa de shaders al pipeline.
     * @param deviceContext Contexto del dispositivo donde se usar�.
     */
    void render(DeviceContext& deviceContext);

    /**
     * @brief Aplica un tipo espec�fico de shader al pipeline.
     * @param deviceContext Contexto del dispositivo donde se usar�.
     * @param type Tipo de shader a aplicar.
     */
    void render(DeviceContext& deviceContext, ShaderType type);

    /**
     * @brief Libera los recursos asociados a los shaders e Input Layout.
     */
    void destroy();

    /**
     * @brief Crea el Input Layout del programa.
     * @param device Dispositivo Direct3D.
     * @param Layout Descriptores del formato de v�rtices.
     * @return HRESULT con el estado de la operaci�n.
     */
    HRESULT CreateInputLayout(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

    /**
     * @brief Crea un shader del tipo especificado usando el archivo del programa.
     * @param device Dispositivo Direct3D.
     * @param type Tipo de shader a crear.
     * @return HRESULT con el estado de la operaci�n.
     */
    HRESULT CreateShader(Device& device, ShaderType type);

    /**
     * @brief Crea un shader del tipo especificado desde un archivo dado.
     * @param device Dispositivo Direct3D.
     * @param type Tipo de shader a crear.
     * @param fileName Ruta del archivo HLSL.
     * @return HRESULT con el estado de la operaci�n.
     */
    HRESULT CreateShader(Device& device, ShaderType type, const std::string& fileName);

    /**
     * @brief Compila un shader desde archivo.
     * @param szFileName Ruta del archivo HLSL.
     * @param szEntryPoint Punto de entrada del shader.
     * @param szShaderModel Modelo de shader (ej. "vs_5_0").
     * @param ppBlobOut Blob de salida con el bytecode compilado.
     * @return HRESULT con el estado de la operaci�n.
     */
    HRESULT CompileShaderFromFile(char* szFileName,
        LPCSTR szEntryPoint,
        LPCSTR szShaderModel,
        ID3DBlob** ppBlobOut);

public:
    ID3D11VertexShader* m_VertexShader = nullptr; ///< Shader de v�rtices.
    ID3D11PixelShader* m_PixelShader = nullptr;   ///< Shader de p�xeles.
    InputLayout m_inputLayout;                    ///< Input Layout asociado.
private:
    std::string m_shaderFileName;                 ///< Nombre del archivo del shader.
    ID3DBlob* m_vertexShaderData = nullptr;       ///< Bytecode del Vertex Shader.
    ID3DBlob* m_pixelShaderData = nullptr;        ///< Bytecode del Pixel Shader.
};
