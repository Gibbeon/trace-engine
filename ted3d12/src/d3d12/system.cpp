#include "te/d3d12/gfxsystem.h"
#include "te/d3d12/device.h"
using namespace te;

bool_t D3D12System::CreateDevice(out_ptr_t<IGfxDevice> result, GfxDeviceDesc& desc)
{
    UINT dxgiFactoryFlags = 0;

    #ifdef _DEBUG
    {
        ID3D12Debug* debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_ID3D12Debug, reinterpret_cast<void**>(&debugController))))
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
    #endif

    IDXGIFactory4* factory;
    ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_IDXGIFactory4, reinterpret_cast<void**>(&factory)));

    IDXGIAdapter1*  adapter = nullptr;
    ID3D12Device*   device = nullptr;

    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_ID3D12Device, reinterpret_cast<void**>(&device))))
        {
            break;
        }
    }

    (*result) = new D3D12Device(factory, adapter, device);

    return true;
}