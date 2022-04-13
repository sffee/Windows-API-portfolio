#include "Bomber.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "GJHCameraManager.h"
#include "InstanceObject.h"
#include "Player.h"
#include "Bomb.h"

float Bomber::ANIMATION_CHANGE_DISTANCE = 100.f;
float Bomber::SPEED_DOWN_DISTANCEX = 50.f;
float Bomber::SPEED_DOWN_DISTANCEY = 100.f;

void Bomber::Start()
{
	SetDefaultHP(100);
	m_IsGravity = false;
	m_KeepHeight = 700.f;
	m_MoveSpeed = 300.f;

	SetMoveCheckX(5000);
	SetMoveCheckY(5000);

	m_AniRender = CreateRender({ 512, 512 }, "Bomber(Left).bmp", ContentsEnum::RENDERORDER::MONSTER);

	CreateAnimation("Idle", "Bomber", 3, 3, 0.1f, true);
	CreateAnimation("FrontStart", "Bomber", 4, 6, 0.1f, false);
	CreateAnimation("FrontEnd", "Bomber", 4, 6, 0.2f, false, true);
	CreateAnimation("BackStart", "Bomber", 0, 1, 0.1f, false);
	CreateAnimation("BackEnd", "Bomber", 2, 2, 0.3f, false);

	CreateAnimation("Idle_Damage", "Bomber_Damage", 3, 3, 0.1f, true);
	CreateAnimation("FrontStart_Damage", "Bomber_Damage", 4, 6, 0.1f, false);
	CreateAnimation("FrontEnd_Damage", "Bomber_Damage", 4, 6, 0.2f, false, true);
	CreateAnimation("BackStart_Damage", "Bomber_Damage", 0, 1, 0.1f, false);
	CreateAnimation("BackEnd_Damage", "Bomber_Damage", 2, 2, 0.3f, false);

	m_SubAniRender = CreateRender({ 512, 512 }, "Bomber(Left).bmp", ContentsEnum::RENDERORDER::MONSTER);

	CreateAnimation("Idle_Propeller", "Bomber", 3, 3, 0.1f, true, false, true);
	CreateAnimation("Propeller_0", "Bomber", 17, 21, 0.1f, true, false, true);
	CreateAnimation("Propeller_1", "Bomber", 7, 11, 0.1f, true, false, true);
	CreateAnimation("Propeller_2", "Bomber", 12, 16, 0.1f, true, false, true);
	CreateAnimation("Propeller_3", "Bomber", 22, 26, 0.1f, true, false, true);
	CreateAnimation("Propeller_4", "Bomber", 27, 31, 0.1f, true, false, true);
	CreateAnimation("Propeller_5", "Bomber", 32, 36, 0.1f, true, false, true);
	CreateAnimation("Propeller_6", "Bomber", 37, 41, 0.1f, true, false, true);

	CreateAnimation("Idle_Propeller_Damage", "Bomber_Damage", 3, 3, 0.1f, true, false, true);
	CreateAnimation("Propeller_0_Damage", "Bomber_Damage", 17, 21, 0.1f, true, false, true);
	CreateAnimation("Propeller_1_Damage", "Bomber_Damage", 7, 11, 0.1f, true, false, true);
	CreateAnimation("Propeller_2_Damage", "Bomber_Damage", 12, 16, 0.1f, true, false, true);
	CreateAnimation("Propeller_3_Damage", "Bomber_Damage", 22, 26, 0.1f, true, false, true);
	CreateAnimation("Propeller_4_Damage", "Bomber_Damage", 27, 31, 0.1f, true, false, true);
	CreateAnimation("Propeller_5_Damage", "Bomber_Damage", 32, 36, 0.1f, true, false, true);
	CreateAnimation("Propeller_6_Damage", "Bomber_Damage", 37, 41, 0.1f, true, false, true);

	m_CurPropellerIndex = 3;
	m_CurPropellerAniStr = "Propeller_3";

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 250, 120 }, ContentsEnum::COLTYPE::MONSTER);
	m_AniCollision->SetBlockMove(false);

	State.CreateState("Idle", &Bomber::IdleInit, &Bomber::IdleState, nullptr, this);
	State.CreateState("BackStart", &Bomber::BackStartInit, &Bomber::BackStartState, nullptr, this);
	State.CreateState("BackEnd", &Bomber::BackEndInit, &Bomber::BackEndState, nullptr, this);
	State.CreateState("FrontStart", &Bomber::FrontStartInit, &Bomber::FrontStartState, nullptr, this);
	State.CreateState("FrontEnd", &Bomber::FrontEndInit, &Bomber::FrontEndState, nullptr, this);

	State.ChangeState("Idle");
	ChangeAnimation("Propeller_3", false, true);

	SetDir(State.CurState, ENUM_DIRECTION::LEFT);

	AttackCoolTimer.SetEventTime(2.f);

	UpDownUpdater.PushOneShotFunc(&Bomber::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Up, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Down, this);
	UpDownUpdater.PushDelay(0.1f);
	UpDownUpdater.PushOneShotFunc(&Bomber::Down, this);
	UpDownUpdater.PushDelay(0.1f);

	BombDropUpdater.PushOneShotFunc(&Bomber::CreateBomb, this);
	BombDropUpdater.PushDelay(0.3f);
	BombDropUpdater.PushOneShotFunc(&Bomber::CreateBomb, this);
	BombDropUpdater.PushDelay(0.3f);
	BombDropUpdater.PushOneShotFunc(&Bomber::CreateBomb, this);
	BombDropUpdater.m_bLoop = false;

	SetAnimationData();

	AppearSoundPlay = false;
}

