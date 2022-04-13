#include "Helicopter.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "GJHCameraManager.h"
#include "InstanceObject.h"
#include "Player.h"
#include "MonsterBullet.h"

float Helicopter::MOVE_MOVESPEED = 500.f;
float Helicopter::ATTACK_MOVESPEED = 50.f;
float Helicopter::SPEED_DOWN_DISTANCEX = 300.f;
float Helicopter::SPEED_DOWN_DISTANCEY = 100.f;

void Helicopter::Start()
{
	SetDefaultHP(40);
	m_IsGravity = false;
	CurAngleStateStr = "Move24";

	SetMoveCheckX(5000);
	SetMoveCheckY(5000);

	m_AniRender = CreateRender({ 512, 512 }, "Helicopter(Left).bmp", ContentsEnum::RENDERORDER::MONSTER);

	CreateAnimation("Move24", "Helicopter", 0, 5, 0.1f, true);
	CreateAnimation("Move26", "Helicopter", 6, 11, 0.1f, true);
	CreateAnimation("Move33", "Helicopter", 12, 17, 0.1f, true);
	CreateAnimation("Move41", "Helicopter", 18, 23, 0.1f, true);
	CreateAnimation("Move46", "Helicopter", 24, 29, 0.1f, true);
	CreateAnimation("Move62", "Helicopter", 30, 35, 0.1f, true);
	CreateAnimation("Move74", "Helicopter", 36, 41, 0.1f, true);
	CreateAnimation("Move90", "Helicopter", 42, 47, 0.1f, true);
	CreateAnimation("Move24_Damage", "Helicopter_Damage", 0, 5, 0.1f, true);
	CreateAnimation("Move26_Damage", "Helicopter_Damage", 6, 11, 0.1f, true);
	CreateAnimation("Move33_Damage", "Helicopter_Damage", 12, 17, 0.1f, true);
	CreateAnimation("Move41_Damage", "Helicopter_Damage", 18, 23, 0.1f, true);
	CreateAnimation("Move46_Damage", "Helicopter_Damage", 24, 29, 0.1f, true);
	CreateAnimation("Move62_Damage", "Helicopter_Damage", 30, 35, 0.1f, true);
	CreateAnimation("Move74_Damage", "Helicopter_Damage", 36, 41, 0.1f, true);
	CreateAnimation("Move90_Damage", "Helicopter_Damage", 42, 47, 0.1f, true);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -90 }, { 120, 130 }, ContentsEnum::COLTYPE::MONSTER);
	m_AniCollision->SetBlockMove(false);

	State.CreateState("Move", &Helicopter::MoveInit, &Helicopter::MoveState, nullptr, this);
	State.CreateState("Attack", &Helicopter::AttackInit, &Helicopter::AttackState, nullptr, this);

	State.ChangeState("Move");
	SetDir(CurAngleStateStr, ENUM_DIRECTION::LEFT);

	KeepPosUpdater.PushDelay(5.f);
	KeepPosUpdater.PushOneShotFunc(&Helicopter::ChangeKeepPos, this);

	KeepHeightUpdater.PushDelay(3.f);
	KeepHeightUpdater.PushOneShotFunc(&Helicopter::ChangeKeepHeight, this);

	UpDownUpdater.PushOneShotFunc(&Helicopter::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Helicopter::Down, this);
	UpDownUpdater.PushDelay(0.1f);

	ChangeKeepPos();
	ChangeKeepHeight();

	AppearSoundPlay = false;

	AttackCoolTimer.SetEventTime(3.f, true);

	SetAnimationData();
}

void Helicopter::Update()
{
	DirUpdate(CurAngleStateStr, true);
	State.Update();
	KeepPosUpdater.Update();
	KeepHeightUpdater.Update();
	UpDownUpdater.Update();
	AttackCoolTimer.EventUpdate();
	FireCheckTimer.EventUpdate();

	__super::Update();
	__super::AnimationDataCheck(CurAngleStateStr);
}

