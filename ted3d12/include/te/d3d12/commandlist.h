#include "te/application.h"
#include "te/d3d12/global.h"

namespace te {

class D3D12Device;

class D3D12CommandList: public IGfxCommandList {
public:
    D3D12CommandList(D3D12Device*, ID3D12GraphicsCommandList*, ID3D12CommandAllocator*);

    virtual bool_t Begin() { return true; }
    virtual bool_t End();

    virtual bool_t Draw(ptr_t<IGfxVertexBuffer> buffer, ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE descriptor);
    virtual bool_t Draw(ptr_t<IGfxVertexBuffer> buffer, ptr_t<IGfxWindow> window);

    ID3D12GraphicsCommandList* GetCommandList() { return _list; }
    ID3D12CommandAllocator* GetCommandAllocator() { return _allocator; }

protected:
    bool_t InitRootSignature();
    bool_t InitPipelineState();

private:
    ID3D12GraphicsCommandList* _list;
    ID3D12CommandAllocator* _allocator;    
    ID3D12PipelineState* _pipelineState;
    ID3D12RootSignature* _rootSignature;
    D3D12Device* _device;
};

}