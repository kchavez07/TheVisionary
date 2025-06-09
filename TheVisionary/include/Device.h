#pragma once
#include "Prerequisites.h"

//--------------------------------------------------------------
// Clase Device
// Encapsula el dispositivo de Direct3D (ID3D11Device)
// Esta clase es fundamental para crear todos los recursos gr�ficos
// que necesita el motor, como texturas, buffers, shaders, estados, etc.
//--------------------------------------------------------------
class Device {
public:
    // Constructor por defecto (no hace nada de momento)
    Device() = default;

    // Destructor por defecto (la limpieza se hace manualmente con destroy)
    ~Device() = default;

    // ==========================================================
    // M�TODO: init()
    // Inicializa el dispositivo si se necesita l�gica adicional.
    // Actualmente es un placeholder para extender m�s adelante.
    // ==========================================================
    void init();

    // ==========================================================
    // M�TODO: update()
    // L�gica de actualizaci�n del dispositivo si llegara a ser necesaria.
    // No se usa com�nmente, pero puede ser �til en ciertos casos.
    // ==========================================================
    void update();

    // ==========================================================
    // M�TODO: render()
    // Si el dispositivo necesita l�gica de render, se puede colocar aqu�.
    // Por lo general, esta funci�n se usa m�s en la clase DeviceContext.
    // ==========================================================
    void render();

    // ==========================================================
    // M�TODO: destroy()
    // Libera el dispositivo de Direct3D y evita fugas de memoria.
    // Se debe llamar al final del ciclo de vida del motor.
    // ==========================================================
    void destroy();

    // ==========================================================
    // M�TODO: CreateRenderTargetView()
    // Crea una vista para dibujar en una textura (por lo general, el backbuffer).
    // ==========================================================
    HRESULT CreateRenderTargetView(ID3D11Resource* pResource,
        const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
        ID3D11RenderTargetView** ppRTView);

    // ==========================================================
    // M�TODO: CreateTexture2D()
    // Crea una textura 2D que puede usarse como recurso visual o superficie de dibujo.
    // ==========================================================
    HRESULT CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Texture2D** ppTexture2D);

    // ==========================================================
    // M�TODO: CreateDepthStencilView()
    // Crea una vista de profundidad/stencil, necesaria para controlar qu� se dibuja delante/detr�s.
    // ==========================================================
    HRESULT CreateDepthStencilView(ID3D11Resource* pResource,
        const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
        ID3D11DepthStencilView** ppDepthStencilView);

    // ==========================================================
    // M�TODO: CreateVertexShader()
    // Crea un shader de v�rtices (transformaciones y datos de entrada).
    // ==========================================================
    HRESULT CreateVertexShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11VertexShader** ppVertexShader);

    // ==========================================================
    // M�TODO: CreateInputLayout()
    // Asocia la estructura de los v�rtices con el shader de v�rtices.
    // Sin esto, los datos no se pueden interpretar correctamente.
    // ==========================================================
    HRESULT CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
        unsigned int NumElements,
        const void* pShaderBytecodeWithInputSignature,
        unsigned int BytecodeLength,
        ID3D11InputLayout** ppInputLayout);

    // ==========================================================
    // M�TODO: CreatePixelShader()
    // Crea un shader de p�xeles (�ltima etapa del pipeline, define color final).
    // ==========================================================
    HRESULT CreatePixelShader(const void* pShaderBytecode,
        unsigned int BytecodeLength,
        ID3D11ClassLinkage* pClassLinkage,
        ID3D11PixelShader** ppPixelShader);

    // ==========================================================
    // M�TODO: CreateBuffer()
    // Crea un buffer gen�rico (puede ser vertex buffer, index buffer o constant buffer).
    // ==========================================================
    HRESULT CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
        const D3D11_SUBRESOURCE_DATA* pInitialData,
        ID3D11Buffer** ppBuffer);

    // ==========================================================
    // M�TODO: CreateSamplerState()
    // Define c�mo se muestrean las texturas (filtrado, wrap, etc.).
    // ==========================================================
    HRESULT CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
        ID3D11SamplerState** ppSamplerState);

    // ==========================================================
    // M�TODO: CreateBlendState()
    // Crea un estado de mezcla para manejar transparencia y combinaci�n de colores.
    // ==========================================================
    HRESULT CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
        ID3D11BlendState** ppBlendState);

    // ==========================================================
    // M�TODO: CreateDepthStencilState()
    // Crea un estado de profundidad/stencil (comparaciones, m�scaras, etc.).
    // ==========================================================
    HRESULT CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc,
        ID3D11DepthStencilState** ppDepthStencilState);

    // ==========================================================
    // M�TODO: CreateRasterizerState()
    // Define c�mo se dibujan los tri�ngulos: relleno, l�neas, orientaci�n, etc.
    // ==========================================================
    HRESULT CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
        ID3D11RasterizerState** ppRasterizerState);

public:
    // ==========================================================
    // Variable: m_device
    // El dispositivo de Direct3D. Se usa para crear todos los recursos.
    // Es uno de los objetos m�s importantes del motor.
    // ==========================================================
    ID3D11Device* m_device = nullptr;
};
