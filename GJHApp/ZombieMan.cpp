#include "ZombieMan.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "ZombieThrowVomit.h"
#include "InstanceObject.h"

void ZombieMan::Start()
{
	SetDefaultHP(10);

	m_MoveSpeed = 50.f;

	m_AniRender = CreateRender({ 512, 512 }, "ZombieMan(Right).bmp", ContentsEnum::RENDERORDER::MONSTER);
	CreateAnimation("Idle", "ZombieMan", 0, 6, 0.15f, true, true);
	CreateAnimation("Move", "ZombieMan", 7, 22, 0.05f, true);
	CreateAnimation("Attack", "ZombieMan", 23, 42, 0.08f, false);
	CreateAnimation("BulletDeath", "ZombieManDeath", 0, 14, 0.05f, false);
	CreateAnimation("GranadeDeath", "ZombieManDeath", 15, 40, 0.08f, false);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -70 }, { 80, 130 }, ContentsEnum::COLTYPE::MONSTER);

	State.CreateState("Idle", &ZombieMan::IdleInit, &ZombieMan::IdleState, nullptr, this);
	State.CreateState("Move", &ZombieMan::MoveInit, &ZombieMan::MoveState, nullptr, this);
	State.CreateState("Attack", &ZombieMan::AttackInit, &ZombieMan::AttackState, nullptr, this);
	State.CreateState("BulletDeath", &ZombieMan::BulletDeathInit, &ZombieMan::BulletDeathState, nullptr, this);
	State.CreateState("GranadeDeath", &ZombieMan::GranadeDeathInit, &ZombieMan::GranadeDeathState, nullptr, this);

	State.ChangeState("Idle");
	SetDir(State.CurState, ENUM_DIRECTION::LEFT);

	SetAnimationData();
}

void ZombieMan::Update()
{
	DirUpdate(State.CurState);
	State.Update();

	__super::Update();
	__super::AnimationDataCheck(State.CurState);
}

void ZombieMan::ColEnter(GJHCollision* _This, GJHCollision* _Other)
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

void ZombieMan::IdleInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Idle");
}

void ZombieMan::IdleState()
{
	if (MoveCheck() == true)
	{
		State.ChangeState("Move");
	}
}

void ZombieMan::MoveInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Move");
	SetFrameTime(22, 0.2f);
}

void ZombieMan::MoveState()
{
	if (MoveCheck() == false)
	{
		State.ChangeState("Idle");
	}

	if (abs(PlayerDistance().x) < 450 &&
		CheckInsideCam() == true)
	{
		State.ChangeState("Attack");
	}

	__super::Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
}

void ZombieMan::AttackInit()
{
	IsThrowVomit = false;
	m_IsDirCheck = false;

	ChangeAnimation("Attack");
}

void ZombieMan::AttackState()
{
	if (GetAnimationFrameIndex() == 32 && IsThrowVomit == false)
	{
		IsThrowVomit = true;

		CreateThrowVomit();
	}

	if (AnimationEnd() == true)
	{
		State.ChangeState("Idle");
	}
}

void ZombieMan::BulletDeathInit()
{
	m_IsDirCheck = false;

	m_AniCollision->SetHitable(false);

	GJHGameEngineSound::PlayOneShot("ZombieManDeath.mp3");
	ChangeAnimation("BulletDeath");
}

void ZombieMan::BulletDeathState()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void ZombieMan::GranadeDeathInit()
{
	m_IsDirCheck = false;

	m_AniCollision->SetHitable(false);

	GJHGameEngineSound::PlayOneShot("ZombieManDeath.mp3");
	ChangeAnimation("GranadeDeath");
}

void ZombieMan::GranadeDeathState()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void ZombieMan::CreateThrowVomit()
{
	{
		InstanceObjectData Data;
		Data.Size = GJHVector(256, 256);
		Data.Pos = GetPos();
		Data.ImageFileName = "ZombieManAttack";
		Data.ImageDir = m_ImageDir;
		Data.ActorPivot = GJHVector(10, -120);
		Data.StartFrame = 0;
		Data.EndFrame = 11;
		Data.FrameTime = 0.05f;

		AniDataMap Map;
		float Delay = 0.08f;
		Map[0] = { PivotData(5, -10), Delay };
		Map[1] = { PivotData(0, -15), Delay };
		Map[2] = { PivotData(5, -15), Delay };
		Map[3] = { PivotData(5, -20), Delay };
		Map[4] = { PivotData(0, -20), Delay };
		Map[5] = { PivotData(0, -5), Delay };
		Map[6] = { PivotData(5, -10), Delay };
		Map[7] = { PivotData(0, -10), Delay };
		Map[8] = { PivotData(0, -10), Delay };
		Map[9] = { PivotData(5, -15), Delay };
		Map[10] = { PivotData(5, -5), Delay };
		Map[11] = { PivotData(10, -10), Delay };
		Data.AniData = Map;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);
	}

	ZombieThrowVomit* NewVomit = GetScene()->CreateActor<ZombieThrowVomit>();
	NewVomit->SetPos(GetPos() + GJHVector((float)(40 * (int)m_ImageDir), -150));
	NewVomit->SetDir("ThrowVomit", m_ImageDir);
	NewVomit->SetMoveSpeed(400.f);
	NewVomit->SetGravity(-300.f);
	NewVomit->SetGravityAddValue(1000.f);
}

