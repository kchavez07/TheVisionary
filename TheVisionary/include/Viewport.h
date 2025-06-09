#pragma once
#include "Prerequisites.h"

// Forward declarations para evitar incluir headers innecesarios en este archivo
class Window;
class DeviceContext;

// ========================================================
// CLASE: Viewport
// El Viewport define el �rea rectangular de la pantalla donde se dibujar�.
// Es como una "ventana de dibujo" dentro del backbuffer.
// ========================================================
class
    Viewport {
public:
    Viewport() = default;
    ~Viewport() = default;

    // ========================================================
    // M�TODO: init(Window&)
    // Inicializa el viewport usando las dimensiones de la ventana.
    // Normalmente se usa esta versi�n si ya tienes una instancia de Window.
    // ========================================================
    HRESULT
        init(const Window& window);

    // ========================================================
    // M�TODO: init(width, height)
    // Inicializa el viewport directamente con dimensiones espec�ficas.
    // �til para viewports personalizados o en herramientas como editores.
    // ========================================================
    HRESULT
        init(unsigned int width, unsigned int height);

    // ========================================================
    // M�TODO: update()
    // (Vac�o por ahora) Se puede usar m�s adelante para animar o adaptar el viewport din�micamente.
    // ========================================================
    void
        update();

    // ========================================================
    // M�TODO: render()
    // Establece el viewport activo en el pipeline gr�fico.
    // Esto le dice a DirectX en qu� regi�n de la pantalla debe dibujar.
    // ========================================================
    void
        render(DeviceContext& deviceContext);

    // ========================================================
    // M�TODO: destroy()
    // Este m�todo queda como placeholder en caso de que m�s adelante
    // se quiera liberar algo asociado al viewport (por ahora, no es necesario).
    // ========================================================
    void
        destroy();

public:
    // Viewport de DirectX. Contiene info como ancho, alto, profundidad y posici�n.
    D3D11_VIEWPORT m_viewport;
};
