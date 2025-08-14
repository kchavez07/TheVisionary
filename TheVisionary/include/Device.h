/**
 * @file Device.h
 * @brief Encapsula la creación de recursos Direct3D 11.
 */

#pragma once
#include "Prerequisites.h"

 /**
  * @class Device
  * @brief Maneja el dispositivo Direct3D 11 y la creación de recursos gráficos.
  */
class Device {
public:
    /** Constructor por defecto. */
    Device() = default;
    /** Destructor por defecto. */
    ~Device() = default;

    /** Inicializa el dispositivo. */
    void init();
    /** Actualiza el estado del dispositivo. */
    void update();
    /** Renderiza contenido usando el dispositivo. */
    void render();
    /** Libera los recursos del dispositivo. */
    void destroy();

    /** Crea una vista de renderizado (RTV). */
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
        const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
        ID3D11RenderTargetView** ppRTView);

    /** Crea una textura 2D. */
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Texture2D** ppTexture2D);

    /** Crea una vista de depth/stencil. */
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
        const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
        ID3D11DepthStencilView** ppDepthStencilView);

    /** Crea un vertex shader. */
    HRESULT CreateVertexShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11VertexShader** ppVertexShader);

    /** Crea un input layout. */
    HRESULT CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
        unsigned int NumElements,
        const void* pShaderBytecodeWithInputSignature,
        unsigned int BytecodeLength,
        ID3D11InputLayout** ppInputLayout);

    /** Crea un pixel shader. */
    HRESULT CreatePixelShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11PixelShader** ppPixelShader);

    /** Crea un buffer. */
    HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Buffer** ppBuffer);

    /** Crea un estado de muestreo (sampler). */
    HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
        ID3D11SamplerState** ppSamplerState);

    /** Crea un estado de mezcla (blend). */
    HRESULT CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
        ID3D11BlendState** ppBlendState);

    /** Crea un estado de depth/stencil. */
    HRESULT CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
        ID3D11DepthStencilState** ppDepthStencilState);

    /** Crea un estado de rasterizado. */
    HRESULT CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
        ID3D11RasterizerState** ppRasterizerState);

public:
    ID3D11Device* m_device = nullptr; ///< Puntero al dispositivo Direct3D 11.
};
