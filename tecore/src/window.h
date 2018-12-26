#pragma once

#include "stdafx.h"

class Window
{
    public:
    Window(UINT width, UINT height, LPCTSTR name);
    virtual ~Window();

    virtual void OnInit();
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnDestroy();

    // Samples override the event handlers to handle specific messages.
    virtual void OnKeyDown(UINT8 /*key*/)   {}
    virtual void OnKeyUp(UINT8 /*key*/)     {}

    // Accessors.
    UINT GetWidth() const           { return m_width; }
    UINT GetHeight() const          { return m_height; }
    LPCTSTR GetTitle() const   { return m_title; }

protected:
    UINT m_width;
    UINT m_height;
    float m_aspectRatio;

private:
    LPCTSTR m_title;
    
    static const UINT FrameCount = 2;

    // Pipeline objects.
    IDXGISwapChain3* m_swapChain;
    ID3D12Device* m_device;
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

inline std::string HrToString(HRESULT hr)
{
    char s_str[64] = {};
    sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
    return std::string(s_str);
}

class HrException : public std::runtime_error
{
public:
    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}
    HRESULT Error() const { return m_hr; }
private:
    const HRESULT m_hr;
};

#define SAFE_RELEASE(p) if (p) (p)->Release()

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw HrException(hr);
    }
}