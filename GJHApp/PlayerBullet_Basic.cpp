#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "PlayerBullet_Basic.h"
#include "InstanceObject.h"
#include "Player.h"

void PlayerBullet_Basic::Start()
{
	m_MoveSpeed = 1500.f;
	m_MaxTime = 0.5f;

	m_AniRender = CreateRender({ 256, 256 }, "Bullet(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Bullet", "Bullet", 0, 0, 1.f);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 20, 20 }, ContentsEnum::COLTYPE::PLAYERBULLET);
	m_AniCollision->SetBlockMove(false);
	
	m_CurTime = 0.f;

	GJHGameEngineSound::PlayOneShot("NormalBullet.mp3", 0.7f);

	m_IsGravity = false;
}

void PlayerBullet_Basic::Update()
{
	__super::Update();

	Move(GJHGameEngineTime::FDeltaTime(m_MoveSpeed));

	m_CurTime += GJHGameEngineTime::FDeltaTime();
	if (m_MaxTime <= m_CurTime)
	{
		Death();
	}

	if (ColMap() == true && GJHGameEngineObjectBase::IsDeath() == false)
	{
		InstanceObjectData Data;
		Data.Size = GJHVector(256, 256);
		Data.Pos = GJHMath::Random(GetPos(), 20, 2);
		Data.ImageFileName = "BulletMapColEffect";
		Data.ImageDir = m_ImageDir;
		Data.ActorPivot = GJHVector(0, 0);
		Data.StartFrame = 0;
		Data.EndFrame = 6;
		Data.FrameTime = 0.05f;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);

		Death();
	}
}

void PlayerBullet_Basic::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::MONSTER ||
		_Other->GetOrder() == (int)ContentsEnum::COLTYPE::NPC)
	{
		Player::AddScore(100);

		m_AniCollision->SetHitable(false);

		InstanceObjectData Data;
		Data.Size = GJHVector(128, 128);
		Data.Pos = GJHMath::RandomPlus(GetPos(), 20);
		Data.ImageFileName = "BulletHitEffect";
		Data.ImageDir = m_ImageDir;
		Data.ActorPivot = GJHVector(0, 0);
		Data.StartFrame = 0;
		Data.EndFrame = 9;
		Data.FrameTime = 0.05f;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);

		Death();
	}
}