void Helicopter::SceneStart()
{
	AttackCoolTimer.Reset();
	AttackCoolTimer.ResetEventTime();
}

void Helicopter::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		m_HP--;
		DrawDamageAnimation(CurAngleStateStr);

		GJHGameEngineSound::PlayOneShot("HelicopterDamage.mp3", 0.5f);

		if (IsDeath() == true)
		{
			GJHGameEngineSound::PlayOneShot("HelicopterExplosion.mp3", 0.4f);

			CreateExplosion();
			MinusMonsterCount();
			Death();
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE)
	{
		m_HP -= 10;

		if (IsDeath() == true)
		{
			GJHGameEngineSound::PlayOneShot("HelicopterExplosion.mp3", 0.4f);

			CreateExplosion();
			MinusMonsterCount();
			Death();
		}
	}
}

void Helicopter::AngleUpdate()
{
	float Angle = abs(GJHMath::VecToVecAngle(m_Player->GetPos(), GetPos()));
	if (90.f <= Angle)
	{
		Angle = abs(Angle - 180.f);
	}

	ENUM_ANGLE AngleEnum = ENUM_ANGLE::ANGLE_NONE;
	GJHString AngleStr;

	if (0.f <= Angle && Angle <= 5.f)
	{
		AngleStr = "Move90";
		AngleEnum = ENUM_ANGLE::ANGLE_90;
	}
	else if (6.f < Angle && Angle <= 24.f)
	{
		AngleStr = "Move24";
		AngleEnum = ENUM_ANGLE::ANGLE_24;
	}
	else if (26.f < Angle && Angle <= 28.5f)
	{
		AngleStr = "Move26";
		AngleEnum = ENUM_ANGLE::ANGLE_26;
	}
	else if (30.5f < Angle && Angle <= 36.f)
	{
		AngleStr = "Move33";
		AngleEnum = ENUM_ANGLE::ANGLE_33;
	}
	else if (38.f < Angle && Angle <= 42.5f)
	{
		AngleStr = "Move41";
		AngleEnum = ENUM_ANGLE::ANGLE_41;
	}
	else if (44.5f < Angle && Angle <= 53.f)
	{
		AngleStr = "Move46";
		AngleEnum = ENUM_ANGLE::ANGLE_46;
	}
	else if (55.f < Angle && Angle <= 67.f)
	{
		AngleStr = "Move62";
		AngleEnum = ENUM_ANGLE::ANGLE_62;
	}
	else if (69.f < Angle && Angle <= 83.f)
	{
		AngleStr = "Move74";
		AngleEnum = ENUM_ANGLE::ANGLE_74;
	}
	else if (85.f < Angle && Angle <= 90.f)
	{
		AngleStr = "Move90";
		AngleEnum = ENUM_ANGLE::ANGLE_90;
	}
	else
	{
		return;
	}

	if (CurAngle == AngleEnum)
	{
		return;
	}

	CurAngle = AngleEnum;
	CurAngleStateStr = AngleStr;
	State.CurState = AngleStr;

	int AniIndex = m_AniRender->GetAnimationFrameIndex() - m_AniRender->GetAnimationStartFrame();
	ChangeAnimation(CurAngleStateStr);
	int CurAniCurIndex = m_AniRender->GetAnimationFrameIndex();

	m_AniRender->SetAnimationFrameIndex(CurAniCurIndex + AniIndex);
}

void Helicopter::ChangeKeepPos()
{
	PrevKeepPosX = KeepPosX;
	do
	{
		KeepPosX = (rand() % (int)ENUM_KEEPPOS::KEEPPOS_MAX * 100.f) + 150.f;
	} while (abs(PrevKeepPosX - KeepPosX) <= 150);

	UpDownUpdater.Reset();
}

void Helicopter::ChangeKeepHeight()
{
	float PrevKeepHeight = KeepHeight;
	do
	{
		KeepHeight = (rand() % (int)ENUM_HEIGHT::HEIGHT_MAX) * 50.f + 650.f;
	} while (PrevKeepHeight == KeepHeight);

	UpDownUpdater.Reset();
}

