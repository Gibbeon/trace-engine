#pragma once 

#include "te/win32/global.h"

namespace te {

class Win32Application : public IApplication
{
public:
    Win32Application(ptr_t pInstance, string_t pszArg);

    virtual bool_t CreateDrawWindow(IDrawWindow** pWindow, uint_t width, uint_t height, string_t pszTitle);

    HINSTANCE GetInstance() { return m_hInstance; }


private:
    HINSTANCE m_hInstance;
    IRenderingEngine* m_pRenderer;
};



}