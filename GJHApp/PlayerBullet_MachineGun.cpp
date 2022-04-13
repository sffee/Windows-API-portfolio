#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "PlayerBullet_MachineGun.h"
#include "InstanceObject.h"
#include "Player.h"

void PlayerBullet_MachineGun::Start()
{
	m_MoveSpeed = 1500.f;
	m_MaxTime = 0.5f;

	m_AniRender = CreateRender({ 256, 256 }, "Bullet(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Bullet0", "Bullet", 15, 15, 1.f);
	CreateAnimation("Bullet-10", "Bullet", 17, 17, 1.f);
	CreateAnimation("Bullet-22", "Bullet", 18, 18, 1.f);
	CreateAnimation("Bullet-52", "Bullet", 24, 24, 1.f);
	CreateAnimation("Bullet-82", "Bullet", 29, 29, 1.f);
	CreateAnimation("Bullet-90", "Bullet", 31, 31, 1.f);
	CreateAnimation("Bullet20", "Bullet", 2, 2, 1.f);
	CreateAnimation("Bullet47", "Bullet", 6, 6, 1.f);
	CreateAnimation("Bullet57", "Bullet", 8, 8, 1.f);
	CreateAnimation("Bullet80", "Bullet", 12, 12, 1.f);
	CreateAnimation("Bullet90", "Bullet", 14, 14, 1.f);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 120, 20 }, ContentsEnum::COLTYPE::PLAYERBULLET);
	m_AniCollision->SetBlockMove(false);

	m_CurTime = 0.f;

	ChangeAnimation("Bullet0");

	m_IsGravity = false;
}

void PlayerBullet_MachineGun::Update()
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

void PlayerBullet_MachineGun::ColEnter(GJHCollision* _This, GJHCollision* _Other)
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

void PlayerBullet_MachineGun::SetAngle(float _Angle)
{
	if (_Angle == 0.f)
	{
		ChangeAnimation("Bullet0");
	}
	else if (-15.f < _Angle && _Angle < -5.f)
	{
		ChangeAnimation("Bullet-10");
	}
	else if (-30.f < _Angle && _Angle < -18.f)
	{
		ChangeAnimation("Bullet-22");
	}
	else if (-60.f < _Angle && _Angle < -49.f)
	{
		ChangeAnimation("Bullet-52");
	}
	else if (-84.f < _Angle && _Angle < -80.f)
	{
		ChangeAnimation("Bullet-82");
	}
	else if (-100.f < _Angle && _Angle < -85.f)
	{
		ChangeAnimation("Bullet-90");
	}
	else if (10.f < _Angle && _Angle < 30.f)
	{
		ChangeAnimation("Bullet20");
	}
	else if (40.f < _Angle && _Angle < 50.f)
	{
		ChangeAnimation("Bullet47");
	}
	else if (55.f < _Angle && _Angle < 60.f)
	{
		ChangeAnimation("Bullet57");
	}
	else if (70.f < _Angle && _Angle < 85.f)
	{
		ChangeAnimation("Bullet80");
	}
	else if (86.f < _Angle && _Angle < 100.f)
	{
		ChangeAnimation("Bullet90");
	}

	m_Angle = _Angle;
}