void Helicopter::Up()
{
	KeepHeight -= 5;
}

void Helicopter::Down()
{
	KeepHeight += 5;
}

void Helicopter::Move()
{
	if (MoveCheck(false) == true)
	{
		GJHVector Distance = GJHVector(GetPos().x - GJHCameraManager::GetCamPos().x - KeepPosX, GJHCameraManager::GetCamMaxPos().y - KeepHeight - GetPos().y);

		int MoveDirX = 0 < Distance.x ? -1 : 1;
		int MoveDirY = 0 < Distance.y ? 1 : -1;
		float MoveRatioX = min(abs(Distance.x) / SPEED_DOWN_DISTANCEX, 1.f);
		float MoveRatioY = min(abs(Distance.y) / SPEED_DOWN_DISTANCEY, 1.f);

		__super::Move(GJHVector(m_MoveSpeed * MoveRatioX * MoveDirX,
			m_MoveSpeed * MoveRatioY * 0.5f * MoveDirY) *
			GJHGameEngineTime::FDeltaTime());
	}
}

void Helicopter::CreateBullet()
{
	float BulletXPos = 0.f, BulletYPos = 0.f;

	{
		InstanceObjectData Data;
		Data.Size = GJHVector(512, 512);
		Data.Pos = GetPos();
		Data.ImageFileName = "Helicopter";
		Data.ImageDir = m_ImageDir;
		Data.FrameTime = 0.03f;

		AniDataMap Map;

		switch (CurAngle)
		{
		case ENUM_ANGLE::ANGLE_24:
			Data.StartFrame = 55;
			Data.EndFrame = 56;
			BulletXPos = 70;
			BulletYPos = -40;
			Map[55] = { PivotData(105, -30), 0.02f };
			Map[56] = { PivotData(105, -30), 0.02f };
			break;
		case ENUM_ANGLE::ANGLE_26:
			Data.StartFrame = 57;
			Data.EndFrame = 58;
			BulletXPos = 80;
			BulletYPos = -20;
			Map[57] = { PivotData(100, -20), 0.02f };
			Map[58] = { PivotData(100, -20), 0.02f };
			break;
		case ENUM_ANGLE::ANGLE_33:
			Data.StartFrame = 59;
			Data.EndFrame = 60;
			BulletXPos = 80;
			BulletYPos = -30;
			Map[59] = { PivotData(95, -15), 0.02f };
			Map[60] = { PivotData(95, -15), 0.02f };
			break;
		case ENUM_ANGLE::ANGLE_41:
			Data.StartFrame = 61;
			Data.EndFrame = 62;
			BulletXPos = 70;
			BulletYPos = -20;
			Map[61] = { PivotData(90, -5), 0.02f };
			Map[62] = { PivotData(90, -5), 0.02f };
			break;
		case ENUM_ANGLE::ANGLE_46:
			Data.StartFrame = 63;
			Data.EndFrame = 64;
			BulletXPos = 50;
			BulletYPos = -20;
			Map[63] = { PivotData(70, 0), 0.02f };
			Map[64] = { PivotData(70, 0), 0.02f };
			break;
		case ENUM_ANGLE::ANGLE_62:
			Data.StartFrame = 65;
			Data.EndFrame = 66;
			BulletXPos = 35;
			BulletYPos = -20;
			Map[65] = { PivotData(55, 5), 0.02f };
			Map[66] = { PivotData(55, 5), 0.02f };
			break;
		case ENUM_ANGLE::ANGLE_74:
			Data.StartFrame = 67;
			Data.EndFrame = 68;
			BulletXPos = 30;
			BulletYPos = -20;
			Map[67] = { PivotData(35, 10), 0.02f };
			Map[68] = { PivotData(35, 10), 0.02f };
			break;
		case ENUM_ANGLE::ANGLE_90:
			Data.StartFrame = 69;
			Data.EndFrame = 70;
			BulletXPos = 0;
			BulletYPos = 0;
			Map[69] = { PivotData(0, 15), 0.02f };
			Map[70] = { PivotData(0, 15), 0.02f };
			break;
		}

		Data.AniData = Map;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);
	}

	float Angle = GJHMath::VecToVecAngle(m_Player->GetPos(), GetPos());
	if (90.f <= Angle)
	{
		Angle = abs(Angle - 180.f);
	}

	MonsterBullet* NewBullet = GetScene()->CreateActor<MonsterBullet>();
	NewBullet->SetPos(GetPos() + GJHVector((float)(BulletXPos * (int)m_ImageDir), (float)BulletYPos));
	NewBullet->SetMaxTime(2.f);
	NewBullet->SetMoveSpeed(800.f);
	NewBullet->SetDir("Bullet", m_ImageDir);
	NewBullet->SetAngle(Angle);
}

