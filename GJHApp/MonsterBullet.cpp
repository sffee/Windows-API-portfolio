#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "MonsterBullet.h"
#include "InstanceObject.h"

void MonsterBullet::Start()
{
	m_MoveSpeed = 1000.f;
	m_MaxTime = 1.0f;

	m_AniRender = CreateRender({ 64, 64 }, "MonsterBullet(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Bullet", "MonsterBullet", 0, 1, 0.05f);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 20, 20 }, ContentsEnum::COLTYPE::MONSTERBULLET);
	m_AniCollision->SetBlockMove(false);

	m_CurTime = 0.f;

	m_IsGravity = false;
}

void MonsterBullet::Update()
{
	__super::Update();

	Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());

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
		Data.StartFrame = 0;
		Data.EndFrame = 6;
		Data.FrameTime = 0.05f;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);

		Death();
	}
}

void MonsterBullet::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
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

void MonsterBullet::SetMaxTime(float _Time)
{
	m_MaxTime = _Time;
}