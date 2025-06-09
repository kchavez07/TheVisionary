#pragma once
#include "Prerequisites.h"

// Forward declarations para evitar dependencias circulares
class Device;
class DeviceContext;
class Texture;

// ================================================
// CLASE: DepthStencilView
// Esta clase administra una "Depth Stencil View", que se usa
// para el z-buffer (profundidad) y operaciones de stencil (máscara).
// Muy útil para saber qué píxeles deben dibujarse y cuáles no,
// dependiendo de qué tan cerca están de la cámara.
// ================================================
class
    DepthStencilView {
public:
    DepthStencilView() = default;
    ~DepthStencilView() = default;

    // ================================================
    // MÉTODO: init()
    // Inicializa la vista de profundidad y stencil a partir de una textura.
    // Requiere un formato (por ejemplo, DXGI_FORMAT_D24_UNORM_S8_UINT).
    // ================================================
    HRESULT
        init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

    // Métodos de ciclo de vida (vacíos por ahora)
    void update();
    void render(DeviceContext& deviceContext);
    void destroy();

public:
    // Puntero a la interfaz ID3D11DepthStencilView
    ID3D11DepthStencilView* m_depthStencilView = nullptr;
};
