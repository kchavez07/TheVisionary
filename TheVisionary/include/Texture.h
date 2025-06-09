#pragma once
#include "Prerequisites.h"

// ================================================================
// @class Texture
// @brief Representa una textura en DirectX 11.
// 
// Esta clase encapsula una textura 2D que puede ser:
// - Cargada desde un archivo de imagen.
// - Generada en tiempo de ejecución como render target o depth buffer.
// También contiene una ShaderResourceView asociada para uso en shaders.
// ================================================================

class Device;
class DeviceContext;

class Texture {
public:
     /**
      * @brief Constructor por defecto.
      */
    Texture() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~Texture() = default;

    /**
     * @brief Carga una textura desde un archivo.
     *
     * @param device Dispositivo de render.
     * @param textureName Ruta o nombre del archivo.
     * @param extensionType Tipo de archivo (PNG, DDS, JPG).
     * @return HRESULT Código de éxito o error.
     */
    HRESULT init(Device device,
        const std::string& textureName,
        ExtensionType extensionType);

    /**
     * @brief Crea una textura vacía, útil para render targets o buffers.
     *
     * @param device Dispositivo de render.
     * @param width Ancho de la textura.
     * @param height Alto de la textura.
     * @param Format Formato de la textura (por ejemplo, DXGI_FORMAT_R8G8B8A8_UNORM).
     * @param BindFlags Indicadores de uso (render target, shader resource...).
     * @param sampleCount Número de muestras para MSAA.
     * @param qualityLevels Calidad del MSAA soportada.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT init(Device device,
        unsigned int width,
        unsigned int height,
        DXGI_FORMAT Format,
        unsigned int BindFlags,
        unsigned int sampleCount = 1,
        unsigned int qualityLevels = 0);

    /**
     * @brief Crea una ShaderResourceView a partir de otra textura existente.
     *
     * @param device Dispositivo de render.
     * @param textureRef Textura de origen.
     * @param format Formato deseado para la vista.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT init(Device& device, Texture& textureRef, DXGI_FORMAT format);

    /**
     * @brief Actualiza internamente la textura.
     * Actualmente no implementado (placeholder).
     */
    void update();

    /**
     * @brief Enlaza la textura al pipeline gráfico.
     *
     * @param deviceContext Contexto del dispositivo.
     * @param StartSlot Primer slot donde se vinculará.
     * @param NumViews Número de vistas consecutivas.
     */
    void render(DeviceContext& deviceContext,
        unsigned int StartSlot,
        unsigned int NumViews);

    /**
     * @brief Libera los recursos de la textura.
     */
    void destroy();

public:
     /**
      * @brief Recurso base de la textura (2D).
      * Puede contener datos de imagen, render target, etc.
      */
    ID3D11Texture2D* m_texture = nullptr;

    /**
     * @brief Vista usada para aplicar la textura en shaders.
     * Es utilizada por el pipeline gráfico para muestrear la textura.
     */
    ID3D11ShaderResourceView* m_textureFromImg = nullptr;
};
