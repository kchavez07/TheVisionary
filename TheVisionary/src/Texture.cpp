// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
#include "Texture.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT Texture::init(Device device, const std::string& textureName, ExtensionType extensionType)
{
	return E_NOTIMPL;
}

HRESULT Texture::init(Device device, unsigned int width,
	unsigned int height, DXGI_FORMAT format,
	unsigned int BindFlags, unsigned int sampleCount,
	unsigned int qualityLevels)
{
	if (!device.m_device) {
		ERROR("Texture", "init", "Device is not initialized / is null.");
		return E_FAIL;
	}
	if (width == 0 || height == 0) {
		ERROR("Texture", "init", "Width and height must be greater than 0.");
		return E_FAIL;
	}

	// Config texture
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	sampleCount = 4;
	UINT sampleQuality = 0;
	device.m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, sampleCount, &sampleQuality);
	if (sampleQuality > 0) sampleQuality -= 1; // Quality levels are 0-based
	desc.SampleDesc.Count = sampleCount;
	desc.SampleDesc.Quality = sampleQuality;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = BindFlags;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	HRESULT hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
	if (FAILED(hr)) {
		ERROR("Texture", "init", ("Failed to create texture with specified parameters. HRESULT: " + std::to_string(hr)).c_str());
		return hr;
	}

	return S_OK;
}

HRESULT Texture::init(Device& device, Texture& textureRef, DXGI_FORMAT format)
{
	if (!device.m_device) {
		ERROR("Texture", "init", "Device is not initialized / is null.");
		return E_FAIL;
	}
	if (!textureRef.m_texture) {
		ERROR("Texture", "init", "Texture reference is not initialized / is null.");
		return E_FAIL;
	}

	// Create shader resource view from texture reference
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	HRESULT hr = device.m_device->CreateShaderResourceView(textureRef.m_texture, &srvDesc, &m_textureFromImg);

	if (FAILED(hr)) {
		ERROR("Texture", "init", ("Failed to create shader resource view from texture reference. HRESULT: " + std::to_string(hr)).c_str());
		return hr;
	}
	return S_OK;
}

void Texture::render(DeviceContext& deviceContext,
	unsigned int StartSlot, unsigned int NumViews)
{
	if (!deviceContext.m_deviceContext) {
		ERROR("Texture", "render", "Device context is not initialized / is null.");
		return;
	}
	if (m_textureFromImg) {
		ID3D11ShaderResourceView* nullSRV[] = { nullptr };
		deviceContext.m_deviceContext->PSSetShaderResources(StartSlot, NumViews, nullSRV);
		deviceContext.m_deviceContext->PSSetShaderResources(StartSlot, NumViews, &m_textureFromImg);
	}
}

void Texture::destroy()
{
	if (m_texture != nullptr) {
		SAFE_RELEASE(m_texture);
	}
	if (m_textureFromImg != nullptr) {
		SAFE_RELEASE(m_textureFromImg);
	}
}