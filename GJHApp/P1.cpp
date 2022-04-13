#include "P1.h"
#include <GJHRenderer.h>

void P1::Start()
{
	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI + 2);
	m_AniRender->CreateAnimation("P1", "CharacterSelectUI.bmp", 1, 2, 0.2f);
	m_AniRender->ChangeAnimation("P1");
	m_AniRender->SetDraw(false);

	m_IsShow = false;
}

void P1::Update()
{
	Timer.EventUpdate();
	if (m_IsShow == false &&
		Timer.CheckEventTime() == true)
	{
		Timer.SetEventPause(false);

		m_IsShow = true;
		m_AniRender->SetDraw(true);
	}
}

void P1::SceneStart()
{
	Timer.ResetEventTime();
	Timer.SetEventTime(1.8f, true);
}
