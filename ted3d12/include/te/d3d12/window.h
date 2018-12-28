#include "te/engine.h"
#include "te/d3d12/global.h"

namespace te {

class Win32Window;
class D3D12CommandQueue;

class D3D12Device;
class D3D12Window : public IGfxWindow {
public:
    D3D12Window(D3D12Device* device, Win32Window* window);

    virtual bool_t SetVisible(bool_t show);
    virtual bool_t SwapBuffers();

    ptr_t<IGfxDevice> GetGfxDevice() { return _device; }
    ID3D12Resource* GetActiveRenderTarget() { return (_renderTargets[_frameIndex]); }
    D3D12_CPU_DESCRIPTOR_HANDLE GetActiveHandle();
    virtual IGfxCommandQueue* GetCommandQueue();

    virtual bool_t ProcessMessages();

private:
    ptr_t<IGfxDevice> _device;

private:
    Win32Window* _window;

    IDXGISwapChain3* _swapChain;
    ID3D12DescriptorHeap* _rtvHeap;
    ID3D12Resource* _renderTargets[2];
    uint_t _rtvDescriptorSize;
    uint_t _frameIndex;
    D3D12CommandQueue* _commandQueue;

    HANDLE _fenceEvent;
    ID3D12Fence* _fence;
    uint_t _fenceValue;
};

}