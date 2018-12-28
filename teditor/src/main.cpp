#include <windows.h>
#include <stdio.h>

#include "te/engine.h"

#define ENSURE(x, y) (x)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
{    
    te::Application app;
    
    ENSURE(app.Init(hInstance, pszArgs), "Failed to initialize platform");

    te::GfxSystemDescBuilder gfxSystemBuilder;

    te::IGfxSystem* gfx = nullptr;
    ENSURE(app.CreateGfxSystem(&gfx, gfxSystemBuilder.Build()), "Failed to create GfxSystem");

    te::GfxDeviceBuilder gfxDeviceBuilder;
    te::IGfxDevice* device = nullptr;
    ENSURE(gfx->CreateDevice(&device, gfxDeviceBuilder.Build()), "Failed to create GfxSystem");
            
    te::IGfxWindow* window = nullptr;
    
    te::WindowBuilder windowDesc;
    windowDesc.SetBounds(te::RECT(0, 0, 1024, 768))
            .SetColorDepth(32)
            .SetBufferCount(2);

    ENSURE(device->CreateGfxWindow(&window, windowDesc.Build()), "Failed to create window");

    //window->SetVisible(FALSE);

    //te::GfxCommandQueueBuilder queuebufferDesc;

    te::IGfxCommandQueue* queue;
    //ENSURE(device->CreateGfxCommandQueue(&queue, queuebufferDesc.Build()), "");

    queue = window->GetCommandQueue();

    te::GfxCommandListBuilder bufferDesc;

    te::IGfxCommandList* commands;
    ENSURE(device->CreateGfxCommandList(&commands, bufferDesc.Build()), "");

    te::GfxVertexBufferBuilder vertexBufferDesc;

    te::IGfxVertexBuffer* vertexbuffer;
    ENSURE(device->CreateVertexBuffer(&vertexbuffer, vertexBufferDesc.Build()), "");

    //vertexbuffer->Write(0, 0, 0);


    while(app.IsRunning())
    {
        //commands->Begin();
        vertexbuffer->Write(0, 0, 0);
        commands->Draw(vertexbuffer, window);

        //
        //app.ProcessMessages();
        //device->ExecuteCommandList(commands);
        queue->ExecuteCommandList(commands);
        //D3D12VertexBuffer::Write

        window->ProcessMessages();
        window->SwapBuffers();

        //commands->End();
    }
}
