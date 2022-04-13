#include "TombStone.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include <GJHGameEngineImage.h>
#include "InstanceObject.h"
#include "GJHCameraManager.h"

void TombStone::Start()
{
	m_IsGravity = false;
	m_IsDamage = false;

	m_AniRender = CreateRender({ 512, 512 }, "MonoeyeUFO_Effect(Left).bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 6);
	CreateAnimation("TombStone", "TombStone", 0, 32, 1000.f, false);
	CreateAnimation("TombStone_Damage", "TombStone_Damage", 0, 32, 1000.f, false);

	m_SubAniRender = CreateRender({ 239, 74 }, "TombStone_Ground.bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 7);
	m_SubAniRender->SetDraw(false);
	m_SubAniRender->SetActorPivot({ 0,-20 });

	State.CreateState("Drop", &TombStone::DropInit, &TombStone::DropState, nullptr, this);
	State.CreateState("Land", &TombStone::LandInit, &TombStone::LandState, nullptr, this);

	m_ThisDamageCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -230 }, { 300, 100 }, ContentsEnum::COLTYPE::NONE);
	m_ThisDamageCollision->SetName("TombStone");

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -275 }, { 150, 600 }, ContentsEnum::COLTYPE::MONSTER);
	m_AniCollision->SetHitable(false);
	
	m_AttackCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -275 }, { 150, 600 }, ContentsEnum::COLTYPE::MONSTERBULLET);

	State.ChangeState("Drop");

	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushOneShotFunc(&TombStone::Up, this);
	UpDownUpdater.PushDelay(0.025f);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushOneShotFunc(&TombStone::Down, this);
	UpDownUpdater.PushDelay(0.025f);

	DamageAniChangeUpdater.PushOneShotFunc(&TombStone::AniIndexChange, this);
	DamageAniChangeUpdater.PushDelay(0.01f);
	DamageAniChangeUpdater.PushOneShotFunc(&TombStone::AniIndexChange, this);
	DamageAniChangeUpdater.PushDelay(0.01f);
	DamageAniChangeUpdater.PushOneShotFunc(&TombStone::AniIndexChange, this);
	DamageAniChangeUpdater.PushDelay(0.01f);
	DamageAniChangeUpdater.PushOneShotFunc(&TombStone::AniIndexChange, this);
	DamageAniChangeUpdater.PushDelay(0.01f);

	DamageAniChangeUpdater.m_bLoop = false;

	SetAnimationData();
}

void TombStone::Update()
{
	CollisionSizeChange();

	State.Update();
	__super::Update();
	__super::AnimationDataCheck("TombStone");
}

void TombStone::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		GJHGameEngineSound::PlayOneShot("HelicopterDamage.mp3", 0.5f);

		Damage();
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE)
	{
		Damage();
	}
	else if (_Other->GetName() == "TombStone")
	{
		LoopDamage();
	}
}

void TombStone::ColStay(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetName() == "TombStone")
	{
		LoopDamage();
	}
}

void TombStone::CollisionSizeChange()
{
	int CurFrame = GetAnimationFrameIndex();
	if (m_AniRender->GetAnimationEndFrame() < CurFrame)
	{
		return;
	}

	float ColYSize = 600.f - ((float)CurFrame * 15.f);
	float ColYPivot = -275.f + ((float)CurFrame * 7.5f);
	m_AniCollision->SetSize({ 150, ColYSize });
	m_AniCollision->SetActorPivot({ 0, ColYPivot });
}

void TombStone::Drop()
{
	__super::Move(GJHVector(0, 1500.f * GJHGameEngineTime::FDeltaTime()));
}

void TombStone::Up()
{
	GJHVector ActorPivot = m_AniRender->GetActorPivot();
	SetActorPivot(ActorPivot + GJHVector(0, -2));
}

void TombStone::Down()
{
	GJHVector ActorPivot = m_AniRender->GetActorPivot();
	SetActorPivot(ActorPivot + GJHVector(0, 2));
}

void TombStone::Damage()
{
	DamageAniChangeUpdater.Reset();
	m_IsDamage = true;

	DrawDamageAnimation("TombStone");
}

void TombStone::LoopDamage()
{
	Damage();
	DamageAniChangeUpdater.m_bLoop = true;
}

void TombStone::AniIndexChange()
{
	int CurFrame = GetAnimationFrameIndex();
	if (m_AniRender->GetAnimationEndFrame() <= CurFrame)
	{
		Death();
	}
	else
	{
		SetAnimationFrameIndex(CurFrame + 1);
	}
}

