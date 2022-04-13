#include "MonoeyeUFO.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "InstanceObject.h"
#include "GJHCameraManager.h"
#include "Laser.h"
#include "Word.h"
#include "Player.h"
#include "Phase2Manager.h"

Word* MonoeyeUFO::m_WordActor = nullptr;
Laser* MonoeyeUFO::m_LaserActor = nullptr;

void MonoeyeUFO::Start()
{
	SetDefaultHP(500);

	m_IsGravity = false;
	m_IsAttackSpeedUp = false;

	m_AniRender = CreateRender({ 768, 768 }, "MonoeyeUFO(Left).bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 4);
	CreateAnimation("Appear", "MonoeyeUFO", 4, 4, 0.1f, true);
	CreateAnimation("Idle", "MonoeyeUFO", 0, 4, 0.1f, true);
	CreateAnimation("Fire", "MonoeyeUFO", 9, 14, 0.1f, true);
	CreateAnimation("Death", "MonoeyeUFO", 17, 17, 0.1f, true);
	CreateAnimation("IdleSpeedUp", "MonoeyeUFO_SpeedUp", 0, 4, 0.1f, true);
	CreateAnimation("FireSpeedUp", "MonoeyeUFO_SpeedUp", 9, 14, 0.1f, true);
	CreateAnimation("Appear_Damage", "MonoeyeUFO_Damage", 4, 4, 0.1f, true);
	CreateAnimation("Idle_Damage", "MonoeyeUFO_Damage", 0, 4, 0.1f, true);
	CreateAnimation("Fire_Damage", "MonoeyeUFO_Damage", 9, 14, 0.1f, true);
	CreateAnimation("IdleSpeedUp_Damage", "MonoeyeUFO_Damage", 0, 4, 0.1f, true);
	CreateAnimation("FireSpeedUp_Damage", "MonoeyeUFO_Damage", 9, 14, 0.1f, true);

	m_SubAniRender = CreateRender({ 768, 768 }, "MonoeyeUFO(Left).bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
	CreateAnimation("Appear", "MonoeyeUFO", 16, 16, 0.1f, true, false, true);
	CreateAnimation("Appear_Damage", "MonoeyeUFO_Damage", 16, 16, 0.1f, true, false, true);
	CreateAnimation("Death", "MonoeyeUFO", 18, 18, 0.1f, true, false, true);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -240 }, { 450, 220 }, ContentsEnum::COLTYPE::MONSTER);
	m_AniCollision->SetBlockMove(false);
	m_AniCollision->SetHitable(false);

	State.CreateState("Appear", &MonoeyeUFO::AppearInit, &MonoeyeUFO::AppearState, nullptr, this);
	State.CreateState("Idle", &MonoeyeUFO::IdleInit, &MonoeyeUFO::IdleState, nullptr, this);
	State.CreateState("Fire", &MonoeyeUFO::FireInit, &MonoeyeUFO::FireState, nullptr, this);
	State.CreateState("Death", &MonoeyeUFO::DeathInit, &MonoeyeUFO::DeathState, nullptr, this);

	State.ChangeState("Appear");

	SetAnimationData();
}

void MonoeyeUFO::Update()
{
	State.Update();
	__super::Update();
	__super::AnimationDataCheck(m_AniRender->GetAnimationName());
}

void MonoeyeUFO::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		m_HP--;
		ChangeDamageAnimation();		

		GJHGameEngineSound::PlayOneShot("HelicopterDamage.mp3", 0.5f);

		if (IsDeath() == true)
		{
			MinusMonsterCount();
			State.ChangeState("Death");
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE)
	{
		m_HP -= 10;
		ChangeDamageAnimation();

		if (IsDeath() == true)
		{
			MinusMonsterCount();
			State.ChangeState("Death");
		}
	}
}

