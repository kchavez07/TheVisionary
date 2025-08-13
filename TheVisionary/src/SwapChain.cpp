#include "SwapChain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "Window.h"

HRESULT
SwapChain::init(Device& device,
    DeviceContext& deviceContext,
    Texture& backBuffer,
    Window window)
{
    if (!window.m_hWnd) {
        ERROR("SwapChain", "init", "Invalid window handle. (m_hWnd is nullptr)");
        return E_POINTER;
    }

    HRESULT hr = S_OK;

    // Crear device + context
    unsigned int createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    const unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    const unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);

    bool created = false;
    for (unsigned int i = 0; i < numDriverTypes; ++i) {
        m_driverType = driverTypes[i];
        hr = D3D11CreateDevice(
            nullptr,
            m_driverType,
            nullptr,
            createDeviceFlags,
            featureLevels,
            numFeatureLevels,
            D3D11_SDK_VERSION,
            &device.m_device,
            &m_featureLevel,
            &deviceContext.m_deviceContext);

        if (SUCCEEDED(hr)) {
            MESSAGE("SwapChain", "init", "Device created successfully.");
            created = true;
            break;
        }
    }
    if (!created) {
        ERROR("SwapChain", "init",
            ("Failed to create D3D11 device. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // **Sin MSAA para depurar (estable y simple)**
    m_sampleCount = 1;
    m_qualityLevels = 0;

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = window.m_width;
    sd.BufferDesc.Height = window.m_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = window.m_hWnd;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.SampleDesc.Count = 1;   // <- importante
    sd.SampleDesc.Quality = 0;   // <- importante

    // Obtener factory
    hr = device.m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgiDevice);
    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to query IDXGIDevice. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }
    hr = m_dxgiDevice->GetAdapter(&m_dxgiAdapter);
    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to get IDXGIAdapter. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }
    hr = m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
        reinterpret_cast<void**>(&m_dxgiFactory));
    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to get IDXGIFactory. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // Crear swap chain
    hr = m_dxgiFactory->CreateSwapChain(device.m_device, &sd, &m_swapChain);
    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to create swap chain. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // Obtener y guardar el back-buffer correctamente
    ID3D11Texture2D* bb = nullptr;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&bb);
    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to get back buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }
    // liberar anterior si existía y asignar el nuevo
    if (backBuffer.m_texture) { backBuffer.m_texture->Release(); backBuffer.m_texture = nullptr; }
    backBuffer.m_texture = bb; // se liberará en destroy() del Texture

    return S_OK;
}

void
SwapChain::destroy() {
    if (m_swapChain) { SAFE_RELEASE(m_swapChain); }
    if (m_dxgiDevice) { SAFE_RELEASE(m_dxgiDevice); }
    if (m_dxgiAdapter) { SAFE_RELEASE(m_dxgiAdapter); }
    if (m_dxgiFactory) { SAFE_RELEASE(m_dxgiFactory); }
}

void
SwapChain::present() {
    if (m_swapChain) {
        HRESULT hr = m_swapChain->Present(0, 0);
        if (FAILED(hr)) {
            ERROR("SwapChain", "present",
                ("Failed to present swap chain. HRESULT: " + std::to_string(hr)).c_str());
        }
    }
    else {
        ERROR("SwapChain", "present", "Swap chain is not initialized.");
    }
}
