#pragma once
#include "Prerequisites.h"

// ================================================
// Clase: Texture
// Representa una textura en DirectX 11, ya sea cargada desde
// imagen o generada como textura vacía para render targets.
// Incluye recursos asociados como la vista ShaderResourceView.
// ================================================
class Device;
class DeviceContext;

class Texture {
public:
    Texture() = default;
    ~Texture() = default;

    // =========================================================
    // Método: init (desde archivo)
    // Carga una textura desde un archivo en disco.
    // Parámetros:
    // - textureName: nombre del archivo.
    // - extensionType: tipo de formato (PNG, JPG, DDS).
    // =========================================================
    HRESULT init(Device device,
        const std::string& textureName,
        ExtensionType extensionType);

    // =========================================================
    // Método: init (textura vacía)
    // Crea una textura vacía con parámetros personalizados.
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
    // Método: init (a partir de otra textura)
    // Permite crear una nueva textura a partir de otra,
    // con un formato diferente (por ejemplo, para conversiones).
    // =========================================================
    HRESULT init(Device& device, Texture& textureRef, DXGI_FORMAT format);

    // =========================================================
    // Método: update
    // Actualiza la textura (por ahora está vacío).
    // =========================================================
    void update();

    // =========================================================
    // Método: render
    // Enlaza la textura al pipeline gráfico para su uso en shaders.
    // =========================================================
    void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

    // =========================================================
    // Método: destroy
    // Libera los recursos asociados a la textura.
    // =========================================================
    void destroy();

public:
    // Puntero al recurso de textura (datos de imagen o render target)
    ID3D11Texture2D* m_texture = nullptr;

    // Puntero a la vista que permite usar la textura en los shaders
    ID3D11ShaderResourceView* m_textureFromImg = nullptr;
};
