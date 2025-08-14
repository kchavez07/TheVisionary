/**
 * @file Texture.cpp
 * @brief Carga/creación, enlace y liberación de texturas 2D (SRV).
 */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "Device.h"
#include "DeviceContext.h"

// Opcional: helper local
static void SafeRelease(IUnknown*& p) { if (p) { p->Release(); p = nullptr; } }

HRESULT
Texture::init(Device device, const std::string& textureName, ExtensionType extensionType) {
    if (!device.m_device) {
        ERROR("Texture", "init", "Device is null.");
        return E_POINTER;
    }
    if (textureName.empty()) {
        ERROR("Texture", "init", "Texture name cannot be empty.");
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;

    // Asegúrate de partir sin recursos previos
    if (m_textureFromImg) { m_textureFromImg->Release(); m_textureFromImg = nullptr; }
    if (m_texture) { m_texture->Release();        m_texture = nullptr; }

    switch (extensionType) {
    case DDS: {
        m_textureName = textureName + ".dds";

        // Usa la versión A para std::string
        hr = D3DX11CreateShaderResourceViewFromFileA(
            device.m_device,
            m_textureName.c_str(),
            nullptr,
            nullptr,
            &m_textureFromImg,
            nullptr
        );

        if (FAILED(hr)) {
            ERROR("Texture", "init",
                ("Failed to load DDS texture. Verify filepath: " + m_textureName).c_str());
            return hr;
        }
        break;
    }

    case PNG: {
        m_textureName = textureName + ".png";
        int width = 0, height = 0, channels = 0;
        unsigned char* data = stbi_load(m_textureName.c_str(), &width, &height, &channels, 4); // RGBA
        if (!data) {
            ERROR("Texture", "init",
                ("Failed to load PNG texture: " + std::string(stbi_failure_reason())).c_str());
            return E_FAIL;
        }

        // Descripción de la textura
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        // Datos iniciales
        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = data;
        initData.SysMemPitch = width * 4;

        hr = device.m_device->CreateTexture2D(&textureDesc, &initData, &m_texture);
        stbi_image_free(data);

        if (FAILED(hr)) {
            ERROR("Texture", "init", "Failed to create texture from PNG data");
            return hr;
        }

        // Crear SRV
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        srvDesc.Texture2D.MostDetailedMip = 0;

        hr = device.m_device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureFromImg);
        // ya no necesitamos la ID3D11Texture2D suelta (la SRV mantiene la referencia al recurso subyacente)
        SafeRelease(reinterpret_cast<IUnknown*&>(m_texture));

        if (FAILED(hr)) {
            ERROR("Texture", "init", "Failed to create shader resource view for PNG texture");
            return hr;
        }
        break;
    }

    default:
        ERROR("Texture", "init", "Unsupported extension type");
        return E_INVALIDARG;
    }

    return hr;
}

HRESULT
Texture::init(Device device,
    unsigned int width,
    unsigned int height,
    DXGI_FORMAT Format,
    unsigned int BindFlags,
    unsigned int sampleCount,
    unsigned int qualityLevels) {
    if (!device.m_device) {
        ERROR("Texture", "init", "Device is null.");
        return E_POINTER;
    }
    if (width == 0 || height == 0) {
        ERROR("Texture", "init", "Width and height must be greater than 0");
        return E_INVALIDARG; // <- faltaba el return
    }

    // Limpia previos
    SafeRelease(reinterpret_cast<IUnknown*&>(m_texture));
    SafeRelease(reinterpret_cast<IUnknown*&>(m_textureFromImg));

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = Format;
    desc.SampleDesc.Count = sampleCount;
    desc.SampleDesc.Quality = qualityLevels;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = BindFlags;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    HRESULT hr = device.m_device->CreateTexture2D(&desc, nullptr, &m_texture);
    if (FAILED(hr)) {
        ERROR("Texture", "init",
            ("Failed to create texture with specified params. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

HRESULT
Texture::init(Device& device, Texture& textureRef, DXGI_FORMAT format) {
    if (!device.m_device) {
        ERROR("Texture", "init", "Device is null.");
        return E_POINTER;
    }
    if (!textureRef.m_texture) {
        ERROR("Texture", "init", "Texture is null.");
        return E_POINTER;
    }

    // Limpia previos
    SafeRelease(reinterpret_cast<IUnknown*&>(m_textureFromImg));

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.MostDetailedMip = 0;

    HRESULT hr = device.m_device->CreateShaderResourceView(
        textureRef.m_texture, &srvDesc, &m_textureFromImg);

    if (FAILED(hr)) {
        ERROR("Texture", "init",
            ("Failed to create shader resource view. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

void Texture::update() {
    // no-op
}

void
Texture::render(DeviceContext& deviceContext,
    unsigned int StartSlot,
    unsigned int NumViews) {
    if (!deviceContext.m_deviceContext) {
        ERROR("Texture", "render", "Device context is null.");
        return;
    }

    // Solo enlaza si tienes SRV (texturas de imagen). El backbuffer NO tiene SRV.
    if (m_textureFromImg) {
        // En la mayoría de casos NumViews = 1. Si usas más, crea un array y pásalo.
        ID3D11ShaderResourceView* srv = m_textureFromImg;
        deviceContext.m_deviceContext->PSSetShaderResources(StartSlot, 1, &srv);
    }
}

void Texture::destroy() {
    // Libera ambos independientemente (no usar else-if)
    SafeRelease(reinterpret_cast<IUnknown*&>(m_textureFromImg));
    SafeRelease(reinterpret_cast<IUnknown*&>(m_texture));
}
