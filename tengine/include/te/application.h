#pragma once

#include "global.h"

namespace te
{

template<class TDescType>
class Builder {
public:
    TDescType& Build() { return _desc; }

protected:
    TDescType _desc;
};

class IDestroyable {
public:
    //  virtual bool_t Destroy();
};


class Viewport {

};

class Camera {

};


class IGfxVertexBuffer : public IDestroyable {
public:
    virtual bool_t Write(void* data, ulong_t offset, ulong_t size)  = 0;
};

struct GfxSystemDesc {
public:
    ptr_t<> hInstance;
};

class GfxSystemDescBuilder : public Builder<GfxSystemDesc> {
public:
    GfxSystemDescBuilder() {
        _desc.hInstance = nullptr;
    } 

    ptr_t<GfxSystemDescBuilder> SetInstance(ptr_t<> instance) { _desc.hInstance = instance; }
};

struct GfxDeviceDesc {

};

class GfxDeviceBuilder : public Builder<GfxDeviceDesc> {
public:

};

class IGfxWindow;
class IGfxCommandList : public IDestroyable {
public:
    virtual bool_t Begin()  = 0;
    virtual bool_t End()  = 0;
    

    virtual bool_t Draw(ptr_t<IGfxVertexBuffer> buffer, ptr_t<IGfxWindow> window) = 0;
};

class IGfxCommandQueue : public IDestroyable {
public:
    virtual bool_t ExecuteCommandList(ptr_t<IGfxCommandList> buffer) = 0;
    virtual bool_t Flush() = 0;
};


class IGfxDevice;
class IGfxWindow : public IDestroyable {
public:
    virtual bool_t SetVisible(bool_t show) = 0;

    virtual bool_t SwapBuffers() = 0;

    virtual bool_t ProcessMessages() = 0;

    virtual IGfxCommandQueue* GetCommandQueue() = 0;

private:
};



struct GfxCommandListDesc {

};

class GfxCommandListBuilder : public Builder<GfxCommandListDesc> {
public:

};

struct GfxCommandQueueDesc {

};

class GfxCommandQueueBuilder : public Builder<GfxCommandQueueDesc> {
public:

};

struct RECT {
    RECT() = default;
    RECT(int_t left, int_t top, int_t width, int_t height) :
        l(left),
        t(top),
        w(width),
        h(height) {
    }
    union {
        struct {
            int_t l, t, w, h;
        };
        int_t array[4];
    };
};

struct WindowDesc {
public:
    RECT bounds;
    string_t title;
    int_t colorDepth;
    int_t bufferCount;
    ptr_t<> hInstance;
};


struct GfxVertexBufferDesc {
public:
    ulong_t size;
};


class IGfxDevice : public IDestroyable {
public:
    virtual bool_t CreateGfxCommandQueue(IGfxCommandQueue** queue, GfxCommandQueueDesc& desc) = 0;
    virtual bool_t CreateGfxCommandList(IGfxCommandList** list, GfxCommandListDesc& desc) = 0;
    virtual bool_t CreateGfxWindow(IGfxWindow**, WindowDesc& desc) = 0;
    virtual bool_t CreateVertexBuffer(IGfxVertexBuffer** buffer, GfxVertexBufferDesc& desc) = 0;
};






class WindowBuilder : public Builder<WindowDesc> {
public:
    WindowBuilder& SetBounds(RECT rect) { _desc.bounds = rect; return *this; }
    WindowBuilder& SetTitle(string_t title) { _desc.title = title; return *this; }
    WindowBuilder& SetColorDepth(int_t colorDepth) { _desc.colorDepth = colorDepth; return *this; }
    WindowBuilder& SetBufferCount(int_t bufferCount) { _desc.bufferCount = bufferCount;  return *this;}

protected:

};




class GfxVertexBufferBuilder : public Builder<GfxVertexBufferDesc> {
public:
    GfxVertexBufferBuilder() {
        _desc.size = 1024 * 1024;
    }
    
    ptr_t<GfxVertexBufferBuilder> SetSize(ulong_t size) { _desc.size = size; return this; }

};

class IGfxSystem : public IDestroyable {
public:
    virtual bool_t CreateDevice(out_ptr_t<IGfxDevice>, GfxDeviceDesc& desc) = 0;
};

class Application {
public:
    bool_t Init(ptr_t<> pInstance, string_t pszArgs);
    bool_t CreateGfxSystem(IGfxSystem** system, GfxSystemDesc& desc);
    bool_t IsRunning();

private:
    ptr_t<> _instance;
};

extern bool_t _CreateGfxSystemImpl(IGfxSystem** system, GfxSystemDesc& desc);

}