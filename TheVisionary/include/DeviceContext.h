/**
 * @file DeviceContext.h
 * @brief Declaraci�n de la clase DeviceContext.
 */

#pragma once
#include "Prerequisites.h"

 /**
  * @class DeviceContext
  * @brief Encapsula el contexto de dispositivo de Direct3D 11.
  *
  * Esta clase es responsable de emitir comandos gr�ficos al pipeline:
  * establecer vistas, limpiar buffers y controlar los estados del render.
  * Cada frame puede tener m�ltiples llamadas desde este contexto
  * para definir el comportamiento gr�fico.
  */
class DeviceContext {
public:
    /** Constructor por defecto. */
    DeviceContext() = default;

    /** Destructor por defecto. */
    ~DeviceContext() = default;

    // ===== Ciclo de vida =====

    /** Inicializa el contexto de dispositivo. */
    void init();

    /** Actualiza l�gica por frame (placeholder). */
    void update();

    /** Ejecuta comandos de render por frame (placeholder). */
    void render();

    /** Libera el contexto de dispositivo. */
    void destroy();

    /** Limpia el estado actual del contexto de render. */
    void clearState();

    /** Libera el contexto de dispositivo y pone el puntero en nullptr. */
    void release();

    // ===== Comandos gr�ficos =====

    /** Establece las regiones de viewport para el render. */
    void RSSetViewports(unsigned int numViewports, const D3D11_VIEWPORT* pViewports);

    /** Limpia el depth-stencil view. */
    void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
        unsigned int clearFlags,
        float depth,
        UINT8 stencil);

    /** Limpia un render target con el color especificado. */
    void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
        const float colorRGBA[4]);

    /** Establece los render targets y el depth stencil. */
    void OMSetRenderTargets(unsigned int numViews,
        ID3D11RenderTargetView* const* ppRenderTargetViews,
        ID3D11DepthStencilView* pDepthStencilView);

    /** Define la topolog�a de la geometr�a para el input assembler. */
    void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);

    /** Asigna texturas al shader de p�xeles. */
    void PSSetShaderResources(UINT startSlot,
        UINT numViews,
        ID3D11ShaderResourceView* const* ppSRVs);

    /** Asigna estados de muestreo al shader de p�xeles. */
    void PSSetSamplers(UINT startSlot,
        UINT numSamplers,
        ID3D11SamplerState* const* ppSamplers);

    /** Dibuja geometr�a usando �ndices. */
    void DrawIndexed(UINT indexCount,
        UINT startIndexLocation,
        INT baseVertexLocation);

public:
    /**
     * @brief Puntero crudo al contexto de Direct3D 11 (debe estar encapsulado por m�todos).
     */
    ID3D11DeviceContext* m_deviceContext = nullptr;
};
