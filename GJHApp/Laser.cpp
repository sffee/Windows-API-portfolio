#include "Laser.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include <GJHGameEngineImage.h>
#include "InstanceObject.h"
#include "GJHCameraManager.h"
#include "TombStone.h"
#include "MonoeyeUFO.h"

Laser::~Laser()
{
	GJHGameEngineSound::StopManagement("BossLaser");
}

void Laser::Start()
{
	m_LoopTime = 0.f;

	m_MoveSpeed = 150.f;
	m_IsGravity = false;

	m_AniRender = CreateRender({ 128, 900 }, "MonoeyeUFO_Effect(Left).bmp", (int)ContentsEnum::RENDERORDER::OBJECT + 1);
	CreateAnimation("Start", "MonoeyeUFO_Effect", 3, 5, 0.1f, false, true);
	CreateAnimation("Loop", "MonoeyeUFO_Effect", 0, 2, 0.1f, true);
	CreateAnimation("End", "MonoeyeUFO_Effect", 3, 5, 0.1f, false);

	m_SubAniRender = CreateRender({ 128, 900 }, "MonoeyeUFO_Effect(Left).bmp", (int)ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Loop", "MonoeyeUFO_Effect", 6, 11, 0.1f, true, false, true);
	m_SubAniRender->Off();

	State.CreateState("Start", &Laser::StartInit, &Laser::StartState, nullptr, this);
	State.CreateState("Loop", &Laser::LoopInit, &Laser::LoopState, nullptr, this);
	State.CreateState("End", &Laser::EndInit, &Laser::EndState, nullptr, this);

	State.ChangeState("Start");

	SetAnimationData();
}

void Laser::Update()
{
	State.Update();
	__super::AnimationDataCheck(State.CurState);
}

void Laser::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
}

void Laser::Move()
{
	while (m_MapColImage->GetImagePixel(GetPos().ix(), GetPos().iy()) == RGB(255, 0, 255))
	{
		__super::Move(GJHVector(0, 1));
	}

	while (m_MapColImage->GetImagePixel(GetPos().ix(), GetPos().iy()) != RGB(255, 0, 255))
	{
		__super::Move(GJHVector(0, -1));
	}
	
	float DistanceX = PlayerDistance().x;
	if (-1.f <= DistanceX && DistanceX <= 1.f)
	{
		return;
	}

	float MoveDir = DistanceX < 0.f ? -1.f : 1.f;

	__super::Move(GJHVector(m_MoveSpeed * MoveDir * GJHGameEngineTime::FDeltaTime(), 0));
}

void Laser::CreateTombStone()
{
	TombStone* NewActor = GetScene()->CreateActor<TombStone>();
	NewActor->SetPos({ GetPos().x, GJHCameraManager::GetCamPos().y - 200.f });
}

void Laser::SetLoopTime(float _Time)
{
	m_LoopTime = _Time;
}

void Laser::StartInit()
{
	GJHGameEngineSound::PlayManagement("BossLaser", "BossLaser.mp3", 0.5f);

	ChangeAnimation("Start");
	SetAnimationFrameIndex(5);
}

void Laser::StartState()
{
	if (AnimationEnd() == true)
	{
		State.ChangeState("Loop");
	}

	Move();
}

void Laser::LoopInit()
{
	ChangeAnimation("Loop");
	ChangeAnimation("Loop", false, true);
	m_SubAniRender->On();

	LoopTimer.Reset();
	LoopTimer.SetEventTime(m_LoopTime, true);
}

void Laser::LoopState()
{
	LoopTimer.EventUpdate();
	if (LoopTimer.CheckEventTime() == true)
	{
		State.ChangeState("End");
	}

	Move();
}

void Laser::EndInit()
{
	ChangeAnimation("End");
	m_SubAniRender->Off();
}

void Laser::EndState()
{
	if (AnimationEnd() == true)
	{
		GJHGameEngineSound::StopManagement("BossLaser");

		CreateTombStone();
		MonoeyeUFO::DeleteLaserActor();
		Death();
	}
}

void Laser::SetAnimationData()
{
	PushAnimationData("Start", 3, 0, -439, 0.04f);
	PushAnimationData("Start", 4, 0, -439, 0.04f);
	PushAnimationData("Start", 5, 0, -439, 0.04f);

	PushAnimationData("Loop", 0, 0, -439, 0.04f);
	PushAnimationData("Loop", 1, 0, -439, 0.04f);
	PushAnimationData("Loop", 2, 0, -439, 0.04f);

	PushAnimationData("End", 3, 0, -439, 0.04f);
	PushAnimationData("End", 4, 0, -439, 0.04f);
	PushAnimationData("End", 5, 0, -439, 0.04f);

	PushAnimationData("Loop", 6, 0, 0, 0.04f, true);
	PushAnimationData("Loop", 7, 0, 0, 0.04f, true);
	PushAnimationData("Loop", 8, 0, 0, 0.04f, true);
	PushAnimationData("Loop", 9, 0, 0, 0.04f, true);
	PushAnimationData("Loop", 10, 0, 0, 0.04f, true);
	PushAnimationData("Loop", 11, 0, 0, 0.04f, true);
}