void Bomber::Update()
{
	State.Update();
	AttackCoolTimer.EventUpdate();
	UpDownUpdater.Update();
	BombDropUpdater.Update();

	if (AttackCoolTimer.CheckEventTime() == true &&
		abs(PlayerDistance().x) < 300)
	{
		Attack();
	}

	__super::Update();
	PropellerAnimationDataCheck();
	PropellerAnimationIndexChanger();
}

void Bomber::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		m_HP--;
		DrawDamageAnimation(State.CurState, m_SubAniRender->GetAnimationName(), true);

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

void Bomber::Move()
{
	if (MoveCheck(false) == true)
	{
		GJHVector Pos = GetPos();

		float DistanceX = Pos.x - m_Player->GetPos().x;
		int MoveDirX = DistanceX < 0 ? 1 : -1;
		float MoveRatioX = min(abs(DistanceX) / SPEED_DOWN_DISTANCEX, 1.f);
		float MoveSpeedX = min(abs(DistanceX), 300.f);

		float KeepHeight = GJHCameraManager::GetCamMaxPos().y - m_KeepHeight;
		float DistanceY = Pos.y - KeepHeight;
		int MoveDirY = DistanceY < 0 ? 1 : -1;
		float MoveRatioY = min(abs(DistanceY) / SPEED_DOWN_DISTANCEY, 1.f);

		__super::Move(GJHVector(MoveSpeedX * MoveRatioX * MoveDirX,
			m_MoveSpeed * MoveRatioY * 0.5f * MoveDirY) *
			GJHGameEngineTime::FDeltaTime());
	}
}

void Bomber::Up()
{
	m_KeepHeight -= 5;
}

void Bomber::Down()
{
	m_KeepHeight += 5;
}

void Bomber::Attack()
{
	BombDropUpdater.Reset();
}

