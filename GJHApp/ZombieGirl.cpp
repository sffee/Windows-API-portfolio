#include "ZombieGirl.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "ZombieThrowVomit.h"
#include "InstanceObject.h"

void ZombieGirl::Start()
{
	SetDefaultHP(10);

	m_MoveSpeed = 50.f;

	m_AniRender = CreateRender({ 512, 512 }, "ZombieGirl(Right).bmp", ContentsEnum::RENDERORDER::MONSTER);
	CreateAnimation("Idle", "ZombieGirl", 0, 11, 0.1f, true);
	CreateAnimation("Move", "ZombieGirl", 12, 23, 0.1f, true);
	CreateAnimation("Attack", "ZombieGirl", 25, 44, 0.1f, false);
	CreateAnimation("BulletDeath", "ZombieGirlDeath", 0, 14, 0.05f, false);
	CreateAnimation("GranadeDeath", "ZombieGirlDeath", 15, 33, 0.08f, false);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -70 }, { 80, 130 }, ContentsEnum::COLTYPE::MONSTER);

	State.CreateState("Idle", &ZombieGirl::IdleInit, &ZombieGirl::IdleState, nullptr, this);
	State.CreateState("Move", &ZombieGirl::MoveInit, &ZombieGirl::MoveState, nullptr, this);
	State.CreateState("Attack", &ZombieGirl::AttackInit, &ZombieGirl::AttackState, nullptr, this);
	State.CreateState("BulletDeath", &ZombieGirl::BulletDeathInit, &ZombieGirl::BulletDeathState, nullptr, this);
	State.CreateState("GranadeDeath", &ZombieGirl::GranadeDeathInit, &ZombieGirl::GranadeDeathState, nullptr, this);

	State.ChangeState("Idle");
	SetDir(State.CurState, ENUM_DIRECTION::LEFT);

	SetAnimationData();

}

void ZombieGirl::Update()
{
	DirUpdate(State.CurState);
	State.Update();

	__super::Update();
	__super::AnimationDataCheck(State.CurState);
}

void ZombieGirl::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		m_HP--;

		CreateBlood(GJHVector(15, -80), 0, 10, 0, 50);

		if (IsDeath() == true)
		{
			MinusMonsterCount();
			State.ChangeState("BulletDeath");
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE)
	{
		m_HP -= 10;

		if (IsDeath() == true)
		{
			MinusMonsterCount();
			State.ChangeState("GranadeDeath");
		}
	}
}

void ZombieGirl::IdleInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Idle");
}

void ZombieGirl::IdleState()
{
	if (MoveCheck() == true)
	{
		State.ChangeState("Move");
	}
}

void ZombieGirl::MoveInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Move");
}

void ZombieGirl::MoveState()
{
	if (MoveCheck() == false)
	{
		State.ChangeState("Idle");
	}

	if (abs(PlayerDistance().x) < 300 &&
		CheckInsideCam() == true)
	{
		State.ChangeState("Attack");
	}

	__super::Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
}

void ZombieGirl::AttackInit()
{
	IsThrowVomit = false;
	m_IsDirCheck = false;

	ChangeAnimation("Attack");
}

void ZombieGirl::AttackState()
{
	if (GetAnimationFrameIndex() == 36 && IsThrowVomit == false)
	{
		IsThrowVomit = true;

		CreateThrowVomit();
	}

	if (AnimationEnd() == true)
	{
		State.ChangeState("Idle");
	}
}

void ZombieGirl::BulletDeathInit()
{
	m_IsDirCheck = false;

	m_AniCollision->SetHitable(false);

	GJHGameEngineSound::PlayOneShot("ZombieGirlDeath.mp3");
	ChangeAnimation("BulletDeath");
}

void ZombieGirl::BulletDeathState()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void ZombieGirl::GranadeDeathInit()
{
	m_IsDirCheck = false;

	m_AniCollision->SetHitable(false);

	GJHGameEngineSound::PlayOneShot("ZombieGirlDeath.mp3");
	ChangeAnimation("GranadeDeath");
}

