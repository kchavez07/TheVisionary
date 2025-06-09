#include "Window.h"

// ==============================================
// M�TODO: init()
// Este m�todo inicializa y crea la ventana principal del motor gr�fico.
// Registra la clase de ventana, define su tama�o y la muestra.
// ==============================================
HRESULT Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc) {
    // Guarda el handle de la instancia de la aplicaci�n
    m_hInst = hInstance;

    // Configura los atributos de la clase de ventana
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW; // Redibuja la ventana al redimensionar
    wcex.lpfnWndProc = wndproc;           // Puntero a la funci�n que procesa los mensajes de ventana
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor por defecto
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Fondo blanco
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "TutorialWindowClass"; // Nombre �nico de clase de ventana
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);

    // Registra la clase de ventana con Windows
    if (!RegisterClassEx(&wcex)) {
        MessageBox(nullptr, "RegisterClassEx failed!", "Error", MB_OK);
        ERROR("Window", "init", "CHECK FOR RegisterClassEx");
        return E_FAIL;
    }

    // Define tama�o deseado de la ventana
    RECT rc = { 0, 0, 1200, 1010 }; // �rea cliente (no incluye bordes ni t�tulo)
    m_rect = rc;

    // Ajusta el tama�o para incluir bordes y barra de t�tulo
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // Crea la ventana en el sistema operativo
    m_hWnd = CreateWindow(
        "TutorialWindowClass",           // Clase registrada
        m_windowName.c_str(),            // T�tulo de la ventana
        WS_OVERLAPPEDWINDOW,             // Estilo de ventana
        CW_USEDEFAULT, CW_USEDEFAULT,    // Posici�n inicial
        rc.right - rc.left,              // Ancho ajustado
        rc.bottom - rc.top,              // Alto ajustado
        nullptr, nullptr, hInstance, nullptr);

    // Verifica si la creaci�n fue exitosa
    if (!m_hWnd) {
        MessageBox(nullptr, "CreateWindow failed!", "Error", MB_OK);
        ERROR("Window", "init", "CHECK FOR CreateWindow()");
        return E_FAIL;
    }

    // Muestra la ventana en pantalla y fuerza su actualizaci�n
    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    // Obtiene el �rea �til de la ventana (�rea cliente) y guarda dimensiones
    GetClientRect(m_hWnd, &m_rect);
    m_width = m_rect.right - m_rect.left;
    m_height = m_rect.bottom - m_rect.top;

    return S_OK;
}

// ==============================================
// M�TODO: update()
// Se llamar� cada frame si es necesario. Actualmente est� vac�o.
// Aqu� podr�amos manejar eventos, l�gica de UI, etc.
// ==============================================
void Window::update() {
}

// ==============================================
// M�TODO: render()
// Renderizado de elementos relacionados exclusivamente con la ventana.
// Actualmente no hace nada, ya que el render depende del pipeline gr�fico.
// ==============================================
void Window::render() {
}

// ==============================================
// M�TODO: destroy()
// Se invoca al cerrar la aplicaci�n. Liberar�a recursos propios de la ventana.
// Actualmente no hay nada que liberar expl�citamente.
// ==============================================
void Window::destroy() {
}
