/* #pragma once

#include "te/d3d12/global.h"

#include "te/d3d12/dxh.h"

namespace te {

class D3D12RenderingDevice : public IRenderingDevice
{
    public:
        D3D12RenderingDevice(ID3D12Device* device, IDXGIFactory4* factory);

        virtual bool_t Attach(IDrawWindow* pWindow);
        virtual bool_t SwapBuffers();

        ID3D12Device* GetD3D12Device() { return m_device; }
        IDXGIFactory4* GetDXGIFactory() { return m_factory; }

        void PopulateCommandList();
        void LoadAssets();
        void WaitForPreviousFrame();

    private:
        ID3D12Device* m_device;
        IDXGIFactory4* m_factory;

        static const UINT FrameCount = 2;

        CD3DX12_VIEWPORT m_viewport;
        CD3DX12_RECT m_scissorRect;

        // App resources.
        ID3D12Resource* m_vertexBuffer;
        D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

        
        


        // Pipeline objects.
        IDXGISwapChain3* m_swapChain;
        ID3D12Resource* m_renderTargets[FrameCount];
        ID3D12CommandAllocator* m_commandAllocator;
        ID3D12CommandQueue* m_commandQueue;
        ID3D12DescriptorHeap* m_rtvHeap;
        ID3D12PipelineState* m_pipelineState;
        ID3D12GraphicsCommandList* m_commandList;
        UINT m_rtvDescriptorSize;

        // Synchronization objects.
        UINT m_frameIndex;
        HANDLE m_fenceEvent;
        ID3D12Fence* m_fence;
        UINT64 m_fenceValue;
};

} */