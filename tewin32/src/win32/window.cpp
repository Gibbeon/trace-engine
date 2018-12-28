#include "te/win32/window.h"
#include "te/win32/application.h"

using namespace te;

Win32Window::Win32Window(ptr_t<> hInstance, uint_t width, uint_t height, string_t pszTitle) :
    m_width(width),
    m_height(height),
    m_title(pszTitle)
{
    // Initialize the window class.
    WNDCLASSEX windowClass = { 0 }; 
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = reinterpret_cast<HINSTANCE>(hInstance.ptr());
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = "Win32Window";
    RegisterClassEx(&windowClass);

    ::RECT windowRect = { 0, 0, static_cast<LONG>(m_width), static_cast<LONG>(m_height) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
    
    // Create the window and store a handle to it.
    this->SetHwnd(CreateWindow(
        windowClass.lpszClassName,
        GetTitle(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        reinterpret_cast<HINSTANCE>(hInstance.ptr()),
        this));

    ShowWindow(m_hWND, SW_SHOWDEFAULT);
}

bool_t Win32Window::ProcessMessages()
{
    MSG msg = {};
    bool_t process = true;
    while (process)
    {
        process = false;
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            process = true; 
        }
    }

    // Return this part of the WM_QUIT message to Windows.
    return static_cast<char>(msg.wParam);
}

void Win32Window::OnRender()
{

}
// Main message handler for the sample.
LRESULT CALLBACK Win32Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Win32Window* pSample = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_CREATE:
        {
            // Save the DXSample* passed in to CreateWindow.
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        }
        return 0;

case WM_PAINT: {
	ValidateRect(hWnd, NULL);
} return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWnd, message, wParam, lParam);
}