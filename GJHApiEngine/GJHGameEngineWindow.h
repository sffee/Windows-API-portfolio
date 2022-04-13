#pragma once

#include <Windows.h>
#include <crtdbg.h>
#include <GJHString.h>
#include <GJHGameEngineMath.h>
#include "GJHGameEngineImage.h"

class GJHWindowDeadTimeInstance
{
public:
    virtual void InitProcess() = 0 {}
    virtual void DeadTimeProcess() = 0 {}
};

class GJHGameEngineWindow
{
private:
    static GJHGameEngineWindow* m_MainWindow;
    static bool m_IsProgress;
    static __int64 __stdcall WndProc(HWND hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam);

public:
    static bool CreateMainWindow(const GJHString& _WindowTitle, const GJHVector& _Size);
    static unsigned __int64 EngineLoop(GJHWindowDeadTimeInstance& _DeadTimeInst);
    static GJHGameEngineWindow* MainWindow();

private:
    static int m_FPSCount;
    static float m_FPSTime;
    static int m_FPS;

private:
    HWND m_HWND;
    HDC m_HDC;

public:
    GJHVector m_Size;
    GJHGameEngineImage WindowBackGround;
    GJHGameEngineImage WindowBackBuffer;

public:
    GJHGameEngineImage& GetBackGround()
    {
        return WindowBackGround;
    }

    GJHGameEngineImage& GetBackBuffer()
    {
        return WindowBackBuffer;
    }

public:
    inline GJHVector GetSize()
    {
        return m_Size;
    }

    void SetSize(const GJHVector& _Size);

public:
    GJHVector GetMousePos()
    {
        POINT MousePos;

        GetCursorPos(&MousePos);
        ScreenToClient(m_HWND, &MousePos);

        return GJHVector((float)MousePos.x, (float)MousePos.y);
    }

public:
    void ApiRenderStart();
    void ApiRenderEnd();

private:
    static void CalcFPS();

public:
    static int GetFPS()
    {
        return m_FPS;
    }

private:
    void Create(const GJHString& _WindowTitle);
};