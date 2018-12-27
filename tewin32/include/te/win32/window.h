#pragma once

#include "te/win32/global.h"

namespace te {
class Win32Application;
class Win32Window : public IDrawWindow
{
    public:
        Win32Window(Win32Application* pApp, uint_t width, uint_t height, string_t pszTitle);

        virtual void OnInit() {}
        virtual void OnDestroy() {}
        virtual void OnRender();
        virtual void OnUpdate() {}

        virtual bool_t Show() { return ShowWindow(m_hWND, SW_SHOWDEFAULT); }
        virtual bool_t Hide() { return ShowWindow(m_hWND, SW_SHOWDEFAULT); }

        // Accessors.
        virtual uint_t GetWidth() const         { return m_width; }
        virtual uint_t GetHeight() const        { return m_height; }
        virtual string_t GetTitle() const       { return m_title; }

        virtual HWND GetHwnd() const { return m_hWND; }
        virtual void SetHwnd(HWND hWND) { m_hWND = hWND; }

        virtual bool_t ProcessMessages();


protected:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    string_t m_title;
    uint_t m_width;
    uint_t m_height;
    HWND m_hWND;
};

}