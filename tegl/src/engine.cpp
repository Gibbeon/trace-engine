#include "te/engine.h"
#include "te/gl/renderingengine.h"

using namespace te;

extern bool_t te::_CreateRenderingEngineImpl(IRenderingEngine** pApp, ptr_t pInstance, string_t pszArg)
{
    *pApp = new GLRenderingEngine(pInstance);
    return *pApp != nullptr;
}