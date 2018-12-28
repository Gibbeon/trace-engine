/* #include "te/win32/application.h"
#include "te/win32/window.h"

using namespace te;

Win32Application::Win32Application(ptr_t pInstance, string_t pszArg)
{
    m_hInstance = reinterpret_cast<HINSTANCE>(pInstance);
    if(FAILED(TraceEngine::CreateRenderingEngine(&m_pRenderer, pInstance, pszArg)))
        throw "Unable to create rendering engine";
}

bool_t Win32Application::CreateDrawWindow(IDrawWindow** pWindow, uint_t width, uint_t height, string_t pszTitle)
{
    *pWindow = new Win32Window(this, width, height, pszTitle);
    
    return true;
}
 */