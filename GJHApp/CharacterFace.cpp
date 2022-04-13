#include "CharacterFace.h"
#include <GJHRenderer.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineSound.h>

void CharacterFace::Start()
{
	m_ImageDir = ENUM_DIRECTION::RIGHT;

	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI);
	m_AniRender->CreateAnimation("Face", "CharacterSelectUI.bmp", 4, 4, 1.f);
	m_AniRender->CreateAnimation("Select", "CharacterSelectUI.bmp", 5, 6, 0.05f, false, true);
	m_AniRender->SetAlpha(0);

	m_AniRender->ChangeAnimation("Face");

	m_Alpha = 0.f;
	
	State.CreateState("FaceColorChange", &CharacterFace::FaceColorChangeInit, &CharacterFace::FaceColorChangeState, nullptr, this);
	State.CreateState("Select", &CharacterFace::SelectInit, &CharacterFace::SelectState, nullptr, this);
}

void CharacterFace::SceneStart()
{
	Timer.ResetEventTime();
	Timer.SetEventTime(1.2f, true);
}

void CharacterFace::Update()
{
	State.Update();

	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true)
	{
		Timer.SetEventPause(true);

		State.ChangeState("FaceColorChange");
	}
}

void CharacterFace::FaceColorChangeInit()
{

}

void CharacterFace::FaceColorChangeState()
{
	m_Alpha += GJHGameEngineTime::FDeltaTime(350.f);
	if (255.f <= m_Alpha)
	{
		if (KEYDOWN("Attack") == true)
		{
			State.ChangeState("Select");
		}

		m_Alpha = 255.f;
	}

	m_AniRender->SetAlpha((int)m_Alpha);
}

void CharacterFace::SelectInit()
{
	GJHGameEngineSound::PlayOneShot("CharacterPick.mp3", 1.f);

	m_AniRender->ChangeAnimation("Select");
	m_AniRender->SetAnimationFrameIndex(6);
}

void CharacterFace::SelectState()
{

}