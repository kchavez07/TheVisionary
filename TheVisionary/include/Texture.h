#pragma once
#include "Prerequisites.h"

// ================================================
// Clase: Texture
// Representa una textura en DirectX 11, ya sea cargada desde
// imagen o generada como textura vac�a para render targets.
// Incluye recursos asociados como la vista ShaderResourceView.
// ================================================
class Device;
class DeviceContext;

class Texture {
public:
    Texture() = default;
    ~Texture() = default;

    // =========================================================
    // M�todo: init (desde archivo)
    // Carga una textura desde un archivo en disco.
    // Par�metros:
    // - textureName: nombre del archivo.
    // - extensionType: tipo de formato (PNG, JPG, DDS).
    // =========================================================
    HRESULT init(Device device,
        const std::string& textureName,
        ExtensionType extensionType);

    // =========================================================
    // M�todo: init (textura vac�a)
    // Crea una textura vac�a con par�metros personalizados.
    // Se usa para render targets, depth buffers, etc.
    // =========================================================
    HRESULT init(Device device,
        unsigned int width,
        unsigned int height,
        DXGI_FORMAT Format,
        unsigned int BindFlags,
        unsigned int sampleCount = 1,
        unsigned int qualityLevels = 0);

    // =========================================================
    // M�todo: init (a partir de otra textura)
    // Permite crear una nueva textura a partir de otra,
    // con un formato diferente (por ejemplo, para conversiones).
    // =========================================================
    HRESULT init(Device& device, Texture& textureRef, DXGI_FORMAT format);

    // =========================================================
    // M�todo: update
    // Actualiza la textura (por ahora est� vac�o).
    // =========================================================
    void update();

    // =========================================================
    // M�todo: render
    // Enlaza la textura al pipeline gr�fico para su uso en shaders.
    // =========================================================
    void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

    // =========================================================
    // M�todo: destroy
    // Libera los recursos asociados a la textura.
    // =========================================================
    void destroy();

public:
    // Puntero al recurso de textura (datos de imagen o render target)
    ID3D11Texture2D* m_texture = nullptr;

    // Puntero a la vista que permite usar la textura en los shaders
    ID3D11ShaderResourceView* m_textureFromImg = nullptr;
};
