#include "ZombieMorden.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "ZombieThrowVomit.h"
#include "InstanceObject.h"

void ZombieMorden::Start()
{
	SetDefaultHP(10);

	m_MoveSpeed = 100.f;
	m_AttackStart = false;

	m_AniRender = CreateRender({ 512, 512 }, "ZombieMorden(Right).bmp", ContentsEnum::RENDERORDER::MONSTER);
	CreateAnimation("Idle", "ZombieMorden", 16, 20, 0.15f, true, true);
	CreateAnimation("Move", "ZombieMorden", 0, 15, 0.08f, true);
	CreateAnimation("Attack", "ZombieMorden", 23, 32, 0.1f, false);
	CreateAnimation("Death", "ZombieDoctorDeath", 0, 14, 0.05f, false);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -70 }, { 80, 130 }, ContentsEnum::COLTYPE::MONSTER);

	State.CreateState("Idle", &ZombieMorden::IdleInit, &ZombieMorden::IdleState, nullptr, this);
	State.CreateState("Move", &ZombieMorden::MoveInit, &ZombieMorden::MoveState, nullptr, this);
	State.CreateState("Attack", &ZombieMorden::AttackInit, &ZombieMorden::AttackState, nullptr, this);
	State.CreateState("Death", &ZombieMorden::DeathInit, &ZombieMorden::DeathState, nullptr, this);

	State.ChangeState("Idle");
	SetDir(State.CurState, ENUM_DIRECTION::LEFT);

	SetAnimationData();
}

void ZombieMorden::Update()
{
	DirUpdate(State.CurState);
	State.Update();

	__super::Update();
	__super::AnimationDataCheck(State.CurState);
}

void ZombieMorden::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (m_AttackStart == true &&
		_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		CreateAttackExplosion();
		Death();
	}
	
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		m_HP--;

		CreateBlood(GJHVector(15, -50), 0, 10, 0, 30);

		if (IsDeath() == true)
		{
			MinusMonsterCount();
			State.ChangeState("Death");
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE)
	{
		m_HP -= 10;

		if (IsDeath() == true)
		{
			MinusMonsterCount();
			State.ChangeState("Death");
		}
	}
}

void ZombieMorden::CreateAttackExplosion()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(256, 256);
	Data.Pos = GetPos();
	Data.ImageFileName = "ZombieMorden_Attack";
	Data.ImageDir = m_ImageDir;
	Data.StartFrame = 0;
	Data.EndFrame = 17;
	Data.SoundFrame = 0;
	Data.SoundFileName = "ZombieMordenAttack.mp3";
	Data.SoundVolume = 0.7f;
	Data.CollisionSize = { 120, 150 };
	Data.CollisionPivot = { 0, -75 };
	Data.CollisionType = ContentsEnum::COLTYPE::MONSTERBULLET;
	Data.CollisionEnableFrameIndex = 0;
	Data.CollisionDisableFrameIndex = 2;

	AniDataMap Map;
	Map[0] = { PivotData(0, -50), 0.05f };
	Map[1] = { PivotData(0, -50), 0.05f };
	Map[2] = { PivotData(0, -20), 0.05f };
	Map[3] = { PivotData(0, -55), 0.05f };
	Map[4] = { PivotData(0, -70), 0.05f };
	Map[5] = { PivotData(0, -80), 0.05f };
	Map[6] = { PivotData(5, -90), 0.05f };
	Map[7] = { PivotData(5, -90), 0.05f };
	Map[8] = { PivotData(0, -90), 0.05f };
	Map[9] = { PivotData(0, -90), 0.05f };
	Map[10] = { PivotData(0, -85), 0.05f };
	Map[11] = { PivotData(0, -80), 0.05f };
	Map[12] = { PivotData(0, -85), 0.05f };
	Map[13] = { PivotData(-5, -90), 0.05f };
	Map[14] = { PivotData(-5, -95), 0.05f };
	Map[15] = { PivotData(-5, -95), 0.05f };
	Map[16] = { PivotData(-5, -95), 0.05f };
	Map[17] = { PivotData(0, -87), 0.05f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void ZombieMorden::IdleInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Idle");
}

void ZombieMorden::IdleState()
{
	if (MoveCheck() == true)
	{
		State.ChangeState("Move");
	}
}

void ZombieMorden::MoveInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Move");
}

void ZombieMorden::MoveState()
{
	if (MoveCheck() == false)
	{
		State.ChangeState("Idle");
	}

	if (abs(PlayerDistance().x) < 250 &&
		CheckInsideCam() == true)
	{
		State.ChangeState("Attack");
	}

	__super::Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
}

