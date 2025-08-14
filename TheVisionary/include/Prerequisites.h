/**
 * @file Prerequisites.h
 * @brief Definiciones base, utilidades y tipos comunes para The Visionary Engine.
 */

#pragma once

 // === Librerías STD ===
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <thread>
#include <algorithm>
#undef min
#undef max

// === Librerías DirectX ===
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "resource.h"

// === Librerías de terceros ===
#include "EngineUtilities\Memory\TSharedPointer.h"
#include "EngineUtilities\Memory\TWeakPointer.h"
#include "EngineUtilities\Memory\TStaticPtr.h"
#include "EngineUtilities\Memory\TUniquePtr.h"

// === Macros ===
/** Libera un recurso COM y lo pone a nullptr. */
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

/** Muestra un mensaje de creación de recurso en el depurador. */
#define MESSAGE(classObj, method, state) \
{ std::wostringstream os_; os_ << classObj << "::" << method << " : [CREATION OF RESOURCE : " << state << "]\n"; \
  OutputDebugStringW(os_.str().c_str()); }

/** Muestra un mensaje de error en el depurador. */
#define ERROR(classObj, method, errorMSG) \
{ try { std::wostringstream os_; os_ << L"ERROR : " << classObj << L"::" << method << L" : " << errorMSG << L"\n"; \
  OutputDebugStringW(os_.str().c_str()); } \
  catch (...) { OutputDebugStringW(L"Failed to log error message.\n"); } }

// === Estructuras ===
/** Vértice con posición y coordenadas UV. */
struct SimpleVertex { XMFLOAT3 Pos; XMFLOAT2 Tex; };

/** Buffer constante con matriz de vista. */
struct CBNeverChanges { XMMATRIX mView; };

/** Buffer constante con matriz de proyección. */
struct CBChangeOnResize { XMMATRIX mProjection; };

/** Buffer constante con matriz de mundo y color de malla. */
struct CBChangesEveryFrame { XMMATRIX mWorld; XMFLOAT4 vMeshColor; };

// === Enumeraciones ===
/** Tipos de extensión de texturas soportadas. */
enum ExtensionType { DDS = 0, PNG = 1, JPG = 2 };

/** Tipos de shader soportados. */
enum ShaderType { VERTEX_SHADER = 0, PIXEL_SHADER = 1 };

/** Tipos de componente en el sistema ECS. */
enum ComponentType { NONE = 0, TRANSFORM = 1, MESH = 2, MATERIAL = 3 };
