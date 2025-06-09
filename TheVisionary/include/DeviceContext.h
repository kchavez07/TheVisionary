#pragma once
#include "Prerequisites.h"

// ==============================================
// Clase: DeviceContext
// Esta clase encapsula el contexto de dispositivo de Direct3D,
// responsable de emitir comandos al pipeline gráfico como:
// establecer vistas, limpiar buffers, y renderizar.
// ==============================================
class DeviceContext {
public:
    DeviceContext() = default;
    ~DeviceContext() = default;

    // Inicializa el contexto de dispositivo (si aplica lógica propia)
    void init();

    // Método llamado por frame para lógica interna
    void update();

    // Método principal de renderizado del contexto
    void render();

    // Libera el recurso m_deviceContext
    void destroy();

    // ==============================================
    // MÉTODO: RSSetViewports
    // Define las regiones de la pantalla donde se dibujará.
    // Se puede usar para dividir la pantalla en múltiples áreas de renderizado.
    // ==============================================
    void RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

    // ==============================================
    // MÉTODO: ClearDepthStencilView
    // Limpia el buffer de profundidad y/o stencil antes del renderizado de un nuevo frame.
    // El parámetro ClearFlags indica si se limpia profundidad, stencil o ambos.
    // ==============================================
    void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
        unsigned int ClearFlags,
        float Depth,
        UINT8 Stencil);

    // ==============================================
    // MÉTODO: ClearRenderTargetView
    // Limpia el render target (por ejemplo el backbuffer) con un color definido por ColorRGBA.
    // Se suele hacer al inicio de cada frame.
    // ==============================================
    void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
        const float ColorRGBA[4]);

    // ==============================================
    // MÉTODO: OMSetRenderTargets
    // Asocia uno o más render targets (color) y un depth stencil (profundidad)
    // al pipeline de renderizado.
    // Es obligatorio antes de dibujar algo.
    // ==============================================
    void OMSetRenderTargets(unsigned int NumViews,
        ID3D11RenderTargetView* const* ppRenderTargetViews,
        ID3D11DepthStencilView* pDepthStencilView);

public:
    // Puntero al contexto de dispositivo, usado para emitir comandos al pipeline gráfico
    ID3D11DeviceContext* m_deviceContext = nullptr;
};
