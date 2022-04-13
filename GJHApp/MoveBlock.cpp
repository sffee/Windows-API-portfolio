#include "MoveBlock.h"
#include <GJHRenderer.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHSceneManager.h>
#include <GJHGameEngineSound.h>
#include "InstanceObject.h"
#include "define.h"

void MoveBlock::Start()
{
	m_IsGravity = false;

	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI);
	m_AniRender->CreateAnimation("Block", "CharacterSelectUI.bmp", 7, 7, 1.f);
	m_AniRender->ChangeAnimation("Block");

	m_CharacterBackRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI);
	m_CharacterBackRender->CreateAnimation("Back", "CharacterSelectUI.bmp", 8, 8, 1.f);
	m_CharacterBackRender->ChangeAnimation("Back");
	m_CharacterBackRender->SetActorPivot({ 0, 42 });
	m_CharacterBackRender->SetDraw(false);

	m_CharacterRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI);
	m_CharacterRender->CreateAnimation("Character", "CharacterSelectUI.bmp", 15, 18, 0.12f, true, true);
	m_CharacterRender->ChangeAnimation("Character");
	m_CharacterRender->SetFrameTime(15, 0.18f);
	m_CharacterRender->SetActorPivot({ 0, 60 });
	m_CharacterRender->SetDraw(false);

	State.CreateState("Start", &MoveBlock::StartInit, &MoveBlock::StartState, nullptr, this);
	State.CreateState("MoveUp", &MoveBlock::MoveUpInit, &MoveBlock::MoveUpState, nullptr, this);
	State.CreateState("MoveDown", &MoveBlock::MoveDownInit, &MoveBlock::MoveDownState, nullptr, this);
	State.CreateState("UpDown", &MoveBlock::UpDownInit, &MoveBlock::UpDownState, nullptr, this);
	State.CreateState("SceneChange", &MoveBlock::SceneChangeInit, &MoveBlock::SceneChangeState, nullptr, this);

	State.ChangeState("Start");
}

void MoveBlock::Update()
{
	State.Update();
}

void MoveBlock::SceneStart()
{
	Timer.ResetEventTime();
	Timer.SetEventTime(0.8f, true);
}

void MoveBlock::CreateEffect()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(1050, 600);
	Data.Pos = GJHVector(1070, 830);
	Data.ImageFileName = "CharacterSelectUI";
	Data.ImageDir = ENUM_DIRECTION::RIGHT;
	Data.StartFrame = 9;
	Data.EndFrame = 14;
	Data.FrameTime = 0.05f;
	Data.NoDir = true;
	Data.Order = (int)ContentsEnum::RENDERORDER::UI + 100;

	AniDataMap Map;
	Map[9] = { PivotData(0, -20), 0.05f };
	Map[10] = { PivotData(-3, -14), 0.05f };
	Map[11] = { PivotData(-5, 2), 0.05f };
	Map[12] = { PivotData(-5, 18), 0.05f };
	Map[13] = { PivotData(-8, 13), 0.05f };
	Map[14] = { PivotData(-8, 19), 0.05f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void MoveBlock::StartInit()
{
	
}

void MoveBlock::StartState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true)
	{
		State.ChangeState("MoveUp");
	}
}

void MoveBlock::MoveUpInit()
{
	Timer.SetEventTime(1.f, true);
	m_TimerEnd = false;
	GJHGameEngineSound::PlayOneShot("CharacterSelectBlockMoveUp.mp3", 0.5f);
}

void MoveBlock::MoveUpState()
{
	Move(GJHVector::UP * GJHGameEngineTime::FDeltaTime(1000.f));

	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true)
	{
		m_TimerEnd = true;
	}

	if (GetPos().y < 30)
	{
		SetPos({ GetPos().x, 30 });

		if (m_TimerEnd == true &&
			KEYDOWN("Attack") == true)
		{
			State.ChangeState("MoveDown");
		}
	}
}

void MoveBlock::MoveDownInit()
{
	m_CharacterBackRender->SetDraw(true);
	m_CharacterRender->SetDraw(true);

	Timer.ResetEventTime();
	Timer.SetEventTime(0.4f, true);

	m_MoveDownCheck = false;
	m_MoveDownSound = false;
}

void MoveBlock::MoveDownState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == false && m_MoveDownCheck == false)
	{
		return;
	}

	if (m_MoveDownSound == false)
	{
		m_MoveDownSound = true;
		GJHGameEngineSound::PlayOneShot("SelectFio.mp3", 1.f);
	}

	m_MoveDownCheck = true;

	Move(GJHVector::DOWN * GJHGameEngineTime::FDeltaTime(2000.f));
	if (550 < GetPos().y)
	{
		SetPos({ GetPos().x, 555 });
		State.ChangeState("UpDown");
	}
}

void MoveBlock::UpDownInit()
{
	CreateEffect();

	m_ShakeTime = 0.8f;
	m_ShakeCount = 0;

	GJHGameEngineSound::PlayOneShot("CharacterSelectBlockMoveDown.mp3", 1.f);
}

void MoveBlock::UpDownState()
{
	m_ShakeTime -= GJHGameEngineTime::FDeltaTime();
	if (m_ShakeTime <= 0.f)
	{
		SetPos({ 1070, 560 });
		State.ChangeState("SceneChange");
		return;
	}

	int m_MoveDir = m_ShakeCount % 2 == 0 ? 1 : -1;
	++m_ShakeCount;

	Move(GJHVector(0, 18.f) * m_ShakeTime * m_MoveDir);
}

void MoveBlock::SceneChangeInit()
{
	Timer.ResetEventTime();
	Timer.SetEventTime(0.6f, true);
}

void MoveBlock::SceneChangeState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true)
	{
		Timer.SetEventPause(true);

		FadeIn(2.f);
	}

	if (m_FadeInStart == true &&
		IsFadeInOutOver() == true)
	{
		GJHSceneManager::Inst.ChangeScene("Play");
	}
}