#pragma once 

#include "te/d3d12global.h"

namespace te {

class D3D12RenderingEngine : public IRenderingEngine
{
    public:
        D3D12RenderingEngine();

        virtual bool_t CreateDevice(IRenderingDevice** pAdapter);

    private:

};

}