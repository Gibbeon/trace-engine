#include <windows.h>

#include "stdafx.h"
#include "win32application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    Window sample(1280, 720, "D3D12 Hello Window");
    return Win32Application::Run(&sample, hInstance, nCmdShow);
}
