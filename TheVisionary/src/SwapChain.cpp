#include "SwapChain.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"
#include "Window.h"

// ============================================================================
// MÉTODO: init()
// Inicializa la swap chain y crea el dispositivo de Direct3D junto con el contexto.
// También configura MSAA, la descripción de la swap chain y obtiene el back buffer.
// ============================================================================
HRESULT
SwapChain::init(Device& device,
    DeviceContext& deviceContext,
    Texture& backBuffer,
    Window window) {

    // Verifica que la ventana sea válida
    if (!window.m_hWnd) {
        ERROR("SwapChain", "init", "Invalid window handle. (m_hWnd is nullptr)");
        return E_POINTER;
    }

    HRESULT hr = S_OK;

    // Configura flags de creación del dispositivo
    unsigned int createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG; // Habilita mensajes de depuración
#endif

    // Tipos de drivers posibles: Hardware, WARP (software rápido) o Referencia (software completo)
    D3D_DRIVER_TYPE driverTypes[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

    // Versiones de DirectX que se intentarán (en orden de prioridad)
    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);

    // Intentamos crear el dispositivo con cada tipo de driver
    for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
        D3D_DRIVER_TYPE driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(
            nullptr,
            driverType,
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
            break;
        }
    }

    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to create D3D11 device. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // ========================================
    // Configuración de MSAA (Antialiasing)
    // ========================================
    m_sampleCount = 4;
    hr = device.m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
        m_sampleCount,
        &m_qualityLevels);
    if (FAILED(hr) || m_qualityLevels == 0) {
        ERROR("SwapChain", "init",
            ("MSAA not supported or invalid quality level. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // ========================================
    // Descripción de la swap chain
    // ========================================
    DXGI_SWAP_CHAIN_DESC sd;
    memset(&sd, 0, sizeof(sd));
    sd.BufferCount = 1; // Solo un backbuffer
    sd.BufferDesc.Width = window.m_width;
    sd.BufferDesc.Height = window.m_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Formato estándar 32-bit RGBA
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = window.m_hWnd;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.SampleDesc.Count = m_sampleCount;
    sd.SampleDesc.Quality = m_qualityLevels - 1;

    // ========================================
    // Obtener las interfaces de DXGI necesarias
    // ========================================
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

    // ========================================
    // Crear la swap chain
    // ========================================
    hr = m_dxgiFactory->CreateSwapChain(device.m_device, &sd, &m_swapChain);
    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to create swap chain. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    // ========================================
    // Obtener el buffer trasero (backbuffer)
    // para usarlo como render target
    // ========================================
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backBuffer));
    if (FAILED(hr)) {
        ERROR("SwapChain", "init",
            ("Failed to get back buffer. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

// ============================================================================
// MÉTODO: destroy()
// Libera todas las interfaces asociadas con la swap chain y el sistema DXGI.
// ============================================================================
void
SwapChain::destroy() {
    if (m_swapChain) SAFE_RELEASE(m_swapChain);
    if (m_dxgiDevice) SAFE_RELEASE(m_dxgiDevice);
    if (m_dxgiAdapter) SAFE_RELEASE(m_dxgiAdapter);
    if (m_dxgiFactory) SAFE_RELEASE(m_dxgiFactory);
}

// ============================================================================
// MÉTODO: present()
// Muestra el contenido del backbuffer en la ventana.
// Este paso intercambia el backbuffer por el frontbuffer.
// ============================================================================
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
