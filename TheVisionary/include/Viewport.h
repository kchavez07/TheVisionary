#pragma once
#include "Prerequisites.h"

// Forward declarations para evitar incluir headers innecesarios en este archivo
class Window;
class DeviceContext;

// ========================================================
// CLASE: Viewport
// El Viewport define el área rectangular de la pantalla donde se dibujará.
// Es como una "ventana de dibujo" dentro del backbuffer.
// ========================================================
class
    Viewport {
public:
    Viewport() = default;
    ~Viewport() = default;

    // ========================================================
    // MÉTODO: init(Window&)
    // Inicializa el viewport usando las dimensiones de la ventana.
    // Normalmente se usa esta versión si ya tienes una instancia de Window.
    // ========================================================
    HRESULT
        init(const Window& window);

    // ========================================================
    // MÉTODO: init(width, height)
    // Inicializa el viewport directamente con dimensiones específicas.
    // Útil para viewports personalizados o en herramientas como editores.
    // ========================================================
    HRESULT
        init(unsigned int width, unsigned int height);

    // ========================================================
    // MÉTODO: update()
    // (Vacío por ahora) Se puede usar más adelante para animar o adaptar el viewport dinámicamente.
    // ========================================================
    void
        update();

    // ========================================================
    // MÉTODO: render()
    // Establece el viewport activo en el pipeline gráfico.
    // Esto le dice a DirectX en qué región de la pantalla debe dibujar.
    // ========================================================
    void
        render(DeviceContext& deviceContext);

    // ========================================================
    // MÉTODO: destroy()
    // Este método queda como placeholder en caso de que más adelante
    // se quiera liberar algo asociado al viewport (por ahora, no es necesario).
    // ========================================================
    void
        destroy();

public:
    // Viewport de DirectX. Contiene info como ancho, alto, profundidad y posición.
    D3D11_VIEWPORT m_viewport;
};
