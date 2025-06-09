#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

// ================================================
// MÉTODO: init()
// Inicializa la vista de profundidad y stencil a partir de una textura 2D.
// Se requiere un formato como DXGI_FORMAT_D24_UNORM_S8_UINT.
// Este recurso es clave para hacer pruebas de profundidad (z-buffer) y stencil.
// ================================================
HRESULT
DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format) {
    // Validación: el dispositivo debe estar inicializado
    if (!device.m_device) {
        ERROR("DepthStencilView", "init", "Device is null.");
    }

    // Validación: la textura debe existir (por ejemplo, una textura de tipo depth)
    if (!depthStencil.m_texture) {
        ERROR("DepthStencilView", "init", "Texture is null.");
        return E_FAIL;
    }

    // Configuramos la descripción de la vista de profundidad/stencil
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    memset(&descDSV, 0, sizeof(descDSV));
    descDSV.Format = format; // Formato de profundidad/stencil
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS; // Multisample (MSAA)
    descDSV.Texture2D.MipSlice = 0; // Solo un mip level (sin LOD)

    // Creamos la DepthStencilView
    HRESULT hr = device.m_device->CreateDepthStencilView(
        depthStencil.m_texture,
        &descDSV,
        &m_depthStencilView);

    if (FAILED(hr)) {
        ERROR("DepthStencilView", "init",
            ("Failed to create depth stencil view. HRESULT: " + std::to_string(hr)).c_str());
        return hr;
    }

    return S_OK;
}

// ================================================
// MÉTODO: render()
// Se llama antes del renderizado de cada frame para limpiar el z-buffer y el stencil.
// Esto evita que los valores de profundidad antiguos interfieran con el nuevo dibujo.
// ================================================
void
DepthStencilView::render(DeviceContext& deviceContext) {
    if (!deviceContext.m_deviceContext) {
        ERROR("DepthStencilView", "render", "Device context is null.");
        return;
    }

    // Limpia el buffer de profundidad y stencil
    deviceContext.m_deviceContext->ClearDepthStencilView(
        m_depthStencilView,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, // Banderas para limpiar ambas partes
        1.0f, // Profundidad inicial (fondo)
        0     // Valor inicial para stencil
    );
}

// ================================================
// MÉTODO: destroy()
// Libera la memoria de la DepthStencilView para evitar fugas.
// ================================================
void
DepthStencilView::destroy() {
    SAFE_RELEASE(m_depthStencilView);
}
