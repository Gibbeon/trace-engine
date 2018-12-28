#include "te/engine.h"
#include "te/d3d12/global.h"

namespace te {

class D3D12CommandQueue : public IGfxCommandQueue {
public:
    D3D12CommandQueue(ptr_t<ID3D12CommandQueue> queue, ID3D12Device* device);
    
    virtual bool_t ExecuteCommandList(ptr_t<IGfxCommandList> buffer);
    virtual bool_t Flush();

    ID3D12CommandQueue* GetD3D12CommandQueue() { return _queue.ptr(); }
private:
    ptr_t<ID3D12CommandQueue> _queue;

    HANDLE _fenceEvent;
    ID3D12Fence* _fence;
    uint_t _fenceValue;
};

}