void Bomber::CreateBomb()
{
	GJHGameEngineSound::PlayOneShot("BomberDrop.mp3", 0.15f);

	{
		InstanceObjectData Data;
		Data.Pos = GetPos();
		Data.Size = GJHVector(512, 512);
		Data.Order = (int)ContentsEnum::RENDERORDER::MONSTER - 2;
		Data.ImageFileName = "Bomber";
		Data.ImageDir = m_ImageDir;
		Data.ActorPivot = GJHVector(0, 50);
		Data.StartFrame = 49;
		Data.EndFrame = 56;
		Data.FrameTime = 0.025f;

		AniDataMap Map;
		Map[49] = { PivotData(0, 0), 0.05f };
		Map[50] = { PivotData(0, 10), 0.05f };
		Map[51] = { PivotData(0, 17), 0.05f };
		Map[52] = { PivotData(0, 23), 0.05f };
		Map[53] = { PivotData(3, 28), 0.05f };
		Map[54] = { PivotData(3, 30), 0.05f };
		Map[55] = { PivotData(3, 34), 0.05f };
		Map[56] = { PivotData(2, 34), 0.05f };
		Data.AniData = Map;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);
	}

	Bomb* NewBomb = GetScene()->CreateActor<Bomb>();
	NewBomb->SetPos(GetPos() + GJHVector(0, 30));
	NewBomb->SetDir("Bomb", ENUM_DIRECTION::LEFT);
}

void Bomber::CreateExplosion()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = GetPos();
	Data.ActorPivot = GJHVector(0, 100);
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

void Bomber::IdleInit()
{
	ChangeAnimation("Idle");
}

void Bomber::IdleState()
{
	if (AppearSoundPlay == false)
	{
		AppearSoundPlay = true;
		GJHGameEngineSound::PlayOneShot("HelicopterAppear.mp3", 0.7f);
	}

	if (PlayerDistance().x < -ANIMATION_CHANGE_DISTANCE)
	{
		State.ChangeState("FrontStart");
	}
	else if (ANIMATION_CHANGE_DISTANCE < PlayerDistance().x)
	{
		State.ChangeState("BackStart");
	}

	Move();
}

void Bomber::BackStartInit()
{
	ChangeAnimation("BackStart");
}

void Bomber::BackStartState()
{
	if (abs(PlayerDistance().x) < ANIMATION_CHANGE_DISTANCE)
	{
		State.ChangeState("BackEnd");
	}

	Move();
}

void Bomber::BackEndInit()
{
	ChangeAnimation("BackEnd");
}

void Bomber::BackEndState()
{
	if (AnimationEnd() == true)
	{
		State.ChangeState("Idle");
	}

	Move();
}

void Bomber::FrontStartInit()
{
	ChangeAnimation("FrontStart");
}

void Bomber::FrontStartState()
{
	if (abs(PlayerDistance().x) < ANIMATION_CHANGE_DISTANCE)
	{
		State.ChangeState("FrontEnd");
	}

	Move();
}

void Bomber::FrontEndInit()
{
	ChangeAnimation("FrontEnd");
	SetAnimationFrameIndex(6);
}

void Bomber::FrontEndState()
{
	if (AnimationEnd() == true)
	{
		State.ChangeState("Idle");
	}

	Move();
}

