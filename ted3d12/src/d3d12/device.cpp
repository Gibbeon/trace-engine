#include "te/d3d12/device.h"
#include "te/d3d12/dxh.h"
#include "te/d3d12/commandqueue.h"
#include "te/d3d12/commandlist.h"
#include "te/d3d12/vertexbuffer.h"
#include "te/d3d12/window.h"
#include "te/win32/window.h"


using namespace te;

D3D12Device::D3D12Device(IDXGIFactory4* factory, IDXGIAdapter1* adapter, ID3D12Device* device) :
    _factory(factory),
    _adapter(adapter),
    _device(device) {
    
    InitRootSignature();
    InitPipelineState();
}

bool_t D3D12Device::InitRootSignature() {
    CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ID3DBlob* signature;
    ID3DBlob* error;

    ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
    ThrowIfFailed(_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_ID3D12RootSignature, reinterpret_cast<void**>(&_rootSignature)));
    return true;
}

bool_t D3D12Device::InitPipelineState() {
    ID3DBlob* vertexShader;
    ID3DBlob* pixelShader;

    #if defined(_DEBUG)
            // Enable better shader debugging with the graphics debugging tools.
            UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    #else
            UINT compileFlags = 0;
    #endif

    ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
    ThrowIfFailed(D3DCompileFromFile(L"c:\\shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));

    // Define the vertex input layout.
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    // Describe and create the graphics pipeline state object (PSO).
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    psoDesc.pRootSignature = _rootSignature;
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader);
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader);
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;

    ThrowIfFailed(_device->CreateGraphicsPipelineState(&psoDesc, IID_ID3D12PipelineState, reinterpret_cast<void**>(&_pipelineState)));
        return true;
}

bool_t D3D12Device::CreateGfxCommandQueue(IGfxCommandQueue** queue, GfxCommandQueueDesc& desc) {
    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    ID3D12CommandQueue* commandQueue = nullptr;
    ThrowIfFailed(_device->CreateCommandQueue(&queueDesc, IID_ID3D12CommandQueue, reinterpret_cast<void**>(&commandQueue)));

    (*queue) = new D3D12CommandQueue(commandQueue, _device);
    return true;
}

bool_t D3D12Device::CreateGfxCommandList(IGfxCommandList** list, GfxCommandListDesc& desc) {
    ID3D12CommandAllocator* commandAllocator;
    ID3D12GraphicsCommandList* commandList;

    ThrowIfFailed(_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, reinterpret_cast<void**>(&commandAllocator)));

    ThrowIfFailed(_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, IID_ID3D12CommandList, reinterpret_cast<void**>(&commandList)));

    ThrowIfFailed(commandList->Close());

    (*list) = new D3D12CommandList(this, commandList, commandAllocator);
    return true;
}

bool_t D3D12Device::CreateVertexBuffer(IGfxVertexBuffer** buffer, GfxVertexBufferDesc& desc) {
    // Note: using upload heaps to transfer static data like vert buffers is not 
    // recommended. Every time the GPU needs it, the upload heap will be marshalled 
    // over. Please read up on Default Heap usage. An upload heap is used here for 
    // code simplicity and because there are very few verts to actually transfer.

    ID3D12Resource* vertexBuffer = nullptr;

    Vertex triangleVertices[] =
        {
            { { 0.0f, 0.25f * (1), 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
            { { 0.25f, -0.25f * 1, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
            { { -0.25f, -0.25f * 1, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
        };

        const UINT vertexBufferSize = sizeof(triangleVertices);

    ThrowIfFailed(_device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_ID3D12Resource, 
        reinterpret_cast<void**>(&vertexBuffer)));

    (*buffer) = new D3D12VertexBuffer(vertexBuffer, vertexBufferSize);
    return true;
}

bool_t D3D12Device::CreateGfxWindow(IGfxWindow** window, WindowDesc& desc) {
    (*window) = new D3D12Window(this, new Win32Window(desc.hInstance, desc.bounds.w, desc.bounds.h,  "Sample Title"));
    return true;
}