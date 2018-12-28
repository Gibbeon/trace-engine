#include "te/d3d12/window.h"
#include "te/d3d12/device.h"
#include "te/d3d12/commandqueue.h"
#include "te/win32/window.h"

using namespace te;
D3D12Window::D3D12Window(D3D12Device* device, Win32Window* window) :
    _window(window),
    _device(device) {

    GfxCommandQueueDesc desc;
    device->CreateGfxCommandQueue(reinterpret_cast<IGfxCommandQueue**>(&_commandQueue), desc);
   
    // Describe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = _window->GetWidth();
    swapChainDesc.Height = _window->GetHeight();
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    IDXGISwapChain1* swapChain;
    ThrowIfFailed(device->GetIDXGIFactory()->CreateSwapChainForHwnd(
        _commandQueue->GetD3D12CommandQueue(),        // Swap chain needs the queue so that it can force a flush on it.
        reinterpret_cast<Win32Window*>(_window)->GetHwnd(),
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapChain
        ));

    // This sample does not support fullscreen transitions.
    //ThrowIfFailed(factory->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWA_NO_ALT_ENTER));

    _swapChain = reinterpret_cast<IDXGISwapChain3*>(swapChain);
    if(_swapChain == nullptr)
    {
        throw HrException(-1);
    }

    _frameIndex = _swapChain->GetCurrentBackBufferIndex();

    // Create descriptor heaps.
    {
        // Describe and create a render target view (RTV) descriptor heap.
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = 2;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        ThrowIfFailed(device->GetID3DDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_ID3D12DescriptorHeap, reinterpret_cast<void**>(&_rtvHeap)));

        _rtvDescriptorSize = device->GetID3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    // Create frame resources.
    {
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(_rtvHeap->GetCPUDescriptorHandleForHeapStart());
        // Create a RTV for each frame.
        for (UINT n = 0; n < 2; n++)
        {
			ID3D12Resource* ptr = nullptr;
			ThrowIfFailed(_swapChain->GetBuffer(n, IID_ID3D12Resource, reinterpret_cast<void**>(&ptr)));
			device->GetID3DDevice()->CreateRenderTargetView(ptr, 0, rtvHandle);
			rtvHandle.ptr += INT64(1) * UINT64(_rtvDescriptorSize);
			_renderTargets[n] = ptr;
        }
    }

    ThrowIfFailed(device->GetID3DDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, reinterpret_cast<void**>(&_fence)));
    _fenceValue = 1;

    _fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (_fenceEvent == nullptr)
    {
        ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
    }

}

bool_t  D3D12Window::ProcessMessages()
{
    return _window->ProcessMessages();
}


IGfxCommandQueue* D3D12Window::GetCommandQueue()
{
    return _commandQueue;
}

bool_t D3D12Window::SetVisible(bool_t show)
{
    _window->Show();
    return true;
}

bool_t D3D12Window::SwapBuffers()
{
    // Present the frame.
    if(FAILED(_swapChain->Present(1, 0)))
    {
       HRESULT res = reinterpret_cast<D3D12Device*>(_device.ptr())->GetID3DDevice()->GetDeviceRemovedReason();
       ThrowIfFailed(res);
    }

    // Create synchronization objects and wait until assets have been uploaded to the GPU.
    //ID3D12Fence* fence;
    //ThrowIfFailed(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, reinterpret_cast<void**>(&m_fence)));
    //m_fenceValue = 1;

    // Create an event handle to use for frame synchronization.
    
    // Wait for the command list to execute; we are reusing the same command 
    // list in our main loop but for now, we just want to wait for setup to 
    // complete before continuing.

    // Signal and increment the fence value.
    const UINT64 fence = _fenceValue;
    ThrowIfFailed(_commandQueue->GetD3D12CommandQueue()->Signal(_fence, fence));
    _fenceValue++;

    // Wait until the previous frame is finished.
    if (_fence->GetCompletedValue() < fence)
    {
        ThrowIfFailed(_fence->SetEventOnCompletion(fence, _fenceEvent));
        WaitForSingleObject(_fenceEvent, INFINITE);
    }

    _frameIndex = _swapChain->GetCurrentBackBufferIndex();

    return true;
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12Window::GetActiveHandle() {
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
    rtvHandle.ptr += INT64(_frameIndex) * UINT64(_rtvDescriptorSize);
    return rtvHandle;
}


