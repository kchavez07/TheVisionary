#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

class Texture {
public:
    Texture() = default;
    ~Texture() = default;

    // Carga desde archivo (si la tienes implementada)
    HRESULT init(Device device,
        const std::string& textureName,
        ExtensionType extensionType);

    // Crea una textura 2D "vacía" (para RT, depth, etc.)
    HRESULT init(Device device,
        unsigned int width,
        unsigned int height,
        DXGI_FORMAT Format,
        unsigned int BindFlags,
        unsigned int sampleCount = 1,
        unsigned int qualityLevels = 0);

    // Inicializa esta textura como "alias" de otra (si lo usas)
    HRESULT init(Device& device, Texture& textureRef, DXGI_FORMAT format);

    // Adjunta un ID3D11Texture2D* (para back-buffer del swapchain)
    void attach(ID3D11Texture2D* tex) { SAFE_RELEASE(m_texture); m_texture = tex; }

    // Punteros nativos (lectura)
    ID3D11Texture2D* raw()  const { return m_texture; }
    ID3D11ShaderResourceView* srv()  const { return m_textureFromImg; }

    void update();

    // Enlaza como SRV en el Pixel Shader (slot StartSlot)
    void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

    void destroy();

public:
    // Recurso de textura (para back-buffer u otras texturas 2D)
    ID3D11Texture2D* m_texture = nullptr;

    // SRV para texturas de imagen (no para back-buffer)
    ID3D11ShaderResourceView* m_textureFromImg = nullptr;

    std::string m_textureName;
};
