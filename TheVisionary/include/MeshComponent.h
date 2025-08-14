#pragma once
#include "Prerequisites.h"
#include "ECS\Component.h"

class DeviceContext;

/**
 * @class MeshComponent
 * @brief Componente ECS que almacena y gestiona los datos de una malla.
 *
 * @details
 * Contiene la informaci�n de v�rtices e �ndices para renderizado.
 * No realiza operaciones gr�ficas por s� mismo, sino que expone
 * los datos para que otras partes del motor los utilicen.
 */
class MeshComponent : public Component {
public:
    /**
     * @brief Constructor por defecto.
     */
    MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

    /**
     * @brief Destructor por defecto.
     */
    virtual ~MeshComponent() = default;

    /**
     * @brief Inicializa el componente (actualmente no realiza operaciones).
     */
    void init() override {}

    /**
     * @brief Actualiza el componente (actualmente no realiza operaciones).
     * @param deltaTime Tiempo transcurrido desde la �ltima actualizaci�n.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente (actualmente no realiza operaciones).
     * @param deviceContext Contexto del dispositivo de render.
     */
    void render(DeviceContext& deviceContext) override {}

    /**
     * @brief Libera recursos asociados (actualmente no realiza operaciones).
     */
    void destroy() override {}

public:
    std::string m_name;                  ///< Nombre de la malla.
    std::vector<SimpleVertex> m_vertex;   ///< Lista de v�rtices.
    std::vector<unsigned int> m_index;    ///< Lista de �ndices.
    int m_numVertex;                      ///< N�mero de v�rtices.
    int m_numIndex;                       ///< N�mero de �ndices.
};
