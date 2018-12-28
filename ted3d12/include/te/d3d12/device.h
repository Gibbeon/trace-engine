#include "te/engine.h"
#include "te/d3d12/global.h"

namespace te {

class D3D12Device : public IGfxDevice {
public:
    D3D12Device(IDXGIFactory4*, IDXGIAdapter1*, ID3D12Device*);
    
    virtual bool_t CreateGfxCommandQueue(IGfxCommandQueue** queue, GfxCommandQueueDesc& desc);
    virtual bool_t CreateGfxCommandList(IGfxCommandList** list, GfxCommandListDesc& desc);

    virtual bool_t CreateGfxWindow(IGfxWindow**, WindowDesc& desc);

    virtual bool_t CreateVertexBuffer(IGfxVertexBuffer** buffer, GfxVertexBufferDesc& desc);

    ID3D12Device* GetID3DDevice() { return _device; }
    IDXGIAdapter1* GetIDXGIAdapter() { return _adapter; }
    IDXGIFactory4* GetIDXGIFactory() { return _factory; }
protected:
    bool_t InitRootSignature();
    bool_t InitPipelineState();

private:
    IDXGIFactory4*  _factory;
    IDXGIAdapter1*  _adapter;
    ID3D12Device*   _device;

    ID3D12RootSignature* _rootSignature;
    ID3D12PipelineState* _pipelineState;
};

}