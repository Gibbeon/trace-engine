#include "te/engine.h"
#include "te/win32/win32application.h"

using namespace te;

extern bool_t te::_CreateApplicationImpl(IApplication** pApp, ptr_t pInstance, string_t pszArg)
{
    *pApp = new Win32Application(pInstance, pszArg);
    return *pApp != nullptr;
}
