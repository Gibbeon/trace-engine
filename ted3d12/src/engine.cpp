/* #include "te/engine.h"
#include "te/d3d12/renderingengine.h"

using namespace te;

extern bool_t te::_CreateRenderingEngineImpl(IRenderingEngine** pApp, ptr_t pInstance, string_t pszArg)
{
    *pApp = new D3D12RenderingEngine();
    return *pApp != nullptr;
} */

#include "te/engine.h"
#include "te/d3d12/gfxsystem.h"

using namespace te;

bool_t te::_CreateGfxSystemImpl(IGfxSystem** system, GfxSystemDesc& desc)
{
    (*system) = new D3D12System();
    return true;
}