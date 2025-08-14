#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;
class MeshComponent;

/**
 * @class Buffer
 * @brief Encapsula un recurso de buffer en Direct3D 11.
 *
 * @details
 * Puede representar diferentes tipos de buffers como:
 * - Vertex Buffer
 * - Index Buffer
 * - Constant Buffer
 *
 * Administra la creación, actualización, uso en render y liberación del recurso.
 */
class Buffer {
public:
    /**
     * @brief Constructor por defecto.
     */
    Buffer() = default;

    /**
     * @brief Destructor por defecto.
     */
    ~Buffer() = default;

    /**
     * @brief Inicializa un Vertex o Index Buffer a partir de una malla.
     * @param device Referencia al dispositivo de render.
     * @param mesh Datos de la malla (vértices e índices).
     * @param bindFlag Tipo de enlace del buffer (D3D11_BIND_VERTEX_BUFFER o D3D11_BIND_INDEX_BUFFER).
     * @return HRESULT indicando éxito o error.
     */
    HRESULT init(Device& device, const MeshComponent& mesh, unsigned int bindFlag);

    /**
     * @brief Inicializa un Constant Buffer vacío.
     * @param device Referencia al dispositivo de render.
     * @param ByteWidth Tamaño en bytes del buffer.
     * @return HRESULT indicando éxito o error.
     */
    HRESULT init(Device& device, unsigned int ByteWidth);

    /**
     * @brief Actualiza el contenido de un Constant Buffer en memoria.
     * @param deviceContext Contexto del dispositivo.
     * @param pDstResource Recurso destino.
     * @param DstSubresource Índice de subrecurso.
     * @param pDstBox Región de destino (opcional).
     * @param pSrcData Puntero a los datos fuente.
     * @param SrcRowPitch Tamaño de fila en bytes.
     * @param SrcDepthPitch Tamaño de profundidad en bytes.
     */
    void update(DeviceContext& deviceContext,
        ID3D11Resource* pDstResource,
        unsigned int DstSubresource,
        const D3D11_BOX* pDstBox,
        const void* pSrcData,
        unsigned int SrcRowPitch,
        unsigned int SrcDepthPitch);

    /**
     * @brief Establece el buffer para su uso en el pipeline de render.
     * @param deviceContext Contexto del dispositivo.
     * @param StartSlot Posición inicial del buffer.
     * @param NumBuffers Número de buffers a establecer.
     * @param setPixelShader Si es true, asigna también al Pixel Shader.
     * @param format Formato del índice (solo para Index Buffers).
     */
    void render(DeviceContext& deviceContext,
        unsigned int StartSlot,
        unsigned int NumBuffers,
        bool setPixelShader = false,
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN);

    /**
     * @brief Libera el recurso del buffer.
     */
    void destroy();

    /**
     * @brief Crea un buffer de Direct3D 11 con una descripción y datos iniciales.
     * @param device Referencia al dispositivo.
     * @param desc Descripción del buffer.
     * @param initData Datos iniciales (puede ser nullptr).
     * @return HRESULT indicando éxito o error.
     */
    HRESULT createBuffer(Device& device,
        D3D11_BUFFER_DESC& desc,
        D3D11_SUBRESOURCE_DATA* initData);

private:
    ID3D11Buffer* m_buffer = nullptr; ///< Puntero al recurso de buffer.
    unsigned int m_stride = 0;        ///< Tamaño de cada elemento (para Vertex Buffers).
    unsigned int m_offset = 0;        ///< Desplazamiento inicial.
    unsigned int m_bindFlag = 0;      ///< Tipo de enlace del buffer.
};
