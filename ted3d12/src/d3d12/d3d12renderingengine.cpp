#include "te/d3d12/d3d12renderingengine.h"
#include "te/d3d12/d3d12renderingdevice.h"

using namespace te;

D3D12RenderingEngine::D3D12RenderingEngine()
{

}

bool_t D3D12RenderingEngine::CreateDevice(IRenderingDevice** pDevice)
{
    UINT dxgiFactoryFlags = 0;

    // Enable the debug layer (requires the Graphics Tools "optional feature").
    // NOTE: Enabling the debug layer after device creation will invalidate the active device.
    {
        ID3D12Debug* debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_ID3D12Debug, reinterpret_cast<void**>(&debugController))))
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }

    IDXGIFactory4* factory;
    ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_IDXGIFactory4, reinterpret_cast<void**>(&factory)));

    IDXGIAdapter1* adapter = nullptr;
    ID3D12Device* m_device = nullptr;

    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_ID3D12Device, reinterpret_cast<void**>(&m_device))))
        {
            break;
        }
    }

    if(m_device == nullptr)
    {
        throw HrException(-1);
    }

    *pDevice = new D3D12RenderingDevice(m_device, factory);

    return true;
}
