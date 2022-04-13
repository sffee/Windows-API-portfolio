#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "GrandFather.h"
#include "InstanceObject.h"
#include "GJHCameraManager.h"
#include "GranadeBox.h"
#include "HeavyMachineGunBox.h"

void GrandFather::Start()
{
	m_MoveSpeed = 150.f;

	m_ImageDir = ENUM_DIRECTION::LEFT;

	m_AniRender = CreateRender({ 512, 512 }, "NPC(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Bind", "NPC", 0, 4, 0.1f, true, true);
	CreateAnimation("BindOut", "NPC", 5, 8, 0.1f, false, false);
	CreateAnimation("Falling", "NPC", 9, 13, 0.1f, true, false);
	CreateAnimation("Walk", "NPC", 14, 25, 0.1f, true, false);
	CreateAnimation("DropItem", "NPC", 26, 36, 0.1f, false, false);
	CreateAnimation("Salute", "NPC", 37, 50, 0.1f, false, false);
	CreateAnimation("RunAway", "NPC", 51, 58, 0.1f, true, false);

	State.CreateState("Bind", &GrandFather::BindInit, &GrandFather::BindState, nullptr, this);
	State.CreateState("BindOut", &GrandFather::BindOutInit, &GrandFather::BindOutState, nullptr, this);
	State.CreateState("Falling", &GrandFather::FallingInit, &GrandFather::FallingState, nullptr, this);
	State.CreateState("Walk", &GrandFather::WalkInit, &GrandFather::WalkState, nullptr, this);
	State.CreateState("DropItem", &GrandFather::DropItemInit, &GrandFather::DropItemState, nullptr, this);
	State.CreateState("Salute", &GrandFather::SaluteInit, &GrandFather::SaluteState, nullptr, this);
	State.CreateState("RunAway", &GrandFather::RunAwayInit, &GrandFather::RunAwayState, nullptr, this);

	State.ChangeState("Bind");

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -50 }, { 100, 100 }, ContentsEnum::COLTYPE::NPC);
	m_AniCollision->SetBlockMove(false);

	m_DropItem = false;

	SetAnimationData();
}

void GrandFather::Update()
{
	State.Update();
	__super::Update();
	__super::AnimationDataCheck(State.CurState);
}

void GrandFather::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (State.CurState == "Bind" &&
		(_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET || _Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE))
	{
		State.ChangeState("BindOut");
	}
	else if (State.CurState == "Walk" &&
		_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		State.ChangeState("DropItem");
	}
}

void GrandFather::ColStay(GJHCollision* _This, GJHCollision* _Other)
{
	if (State.CurState == "Bind" &&
		(_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET || _Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE))
	{
		State.ChangeState("BindOut");
	}
	else if (State.CurState == "Walk" &&
		_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		State.ChangeState("DropItem");
	}
}

void GrandFather::DropItem()
{
	if (m_DropItemType == ENUM_ITEMTYPE::GRANADE)
	{
		GranadeBox* NewItem = GetScene()->CreateActor<GranadeBox>();
		NewItem->SetName("GranadeBox");
		NewItem->SetPos(GetPos() + GJHVector((float)(50 * (int)m_ImageDir), -50.f));
		NewItem->SetDir("Idle", m_ImageDir);
	}
	else if (m_DropItemType == ENUM_ITEMTYPE::HEAVYMACHINEGUN)
	{
		HeavyMachineGunBox* NewItem = GetScene()->CreateActor<HeavyMachineGunBox>();
		NewItem->SetName("HeavyMachineGunBox");
		NewItem->SetPos(GetPos() + GJHVector((float)(50 * (int)m_ImageDir), -50.f));
		NewItem->SetDir("Idle", m_ImageDir);
	}

	m_DropItem = true;
}

void GrandFather::BindInit()
{
	ChangeAnimation("Bind");
}

void GrandFather::BindState()
{

}

void GrandFather::BindOutInit()
{
	ChangeAnimation("BindOut");

	m_AniCollision->SetHitable(false);
}

void GrandFather::BindOutState()
{
	if (AnimationEnd() == true)
	{
		m_StartPos = GetPos();
		State.ChangeState("Walk");
	}
}

void GrandFather::FallingInit()
{
	ChangeAnimation("Falling");
	m_Jump = true;
	m_Gravity = 300.f;
	m_GravityAddValue = 500.f;
}

void GrandFather::FallingState()
{
	if (m_Jump == false)
	{
		m_StartPos = GetPos();
		State.ChangeState("Walk");
	}
}

void GrandFather::WalkInit()
{
	ChangeAnimation("Walk");
	m_AniCollision->SetHitable(true);
	m_AniCollision->SetOrder((int)ContentsEnum::COLTYPE::NONE);
}

void GrandFather::WalkState()
{
	float PosX = GetPos().x + m_MoveSpeed * GJHGameEngineTime::FDeltaTime();
	if (PosX < m_StartPos.x - 200.f ||
		m_StartPos.x + 200.f < PosX)
	{
		m_ImageDir = m_ImageDir == ENUM_DIRECTION::LEFT ? ENUM_DIRECTION::RIGHT : ENUM_DIRECTION::LEFT;
		State.ChangeState("Walk");
	}

	Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
}

void GrandFather::DropItemInit()
{
	m_AniCollision->SetHitable(false);

	GJHGameEngineSound::PlayOneShot("GrandFatherThankyou.mp3", 0.7f);
	ChangeAnimation("DropItem");
}