void Bomber::SetAnimationData()
{
	PushPropellerAnimationData("Propeller_0", 17, 29, -92, 0.05f);
	PushPropellerAnimationData("Propeller_0", 18, 29, -92, 0.05f);
	PushPropellerAnimationData("Propeller_0", 19, 29, -92, 0.05f);
	PushPropellerAnimationData("Propeller_0", 20, 29, -92, 0.05f);
	PushPropellerAnimationData("Propeller_0", 21, 29, -92, 0.05f);

	PushPropellerAnimationData("Propeller_1", 7, 31, -89, 0.05f);
	PushPropellerAnimationData("Propeller_1", 8, 31, -89, 0.05f);
	PushPropellerAnimationData("Propeller_1", 9, 31, -89, 0.05f);
	PushPropellerAnimationData("Propeller_1", 10, 31, -89, 0.05f);
	PushPropellerAnimationData("Propeller_1", 11, 31, -89, 0.05f);

	PushPropellerAnimationData("Propeller_2", 12, 31, -94, 0.05f);
	PushPropellerAnimationData("Propeller_2", 13, 31, -94, 0.05f);
	PushPropellerAnimationData("Propeller_2", 14, 31, -94, 0.05f);
	PushPropellerAnimationData("Propeller_2", 15, 31, -94, 0.05f);
	PushPropellerAnimationData("Propeller_2", 16, 31, -94, 0.05f);

	PushPropellerAnimationData("Propeller_3", 22, 29, -91, 0.05f);
	PushPropellerAnimationData("Propeller_3", 23, 29, -91, 0.05f);
	PushPropellerAnimationData("Propeller_3", 24, 29, -91, 0.05f);
	PushPropellerAnimationData("Propeller_3", 25, 29, -91, 0.05f);
	PushPropellerAnimationData("Propeller_3", 26, 29, -91, 0.05f);

	PushPropellerAnimationData("Propeller_4", 27, 30, -92, 0.05f);
	PushPropellerAnimationData("Propeller_4", 28, 30, -92, 0.05f);
	PushPropellerAnimationData("Propeller_4", 29, 30, -92, 0.05f);
	PushPropellerAnimationData("Propeller_4", 30, 30, -92, 0.05f);
	PushPropellerAnimationData("Propeller_4", 31, 30, -92, 0.05f);

	PushPropellerAnimationData("Propeller_5", 32, 29, -95, 0.05f);
	PushPropellerAnimationData("Propeller_5", 33, 29, -95, 0.05f);
	PushPropellerAnimationData("Propeller_5", 34, 29, -95, 0.05f);
	PushPropellerAnimationData("Propeller_5", 35, 29, -95, 0.05f);
	PushPropellerAnimationData("Propeller_5", 36, 29, -95, 0.05f);

	PushPropellerAnimationData("Propeller_6", 37, 30, -93, 0.05f);
	PushPropellerAnimationData("Propeller_6", 38, 30, -93, 0.05f);
	PushPropellerAnimationData("Propeller_6", 39, 30, -93, 0.05f);
	PushPropellerAnimationData("Propeller_6", 40, 30, -93, 0.05f);
	PushPropellerAnimationData("Propeller_6", 41, 30, -93, 0.05f);
}

void Bomber::PushPropellerAnimationData(const GJHString& _Name, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime)
{
	AniData Data;
	Data.Pivot.x = (float)_PivotX;
	Data.Pivot.y = (float)_PivotY;
	Data.FrameTime = _FrameTime;

	std::map<GJHString, std::map<int, AniData>>::iterator Find = m_PropellerAnimationData.find(_Name);

	if (Find == m_PropellerAnimationData.end())
	{
		m_PropellerAnimationData.insert(std::map<GJHString, std::map<int, AniData>>::value_type(_Name, std::map<int, AniData>()));

		Find = m_PropellerAnimationData.find(_Name);
	}

	Find->second.insert(std::map<int, AniData>::value_type(_FrameIndex, Data));
}

void Bomber::PropellerAnimationDataCheck()
{
	std::map<GJHString, std::map<int, AniData>>::iterator Find = m_PropellerAnimationData.find(m_CurPropellerAniStr);
	if (Find == m_PropellerAnimationData.end())
	{
		return;
	}

	int CurFrameIndex = m_SubAniRender->GetAnimationFrameIndex();
	std::map<int, AniData>::iterator Find2 = Find->second.find(CurFrameIndex);
	if (Find2 == Find->second.end())
	{
		return;
	}

	m_SubAniRender->SetAddActorPivot({ Find2->second.Pivot.x, Find2->second.Pivot.y });
	m_SubAniRender->SetFrameTime(CurFrameIndex, Find2->second.FrameTime);
}

void Bomber::ChangePropellerAnimation(int _Index)
{
	if (m_CurPropellerIndex == _Index)
	{
		return;
	}

	m_CurPropellerIndex = _Index;
	
	char Buffer[256];
	_itoa_s(_Index, Buffer, 10);
	m_CurPropellerAniStr = GJHString("Propeller_") + Buffer;

	ChangeAnimation(m_CurPropellerAniStr, false, true);
}

void Bomber::PropellerAnimationIndexChanger()
{
	int CurFrameIndex = m_AniRender->GetAnimationFrameIndex();

	if (CurFrameIndex == m_CurPropellerIndex)
	{
		return;
	}

	ChangePropellerAnimation(CurFrameIndex);
}