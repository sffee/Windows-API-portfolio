#include "Word.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include <GJHGameEngineImage.h>
#include "InstanceObject.h"
#include "GJHCameraManager.h"
#include "MonoeyeUFO.h"

void Word::Start()
{
	m_MoveSpeed = 500.f;
	m_IsGravity = false;
	
	m_YSize = 0.f;
	m_YAddSize = 1500.f;
	m_WordCount = 0;
	m_WordMaxCount = 0;
	m_IsSpeedUp = false;

	m_AniRender = CreateRender({ 768, 768 }, "MonoeyeUFO(Left).bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 5);
	CreateAnimation("Loop", "MonoeyeUFO", 15, 15, 0.1f, true);
	CreateAnimation("LoopSpeedUp", "MonoeyeUFO_SpeedUp", 15, 15, 0.1f, true);
	CreateAnimation("Loop_Damage", "MonoeyeUFO_Damage", 15, 15, 0.1f, true);
	CreateAnimation("LoopSpeedUp_Damage", "MonoeyeUFO_Damage", 15, 15, 0.1f, true);

	ChangeAnimation("Loop");

	State.CreateState("SizeUp", &Word::SizeUpInit, &Word::SizeUpState, nullptr, this);
	State.CreateState("Fly", &Word::FlyInit, &Word::FlyState, nullptr, this);

	State.ChangeState("SizeUp");
}

void Word::Update()
{
	State.Update();

	__super::Update();
	__super::AnimationDataCheck(State.CurState);
}

void Word::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
}

void Word::Damage()
{
	if (m_IsSpeedUp == true)
	{
		DrawDamageAnimation("LoopSpeedUp");
	}
	else
	{
		DrawDamageAnimation("Loop");
	}
}

void Word::SetYAddSize(float _Size)
{
	m_YAddSize = _Size;
}

void Word::SetWordMaxCount(int _Count)
{
	m_WordMaxCount = _Count;
}

void Word::SetSpeedUp()
{
	m_IsSpeedUp = true;
	ChangeAnimation("LoopSpeedUp");
}

void Word::SetDefaultPos(const GJHVector& _Pos)
{
	m_DefaultPos = _Pos;
}

void Word::SizeUpInit()
{
	SetPos(m_DefaultPos);

	m_AniRender->SetSize({ 768, 768 });
}

void Word::SizeUpState()
{
	m_YSize += m_YAddSize * GJHGameEngineTime::FDeltaTime();
	m_AniRender->SetSize({ 768, 768 + m_YSize });
	SetPos({ m_DefaultPos.x, m_DefaultPos.y - m_YSize / 15.f });

	if (1480 <= m_YSize)
	{
		m_YSize = 0;
		State.ChangeState("Fly");
	}
}

void Word::FlyInit()
{
	FlyTimer.ResetEventTime();
	FlyTimer.SetEventTime(0.15f, true);
}

void Word::FlyState()
{
	Move(GJHVector(0, -3000.f) * GJHGameEngineTime::FDeltaTime());

	FlyTimer.EventUpdate();
	if (FlyTimer.CheckEventTime() == true)
	{
		if (m_WordMaxCount <= m_WordCount)
		{
			MonoeyeUFO::DeleteWordActor();
			Death();
		}
		
		m_WordCount++;
		m_YAddSize = 7000.f;
		State.ChangeState("SizeUp");
	}
}