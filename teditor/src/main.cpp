#include <windows.h>
#include <stdio.h>

#include "te/engine.h"

using namespace te;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pszArgs, int nCmdShow)
{
    IApplication* main = nullptr;
    IRenderingEngine* renderer = nullptr;

    if(SUCCEEDED(TraceEngine::CreateApplication(&main, hInstance, pszArgs)))
    {        
        IDrawWindow* mainWindow;
        if(SUCCEEDED(main->CreateDrawWindow(&mainWindow, 1024, 768, "D3D12 Hello Window")))
        {
            if(SUCCEEDED(TraceEngine::CreateRenderingEngine(&renderer, hInstance, pszArgs)))
            {
                IRenderingDevice* device;
                if(SUCCEEDED(renderer->CreateDevice(&device)))
                {
                    device->Attach(mainWindow);                    
                    while(SUCCEEDED(TraceEngine::Run(mainWindow))) {};
                }
                else
                {
                    printf("Failed to create a compaitable rendering device");
                }
            }
            else
            {
                printf("Failed to create rendering engine");
            }
        }
        else
        {
            
            printf("Failed to create window");
        }
    }
    else
    {
        printf("Failed to create application.");
    }
    
    //Window sample(1024, 1024, "D3D12 Hello Window");
    //return Win32Application::Run(&sample, hInstance, nCmdShow);
}