void MonoeyeUFO::AttackSpeedUpCheck()
{
	if (m_IsAttackSpeedUp == true)
	{
		return;
	}

	int ChangeHP = (int)(m_MaxHP / 2);
	if (m_HP <= ChangeHP)
	{
		m_IsAttackSpeedUp = true;
	}
}

void MonoeyeUFO::CreateLaser(bool _IsSpeedUp)
{
	m_LaserActor = GetScene()->CreateActor<Laser>();
	m_LaserActor->SetPos({ m_Player->GetPos().x, GJHCameraManager::GetCamMaxPos().y });

	if (_IsSpeedUp == true)
	{
		m_LaserActor->SetLoopTime(0.6f);
	}
	else
	{
		m_LaserActor->SetLoopTime(1.8f);
	}
}

void MonoeyeUFO::CreateWord(bool _IsSpeedUp)
{
	m_WordActor = GetScene()->CreateActor<Word>();
	m_WordActor->SetDefaultPos({ GetPos().x, GetPos().y - 195.f });
	if (_IsSpeedUp == true)
	{
		m_WordActor->SetSpeedUp();
		m_WordActor->SetWordMaxCount(2);
		m_WordActor->SetYAddSize(3000.f);
	}
	else
	{
		m_WordActor->SetWordMaxCount(5);
	}
}

void MonoeyeUFO::ChangeDamageAnimation()
{
	DrawDamageAnimation(m_AniRender->GetAnimationName(), "Appear", true);
	if (m_WordActor != nullptr)
	{
		m_WordActor->Damage();
	}
}

