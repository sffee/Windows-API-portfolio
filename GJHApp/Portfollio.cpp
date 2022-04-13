#include <Windows.h>
#include <GJHGameEngineWindow.h>
#include "GJHGameEngineMain.h"
#include <GJHGameEngineDirectory.h>
#include <GJHResourcesManager.h>
#include <GJHGameEngineDebug.h>

int __stdcall wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR     lpCmdLine,
    _In_ int        nCmdShow)
{
    srand((unsigned int)time(0));

    GJHGameEngineDebug::LeckCheck();
    //_CrtSetBreakAlloc(14314);

    GJHGameEngineWindow::CreateMainWindow("Metal Slug", { 1280, 960 } );

    GJHGameEngineWindow::EngineLoop(GJHGameEngineMain::Inst);

    GJHResourcesManager::Destroy();
}