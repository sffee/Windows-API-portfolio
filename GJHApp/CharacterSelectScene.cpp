#include <GJHGameEngineWindow.h>
#include <GJHGameEngineSound.h>
#include "CharacterSelectScene.h"
#include "FadeInOut.h"
#include "CharacterSelectBackGround.h"
#include "CharacterFace.h"
#include "MoveBlock.h"
#include "P1.h"

void CharacterSelectScene::Loading()
{
	{
		CharacterSelectBackGround* NewActor = CreateActor<CharacterSelectBackGround>();
		NewActor->SetPos(GJHGameEngineWindow::MainWindow()->GetSize().HalfVector2D());
	}

	{
		CharacterFace* NewActor = CreateActor<CharacterFace>();
		NewActor->SetPos({ 1070, 592 });
	}

	{
		MoveBlock* NewActor = CreateActor<MoveBlock>();
		NewActor->SetPos({ 1070, 560 });
	}

	{
		P1* NewActor = CreateActor<P1>();
		NewActor->SetPos({ 1080, 250 });
	}
}

void CharacterSelectScene::SceneUpdate()
{
	BlackBox();

	Timer.EventUpdate();
	if (m_PlayBGM == false &&
		Timer.CheckEventTime() == true)
	{
		GJHGameEngineSound::PlayManagement("BGM", "CharacterSelect.mp3", 1.f, true);
		m_PlayBGM = true;
	}
}

void CharacterSelectScene::SceneChangeStart()
{
	__super::SceneChangeStart();

	FadeInOut* m_FadeInOutActor = CreateActor<FadeInOut>();
	m_FadeInOutActor->SetPos({ WINDOWWIDTH / 2, WINDOWHEIGHT / 2 });
	m_FadeInOutActor->FadeOut(0.3f);

	Timer.ResetEventTime();
	Timer.SetEventTime(0.6f, true);
	m_PlayBGM = false;
}

void CharacterSelectScene::SceneChangeEnd()
{
	GJHGameEngineSound::StopManagement("BGM");
}

void CharacterSelectScene::BlackBox()
{
	HDC hDC = GJHGameEngineWindow::MainWindow()->GetBackBuffer();

	HBRUSH Brush, oBrush;

	Brush = CreateSolidBrush(RGB(0, 0, 0));
	oBrush = (HBRUSH)SelectObject(hDC, Brush);

	Rectangle(hDC, 0, 0, 1280, 960);

	SelectObject(hDC, oBrush);
	DeleteObject(Brush);
}