void MonoeyeUFO::CreateDeathExplosion(const GJHVector& _Pos, float _Gravity, float _GravityAddValue, float _MoveSpeed, int _Order)
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = _Pos;
	Data.Order = _Order;
	Data.ImageFileName = "Explosion";
	Data.ImageDir = ENUM_DIRECTION::RIGHT;
	Data.StartFrame = 58;
	Data.EndFrame = 83;
	Data.MoveSpeed = _MoveSpeed;

	if (_Gravity != 0.f)
	{
		Data.Gravity = _Gravity;
		Data.GravityAddValue = _GravityAddValue;
		Data.IsGravity = true;
	}

	AniDataMap Map;
	Map[56] = { PivotData(0, -140), 0.04f };
	Map[57] = { PivotData(0, -140), 0.04f };
	Map[58] = { PivotData(0, -105), 0.04f };
	Map[59] = { PivotData(0, -105), 0.04f };
	Map[60] = { PivotData(0, -105), 0.04f };
	Map[61] = { PivotData(1, -111), 0.04f };
	Map[62] = { PivotData(0, -115), 0.04f };
	Map[63] = { PivotData(-2, -117), 0.04f };
	Map[64] = { PivotData(-2, -118), 0.04f };
	Map[65] = { PivotData(-2, -120), 0.04f };
	Map[66] = { PivotData(-2, -124), 0.04f };
	Map[67] = { PivotData(0, -125), 0.04f };
	Map[68] = { PivotData(0, -130), 0.04f };
	Map[69] = { PivotData(0, -130), 0.04f };
	Map[70] = { PivotData(0, -125), 0.04f };
	Map[71] = { PivotData(0, -125), 0.04f };
	Map[72] = { PivotData(-5, -130), 0.04f };
	Map[73] = { PivotData(0, -130), 0.04f };
	Map[74] = { PivotData(0, -135), 0.04f };
	Map[75] = { PivotData(-5, -135), 0.04f };
	Map[76] = { PivotData(-15, -140), 0.04f };
	Map[77] = { PivotData(-17, -140), 0.04f };
	Map[78] = { PivotData(-18, -155), 0.04f };
	Map[79] = { PivotData(-20, -155), 0.04f };
	Map[80] = { PivotData(-20, -170), 0.04f };
	Map[81] = { PivotData(-19, -169), 0.04f };
	Map[82] = { PivotData(-22, -132), 0.04f };
	Map[83] = { PivotData(-24, -127), 0.04f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void MonoeyeUFO::CreateStartStone(ENUM_DIRECTION _Dir, float _MoveSpeed, float _Gravity)
{
	float Random = (GJHMath::Random(6) / 10.f) + 1.f;
	float XPosRandom = (float)GJHMath::Random(-100, 100);

	InstanceObjectData Data;
	Data.Size = GJHVector(128 * Random, 900 * Random);
	Data.Pos = GJHVector(22800 + XPosRandom, 3090);
	Data.ImageFileName = "MonoeyeUFO_Effect";
	Data.ImageDir = _Dir;
	Data.StartFrame = 12;
	Data.EndFrame = 19;
	Data.FrameTime = 0.05f;
	Data.MoveSpeed = _MoveSpeed;
	Data.IsGravity = true;
	Data.Gravity = _Gravity;
	Data.GravityAddValue = 150.f;
	Data.IsLoop = true;
	Data.CheckColMap = true;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void MonoeyeUFO::CreateStone(ENUM_DIRECTION _Dir, float _MoveSpeed, float _Gravity)
{
	float Random = (GJHMath::Random(6) / 10.f) + 1.f;
	float XPosRandom = (float)GJHMath::Random(-50, 50);

	InstanceObjectData Data;
	Data.Size = GJHVector(128 * Random, 900 * Random);
	Data.Pos = GetPos() + GJHVector(XPosRandom, -200.f);
	Data.ImageFileName = "MonoeyeUFO_Effect";
	Data.ImageDir = _Dir;
	Data.StartFrame = 12;
	Data.EndFrame = 19;
	Data.FrameTime = 0.05f;
	Data.MoveSpeed = _MoveSpeed;
	Data.IsGravity = true;
	Data.Gravity = _Gravity;
	Data.GravityAddValue = 150.f;
	Data.IsLoop = true;
	Data.CheckColMap = true;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void MonoeyeUFO::DeleteWordActor()
{
	m_WordActor = nullptr;
}

void MonoeyeUFO::DeleteLaserActor()
{
	m_LaserActor = nullptr;
}

void MonoeyeUFO::AppearInit()
{
	GJHCameraManager::CamShake(8.f, 1.5f, 2.f);

	Timer.Reset();
	Timer.SetEventTime(1.8f, true);

	ChangeAnimation("Appear");
	ChangeAnimation("Appear", false, true);

	GJHGameEngineSound::PlayOneShot("BossAppear.mp3", 0.7f);

	GJHGameEngineSound::PlayManagement("BossBGM", "Boss.mp3", 1.f, true);

	for (int i = 0; i < 5; ++i)
	{
		CreateStartStone(ENUM_DIRECTION::LEFT, (float)GJHMath::Random(100, 300), (float)GJHMath::Random(-600, -300) + 100.f);
	}

	for (int i = 0; i < 5; ++i)
	{
		CreateStartStone(ENUM_DIRECTION::LEFT, (float)GJHMath::Random(0, 100), (float)GJHMath::Random(-600, -300) + 100.f);
	}

	for (int i = 0; i < 5; ++i)
	{
		CreateStartStone(ENUM_DIRECTION::RIGHT, (float)GJHMath::Random(0, 100), (float)GJHMath::Random(-600, -300) + 100.f);
	}

	for (int i = 0; i < 5; ++i)
	{
		CreateStartStone(ENUM_DIRECTION::RIGHT, (float)GJHMath::Random(100, 300), (float)GJHMath::Random(-600, -300) + 100.f);
	}

	Phase2Manager::SetBossAppear(true);
}

void MonoeyeUFO::AppearState()
{
	Move(GJHVector::UP * 2000.f * GJHGameEngineTime::FDeltaTime());

	Timer.EventUpdate();
	if (GetPos().y <= 2900)
	{
		SetPos({ GetPos().x, 2900.f });
		m_AniCollision->SetHitable(true);
		
		if (Timer.CheckEventTime() == true)
		{
			State.ChangeState("Fire");
		}
	}
}

void MonoeyeUFO::IdleInit()
{
	AttackSpeedUpCheck();

	if (m_IsAttackSpeedUp == true)
	{
		ChangeAnimation("IdleSpeedUp");
		AttackTimer.SetEventTime(1.f, true);
		CreateLaser(true);
	}
	else
	{
		ChangeAnimation("Idle");
		AttackTimer.SetEventTime(2.1f, true);
		CreateLaser(false);
	}
	AttackTimer.Reset();

	GJHGameEngineSound::StopManagement("BossFire");
}

void MonoeyeUFO::IdleState()
{
	AttackTimer.EventUpdate();
	if (AttackTimer.CheckEventTime() == true)
	{
		State.ChangeState("Fire");
	}
}

void MonoeyeUFO::FireInit()
{
	AttackSpeedUpCheck();

	if (m_IsAttackSpeedUp == true)
	{
		ChangeAnimation("FireSpeedUp");
		AttackTimer.SetEventTime(1.5f, true);
		CreateWord(true);

		GJHGameEngineSound::PlayManagement("BossFire", "BossFire_Short.mp3", 0.5f);
	}
	else
	{
		ChangeAnimation("Fire");
		AttackTimer.SetEventTime(3.f, true);
		CreateWord(false);

		GJHGameEngineSound::PlayManagement("BossFire", "BossFire.mp3", 0.5f);
	}
	AttackTimer.Reset();
}

void MonoeyeUFO::FireState()
{
	AttackTimer.EventUpdate();
	if (AttackTimer.CheckEventTime() == true)
	{
		State.ChangeState("Idle");
	}
}

void MonoeyeUFO::DeathInit()
{
	ChangeAnimation("IdleSpeedUp");
	m_AniCollision->SetHitable(false);

	if (m_LaserActor != nullptr)
	{
		m_LaserActor->Death();
	}

	if (m_WordActor != nullptr)
	{
		m_WordActor->Death();
	}

	GJHGameEngineSound::StopManagement("BossFire");

	Timer.ResetEventTime();
	Timer.SetEventTime(0.5f, true);

	MissionCompleteTimer.ResetEventTime();
	MissionCompleteTimer.SetEventTime(8.f, true);

	Phase2Manager::SetBossDie(true);
}

void MonoeyeUFO::DeathState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true)
	{
		switch (m_DeathExplosionCount)
		{
		case 0:
			CreateDeathExplosion({ 22960, 2721 });
			GJHCameraManager::CamShake(1, 0.3f);
			GJHGameEngineSound::PlayOneShot("GranadeExplosion.mp3", 0.7f);
			break;
		case 1:
			CreateDeathExplosion({ 22735, 2722 });
			GJHCameraManager::CamShake(1, 0.3f);
			GJHGameEngineSound::PlayOneShot("GranadeExplosion.mp3", 0.7f);
			break;
		case 2:
			CreateDeathExplosion({ 22690, 2651 });
			GJHCameraManager::CamShake(1, 0.3f);
			GJHGameEngineSound::PlayOneShot("GranadeExplosion.mp3", 0.7f);
			break;
		case 3:
			CreateDeathExplosion({ 22734, 2790 });
			GJHCameraManager::CamShake(1, 0.3f);
			GJHGameEngineSound::PlayOneShot("GranadeExplosion.mp3", 0.7f);
			break;
		case 4:
			CreateDeathExplosion({ 22692, 2651 });
			GJHCameraManager::CamShake(1, 0.3f);
			GJHGameEngineSound::PlayOneShot("GranadeExplosion.mp3", 0.7f);
			break;
		case 5:
			CreateDeathExplosion({ 22840, 2694 });
			GJHCameraManager::CamShake(1, 0.3f);
			GJHGameEngineSound::PlayOneShot("GranadeExplosion.mp3", 0.7f);
			break;
		case 6:
			CreateDeathExplosion({ 22960, 2721 });
			GJHCameraManager::CamShake(1, 0.3f);
			GJHGameEngineSound::PlayOneShot("GranadeExplosion.mp3", 0.7f);
			break;
		case 7:
			CreateDeathExplosion({ 22642, 2770 });
			CreateDeathExplosion({ 22729, 2777 });
			CreateDeathExplosion({ 22893, 2777 });
			CreateDeathExplosion({ 23000, 2768 });
			CreateDeathExplosion({ 22666, 2725 });
			CreateDeathExplosion({ 22800, 2736 });
			CreateDeathExplosion({ 22642, 2770 });
			CreateDeathExplosion({ 22917, 2723 });

			GJHGameEngineSound::FadeOut("BossBGM", 5.f);
			GJHGameEngineSound::PlayOneShot("BossLastExplosion.mp3", 1.f);

			for (int i = 0; i < 10; ++i)
			{
				CreateStone(ENUM_DIRECTION::LEFT, (float)GJHMath::Random(100, 300), (float)GJHMath::Random(-700, -200) + 100.f);
			}

			for (int i = 0; i < 5; ++i)
			{
				CreateStone(ENUM_DIRECTION::LEFT, (float)GJHMath::Random(0, 100), (float)GJHMath::Random(-700, -200) + 100.f);
			}

			for (int i = 0; i < 5; ++i)
			{
				CreateStone(ENUM_DIRECTION::RIGHT, (float)GJHMath::Random(0, 100), (float)GJHMath::Random(-700, -200) + 100.f);
			}

			for (int i = 0; i < 10; ++i)
			{
				CreateStone(ENUM_DIRECTION::RIGHT, (float)GJHMath::Random(100, 300), (float)GJHMath::Random(-700, -200) + 100.f);
			}

			ChangeAnimation("Death");
			SetActorPivot({ 0, 180 });

			ChangeAnimation("Death", false, true);
			m_SubAniRender->SetActorPivot({ 0, -200 });

			Timer.SetEventTime(0.2f, true);

			GJHCameraManager::CamShake(8, 3.f);
			break;
		case 8:
			CreateDeathExplosion({ 22720, 2890 }, -50.f, -200.f, -50.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 9:
			CreateDeathExplosion({ 22860, 2920 }, -50.f, -200.f, 50.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 10:
			CreateDeathExplosion({ 22720, 2890 }, -50.f, -200.f, -70.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 11:
			CreateDeathExplosion({ 22880, 2920 }, -50.f, -200.f, 100.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 12:
			CreateDeathExplosion({ 22730, 2890 }, -50.f, -200.f, 0.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 13:
			CreateDeathExplosion({ 22820, 2920 }, -50.f, -200.f, 20.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 14:
			CreateDeathExplosion({ 22760, 2890 }, -50.f, -200.f, -100.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 15:
			CreateDeathExplosion({ 22850, 2920 }, -50.f, -200.f, 60.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 16:
			CreateDeathExplosion({ 22700, 2890 }, -50.f, -200.f, -30.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 17:
			CreateDeathExplosion({ 22790, 2920 }, -50.f, -200.f, 40.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 18:
			CreateDeathExplosion({ 22730, 2890 }, -50.f, -200.f, -80.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			CreateDeathExplosion({ 22750, 2920 }, -50.f, -200.f, -10.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			break;
		case 19:
			CreateDeathExplosion({ 22780, 2890 }, -50.f, -200.f, 10.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			CreateDeathExplosion({ 22820, 2920 }, -50.f, -200.f, 60.f, (int)ContentsEnum::RENDERORDER::MAPOBJECT + 3);
			m_DeathExplosionCount = 7;
			break;
		}

		++m_DeathExplosionCount;
	}

	MissionCompleteTimer.EventUpdate();
	if (MissionCompleteTimer.CheckEventTime() == true)
	{
		MissionCompleteTimer.SetEventPause(true);

		Phase2Manager::SetMissionComplete();
	}
}

void MonoeyeUFO::SetAnimationData()
{
	PushAnimationData("Appear", 4, 0, -248, 0.10f);

	PushAnimationData("Idle", 0, 0, -248, 0.16f);
	PushAnimationData("Idle", 1, 0, -248, 0.16f);
	PushAnimationData("Idle", 2, -1, -248, 0.16f);
	PushAnimationData("Idle", 3, 0, -248, 0.16f);
	PushAnimationData("Idle", 4, 0, -248, 0.16f);

	PushAnimationData("Fire", 9, -1, -385, 0.10f);
	PushAnimationData("Fire", 10, -2, -392, 0.10f);
	PushAnimationData("Fire", 11, -1, -391, 0.10f);
	PushAnimationData("Fire", 12, -2, -389, 0.10f);
	PushAnimationData("Fire", 13, -1, -387, 0.10f);
	PushAnimationData("Fire", 14, -1, -384, 0.10f);

	PushAnimationData("Idle_Damage", 0, 0, -248, 0.16f);
	PushAnimationData("Idle_Damage", 1, 0, -248, 0.16f);
	PushAnimationData("Idle_Damage", 2, -1, -248, 0.16f);
	PushAnimationData("Idle_Damage", 3, 0, -248, 0.16f);
	PushAnimationData("Idle_Damage", 4, 0, -248, 0.16f);

	PushAnimationData("Fire_Damage", 9, -1, -385, 0.10f);
	PushAnimationData("Fire_Damage", 10, -2, -392, 0.10f);
	PushAnimationData("Fire_Damage", 11, -1, -391, 0.10f);
	PushAnimationData("Fire_Damage", 12, -2, -389, 0.10f);
	PushAnimationData("Fire_Damage", 13, -1, -387, 0.10f);
	PushAnimationData("Fire_Damage", 14, -1, -384, 0.10f);

	PushAnimationData("IdleSpeedUp", 0, 0, -248, 0.16f);
	PushAnimationData("IdleSpeedUp", 1, 0, -248, 0.16f);
	PushAnimationData("IdleSpeedUp", 2, -1, -248, 0.16f);
	PushAnimationData("IdleSpeedUp", 3, 0, -248, 0.16f);
	PushAnimationData("IdleSpeedUp", 4, 0, -248, 0.16f);

	PushAnimationData("FireSpeedUp", 9, -1, -385, 0.10f);
	PushAnimationData("FireSpeedUp", 10, -2, -392, 0.10f);
	PushAnimationData("FireSpeedUp", 11, -1, -391, 0.10f);
	PushAnimationData("FireSpeedUp", 12, -2, -389, 0.10f);
	PushAnimationData("FireSpeedUp", 13, -1, -387, 0.10f);
	PushAnimationData("FireSpeedUp", 14, -1, -384, 0.10f);

	PushAnimationData("IdleSpeedUp_Damage", 0, 0, -248, 0.16f);
	PushAnimationData("IdleSpeedUp_Damage", 1, 0, -248, 0.16f);
	PushAnimationData("IdleSpeedUp_Damage", 2, -1, -248, 0.16f);
	PushAnimationData("IdleSpeedUp_Damage", 3, 0, -248, 0.16f);
	PushAnimationData("IdleSpeedUp_Damage", 4, 0, -248, 0.16f);

	PushAnimationData("FireSpeedUp_Damage", 9, -1, -385, 0.10f);
	PushAnimationData("FireSpeedUp_Damage", 10, -2, -392, 0.10f);
	PushAnimationData("FireSpeedUp_Damage", 11, -1, -391, 0.10f);
	PushAnimationData("FireSpeedUp_Damage", 12, -2, -389, 0.10f);
	PushAnimationData("FireSpeedUp_Damage", 13, -1, -387, 0.10f);
	PushAnimationData("FireSpeedUp_Damage", 14, -1, -384, 0.10f);
}