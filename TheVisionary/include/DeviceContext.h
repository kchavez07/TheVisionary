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
  * establecer vistas, limpiar buffers, y controlar los estados del render.
  * Cada frame puede tener m�ltiples llamadas desde este contexto para definir el comportamiento gr�fico.
  */
class DeviceContext {
public:
    /**
     * @brief Constructor por defecto.
     */
    DeviceContext() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~DeviceContext() = default;

    /**
     * @brief Inicializa el contexto de dispositivo (placeholder).
     */
    void init();

    /**
     * @brief Actualizaci�n por cuadro (placeholder para l�gica futura).
     */
    void update();

    /**
     * @brief M�todo principal de render. Placeholder para emitir comandos de dibujo.
     */
    void render();

    /**
     * @brief Libera el contexto de dispositivo asociado.
     */
    void destroy();

    /**
     * @brief Establece una o varias regiones de pantalla donde se renderizar�.
     *
     * @param NumViewports N�mero de viewports a establecer.
     * @param pViewports Arreglo de estructuras D3D11_VIEWPORT con la informaci�n de cada regi�n.
     */
    void RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

    /**
     * @brief Limpia el buffer de profundidad y/o stencil.
     *
     * @param pDepthStencilView Vista de profundidad a limpiar.
     * @param ClearFlags Flags para definir si se limpia la profundidad, el stencil o ambos.
     * @param Depth Valor de profundidad a asignar.
     * @param Stencil Valor del stencil a asignar.
     */
    void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
        unsigned int ClearFlags,
        float Depth,
        UINT8 Stencil);

    /**
     * @brief Limpia la vista de render con un color determinado.
     *
     * @param pRenderTargetView Vista de render target (por ejemplo, el backbuffer).
     * @param ColorRGBA Color en formato RGBA que se usar� para limpiar.
     */
    void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
        const float ColorRGBA[4]);

    /**
     * @brief Asocia render targets y un depth stencil al pipeline.
     *
     * @param NumViews N�mero de render targets.
     * @param ppRenderTargetViews Arreglo de punteros a vistas de render.
     * @param pDepthStencilView Vista de profundidad a usar.
     */
    void OMSetRenderTargets(unsigned int NumViews,
        ID3D11RenderTargetView* const* ppRenderTargetViews,
        ID3D11DepthStencilView* pDepthStencilView);

public:
    /**
     * @brief Contexto de dispositivo de Direct3D.
     *
     * Este puntero permite emitir comandos gr�ficos al pipeline, como establecer buffers o dibujar geometr�a.
     */
    ID3D11DeviceContext* m_deviceContext = nullptr;
};
