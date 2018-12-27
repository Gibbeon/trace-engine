#pragma once 

#include "te/gl/global.h"

namespace te {

class GLRenderingEngine : public IRenderingEngine
{
    public:
        GLRenderingEngine(ptr_t);

        virtual bool_t CreateDevice(IRenderingDevice** pAdapter);
    private:
        ptr_t m_pInstance;

};


}