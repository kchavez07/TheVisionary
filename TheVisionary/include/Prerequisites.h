#pragma once

// =======================================
// @file Prerequisites.h
// @brief Incluye librer�as esenciales y define macros, estructuras y tipos usados globalmente.
// =======================================

// ------------------------------
// Librer�as est�ndar
// ------------------------------
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <thread>

// ------------------------------
// Librer�as de DirectX
// ------------------------------
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"

// ------------------------------
// Macros �tiles
// ------------------------------

/**
 * @brief Libera un recurso COM de forma segura y lo pone en nullptr.
 */
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

 /**
  * @brief Macro para imprimir mensajes de creaci�n de recursos en la consola de depuraci�n.
  *
  * @param classObj Nombre de la clase desde la que se llama.
  * @param method Nombre del m�todo.
  * @param state Mensaje de estado o descripci�n.
  */
#define MESSAGE(classObj, method, state)                       \
{                                                              \
   std::wostringstream os_;                                    \
   os_ << classObj << "::" << method << " : "                  \
       << "[CREATION OF RESOURCE : " << state << "] \n";       \
   OutputDebugStringW(os_.str().c_str());                      \
}

  /**
   * @brief Macro para imprimir errores con formato en la consola de depuraci�n.
   *
   * @param classObj Nombre de la clase desde la que se llama.
   * @param method Nombre del m�todo.
   * @param errorMSG Mensaje de error.
   */
#define ERROR(classObj, method, errorMSG)                                       \
{                                                                               \
    try {                                                                       \
    std::wostringstream os_;                                                    \
    os_ << L"ERROR : " << classObj << L"::" << method                           \
        << L" : " << errorMSG << L"\n";                                         \
    OutputDebugStringW(os_.str().c_str());                                      \
    } catch (...) {                                                             \
    OutputDebugStringW(L"Failed to log error message.\n");                      \
    }                                                                           \
}

   // ------------------------------
   // Estructuras usadas en shaders y buffers
   // ------------------------------

   /**
    * @struct SimpleVertex
    * @brief Representa un v�rtice simple con posici�n 3D y coordenadas de textura 2D.
    */
struct SimpleVertex {
    XMFLOAT3 Pos;  ///< Posici�n 3D del v�rtice.
    XMFLOAT2 Tex;  ///< Coordenadas de textura (UV).
};

/**
 * @struct CBNeverChanges
 * @brief Contiene la matriz de vista que no cambia entre frames.
 */
struct CBNeverChanges {
    XMMATRIX mView;
};

/**
 * @struct CBChangeOnResize
 * @brief Contiene la matriz de proyecci�n que cambia al redimensionar la ventana.
 */
struct CBChangeOnResize {
    XMMATRIX mProjection;
};

/**
 * @struct CBChangesEveryFrame
 * @brief Contiene informaci�n que cambia cada frame: la matriz del mundo y el color del mesh.
 */
struct CBChangesEveryFrame {
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};

// ------------------------------
// Enumeraciones
// ------------------------------

/**
 * @enum ExtensionType
 * @brief Indica el tipo de extensi�n de imagen que se cargar� como textura.
 */
enum ExtensionType {
    DDS = 0,  ///< Formato DirectDraw Surface.
    PNG = 1,  ///< Formato Portable Network Graphics.
    JPG = 2   ///< Formato Joint Photographic Experts Group.
};