void TombStone::CreateStone(ENUM_DIRECTION _Dir, float _MoveSpeed, float _Gravity)
{
	float Random = (GJHMath::Random(5) / 10.f) + 1.f;
	float XPosRandom = (float)GJHMath::Random(-50, 50);

	InstanceObjectData Data;
	Data.Size = GJHVector(128 * Random, 900 * Random);
	Data.Pos = GetPos() + GJHVector(XPosRandom, -50.f);
	Data.ImageFileName = "MonoeyeUFO_Effect";
	Data.ImageDir = _Dir;
	Data.StartFrame = 12;
	Data.EndFrame = 19;
	Data.FrameTime = 0.05f;
	Data.MoveSpeed = _MoveSpeed;
	Data.IsGravity = true;
	Data.Gravity = _Gravity;
	Data.GravityAddValue = 300.f;
	Data.IsLoop = true;
	Data.CheckColMap = true;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void TombStone::DropInit()
{
	ChangeAnimation("TombStone");
}

void TombStone::DropState()
{
	Drop();

	if (ColMap((int)(m_AniRender->GetSize().y / 2) - 30) == true)
	{
		m_ThisDamageCollision->Off();

		GJHCameraManager::CamShake(2.f, 0.7f);
		State.ChangeState("Land");
	}
}

void TombStone::LandInit()
{
	AniChangeTimer.Reset();
	AniChangeTimer.SetEventTime(0.3f, false);

	CreateStone(ENUM_DIRECTION::LEFT, 100.f, -300.f);
	CreateStone(ENUM_DIRECTION::LEFT, 150.f, -500.f);
	CreateStone(ENUM_DIRECTION::LEFT, 200.f, -600.f);
	CreateStone(ENUM_DIRECTION::RIGHT, 50.f, -100.f);
	CreateStone(ENUM_DIRECTION::RIGHT, 130.f, -200.f);
	CreateStone(ENUM_DIRECTION::RIGHT, 250.f, -400.f);

	GJHGameEngineSound::PlayOneShot("TombStoneLand.mp3", 1.f);

	m_AniCollision->SetHitable(true);
	m_AttackCollision->SetHitable(false);
	m_SubAniRender->SetDraw(true);
}

void TombStone::LandState()
{
	UpDownUpdater.Update();
	AniChangeTimer.EventUpdate();

	if (m_IsDamage == true)
	{
		DamageAniChangeUpdater.Update();
		if (DamageAniChangeUpdater.GetIsEnd() == true)
		{
			m_IsDamage = false;
		}
	}

	if (AniChangeTimer.CheckEventTime() == true)
	{
		AniIndexChange();
	}
}

void TombStone::SetAnimationData()
{
	PushAnimationData("TombStone", 0, 0, -250, 1000.f);
	PushAnimationData("TombStone", 1, 0, -245, 1000.f);
	PushAnimationData("TombStone", 2, 0, -238, 1000.f);
	PushAnimationData("TombStone", 3, 0, -229, 1000.f);
	PushAnimationData("TombStone", 4, 0, -220, 1000.f);
	PushAnimationData("TombStone", 5, 0, -210, 1000.f);
	PushAnimationData("TombStone", 6, 0, -204, 1000.f);
	PushAnimationData("TombStone", 7, 0, -201, 1000.f);
	PushAnimationData("TombStone", 8, 0, -197, 1000.f);
	PushAnimationData("TombStone", 9, -2, -187, 1000.f);
	PushAnimationData("TombStone", 10, -6, -180, 1000.f);
	PushAnimationData("TombStone", 11, -9, -173, 1000.f);
	PushAnimationData("TombStone", 12, -7, -167, 1000.f);
	PushAnimationData("TombStone", 13, -8, -160, 1000.f);
	PushAnimationData("TombStone", 14, -8, -153, 1000.f);
	PushAnimationData("TombStone", 15, -8, -147, 1000.f);
	PushAnimationData("TombStone", 16, -7, -138, 1000.f);
	PushAnimationData("TombStone", 17, -7, -131, 1000.f);
	PushAnimationData("TombStone", 18, -7, -124, 1000.f);
	PushAnimationData("TombStone", 19, -9, -117, 1000.f);
	PushAnimationData("TombStone", 20, -9, -110, 1000.f);
	PushAnimationData("TombStone", 21, -9, -103, 1000.f);
	PushAnimationData("TombStone", 22, -9, -96, 1000.f);
	PushAnimationData("TombStone", 23, -9, -89, 1000.f);
	PushAnimationData("TombStone", 24, -9, -82, 1000.f);
	PushAnimationData("TombStone", 25, -9, -75, 1000.f);
	PushAnimationData("TombStone", 26, -7, -68, 1000.f);
	PushAnimationData("TombStone", 27, -7, -61, 1000.f);
	PushAnimationData("TombStone", 28, -7, -54, 1000.f);
	PushAnimationData("TombStone", 29, -7, -47, 1000.f);
	PushAnimationData("TombStone", 30, -7, -40, 1000.f);
	PushAnimationData("TombStone", 31, -7, -33, 1000.f);
	PushAnimationData("TombStone", 32, -7, -26, 1000.f);
}