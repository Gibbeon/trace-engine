#include "te/d3d12/commandqueue.h"
#include "te/d3d12/commandlist.h"

using namespace te;

D3D12CommandQueue::D3D12CommandQueue(ptr_t<ID3D12CommandQueue> queue, ID3D12Device* device) :
    _queue(queue) {

    ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, reinterpret_cast<void**>(&_fence)));
    _fenceValue = 1;

    _fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (_fenceEvent == nullptr)
    {
        ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
    }
}
    
bool_t D3D12CommandQueue::ExecuteCommandList(ptr_t<IGfxCommandList> list) {
    ID3D12CommandList* ppCommandLists[] = { list.As<D3D12CommandList>()->GetCommandList() };
    _queue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
    return true;
}

bool_t D3D12CommandQueue::Flush() {
    // Signal and increment the fence value.
    const UINT64 fenceToWaitFor = _fenceValue + 1;
    ThrowIfFailed(_queue->Signal(_fence, fenceToWaitFor));
    _fenceValue++;

    // Wait until the fence is completed.
    ThrowIfFailed(_fence->SetEventOnCompletion(fenceToWaitFor, _fenceEvent));
    WaitForSingleObject(_fenceEvent, INFINITE);

    return true;
}




