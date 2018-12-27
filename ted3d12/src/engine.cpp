#include "te/engine.h"
#include "te/d3d12/renderingengine.h"

using namespace te;

extern bool_t te::_CreateRenderingEngineImpl(IRenderingEngine** pApp, ptr_t pInstance, string_t pszArg)
{
    *pApp = new D3D12RenderingEngine();
    return *pApp != nullptr;
}