#pragma once 

#include <windows.h>
#include <InitGuid.h>
#include <d3d12.h>
#include <stdio.h>
#include <stdexcept>
#include <dxgi1_4.h>
//#include <D3Dcompiler.h>
//#include <DirectXMath.h>
//#include "d3dx12.h"

#include <string>
//#include <wrl.h>
#include <shellapi.h>
#include "te/engine.h"

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