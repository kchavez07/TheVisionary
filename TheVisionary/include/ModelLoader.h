#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

/**
 * @class ModelLoader
 * @brief Carga y procesa modelos 3D en formatos OBJ y FBX.
 *
 * @details
 * Ofrece funciones para leer geometría, materiales y texturas
 * desde archivos, generando componentes de malla listos para render.
 */
class ModelLoader {
public:
    /** @brief Constructor por defecto. */
    ModelLoader() = default;

    /** @brief Destructor por defecto. */
    ~ModelLoader() = default;

    /**
     * @brief Carga un modelo en formato OBJ.
     * @param filePath Ruta del archivo OBJ.
     * @return Un componente de malla con la geometría cargada.
     */
    MeshComponent LoadOBJModel(const std::string& filePath);

    /**
     * @brief Inicializa el administrador de FBX SDK.
     * @return true si la inicialización fue exitosa.
     */
    bool InitializeFBXManager();

    /**
     * @brief Carga un modelo en formato FBX.
     * @param filePath Ruta del archivo FBX.
     * @return true si el modelo se cargó correctamente.
     */
    bool LoadFBXModel(const std::string& filePath);

    /**
     * @brief Procesa un nodo de la escena FBX.
     * @param node Puntero al nodo FBX.
     */
    void ProcessFBXNode(FbxNode* node);

    /**
     * @brief Procesa una malla de un nodo FBX.
     * @param node Puntero al nodo que contiene la malla.
     */
    void ProcessFBXMesh(FbxNode* node);

    /**
     * @brief Procesa los materiales de un modelo FBX.
     * @param material Puntero al material FBX.
     */
    void ProcessFBXMaterials(FbxSurfaceMaterial* material);

    /**
     * @brief Obtiene los nombres de archivos de texturas.
     * @return Lista de nombres de archivos de texturas.
     */
    std::vector<std::string> GetTextureFileNames() const { return textureFileNames; }

private:
    FbxManager* lSdkManager = nullptr; ///< Administrador de FBX SDK.
    FbxScene* lScene = nullptr;        ///< Escena FBX cargada.
    std::vector<std::string> textureFileNames; ///< Lista de texturas extraídas.

public:
    std::string modelName; ///< Nombre del modelo cargado.
    std::vector<MeshComponent> meshes; ///< Mallas cargadas.
};
