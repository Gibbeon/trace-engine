/* #pragma once

#include "global.h"

namespace te
{

class IRenderingDevice;
class IDrawWindow {
public:
    virtual bool_t Show() = 0;
    virtual bool_t Hide() = 0;
    
    virtual bool_t ProcessMessages() = 0;

    virtual void OnInit() = 0;
    virtual void OnDestroy() = 0;
    virtual void OnRender() = 0;
    virtual void OnUpdate() = 0;

    // Accessors.
    virtual uint_t GetWidth() const         { return m_width; }
    virtual uint_t GetHeight() const        { return m_height; }
    virtual string_t GetTitle() const       { return m_title; }

    
        virtual void SetRenderingDevice(IRenderingDevice* device) { m_device = device; }


    IRenderingDevice* m_device;
 private:
    string_t m_title;
    uint_t m_width;
    uint_t m_height;
    
};
  
class IApplication {
public:
    virtual bool_t CreateDrawWindow(IDrawWindow** pWindow, uint_t width, uint_t height, string_t pszTitle) = 0;
};

class IRenderingDevice {
public:
        virtual bool_t Attach(IDrawWindow* pWindow) = 0;
        virtual bool_t SwapBuffers() = 0;
};

class IRenderingEngine {
public:
        virtual bool_t CreateDevice(IRenderingDevice** pAdapter) = 0;
};


class TraceEngine {
public:
    static bool_t CreateApplication(IApplication** pApp, ptr_t pInstance, string_t pszArg);
    static bool_t CreateRenderingEngine(IRenderingEngine** pRenderEngine, ptr_t pInstance, string_t pszArg);
    static bool_t Run(IDrawWindow* main);
};

extern bool_t _CreateApplicationImpl(IApplication** pApp, ptr_t pInstance, string_t pszArg);
extern bool_t _CreateRenderingEngineImpl(IRenderingEngine** pApp, ptr_t pInstance, string_t pszArg);

} */

#include "te/application.h"