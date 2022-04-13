#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "GranadeBox.h"
#include "InstanceObject.h"

void GranadeBox::Start()
{
	m_ImageDir = ENUM_DIRECTION::LEFT;

	m_Gravity = 500.f;
	m_GravityAddValue = 800.f;
	
	m_AniRender = CreateRender({ 512, 512 }, "Item(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Idle", "Item", 0, 5, 0.1f);
	CreateAnimation("PickUp", "Item", 6, 6, 0.05f, false);

	ChangeAnimation("Idle");

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -100 }, { 150, 150 }, ContentsEnum::COLTYPE::ITEM);
	m_AniCollision->SetBlockMove(false);

	SetAnimationData();
}

void GranadeBox::Update()
{
	if (m_AniRender->GetAnimationName() == "PickUp" &&
		m_AniRender->AnimationEnd() == true)
	{
		GJHGameEngineSound::PlayOneShot("GetGranadeBox.mp3", 0.7f);

		PickUpEffect();
		Death();
	}

	ObjectBase::Update();
	ObjectBase::AnimationDataCheck("Idle");
}

void GranadeBox::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		m_AniCollision->SetHitable(false);
		ChangeAnimation("PickUp");
	}
}

void GranadeBox::ColStay(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		m_AniCollision->SetHitable(false);
		ChangeAnimation("PickUp");
	}
}

void GranadeBox::PickUpEffect()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = GetPos();
	Data.ImageFileName = "Item";
	Data.ImageDir = m_ImageDir;
	Data.StartFrame = 9;
	Data.EndFrame = 14;
	Data.FrameTime = 0.04f;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void GranadeBox::SetAnimationData()
{
	PushAnimationData("Idle", 0, 0, 0, 1.5f);
}