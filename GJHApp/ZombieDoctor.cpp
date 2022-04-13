#include "ZombieDoctor.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "ZombieThrowVomit.h"
#include "InstanceObject.h"

void ZombieDoctor::Start()
{
	SetDefaultHP(10);

	m_MoveSpeed = 50.f;

	m_AniRender = CreateRender({ 512, 512 }, "ZombieDoctor(Right).bmp", ContentsEnum::RENDERORDER::MONSTER);
	CreateAnimation("Idle", "ZombieDoctor", 0, 6, 0.1f, true, true);
	CreateAnimation("Move", "ZombieDoctor", 7, 18, 0.1f, true);
	CreateAnimation("Attack", "ZombieDoctor", 19, 46, 0.1f, false);
	CreateAnimation("BulletDeath", "ZombieDoctorDeath", 0, 14, 0.05f, false);
	CreateAnimation("GranadeDeath", "ZombieDoctorDeath", 15, 39, 0.08f, false);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -70 }, { 80, 130 }, ContentsEnum::COLTYPE::MONSTER);

	State.CreateState("Idle", &ZombieDoctor::IdleInit, &ZombieDoctor::IdleState, nullptr, this);
	State.CreateState("Move", &ZombieDoctor::MoveInit, &ZombieDoctor::MoveState, nullptr, this);
	State.CreateState("Attack", &ZombieDoctor::AttackInit, &ZombieDoctor::AttackState, nullptr, this);
	State.CreateState("BulletDeath", &ZombieDoctor::BulletDeathInit, &ZombieDoctor::BulletDeathState, nullptr, this);
	State.CreateState("GranadeDeath", &ZombieDoctor::GranadeDeathInit, &ZombieDoctor::GranadeDeathState, nullptr, this);

	State.ChangeState("Idle");
	SetDir(State.CurState, ENUM_DIRECTION::LEFT);

	SetAnimationData();
}

void ZombieDoctor::Update()
{
	DirUpdate(State.CurState);
	State.Update();

	__super::Update();
	__super::AnimationDataCheck(State.CurState);
}

void ZombieDoctor::ColEnter(GJHCollision* _This, GJHCollision* _Other)
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

void ZombieDoctor::IdleInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Idle");
}

void ZombieDoctor::IdleState()
{
	if (MoveCheck() == true)
	{
		State.ChangeState("Move");
	}
}

void ZombieDoctor::MoveInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Move");
}

void ZombieDoctor::MoveState()
{
	if (MoveCheck() == false)
	{
		State.ChangeState("Idle");
	}

	if (abs(PlayerDistance().x) < 400 &&
		CheckInsideCam() == true)
	{
		State.ChangeState("Attack");
	}

	__super::Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
}

void ZombieDoctor::AttackInit()
{
	IsThrowVomit = false;
	m_IsDirCheck = false;

	ChangeAnimation("Attack");
}

void ZombieDoctor::AttackState()
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

void ZombieDoctor::BulletDeathInit()
{
	m_IsDirCheck = false;

	m_AniCollision->SetHitable(false);

	GJHGameEngineSound::PlayOneShot("ZombieManDeath.mp3");
	ChangeAnimation("BulletDeath");
}

void ZombieDoctor::BulletDeathState()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void ZombieDoctor::GranadeDeathInit()
{
	m_IsDirCheck = false;

	m_AniCollision->SetHitable(false);

	GJHGameEngineSound::PlayOneShot("ZombieManDeath.mp3");
	ChangeAnimation("GranadeDeath");
}

void ZombieDoctor::GranadeDeathState()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void ZombieDoctor::CreateThrowVomit()
{
	{
		InstanceObjectData Data;
		Data.Size = GJHVector(256, 256);
		Data.Pos = GetPos();
		Data.ImageFileName = "ZombieDoctorAttack";
		Data.ImageDir = m_ImageDir;
		Data.ActorPivot = GJHVector(20, 0);
		Data.StartFrame = 0;
		Data.EndFrame = 11;
		Data.FrameTime = 0.1f;

		AniDataMap Map;
		float Delay = 0.1f;
		Map[0] = { PivotData(40, -55), Delay };
		Map[1] = { PivotData(60, -60), Delay };
		Map[2] = { PivotData(90, -70), Delay };
		Map[3] = { PivotData(95, -55), Delay };
		Map[4] = { PivotData(75, -55), Delay };
		Map[5] = { PivotData(75, -55), Delay };
		Map[6] = { PivotData(75, -55), Delay };
		Map[7] = { PivotData(75, -55), Delay };
		Map[8] = { PivotData(65, -55), Delay };
		Map[9] = { PivotData(65, -40), Delay };
		Map[10] = { PivotData(50, -10), Delay };
		Map[11] = { PivotData(75, -10), Delay };
		Data.AniData = Map;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);
	}

	ZombieThrowVomit* NewVomit = GetScene()->CreateActor<ZombieThrowVomit>();
	NewVomit->SetPos(GetPos() + GJHVector((float)(80 * (int)m_ImageDir), -70));
	NewVomit->SetDir("ThrowVomit", m_ImageDir);
	NewVomit->SetMoveSpeed(400.f);
	NewVomit->SetGravity(-300.f);
	NewVomit->SetGravityAddValue(1000.f);
}

void ZombieDoctor::SetAnimationData()
{
	float Delay = 0.1f;
	int XGap = 0;
	int YGap = 0;
	PushAnimationData("Idle", 0, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 1, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 2, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 3, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 4, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 5, 12 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 6, 15 + XGap, 0 + YGap, Delay);

	PushAnimationData("Move", 7, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 8, 24 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 9, 27 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 10, 5 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 11, 21 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 12, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 13, 13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 14, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 15, 30 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 16, 33 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 17, 33 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 18, 25 + XGap, 0 + YGap, Delay);

	PushAnimationData("Attack", 19, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 20, 7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 21, 4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 22, 7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 23, -3 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 24, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 25, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 26, 22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 27, 26 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 28, 26 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 29, -9 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 30, -9 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 31, -13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 32, -6 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 33, -6 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 34, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 35, 22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 36, 24 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 37, 27 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 38, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 39, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 40, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 41, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 42, -3 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 43, -4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 44, -4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 45, 4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 46, 11 + XGap, 0 + YGap, Delay);

	PushAnimationData("AttackEffect", 0, 40 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 1, 60 + XGap, -60 + YGap, Delay);
	PushAnimationData("AttackEffect", 2, 90 + XGap, -70 + YGap, Delay);
	PushAnimationData("AttackEffect", 3, 95 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 4, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 5, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 6, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 7, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 8, 65 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 9, 65 + XGap, -40 + YGap, Delay);
	PushAnimationData("AttackEffect", 10, 50 + XGap, -10 + YGap, Delay);
	PushAnimationData("AttackEffect", 11, 75 + XGap, -10 + YGap, Delay);

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
	PushAnimationData("GranadeDeath", 17, 12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 18, 12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 19, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 20, -1 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 21, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 22, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 23, 23 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 24, 22 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 25, 23 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 26, 19 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 27, 16 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 28, 20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 29, 18 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 30, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 31, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 32, -10 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 33, -13 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 34, 2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 35, -8 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 36, -10 + XGap, -95 + YGap, Delay);
	PushAnimationData("GranadeDeath", 37, -10 + XGap, -95 + YGap, Delay);
	PushAnimationData("GranadeDeath", 38, 1 + XGap, -53 + YGap, Delay);
	PushAnimationData("GranadeDeath", 39, 4 + XGap, -53 + YGap, Delay);
}