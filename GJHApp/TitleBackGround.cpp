#include "TitleBackGround.h"
#include <GJHGameEngineScene.h>
#include <GJHGameEngineWindow.h>
#include <GJHResourcesManager.h>
#include <GJHRenderer.h>
#include "define.h"

void TitleBackGround::Start()
{
	{
		GJHRenderer* Render = CreateRender({ 1280, 960 }, "Title.bmp", ContentsEnum::RENDERORDER::BACKGROUND);
		Render->SetTransColor(RGB(100, 0, 0));
	}

	{
		PressStartRender = CreateRender({ 348, 60 }, "PressStart.bmp", ContentsEnum::RENDERORDER::NORMAL);
		PressStartRender->SetActorPivot({ 0, 250 });
		PressStartRender->SetTransColor(RGB(0, 253, 24));

		PressStartUpdate.PushFunc(0.5f, &TitleBackGround::PressStartOn, this);
		PressStartUpdate.PushFunc(0.5f, &TitleBackGround::PressStartOff, this);
	}
}

void TitleBackGround::Update()
{
	PressStartUpdate.Update();
}

void TitleBackGround::PressStartOn()
{
	PressStartRender->SetDraw(true);
}

void TitleBackGround::PressStartOff()
{
	PressStartRender->SetDraw(false);
}