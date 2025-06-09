#pragma once
#include "Prerequisites.h"

//--------------------------------------------------------------
// Clase Device
// Encapsula el dispositivo de Direct3D (ID3D11Device)
// Esta clase es fundamental para crear todos los recursos gráficos
// que necesita el motor, como texturas, buffers, shaders, estados, etc.
//--------------------------------------------------------------
class Device {
public:
    // Constructor por defecto (no hace nada de momento)
    Device() = default;

    // Destructor por defecto (la limpieza se hace manualmente con destroy)
    ~Device() = default;

    // ==========================================================
    // MÉTODO: init()
    // Inicializa el dispositivo si se necesita lógica adicional.
    // Actualmente es un placeholder para extender más adelante.
    // ==========================================================
    void init();

    // ==========================================================
    // MÉTODO: update()
    // Lógica de actualización del dispositivo si llegara a ser necesaria.
    // No se usa comúnmente, pero puede ser útil en ciertos casos.
    // ==========================================================
    void update();

    // ==========================================================
    // MÉTODO: render()
    // Si el dispositivo necesita lógica de render, se puede colocar aquí.
    // Por lo general, esta función se usa más en la clase DeviceContext.
    // ==========================================================
    void render();

    // ==========================================================
    // MÉTODO: destroy()
    // Libera el dispositivo de Direct3D y evita fugas de memoria.
    // Se debe llamar al final del ciclo de vida del motor.
    // ==========================================================
    void destroy();

    // ==========================================================
    // MÉTODO: CreateRenderTargetView()
    // Crea una vista para dibujar en una textura (por lo general, el backbuffer).
    // ==========================================================
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
        const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
        ID3D11RenderTargetView** ppRTView);

    // ==========================================================
    // MÉTODO: CreateTexture2D()
    // Crea una textura 2D que puede usarse como recurso visual o superficie de dibujo.
    // ==========================================================
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Texture2D** ppTexture2D);

    // ==========================================================
    // MÉTODO: CreateDepthStencilView()
    // Crea una vista de profundidad/stencil, necesaria para controlar qué se dibuja delante/detrás.
    // ==========================================================
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
        const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
        ID3D11DepthStencilView** ppDepthStencilView);

    // ==========================================================
    // MÉTODO: CreateVertexShader()
    // Crea un shader de vértices (transformaciones y datos de entrada).
    // ==========================================================
    HRESULT CreateVertexShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11VertexShader** ppVertexShader);

    // ==========================================================
    // MÉTODO: CreateInputLayout()
    // Asocia la estructura de los vértices con el shader de vértices.
    // Sin esto, los datos no se pueden interpretar correctamente.
    // ==========================================================
    HRESULT CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
        unsigned int NumElements,
        const void* pShaderBytecodeWithInputSignature,
        unsigned int BytecodeLength,
        ID3D11InputLayout** ppInputLayout);

    // ==========================================================
    // MÉTODO: CreatePixelShader()
    // Crea un shader de píxeles (última etapa del pipeline, define color final).
    // ==========================================================
    HRESULT CreatePixelShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11PixelShader** ppPixelShader);

    // ==========================================================
    // MÉTODO: CreateBuffer()
    // Crea un buffer genérico (puede ser vertex buffer, index buffer o constant buffer).
    // ==========================================================
    HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Buffer** ppBuffer);

    // ==========================================================
    // MÉTODO: CreateSamplerState()
    // Define cómo se muestrean las texturas (filtrado, wrap, etc.).
    // ==========================================================
    HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
        ID3D11SamplerState** ppSamplerState);

    // ==========================================================
    // MÉTODO: CreateBlendState()
    // Crea un estado de mezcla para manejar transparencia y combinación de colores.
    // ==========================================================
    HRESULT CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
        ID3D11BlendState** ppBlendState);

    // ==========================================================
    // MÉTODO: CreateDepthStencilState()
    // Crea un estado de profundidad/stencil (comparaciones, máscaras, etc.).
    // ==========================================================
    HRESULT CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
        ID3D11DepthStencilState** ppDepthStencilState);

    // ==========================================================
    // MÉTODO: CreateRasterizerState()
    // Define cómo se dibujan los triángulos: relleno, líneas, orientación, etc.
    // ==========================================================
    HRESULT CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
        ID3D11RasterizerState** ppRasterizerState);

public:
    // ==========================================================
    // Variable: m_device
    // El dispositivo de Direct3D. Se usa para crear todos los recursos.
    // Es uno de los objetos más importantes del motor.
    // ==========================================================
    ID3D11Device* m_device = nullptr;
};
