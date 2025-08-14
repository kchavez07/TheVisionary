/**
 * @file DeviceContext.h
 * @brief Encapsula el contexto de dispositivo Direct3D 11 para The Visionary Engine.
 */

#pragma once
#include "Prerequisites.h"

 /**
  * @class DeviceContext
  * @brief Maneja las operaciones de render y configuración del pipeline gráfico.
  */
class DeviceContext {
public:
    /** Constructor por defecto. */
    DeviceContext() = default;
    /** Destructor por defecto. */
    ~DeviceContext() = default;

    /** Inicializa el contexto. */
    void init();
    /** Actualiza el estado del contexto. */
    void update();
    /** Ejecuta el render. */
    void render();
    /** Libera los recursos. */
    void destroy();

    /** Configura el/los viewport(s). */
    void RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

    /** Asigna texturas a un pixel shader. */
    void PSSetShaderResources(unsigned int StartSlot,
        unsigned int NumViews,
        ID3D11ShaderResourceView* const* ppShaderResourceViews);

    /** Define el input layout. */
    void IASetInputLayout(ID3D11InputLayout* pInputLayout);

    /** Asigna el vertex shader. */
    void VSSetShader(ID3D11VertexShader* pVertexShader,
        ID3D11ClassInstance* const* ppClassInstances,
        unsigned int NumClassInstances);

    /** Asigna el pixel shader. */
    void PSSetShader(ID3D11PixelShader* pPixelShader,
        ID3D11ClassInstance* const* ppClassInstances,
        unsigned int NumClassInstances);

    /** Actualiza un recurso en GPU. */
    void UpdateSubresource(ID3D11Resource* pDstResource,
        unsigned int DstSubresource,
        const D3D11_BOX* pDstBox,
        const void* pSrcData,
        unsigned int SrcRowPitch,
        unsigned int SrcDepthPitch);

    /** Asigna los vertex buffers. */
    void IASetVertexBuffers(unsigned int StartSlot,
        unsigned int NumBuffers,
        ID3D11Buffer* const* ppVertexBuffers,
        const unsigned int* pStrides,
        const unsigned int* pOffsets);

    /** Asigna el index buffer. */
    void IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
        DXGI_FORMAT Format,
        unsigned int Offset);

    /** Configura los samplers para el pixel shader. */
    void PSSetSamplers(unsigned int StartSlot,
        unsigned int NumSamplers,
        ID3D11SamplerState* const* ppSamplers);

    /** Define el rasterizer state. */
    void RSSetState(ID3D11RasterizerState* pRasterizerState);

    /** Define el blend state. */
    void OMSetBlendState(ID3D11BlendState* pBlendState,
        const float BlendFactor[4],
        unsigned int SampleMask);

    /** Asigna render targets y depth stencil. */
    void OMSetRenderTargets(unsigned int NumViews,
        ID3D11RenderTargetView* const* ppRenderTargetViews,
        ID3D11DepthStencilView* pDepthStencilView);

    /** Define la topología de primitivas. */
    void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

    /** Limpia un render target view. */
    void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
        const float ColorRGBA[4]);

    /** Limpia un depth stencil view. */
    void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
        unsigned int ClearFlags,
        float Depth,
        UINT8 Stencil);

    /** Asigna constant buffers para vertex shader. */
    void VSSetConstantBuffers(unsigned int StartSlot,
        unsigned int NumBuffers,
        ID3D11Buffer* const* ppConstantBuffers);

    /** Asigna constant buffers para pixel shader. */
    void PSSetConstantBuffers(unsigned int StartSlot,
        unsigned int NumBuffers,
        ID3D11Buffer* const* ppConstantBuffers);

    /** Dibuja usando índices. */
    void DrawIndexed(unsigned int IndexCount,
        unsigned int StartIndexLocation,
        int BaseVertexLocation);

public:
    ID3D11DeviceContext* m_deviceContext = nullptr; ///< Puntero al contexto de dispositivo.
};