void ZombieMorden::AttackInit()
{
	m_IsDirCheck = false;

	ChangeAnimation("Attack");

}

void ZombieMorden::AttackState()
{
	if (GetAnimationFrameIndex() == 26 &&
		m_AttackStart == false)
	{
		m_AttackStart = true;
		m_AniCollision->SetActorPivot({ 0, -55 });
		m_AniCollision->SetSize({ 100, 80 });
		Jump(-500.f, 1200.f);
	}

	if (m_AttackStart == true)
	{
		__super::Move(400.f * GJHGameEngineTime::FDeltaTime());
	}

	if (ColMap(30) == true && m_AttackStart == true)
	{
		CreateAttackExplosion();
		Death();
	}
}

void ZombieMorden::DeathInit()
{
	m_IsDirCheck = false;
	m_IsGravity = false;
	m_AniCollision->SetHitable(false);

	ChangeAnimation("Death");

	GJHGameEngineSound::PlayOneShot("ZombieManDeath.mp3");
}

void ZombieMorden::DeathState()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void ZombieMorden::SetAnimationData()
{
	PushAnimationData("Idle", 16, 0, 0, 0.18f);
	PushAnimationData("Idle", 17, 2, 0, 0.15f);
	PushAnimationData("Idle", 18, 4, 0, 0.15f);
	PushAnimationData("Idle", 19, 4, 0, 0.15f);
	PushAnimationData("Idle", 20, 4, 0, 0.15f);

	PushAnimationData("Move", 0, 0, 0, 0.08f);
	PushAnimationData("Move", 1, 0, 0, 0.08f);
	PushAnimationData("Move", 2, 0, 0, 0.08f);
	PushAnimationData("Move", 3, 0, 0, 0.08f);
	PushAnimationData("Move", 4, 0, 0, 0.08f);
	PushAnimationData("Move", 5, 0, 0, 0.08f);
	PushAnimationData("Move", 6, 0, 0, 0.08f);
	PushAnimationData("Move", 7, 0, 0, 0.08f);
	PushAnimationData("Move", 8, 0, 0, 0.08f);
	PushAnimationData("Move", 9, 0, 0, 0.08f);
	PushAnimationData("Move", 10, 0, 0, 0.08f);
	PushAnimationData("Move", 11, 0, 0, 0.08f);
	PushAnimationData("Move", 12, 0, 0, 0.08f);
	PushAnimationData("Move", 13, 0, 0, 0.08f);
	PushAnimationData("Move", 14, 0, 0, 0.08f);
	PushAnimationData("Move", 15, 0, 0, 0.08f);

	PushAnimationData("Attack", 23, 0, 0, 0.10f);
	PushAnimationData("Attack", 24, 0, 0, 0.10f);
	PushAnimationData("Attack", 25, 0, 0, 0.20f);
	PushAnimationData("Attack", 26, 0, 0, 0.10f);
	PushAnimationData("Attack", 27, 0, -20, 0.10f);
	PushAnimationData("Attack", 28, 0, -20, 0.10f);
	PushAnimationData("Attack", 29, 0, -20, 0.10f);
	PushAnimationData("Attack", 30, 0, -20, 0.10f);
	PushAnimationData("Attack", 31, 0, -20, 0.10f);
	PushAnimationData("Attack", 32, 0, -20, 0.10f);
	
	float Delay = 0.05f;
	int XGap = -20;
	int YGap = -60;
	PushAnimationData("Death", 0, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Death", 1, 2 + XGap, -1 + YGap, Delay);
	PushAnimationData("Death", 2, -9 + XGap, -6 + YGap, Delay);
	PushAnimationData("Death", 3, -21 + XGap, -17 + YGap, Delay);
	PushAnimationData("Death", 4, -31 + XGap, -23 + YGap, Delay);
	PushAnimationData("Death", 5, -40 + XGap, -35 + YGap, Delay);
	PushAnimationData("Death", 6, -16 + XGap, -47 + YGap, Delay);
	PushAnimationData("Death", 7, -15 + XGap, -45 + YGap, Delay);
	PushAnimationData("Death", 8, -15 + XGap, -54 + YGap, Delay);
	PushAnimationData("Death", 9, 11 + XGap, -35 + YGap, Delay);
	PushAnimationData("Death", 10, 12 + XGap, -43 + YGap, Delay);
	PushAnimationData("Death", 11, 15 + XGap, -58 + YGap, Delay);
	PushAnimationData("Death", 12, 23 + XGap, -46 + YGap, Delay);
	PushAnimationData("Death", 13, 25 + XGap, -20 + YGap, Delay);
	PushAnimationData("Death", 14, 11 + XGap, -9 + YGap, Delay);
}