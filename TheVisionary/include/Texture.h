#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/**
 * @class Texture
 * @brief Administra texturas DirectX 11 (desde archivo, vacías o alias).
 *
 * Ofrece inicialización desde imagen, creación de texturas 2D para
 * render targets o depth buffers, y referencia a texturas existentes
 * (por ejemplo, el back-buffer del swap chain).
 */
class Texture {
public:
    Texture() = default;
    ~Texture() = default;

    /**
     * @brief Inicializa desde archivo.
     * @param device Dispositivo de render.
     * @param textureName Nombre/ubicación de la textura.
     * @param extensionType Tipo de extensión de imagen.
     */
    HRESULT init(Device device,
        const std::string& textureName,
        ExtensionType extensionType);

    /**
     * @brief Crea una textura 2D vacía.
     * @param device Dispositivo de render.
     * @param width Ancho en píxeles.
     * @param height Alto en píxeles.
     * @param Format Formato de la textura.
     * @param BindFlags Banderas de uso (RTV, DSV, SRV, etc.).
     * @param sampleCount Muestras para MSAA (por defecto 1).
     * @param qualityLevels Niveles de calidad MSAA (por defecto 0).
     */
    HRESULT init(Device device,
        unsigned int width,
        unsigned int height,
        DXGI_FORMAT Format,
        unsigned int BindFlags,
        unsigned int sampleCount = 1,
        unsigned int qualityLevels = 0);

    /**
     * @brief Inicializa como alias de otra textura.
     * @param device Dispositivo de render.
     * @param textureRef Textura de referencia.
     * @param format Formato de la vista.
     */
    HRESULT init(Device& device, Texture& textureRef, DXGI_FORMAT format);

    /**
     * @brief Adjunta un recurso nativo existente (por ejemplo back-buffer).
     */
    void attach(ID3D11Texture2D* tex) { SAFE_RELEASE(m_texture); m_texture = tex; }

    /// @return Puntero nativo a ID3D11Texture2D.
    ID3D11Texture2D* raw() const { return m_texture; }

    /// @return Puntero SRV para texturas de imagen.
    ID3D11ShaderResourceView* srv() const { return m_textureFromImg; }

    void update();

    /**
     * @brief Enlaza como SRV al Pixel Shader.
     * @param deviceContext Contexto de dispositivo.
     * @param StartSlot Slot inicial.
     * @param NumViews Número de vistas a enlazar.
     */
    void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

    /// Libera recursos de la textura.
    void destroy();

public:
    ID3D11Texture2D* m_texture = nullptr;                 ///< Recurso de textura 2D.
    ID3D11ShaderResourceView* m_textureFromImg = nullptr; ///< Vista SRV (si aplica).
    std::string m_textureName;                            ///< Nombre o ruta.
};