void GrandFather::DropItemState()
{
	if (m_DropItem == false &&
		m_AniRender->GetAnimationFrameIndex() == 33)
	{
		DropItem();
	}

	if (AnimationEnd() == true)
	{
		State.ChangeState("Salute");
	}
}

void GrandFather::SaluteInit()
{
	ChangeAnimation("Salute");
}

void GrandFather::SaluteState()
{
	if (AnimationEnd() == true)
	{
		State.ChangeState("RunAway");
	}
}

void GrandFather::RunAwayInit()
{
	m_MoveSpeed = 300.f;

	m_ImageDir = ENUM_DIRECTION::LEFT;
	ChangeAnimation("RunAway");
}

void GrandFather::RunAwayState()
{
	Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
	
	if (GetPos().x < GJHCameraManager::GetCamPos().x ||
		GJHCameraManager::GetCamMaxPos().x < GetPos().x)
	{
		Death();
	}
}

void GrandFather::SetAnimationData()
{
	PushAnimationData("Bind", 0, -5, 0, 0.13f);
	PushAnimationData("Bind", 1, -7, 0, 0.13f);
	PushAnimationData("Bind", 2, -2, 0, 0.13f);
	PushAnimationData("Bind", 3, 0, 0, 0.13f);
	PushAnimationData("Bind", 4, 0, 0, 0.13f);

	PushAnimationData("BindOut", 5, -5, 0, 0.10f);
	PushAnimationData("BindOut", 6, -5, 0, 0.10f);
	PushAnimationData("BindOut", 7, -5, 0, 0.10f);
	PushAnimationData("BindOut", 8, -5, 0, 0.10f);

	PushAnimationData("Falling", 9, 10, 0, 0.05f);
	PushAnimationData("Falling", 10, 11, 0, 0.05f);
	PushAnimationData("Falling", 11, 0, 0, 0.05f);
	PushAnimationData("Falling", 12, -6, 0, 0.05f);
	PushAnimationData("Falling", 13, -6, 0, 0.05f);

	PushAnimationData("Walk", 14, -15, 0, 0.10f);
	PushAnimationData("Walk", 15, -15, 0, 0.10f);
	PushAnimationData("Walk", 16, -15, 0, 0.10f);
	PushAnimationData("Walk", 17, 0, 0, 0.10f);
	PushAnimationData("Walk", 18, 0, 0, 0.10f);
	PushAnimationData("Walk", 19, -5, 0, 0.10f);
	PushAnimationData("Walk", 20, -10, 0, 0.10f);
	PushAnimationData("Walk", 21, 0, 0, 0.10f);
	PushAnimationData("Walk", 22, 5, 0, 0.10f);
	PushAnimationData("Walk", 23, 0, 0, 0.10f);
	PushAnimationData("Walk", 24, -10, 0, 0.10f);
	PushAnimationData("Walk", 25, -20, 0, 0.10f);

	PushAnimationData("DropItem", 26, 0, 0, 0.10f);
	PushAnimationData("DropItem", 27, 0, 0, 0.10f);
	PushAnimationData("DropItem", 28, -5, 0, 0.10f);
	PushAnimationData("DropItem", 29, -5, 0, 0.10f);
	PushAnimationData("DropItem", 30, 2, 0, 0.10f);
	PushAnimationData("DropItem", 31, 2, 0, 0.10f);
	PushAnimationData("DropItem", 32, 23, 0, 0.10f);
	PushAnimationData("DropItem", 33, 35, 0, 0.10f);
	PushAnimationData("DropItem", 34, 42, 0, 0.10f);
	PushAnimationData("DropItem", 35, 39, 0, 0.10f);
	PushAnimationData("DropItem", 36, 39, 0, 0.20f);

	PushAnimationData("Salute", 37, 0, 0, 0.07f);
	PushAnimationData("Salute", 38, 0, 0, 0.07f);
	PushAnimationData("Salute", 39, 0, 0, 0.07f);
	PushAnimationData("Salute", 40, -8, 0, 0.07f);
	PushAnimationData("Salute", 41, -10, 0, 0.07f);
	PushAnimationData("Salute", 42, -6, 0, 0.07f);
	PushAnimationData("Salute", 43, -6, 0, 0.07f);
	PushAnimationData("Salute", 44, -6, 0, 0.07f);
	PushAnimationData("Salute", 45, 2, 0, 0.07f);
	PushAnimationData("Salute", 46, 7, 0, 0.07f);
	PushAnimationData("Salute", 47, 7, 0, 0.22f);
	PushAnimationData("Salute", 48, 15, 0, 0.07f);
	PushAnimationData("Salute", 49, 24, 0, 0.07f);
	PushAnimationData("Salute", 50, 16, 0, 0.07f);

	PushAnimationData("RunAway", 51, 0, 0, 0.07f);
	PushAnimationData("RunAway", 52, 0, 0, 0.07f);
	PushAnimationData("RunAway", 53, 0, 0, 0.07f);
	PushAnimationData("RunAway", 54, 0, 0, 0.07f);
	PushAnimationData("RunAway", 55, 0, 0, 0.07f);
	PushAnimationData("RunAway", 56, 0, 0, 0.07f);
	PushAnimationData("RunAway", 57, -5, 0, 0.07f);
	PushAnimationData("RunAway", 58, -10, 0, 0.07f);
}