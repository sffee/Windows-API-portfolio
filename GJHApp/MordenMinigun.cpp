#include "MordenMinigun.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "InstanceObject.h"
#include "MonsterBullet.h"

void MordenMinigun::Start()
{
	SetDefaultHP(1);

	m_MoveSpeed = 150.f;

	m_IsShotBullet = false;
	m_Death = false;

	m_AniRender = CreateRender({ 512, 512 }, "Morden_Minigun(Left).bmp", ContentsEnum::RENDERORDER::MONSTER);
	CreateAnimation("Idle", "Morden_Minigun", 31, 34, 0.15f, true, true);
	CreateAnimation("Move", "Morden_Minigun", 8, 19, 0.1f, true);
	CreateAnimation("Attack", "Morden_Minigun", 58, 87, 0.1f, false);
	CreateAnimation("AttackEffect", "Morden_Minigun", 88, 91, 0.1f, false);
	CreateAnimation("Death1", "Morden_Death", 0, 10, 0.1f, false);
	CreateAnimation("Death2", "Morden_Death", 48, 54, 0.1f, false);
	CreateAnimation("GranadeDeathJump", "Morden_Death", 81, 85, 0.06f, true, true);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -70 }, { 80, 130 }, ContentsEnum::COLTYPE::MONSTER);

	State.CreateState("Idle", &MordenMinigun::IdleInit, &MordenMinigun::IdleState, nullptr, this);
	State.CreateState("Move", &MordenMinigun::MoveInit, &MordenMinigun::MoveState, nullptr, this);
	State.CreateState("Attack", &MordenMinigun::AttackInit, &MordenMinigun::AttackState, nullptr, this);
	State.CreateState("Death1", &MordenMinigun::Death1Init, &MordenMinigun::Death1State, nullptr, this);
	State.CreateState("Death2", &MordenMinigun::Death2Init, &MordenMinigun::Death2State, nullptr, this);
	State.CreateState("GranadeDeathJump", &MordenMinigun::GranadeDeathJumpInit, &MordenMinigun::GranadeDeathJumpState, nullptr, this);

	State.ChangeState("Idle");
	SetDir(State.CurState, ENUM_DIRECTION::LEFT);

	CoolTimer.SetEventTime(2.f);

	SetAnimationData();
}

void MordenMinigun::Update()
{
	DirUpdate(State.CurState);
	State.Update();
	CoolTimer.EventUpdate();

	__super::Update();
	__super::AnimationDataCheck(State.CurState);
}

void MordenMinigun::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		m_HP--;

		CreateBlood(GJHVector(20, -50));

		if (IsDeath() == true)
		{
			CreateExplosion();
			MinusMonsterCount();

			int Random = GJHMath::Random(1);
			if (Random == 0)
			{
				State.ChangeState("Death1");
			}
			else if (Random == 1)
			{
				State.ChangeState("Death2");
			}
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE)
	{
		m_HP -= 10;

		if (IsDeath() == true)
		{
			CreateExplosion();
			MinusMonsterCount();

			State.ChangeState("GranadeDeathJump");
		}
	}
}