void ZombieGirl::GranadeDeathState()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void ZombieGirl::CreateThrowVomit()
{
	{
		InstanceObjectData Data;
		Data.Size = GJHVector(256, 256);
		Data.Pos = GetPos();
		Data.ImageFileName = "ZombieGirlAttack";
		Data.ImageDir = m_ImageDir;
		Data.ActorPivot = GJHVector(20, 0);
		Data.StartFrame = 0;
		Data.EndFrame = 9;
		Data.FrameTime = 0.1f;

		AniDataMap Map;
		float Delay = 0.1f;
		Map[0] = { PivotData(-17, -119), Delay };
		Map[1] = { PivotData(-11, -111), Delay };
		Map[2] = { PivotData(23, -99), Delay };
		Map[3] = { PivotData(38, -94), Delay };
		Map[4] = { PivotData(43, -84), Delay };
		Map[5] = { PivotData(53, -74), Delay };
		Map[6] = { PivotData(23, -84), Delay };
		Map[7] = { PivotData(23, -64), Delay };
		Map[8] = { PivotData(38, -59), Delay };
		Map[9] = { PivotData(43, -59), Delay };
		Data.AniData = Map;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);
	}

	ZombieThrowVomit* NewVomit = GetScene()->CreateActor<ZombieThrowVomit>();
	NewVomit->SetPos(GetPos() + GJHVector((float)(10 * (int)m_ImageDir), -120));
	NewVomit->SetDir("ThrowVomit", m_ImageDir);
	NewVomit->SetMoveSpeed(400.f);
	NewVomit->SetGravity(-300.f);
	NewVomit->SetGravityAddValue(1000.f);
}

void ZombieGirl::SetAnimationData()
{
	float Delay = 0.1f;
	int XGap = 0;
	int YGap = 0;
	PushAnimationData("Idle", 0, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 1, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 2, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 3, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 4, 11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 5, 4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 6, 11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 7, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 8, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 9, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 10, -2 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 11, -2 + XGap, 0 + YGap, Delay);

	PushAnimationData("Move", 12, -17 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 13, -17 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 14, -7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 15, 10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 16, 10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 17, 10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 18, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 19, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 20, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 21, -12 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 22, -17 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 23, -22 + XGap, 0 + YGap, Delay);

	PushAnimationData("Attack", 25, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 26, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 27, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 28, -3 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 29, -7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 30, -10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 31, -24 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 32, -32 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 33, -11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 34, -11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 35, -8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 36, -5 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 37, -22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 38, -22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 39, 13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 40, 2 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 41, 2 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 42, 27 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 43, 13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 44, 3 + XGap, 0 + YGap, Delay);

	Delay = 0.05f;
	XGap = -20;
	YGap = -60;
	PushAnimationData("BulletDeath", 0, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("BulletDeath", 1, 2 + XGap, -1 + YGap, Delay);
	PushAnimationData("BulletDeath", 2, -9 + XGap, -6 + YGap, Delay);
	PushAnimationData("BulletDeath", 3, -21 + XGap, -17 + YGap, Delay);
	PushAnimationData("BulletDeath", 4, -31 + XGap, -23 + YGap, Delay);
	PushAnimationData("BulletDeath", 5, -40 + XGap, -35 + YGap, Delay);
	PushAnimationData("BulletDeath", 6, -16 + XGap, -47 + YGap, Delay);
	PushAnimationData("BulletDeath", 7, -15 + XGap, -45 + YGap, Delay);
	PushAnimationData("BulletDeath", 8, -15 + XGap, -54 + YGap, Delay);
	PushAnimationData("BulletDeath", 9, 11 + XGap, -35 + YGap, Delay);
	PushAnimationData("BulletDeath", 10, 12 + XGap, -43 + YGap, Delay);
	PushAnimationData("BulletDeath", 11, 15 + XGap, -58 + YGap, Delay);
	PushAnimationData("BulletDeath", 12, 23 + XGap, -46 + YGap, Delay);
	PushAnimationData("BulletDeath", 13, 25 + XGap, -20 + YGap, Delay);
	PushAnimationData("BulletDeath", 14, 11 + XGap, -9 + YGap, Delay);

	Delay = 0.08f;
	XGap = 0;
	YGap = 0;
	PushAnimationData("GranadeDeath", 15, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 16, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 17, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 18, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 19, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 20, -10 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 21, -3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 22, -3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 23, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 24, 7 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 25, 3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 26, -14 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 27, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 28, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 29, -5 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 30, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 31, -6 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 32, -32 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 33, -25 + XGap, -110 + YGap, Delay);
}