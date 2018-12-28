#include "te/engine.h"
#include "te/d3d12/global.h"

namespace te {

class D3D12System : public IGfxSystem {
    virtual bool_t CreateDevice(out_ptr_t<IGfxDevice>, GfxDeviceDesc& desc);
};

}