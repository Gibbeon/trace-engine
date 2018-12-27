#include "te/gl/renderingengine.h"
#include "te/gl/renderingdevice.h"

using namespace te;

GLRenderingEngine::GLRenderingEngine(ptr_t pInstance) :
    m_pInstance(pInstance)
{

}

bool_t GLRenderingEngine::CreateDevice(IRenderingDevice** pAdapter)
{
    (*pAdapter) = new GLRenderingDevice();
    reinterpret_cast<GLRenderingDevice*>(*pAdapter)->InitializeExtensions(m_pInstance);
    return true;
}



