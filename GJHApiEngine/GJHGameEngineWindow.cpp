#include "GJHGameEngineWindow.h"
#include <assert.h>
#include <GJHGameEngineMath.h>
#include <GJHGameEngineTime.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineSound.h>
#include <GJHCameraManager.h>

GJHGameEngineWindow* GJHGameEngineWindow::m_MainWindow = nullptr;
bool GJHGameEngineWindow::m_IsProgress = false;
int GJHGameEngineWindow::m_FPSCount = 0;
float GJHGameEngineWindow::m_FPSTime = 0.f;
int GJHGameEngineWindow::m_FPS = 0;

__int64 __stdcall GJHGameEngineWindow::WndProc(HWND hWnd, unsigned int message, unsigned __int64 wParam, __int64 lParam)
{
    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_SIZE:
        break;
    case WM_KILLFOCUS:
        break;
    case WM_SETFOCUS:
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        m_IsProgress = false;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

bool GJHGameEngineWindow::CreateMainWindow(const GJHString& _WindowTitle, const GJHVector& _Size)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    m_MainWindow = new GJHGameEngineWindow();

    {
        WNDCLASSEXW wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = &GJHGameEngineWindow::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = nullptr;
        wcex.hIcon = nullptr;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = L"DEFWINDOW";
        wcex.hIconSm = nullptr;

        if (RegisterClassExW(&wcex) == 0)
        {
            unsigned long ErrorCode = GetLastError();
            assert(false);
        }
    }

    m_MainWindow->Create(_WindowTitle);
    m_MainWindow->SetSize(_Size);
    m_IsProgress = true;

    return true;
}

unsigned __int64 GJHGameEngineWindow::EngineLoop(GJHWindowDeadTimeInstance& _DeadTimeInst)
{
    _DeadTimeInst.InitProcess();

    MSG msg;

    while (m_IsProgress)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            CalcFPS();

            GJHGameEngineTime::Update();
            GJHGameEngineInput::Update();
            GJHGameEngineSound::Update();
            GJHCameraManager::Update();

            _DeadTimeInst.DeadTimeProcess();
        }
    }

    if (m_MainWindow != nullptr)
    {
        delete m_MainWindow;
        m_MainWindow = nullptr;
    }

    return msg.wParam;
}

void GJHGameEngineWindow::Create(const GJHString& _WindowTitle)
{
    m_HWND = CreateWindowW(L"DEFWINDOW", _WindowTitle.ConvertWString().c_str(),
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_THICKFRAME |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        100, 100, CW_USEDEFAULT, 0, nullptr, nullptr, nullptr, nullptr);

    if (m_HWND == nullptr)
    {
        assert(false);
    }

    ShowWindow(m_HWND, SW_SHOW);
    UpdateWindow(m_HWND);

    WindowBackGround.Create(GetDC(m_HWND));

    return;
}

GJHGameEngineWindow* GJHGameEngineWindow::MainWindow()
{
    return m_MainWindow;
}

void GJHGameEngineWindow::SetSize(const GJHVector& _Size)
{
    m_Size = _Size;

    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(m_HWND, nullptr, 0, 0, Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOMOVE | SWP_NOZORDER);

    WindowBackGround.ImageSizeCheck();

    WindowBackBuffer.Release();
    WindowBackBuffer.Create(_Size);
}

void GJHGameEngineWindow::ApiRenderStart()
{
    WindowBackBuffer.Clear();

    {
        POINT Arr[2];
        Arr[0] = { GetSize().hix(), 0 };
        Arr[1] = { GetSize().hix(), GetSize().iy() };
        Polygon(WindowBackBuffer, Arr, 2);
    }

    {
        POINT Arr[2];
        Arr[0] = { 0, GetSize().hiy() };
        Arr[1] = { GetSize().ix(), GetSize().hiy() };
        Polygon(WindowBackBuffer, Arr, 2);
    }
}

void GJHGameEngineWindow::ApiRenderEnd()
{
    WindowBackGround.BitCopy(WindowBackBuffer);
}

void GJHGameEngineWindow::CalcFPS()
{
    m_FPSCount++;
    m_FPSTime += GJHGameEngineTime::FDeltaTime();

    if (1.f <= m_FPSTime)
    {
        m_FPS = m_FPSCount;
        m_FPSCount = 0;
        m_FPSTime = 0.f;
    }
}