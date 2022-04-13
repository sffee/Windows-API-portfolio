#include "MapChange.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include <GJHGameEngineImage.h>
#include "InstanceObject.h"
#include "GJHCameraManager.h"
#include "MonoeyeUFO.h"

void MapChange::Start()
{
	AniIndex = 0;
	m_Gravity = false;
	
	m_AniRender = CreateRender({ 1295, 951 }, "MapChange.bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
	m_AniRender->CreateAnimation("MapChange0", "MapChange.bmp", 0, 0, 1000.f, false);
	m_AniRender->CreateAnimation("MapChange1", "MapChange.bmp", 1, 1, 1000.f, false);
	m_AniRender->CreateAnimation("MapChange2", "MapChange.bmp", 2, 2, 1000.f, false);
	m_AniRender->CreateAnimation("MapChange3", "MapChange.bmp", 3, 3, 1000.f, false);
	m_AniRender->SetDraw(false);

	m_AniRender->ChangeAnimation("MapChange0");

	m_SubAniRender = CreateRender({ 1064, 210 }, "BossRoomGround.bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 5);
	m_SubAniRender->SetActorPivot({ -115, 373 });
	m_SubAniRender->SetDraw(false);

	State.CreateState("MapChange0", &MapChange::MapChange0Init, &MapChange::MapChange0State, nullptr, this);
	State.CreateState("MapChange1", &MapChange::MapChange1Init, &MapChange::MapChange1State, nullptr, this);
	State.CreateState("MapChange2", &MapChange::MapChange2Init, &MapChange::MapChange2State, nullptr, this);
	State.CreateState("MapChange3", &MapChange::MapChange3Init, &MapChange::MapChange3State, nullptr, this);
	State.CreateState("MapChangeEnd", &MapChange::MapChangeEndInit, &MapChange::MapChangeEndState, nullptr, this);

	State.ChangeState("MapChange0");

	Timer.SetEventTime(0.5f, true);
}

void MapChange::Update()
{
	State.Update();
	Timer.EventUpdate();
}

void MapChange::CreateEffect(const GJHVector& _Pos)
{
	GJHGameEngineSound::PlayOneShot("LightOff.mp3", 0.05f);

	InstanceObjectData Data;
	Data.Size = GJHVector(141, 141);
	Data.Pos = _Pos;
	Data.ImageFileName = "BulletHitEffect";
	Data.ImageDir = ENUM_DIRECTION::RIGHT;
	Data.StartFrame = 0;
	Data.EndFrame = 9;
	Data.FrameTime = 0.04f;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void MapChange::MapChange0Init()
{
	m_AniRender->SetDraw(true);
	m_AniRender->ChangeAnimation("MapChange0");

	Timer.ResetEventTime();

	CreateEffect({ 22194, 2336 });
	CreateEffect({ 22197, 2425 });
}

void MapChange::MapChange0State()
{
	if (Timer.CheckEventTime() == true)
	{
		State.ChangeState("MapChange1");
	}
}

void MapChange::MapChange1Init()
{
	SetPos(GetPos() + GJHVector(0, 3));

	m_AniRender->ChangeAnimation("MapChange1");

	Timer.ResetEventTime();

	CreateEffect({ 22480, 2464 });
	CreateEffect({ 22525, 2478 });
	CreateEffect({ 22469, 2523 });
	CreateEffect({ 22529, 2539 });
}

void MapChange::MapChange1State()
{
	if (Timer.CheckEventTime() == true)
	{
		State.ChangeState("MapChange2");
	}
}

void MapChange::MapChange2Init()
{
	SetPos(GetPos() + GJHVector(0, 1));

	m_AniRender->ChangeAnimation("MapChange2");

	Timer.ResetEventTime();

	CreateEffect({ 23057, 2478 });
	CreateEffect({ 23104, 2463 });
	CreateEffect({ 23053, 2539 });
	CreateEffect({ 23114, 2526 });
}

void MapChange::MapChange2State()
{
	if (Timer.CheckEventTime() == true)
	{
		State.ChangeState("MapChange3");
	}
}

void MapChange::MapChange3Init()
{
	m_AniRender->ChangeAnimation("MapChange3");
	m_SubAniRender->SetDraw(true);

	Timer.ResetEventTime();

	CreateEffect({ 23390, 2342 });
	CreateEffect({ 23455, 2312 });
	CreateEffect({ 23383, 2425 });
	CreateEffect({ 23464, 2406 });
}

void MapChange::MapChange3State()
{
	if (Timer.CheckEventTime() == true)
	{
		State.ChangeState("MapChangeEnd");
	}
}

void MapChange::MapChangeEndInit()
{
	Timer.SetEventTime(1.f, true);
}

void MapChange::MapChangeEndState()
{
	if (Timer.CheckEventTime() == true)
	{
		Timer.SetEventPause(true);
		
		MonoeyeUFO* NewActor = GetScene()->CreateActor<MonoeyeUFO>();
		NewActor->SetPos({ 22800, 3500 });
	}
}