void ZombieMan::SetAnimationData()
{
	float Delay = 0.1f;
	int XGap = 0;
	int YGap = 0;
	PushAnimationData("Idle", 0, 0, 0, 0.10f);
	PushAnimationData("Idle", 1, 0, 0, 0.10f);
	PushAnimationData("Idle", 2, 4, 0, 0.10f);
	PushAnimationData("Idle", 3, 1, 0, 0.10f);
	PushAnimationData("Idle", 4, 1, 0, 0.10f);
	PushAnimationData("Idle", 5, -3, 0, 0.10f);
	PushAnimationData("Idle", 6, -3, 0, 0.10f);

	PushAnimationData("Move", 7, 3, 0, Delay);
	PushAnimationData("Move", 8, 3, 0, Delay);
	PushAnimationData("Move", 10, -4, 0, Delay);
	PushAnimationData("Move", 12, -4, 0, Delay);
	PushAnimationData("Move", 13, 6, 0, Delay);
	PushAnimationData("Move", 14, 4, 0, Delay);
	PushAnimationData("Move", 15, 4, 0, Delay);
	PushAnimationData("Move", 16, 8, 0, Delay);
	PushAnimationData("Move", 17, -18, 0, Delay);
	PushAnimationData("Move", 18, -26, 0, Delay);
	PushAnimationData("Move", 19, -20, 0, Delay);
	PushAnimationData("Move", 20, -12, 0, Delay);
	PushAnimationData("Move", 21, -10, 0, Delay);
	PushAnimationData("Move", 22, -10, 0, Delay);

	PushAnimationData("Attack", 23, 0, 0, 0.08f);
	PushAnimationData("Attack", 24, -6, 0, 0.08f);
	PushAnimationData("Attack", 25, -9, 0, 0.08f);
	PushAnimationData("Attack", 26, 5, 0, 0.08f);
	PushAnimationData("Attack", 27, 2, 0, 0.08f);
	PushAnimationData("Attack", 28, -5, 0, 0.08f);
	PushAnimationData("Attack", 29, 9, 0, 0.08f);
	PushAnimationData("Attack", 30, 8, 0, 0.08f);
	PushAnimationData("Attack", 31, 15, 0, 0.08f);
	PushAnimationData("Attack", 32, 5, 0, 0.08f);
	PushAnimationData("Attack", 33, -2, 0, 0.24f);
	PushAnimationData("Attack", 34, -2, 0, 0.12f);
	PushAnimationData("Attack", 35, -9, 0, 0.12f);
	PushAnimationData("Attack", 36, -19, 0, 0.12f);
	PushAnimationData("Attack", 37, -19, 0, 0.12f);
	PushAnimationData("Attack", 38, -19, 0, 0.12f);
	PushAnimationData("Attack", 39, -12, 0, 0.12f);
	PushAnimationData("Attack", 40, -9, 0, 0.12f);
	PushAnimationData("Attack", 41, 1, 0, 0.12f);
	PushAnimationData("Attack", 42, 1, 0, 0.12f);

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
	PushAnimationData("GranadeDeath", 15, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 16, 8 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 17, 1 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 18, 1 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 19, -14 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 20, -11 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 21, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 22, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 23, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 24, 5 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 25, 7 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 26, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 27, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 28, 7 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 29, 3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 30, -21 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 31, -22 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 32, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 33, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 34, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 35, -15 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 36, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 37, -35 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 38, -10 + XGap, -55 + YGap, Delay);
	PushAnimationData("GranadeDeath", 39, -6 + XGap, -27 + YGap, Delay);
	PushAnimationData("GranadeDeath", 40, 0 + XGap, -30 + YGap, Delay);
}