void MordenMinigun::CreateAttackEffect()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = GetPos();
	Data.ImageFileName = "Morden_Minigun";
	Data.ImageDir = m_ImageDir;
	Data.StartFrame = 88;
	Data.EndFrame = 91;

	AniDataMap Map;
	Map[88] = { PivotData(175, -35), 0.05f };
	Map[89] = { PivotData(175, -35), 0.05f };
	Map[90] = { PivotData(145, -30), 0.05f };
	Map[91] = { PivotData(137, -58), 0.05f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void MordenMinigun::CreateBullet()
{
	MonsterBullet* NewBullet = GetScene()->CreateActor<MonsterBullet>();
	NewBullet->SetPos(GetPos() + GJHVector((float)(150 * (int)m_ImageDir), -50));
	NewBullet->SetDir("Bullet", m_ImageDir);
	NewBullet->SetAngle((float)GJHMath::Random(-3, 3));
}

void MordenMinigun::CreateExplosion()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = GetPos();
	Data.ActorPivot = GJHVector(-20, -20);
	Data.ImageFileName = "Explosion";
	Data.ImageDir = m_ImageDir;
	Data.StartFrame = 0;
	Data.EndFrame = 27;

	AniDataMap Map;
	Map[0] = { PivotData(0, -55), 0.03f };
	Map[1] = { PivotData(0, -55), 0.03f };
	Map[2] = { PivotData(0, -45), 0.03f };
	Map[3] = { PivotData(2, -43), 0.03f };
	Map[4] = { PivotData(-2, -43), 0.03f };
	Map[5] = { PivotData(0, -45), 0.03f };
	Map[6] = { PivotData(0, -50), 0.03f };
	Map[7] = { PivotData(0, -50), 0.03f };
	Map[8] = { PivotData(0, -51), 0.03f };
	Map[9] = { PivotData(0, -51), 0.03f };
	Map[10] = { PivotData(0, -51), 0.03f };
	Map[11] = { PivotData(0, -50), 0.03f };
	Map[12] = { PivotData(0, -55), 0.03f };
	Map[13] = { PivotData(2, -55), 0.03f };
	Map[14] = { PivotData(0, -55), 0.03f };
	Map[15] = { PivotData(0, -55), 0.03f };
	Map[16] = { PivotData(0, -55), 0.03f };
	Map[17] = { PivotData(0, -55), 0.03f };
	Map[18] = { PivotData(0, -55), 0.03f };
	Map[19] = { PivotData(0, -55), 0.03f };
	Map[20] = { PivotData(-3, -57), 0.03f };
	Map[21] = { PivotData(-5, -57), 0.03f };
	Map[22] = { PivotData(-4, -62), 0.03f };
	Map[23] = { PivotData(-3, -65), 0.03f };
	Map[24] = { PivotData(-5, -62), 0.03f };
	Map[25] = { PivotData(-5, -64), 0.03f };
	Map[26] = { PivotData(-4, -50), 0.03f };
	Map[27] = { PivotData(-3, -51), 0.03f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void MordenMinigun::IdleInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Idle");
}

void MordenMinigun::IdleState()
{
	if (abs(PlayerDistance().x) < 800 &&
		abs(PlayerDistance().y) < 40 &&
		CoolTimer.CheckEventTime() == true)
	{
		State.ChangeState("Attack");
	}
	else if (MoveCheck() == true &&
			 400 < abs(PlayerDistance().x))
	{
		State.ChangeState("Move");
	}
}

void MordenMinigun::MoveInit()
{
	m_IsDirCheck = true;

	ChangeAnimation("Move");
}

void MordenMinigun::MoveState()
{
	if (MoveCheck() == false ||
		(abs(PlayerDistance().x) < 400 &&
		 abs(PlayerDistance().y) < 40))
	{
		State.ChangeState("Idle");
	}

	if (abs(PlayerDistance().x) < 800 &&
		abs(PlayerDistance().y) < 40 &&
		CoolTimer.CheckEventTime() == true &&
		CheckInsideCam() == true)
	{
		State.ChangeState("Attack");
	}

	__super::Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
}

void MordenMinigun::AttackInit()
{
	m_IsShotBullet = false;
	m_IsOneShot = false;
	m_IsDirCheck = false;

	ChangeAnimation("Attack");
}

void MordenMinigun::AttackState()
{
	if (GetAnimationFrameIndex() == 78 &&
		m_IsOneShot == false &&
		m_IsShotBullet == false)
	{
		GJHGameEngineSound::PlayOneShot("MordenMinigunAttack.mp3");
	}

	if (GetAnimationFrameIndex() == 78 &&
		m_IsShotBullet == false)
	{
		m_IsShotBullet = true;

		CreateAttackEffect();
		CreateBullet();
	}

	if (GetAnimationFrameIndex() == 80 &&
		m_IsOneShot == true)
	{
		m_IsShotBullet = false;
	}

	if (GetAnimationFrameIndex() == 81 &&
		m_IsOneShot == true)
	{
		if (m_IsOneShot == true &&
			m_IsShotBullet == false)
		{
			m_IsShotBullet = true;

			CreateBullet();
		}
	}

	if (GetAnimationFrameIndex() == 82 &&
		m_IsOneShot == false)
	{
		m_IsOneShot = true;
		m_IsShotBullet = false;

		SetAnimationFrameIndex(78);
	}

	if (AnimationEnd() == true)
	{
		CoolTimer.ResetEventTime();
		State.ChangeState("Idle");
	}
}

void MordenMinigun::Death1Init()
{
	m_IsDirCheck = false;

	GJHGameEngineSound::PlayOneShot("MordenDeath3.mp3", 1.f);

	m_AniCollision->SetHitable(false);
	ChangeAnimation("Death1");
}

void MordenMinigun::Death1State()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void MordenMinigun::Death2Init()
{
	m_IsDirCheck = false;

	GJHGameEngineSound::PlayOneShot("MordenDeath5.mp3", 1.f);

	m_AniCollision->SetHitable(false);
	ChangeAnimation("Death2");
}

void MordenMinigun::Death2State()
{
	if (AnimationEnd() == true)
	{
		Death();
	}
}

void MordenMinigun::GranadeDeathJumpInit()
{
	m_IsDirCheck = false;

	GJHGameEngineSound::PlayOneShot("MordenDeath4.mp3", 1.f);

	m_AniCollision->SetHitable(false);
	ChangeAnimation("GranadeDeathJump");
	Jump(-700.f);
	m_GravityAddValue = 1200.f;
}

void MordenMinigun::GranadeDeathJumpState()
{
	__super::Move(-150.f * GJHGameEngineTime::FDeltaTime());

	if (ColMap(10) == true)
	{
		State.ChangeState("Death1");
	}
}

void MordenMinigun::SetAnimationData()
{
	PushAnimationData("Idle", 31, 0, 0, 0.13f);
	PushAnimationData("Idle", 32, 0, 0, 0.13f);
	PushAnimationData("Idle", 33, -4, 0, 0.13f);
	PushAnimationData("Idle", 34, -5, 0, 0.13f);

	PushAnimationData("Attack", 58, 0, 0, 0.15f);
	PushAnimationData("Attack", 59, -5, 0, 0.15f);
	PushAnimationData("Attack", 60, -6, 0, 0.15f);
	PushAnimationData("Attack", 61, -6, 0, 0.15f);
	PushAnimationData("Attack", 62, -6, 0, 0.06f);
	PushAnimationData("Attack", 63, -12, 0, 0.06f);
	PushAnimationData("Attack", 64, -14, 0, 0.06f);
	PushAnimationData("Attack", 65, -15, 0, 0.06f);
	PushAnimationData("Attack", 66, -8, 0, 0.06f);
	PushAnimationData("Attack", 67, -9, 0, 0.06f);
	PushAnimationData("Attack", 68, -3, 0, 0.12f);
	PushAnimationData("Attack", 69, -2, 0, 0.12f);
	PushAnimationData("Attack", 70, -2, 0, 0.12f);
	PushAnimationData("Attack", 71, 5, 0, 0.12f);
	PushAnimationData("Attack", 72, 3, 0, 0.12f);
	PushAnimationData("Attack", 73, 7, 0, 0.12f);
	PushAnimationData("Attack", 74, 12, 0, 0.12f);
	PushAnimationData("Attack", 75, 22, 0, 0.12f);
	PushAnimationData("Attack", 76, 23, 0, 0.12f);
	PushAnimationData("Attack", 77, 24, 0, 0.12f);
	PushAnimationData("Attack", 78, 18, 0, 0.05f);
	PushAnimationData("Attack", 79, 24, 0, 0.05f);
	PushAnimationData("Attack", 80, 20, 0, 0.05f);
	PushAnimationData("Attack", 81, 23, 0, 0.05f);
	PushAnimationData("Attack", 82, 22, 0, 0.20f);
	PushAnimationData("Attack", 83, 12, 0, 0.12f);
	PushAnimationData("Attack", 84, -4, 0, 0.12f);
	PushAnimationData("Attack", 85, -7, 0, 0.12f);
	PushAnimationData("Attack", 86, 1, 0, 0.12f);
	PushAnimationData("Attack", 87, 1, 0, 0.12f);

	PushAnimationData("Death1", 0, 0, 0, 0.05f);
	PushAnimationData("Death1", 1, 0, 0, 0.05f);
	PushAnimationData("Death1", 2, 0, 0, 0.05f);
	PushAnimationData("Death1", 3, 0, 0, 0.05f);
	PushAnimationData("Death1", 4, 0, 0, 0.05f);
	PushAnimationData("Death1", 5, 0, 0, 0.05f);
	PushAnimationData("Death1", 6, 0, 0, 0.05f);
	PushAnimationData("Death1", 7, 0, 0, 0.05f);
	PushAnimationData("Death1", 8, 0, 0, 0.05f);
	PushAnimationData("Death1", 9, 0, 0, 0.05f);
	PushAnimationData("Death1", 10, 0, 0, 0.25f);

	PushAnimationData("Death2", 48, 0, 0, 0.08f);
	PushAnimationData("Death2", 49, 0, 0, 0.08f);
	PushAnimationData("Death2", 50, 0, 0, 0.08f);
	PushAnimationData("Death2", 51, 0, 0, 0.08f);
	PushAnimationData("Death2", 52, 0, 0, 0.08f);
	PushAnimationData("Death2", 53, 0, 0, 0.08f);
	PushAnimationData("Death2", 54, 0, 0, 0.25f);

	PushAnimationData("GrandeDeathJump", 81, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 82, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 83, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 84, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 85, 0, 0, 0.07f);
}