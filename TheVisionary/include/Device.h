#pragma once
#include "Prerequisites.h"

/**
 * @file Device.h
 * @class Device
 * @brief Encapsula el dispositivo principal de Direct3D (ID3D11Device).
 *
 * Esta clase es esencial para la creación de recursos gráficos como shaders,
 * texturas, buffers, estados y vistas. Su propósito es centralizar todas
 * las llamadas al API para generar recursos del motor.
 */
class Device {
public:
    /**
     * @brief Constructor por defecto.
     */
    Device() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~Device() = default;

    /**
     * @brief Inicializa el dispositivo si se requiere lógica adicional.
     */
    void init();

    /**
     * @brief Actualiza el dispositivo (placeholder).
     */
    void update();

    /**
     * @brief Renderiza el dispositivo (placeholder).
     */
    void render();

    /**
     * @brief Libera los recursos asociados al dispositivo.
     */
    void destroy();

    /**
     * @brief Crea una vista de renderizado desde un recurso.
     * @param pResource Recurso base (como textura).
     * @param pDesc Descripción de la vista.
     * @param ppRTView Resultado: puntero a la vista creada.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
        const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
        ID3D11RenderTargetView** ppRTView);

    /**
     * @brief Crea una textura 2D.
     * @param pDesc Descripción de la textura.
     * @param pInitialData Datos iniciales (opcional).
     * @param ppTexture2D Resultado: puntero a la textura creada.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Texture2D** ppTexture2D);

    /**
     * @brief Crea una vista de profundidad y stencil.
     * @param pResource Recurso base (textura con soporte de profundidad).
     * @param pDesc Descripción de la vista.
     * @param ppDepthStencilView Resultado: puntero a la vista creada.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
        const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
        ID3D11DepthStencilView** ppDepthStencilView);

    /**
     * @brief Crea un shader de vértices.
     * @param pShaderBytecode Bytecode del shader.
     * @param BytecodeLength Tamaño del bytecode.
     * @param pClassLinkage Opcional: soporte para herencia de shaders.
     * @param ppVertexShader Resultado: puntero al shader creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateVertexShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11VertexShader** ppVertexShader);

    /**
     * @brief Crea un Input Layout para definir cómo se leen los vértices.
     * @param pInputElementDescs Descripción del layout.
     * @param NumElements Número de elementos en el layout.
     * @param pShaderBytecodeWithInputSignature Bytecode con firma de entrada.
     * @param BytecodeLength Tamaño del bytecode.
     * @param ppInputLayout Resultado: puntero al layout creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
        unsigned int NumElements,
        const void* pShaderBytecodeWithInputSignature,
        unsigned int BytecodeLength,
        ID3D11InputLayout** ppInputLayout);

    /**
     * @brief Crea un shader de píxeles.
     * @param pShaderBytecode Bytecode del shader.
     * @param BytecodeLength Tamaño del bytecode.
     * @param pClassLinkage Opcional: soporte para herencia de shaders.
     * @param ppPixelShader Resultado: puntero al shader creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreatePixelShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11PixelShader** ppPixelShader);

    /**
     * @brief Crea un buffer (vertex, index o constant).
     * @param pDesc Descripción del buffer.
     * @param pInitialData Datos iniciales (opcional).
     * @param ppBuffer Resultado: puntero al buffer creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Buffer** ppBuffer);

    /**
     * @brief Crea un Sampler State (modo de muestreo para texturas).
     * @param pSamplerDesc Descripción del muestreo.
     * @param ppSamplerState Resultado: puntero al estado creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
        ID3D11SamplerState** ppSamplerState);

    /**
     * @brief Crea un Blend State (modo de mezcla para transparencia).
     * @param pBlendStateDesc Descripción de la mezcla.
     * @param ppBlendState Resultado: puntero al estado creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
        ID3D11BlendState** ppBlendState);

    /**
     * @brief Crea un Depth Stencil State (modo de pruebas de profundidad).
     * @param pDepthStencilDesc Descripción del estado.
     * @param ppDepthStencilState Resultado: puntero al estado creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
        ID3D11DepthStencilState** ppDepthStencilState);

    /**
     * @brief Crea un Rasterizer State (modo de dibujo de triángulos).
     * @param pRasterizerDesc Descripción del rasterizado.
     * @param ppRasterizerState Resultado: puntero al estado creado.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
        ID3D11RasterizerState** ppRasterizerState);

    /**
     * @brief Puntero al dispositivo de Direct3D.
     *
     * Se utiliza para crear todos los recursos gráficos del motor.
     */
    ID3D11Device* m_device = nullptr;
};
