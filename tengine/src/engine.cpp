#include "te/engine.h"

using namespace te;

bool_t TraceEngine::CreateApplication(IApplication** pApp, ptr_t pInstance, string_t pszArg)
{
    return _CreateApplicationImpl(pApp, pInstance, pszArg);
}

bool_t TraceEngine::Run(IDrawWindow* pWindow)
{
    while(pWindow->ProcessMessages());
    return false;
}

bool_t TraceEngine::CreateRenderingEngine(IRenderingEngine** pRenderEngine, ptr_t pInstance, string_t pszArg)
{
    return _CreateRenderingEngineImpl(pRenderEngine, pInstance, pszArg);
}