void Helicopter::CreateExplosion()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = GetPos();
	Data.ActorPivot = GJHVector(-0, -0);
	Data.ImageFileName = "Explosion";
	Data.ImageDir = m_ImageDir;
	Data.StartFrame = 56;
	Data.EndFrame = 83;

	AniDataMap Map;
	Map[56] = { PivotData(0, -140), 0.03f };
	Map[57] = { PivotData(0, -140), 0.03f };
	Map[58] = { PivotData(0, -105), 0.03f };
	Map[59] = { PivotData(0, -105), 0.03f };
	Map[60] = { PivotData(0, -105), 0.03f };
	Map[61] = { PivotData(1, -111), 0.03f };
	Map[62] = { PivotData(0, -115), 0.03f };
	Map[63] = { PivotData(-2, -117), 0.03f };
	Map[64] = { PivotData(-2, -118), 0.03f };
	Map[65] = { PivotData(-2, -120), 0.03f };
	Map[66] = { PivotData(-2, -124), 0.03f };
	Map[67] = { PivotData(0, -125), 0.03f };
	Map[68] = { PivotData(0, -130), 0.03f };
	Map[69] = { PivotData(0, -130), 0.03f };
	Map[70] = { PivotData(0, -125), 0.03f };
	Map[71] = { PivotData(0, -125), 0.03f };
	Map[72] = { PivotData(-5, -130), 0.03f };
	Map[73] = { PivotData(0, -130), 0.03f };
	Map[74] = { PivotData(0, -135), 0.03f };
	Map[75] = { PivotData(-5, -135), 0.03f };
	Map[76] = { PivotData(-15, -140), 0.03f };
	Map[77] = { PivotData(-17, -140), 0.03f };
	Map[78] = { PivotData(-18, -155), 0.03f };
	Map[79] = { PivotData(-20, -155), 0.03f };
	Map[80] = { PivotData(-20, -170), 0.03f };
	Map[81] = { PivotData(-19, -169), 0.03f };
	Map[82] = { PivotData(-22, -132), 0.03f };
	Map[83] = { PivotData(-24, -127), 0.03f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void Helicopter::MoveInit()
{
	m_MoveSpeed = MOVE_MOVESPEED;

	ChangeAnimation(CurAngleStateStr);
}

void Helicopter::MoveState()
{
	if (AppearSoundPlay == false)
	{
		AppearSoundPlay = true;
		GJHGameEngineSound::PlayOneShot("HelicopterAppear.mp3", 0.4f);
	}

	AngleUpdate();

	if (AttackCoolTimer.CheckEventTime() == true &&
		CheckInsideCam() == true)
	{
		State.ChangeState("Attack");
	}

	Move();
}

void Helicopter::AttackInit()
{
	m_MoveSpeed = ATTACK_MOVESPEED;
	FireCheckTimer.SetEventTime(0.05f);

	FireBulletCount = 0;

	GJHGameEngineSound::PlayOneShot("HelicopterAttack.mp3", 0.7f);
}

void Helicopter::AttackState()
{
	if (3 <= FireBulletCount)
	{
		State.ChangeState("Move");
	}
	
	if (FireCheckTimer.CheckEventTime() == true)
	{
		CreateBullet();
		FireBulletCount++;
	}

	Move();
}

void Helicopter::SetAnimationData()
{
	PushAnimationData("Move24", 0, -30, -105, 0.05f);
	PushAnimationData("Move24", 1, -38, -105, 0.05f);
	PushAnimationData("Move24", 2, -39, -105, 0.05f);
	PushAnimationData("Move24", 3, -38, -105, 0.05f);
	PushAnimationData("Move24", 4, -38, -105, 0.05f);
	PushAnimationData("Move24", 5, -30, -106, 0.05f);

	PushAnimationData("Move26", 6, -39, -113, 0.05f);
	PushAnimationData("Move26", 7, -39, -113, 0.05f);
	PushAnimationData("Move26", 8, -39, -113, 0.05f);
	PushAnimationData("Move26", 9, -39, -113, 0.05f);
	PushAnimationData("Move26", 10, -29, -113, 0.05f);
	PushAnimationData("Move26", 11, -29, -113, 0.05f);

	PushAnimationData("Move33", 12, -40, -120, 0.05f);
	PushAnimationData("Move33", 13, -40, -120, 0.05f);
	PushAnimationData("Move33", 14, -40, -120, 0.05f);
	PushAnimationData("Move33", 15, -40, -120, 0.05f);
	PushAnimationData("Move33", 16, -23, -120, 0.05f);
	PushAnimationData("Move33", 17, -24, -120, 0.05f);

	PushAnimationData("Move41", 18, -38, -125, 0.05f);
	PushAnimationData("Move41", 19, -38, -125, 0.05f);
	PushAnimationData("Move41", 20, -38, -125, 0.05f);
	PushAnimationData("Move41", 21, -38, -125, 0.05f);
	PushAnimationData("Move41", 22, -21, -125, 0.05f);
	PushAnimationData("Move41", 23, -12, -125, 0.05f);

	PushAnimationData("Move46", 24, -23, -125, 0.05f);
	PushAnimationData("Move46", 25, -27, -125, 0.05f);
	PushAnimationData("Move46", 26, -27, -125, 0.05f);
	PushAnimationData("Move46", 27, -27, -125, 0.05f);
	PushAnimationData("Move46", 28, -9, -125, 0.05f);
	PushAnimationData("Move46", 29, -6, -125, 0.05f);

	PushAnimationData("Move62", 30, 3, -125, 0.05f);
	PushAnimationData("Move62", 31, -8, -125, 0.05f);
	PushAnimationData("Move62", 32, -15, -125, 0.05f);
	PushAnimationData("Move62", 33, -15, -125, 0.05f);
	PushAnimationData("Move62", 34, 6, -125, 0.05f);
	PushAnimationData("Move62", 35, 6, -125, 0.05f);

	PushAnimationData("Move74", 36, 4, -125, 0.05f);
	PushAnimationData("Move74", 37, 7, -125, 0.05f);
	PushAnimationData("Move74", 38, 1, -125, 0.05f);
	PushAnimationData("Move74", 39, 1, -125, 0.05f);
	PushAnimationData("Move74", 40, 10, -125, 0.05f);
	PushAnimationData("Move74", 41, 4, -125, 0.05f);

	PushAnimationData("Move90", 42, 0, -125, 0.05f);
	PushAnimationData("Move90", 43, 6, -125, 0.05f);
	PushAnimationData("Move90", 44, 0, -125, 0.05f);
	PushAnimationData("Move90", 45, 1, -125, 0.05f);
	PushAnimationData("Move90", 46, 3, -125, 0.05f);
	PushAnimationData("Move90", 47, 0, -125, 0.05f);

	PushAnimationData("Move24_Damage", 0, -30, -105, 0.05f);
	PushAnimationData("Move24_Damage", 1, -38, -105, 0.05f);
	PushAnimationData("Move24_Damage", 2, -39, -105, 0.05f);
	PushAnimationData("Move24_Damage", 3, -38, -105, 0.05f);
	PushAnimationData("Move24_Damage", 4, -38, -105, 0.05f);
	PushAnimationData("Move24_Damage", 5, -30, -106, 0.05f);

	PushAnimationData("Move26_Damage", 6, -39, -113, 0.05f);
	PushAnimationData("Move26_Damage", 7, -39, -113, 0.05f);
	PushAnimationData("Move26_Damage", 8, -39, -113, 0.05f);
	PushAnimationData("Move26_Damage", 9, -39, -113, 0.05f);
	PushAnimationData("Move26_Damage", 10, -29, -113, 0.05f);
	PushAnimationData("Move26_Damage", 11, -29, -113, 0.05f);

	PushAnimationData("Move33_Damage", 12, -40, -120, 0.05f);
	PushAnimationData("Move33_Damage", 13, -40, -120, 0.05f);
	PushAnimationData("Move33_Damage", 14, -40, -120, 0.05f);
	PushAnimationData("Move33_Damage", 15, -40, -120, 0.05f);
	PushAnimationData("Move33_Damage", 16, -23, -120, 0.05f);
	PushAnimationData("Move33_Damage", 17, -24, -120, 0.05f);

	PushAnimationData("Move41_Damage", 18, -38, -125, 0.05f);
	PushAnimationData("Move41_Damage", 19, -38, -125, 0.05f);
	PushAnimationData("Move41_Damage", 20, -38, -125, 0.05f);
	PushAnimationData("Move41_Damage", 21, -38, -125, 0.05f);
	PushAnimationData("Move41_Damage", 22, -21, -125, 0.05f);
	PushAnimationData("Move41_Damage", 23, -12, -125, 0.05f);

	PushAnimationData("Move46_Damage", 24, -23, -125, 0.05f);
	PushAnimationData("Move46_Damage", 25, -27, -125, 0.05f);
	PushAnimationData("Move46_Damage", 26, -27, -125, 0.05f);
	PushAnimationData("Move46_Damage", 27, -27, -125, 0.05f);
	PushAnimationData("Move46_Damage", 28, -9, -125, 0.05f);
	PushAnimationData("Move46_Damage", 29, -6, -125, 0.05f);

	PushAnimationData("Move62_Damage", 30, 3, -125, 0.05f);
	PushAnimationData("Move62_Damage", 31, -8, -125, 0.05f);
	PushAnimationData("Move62_Damage", 32, -15, -125, 0.05f);
	PushAnimationData("Move62_Damage", 33, -15, -125, 0.05f);
	PushAnimationData("Move62_Damage", 34, 6, -125, 0.05f);
	PushAnimationData("Move62_Damage", 35, 6, -125, 0.05f);

	PushAnimationData("Move74_Damage", 36, 4, -125, 0.05f);
	PushAnimationData("Move74_Damage", 37, 7, -125, 0.05f);
	PushAnimationData("Move74_Damage", 38, 1, -125, 0.05f);
	PushAnimationData("Move74_Damage", 39, 1, -125, 0.05f);
	PushAnimationData("Move74_Damage", 40, 10, -125, 0.05f);
	PushAnimationData("Move74_Damage", 41, 4, -125, 0.05f);

	PushAnimationData("Move90_Damage", 42, 0, -125, 0.05f);
	PushAnimationData("Move90_Damage", 43, 6, -125, 0.05f);
	PushAnimationData("Move90_Damage", 44, 0, -125, 0.05f);
	PushAnimationData("Move90_Damage", 45, 1, -125, 0.05f);
	PushAnimationData("Move90_Damage", 46, 3, -125, 0.05f);
	PushAnimationData("Move90_Damage", 47, 0, -125, 0.05f);
}