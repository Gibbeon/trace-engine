#include "te/application.h"

using namespace te;

bool_t Application::Init(ptr_t<> pInstance, string_t pszArgs) {
    _instance = pInstance;
    return true;
}

bool_t Application::CreateGfxSystem(IGfxSystem** system, GfxSystemDesc& desc) {
    return _CreateGfxSystemImpl(system, desc);
}

bool_t Application::IsRunning() {
    return true;
}
