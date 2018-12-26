/*#include <cstdio>

int main(int argc, char** argv) {
    printf("Hello World!");
}
*/

//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************
#include <windows.h>

#include "stdafx.h"
#include "win32application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    Window sample(1280, 720, "D3D12 Hello Window");
    return Win32Application::Run(&sample, hInstance, nCmdShow);
}
