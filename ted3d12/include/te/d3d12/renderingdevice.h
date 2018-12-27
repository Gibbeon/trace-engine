#pragma once

#include "te/d3d12/global.h"

namespace te {

struct CD3DX12_RECT : public D3D12_RECT
{
    CD3DX12_RECT() = default;
    explicit CD3DX12_RECT( const D3D12_RECT& o ) :
        D3D12_RECT( o )
    {}
    explicit CD3DX12_RECT(
        LONG Left,
        LONG Top,
        LONG Right,
        LONG Bottom )
    {
        left = Left;
        top = Top;
        right = Right;
        bottom = Bottom;
    }
};

struct CD3DX12_VIEWPORT : public D3D12_VIEWPORT
{
    CD3DX12_VIEWPORT() = default;
    explicit CD3DX12_VIEWPORT( const D3D12_VIEWPORT& o ) :
        D3D12_VIEWPORT( o )
    {}
    explicit CD3DX12_VIEWPORT(
        FLOAT topLeftX,
        FLOAT topLeftY,
        FLOAT width,
        FLOAT height,
        FLOAT minDepth = D3D12_MIN_DEPTH,
        FLOAT maxDepth = D3D12_MAX_DEPTH )
    {
        TopLeftX = topLeftX;
        TopLeftY = topLeftY;
        Width = width;
        Height = height;
        MinDepth = minDepth;
        MaxDepth = maxDepth;
    }
    explicit CD3DX12_VIEWPORT(
        ID3D12Resource* pResource,
        UINT mipSlice = 0,
        FLOAT topLeftX = 0.0f,
        FLOAT topLeftY = 0.0f,
        FLOAT minDepth = D3D12_MIN_DEPTH,
        FLOAT maxDepth = D3D12_MAX_DEPTH )
    {
        auto Desc = pResource->GetDesc();
        const UINT64 SubresourceWidth = Desc.Width >> mipSlice;
        const UINT64 SubresourceHeight = Desc.Height >> mipSlice;
        switch (Desc.Dimension)
        {
        case D3D12_RESOURCE_DIMENSION_BUFFER:
            TopLeftX = topLeftX;
            TopLeftY = 0.0f;
            Width = Desc.Width - topLeftX;
            Height = 1.0f;
            break;
        case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
            TopLeftX = topLeftX;
            TopLeftY = 0.0f;
            Width = (SubresourceWidth ? SubresourceWidth : 1.0f) - topLeftX;
            Height = 1.0f;
            break;
        case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
        case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
            TopLeftX = topLeftX;
            TopLeftY = topLeftY;
            Width = (SubresourceWidth ? SubresourceWidth : 1.0f) - topLeftX;
            Height = (SubresourceHeight ? SubresourceHeight: 1.0f) - topLeftY;
            break;
        default: break;
        }

        MinDepth = minDepth;
        MaxDepth = maxDepth;
    }
};
struct Vec3
{

    float x,y,z;
};

struct Color
{
    float r,g,b,a;
};

struct Vertex
{
    Vec3 position;
    Color color;
};

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

        
        ID3D12RootSignature* m_rootSignature;


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

}