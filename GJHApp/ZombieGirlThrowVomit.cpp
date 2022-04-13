#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "ZombieGirlThrowVomit.h"
#include "InstanceObject.h"

void ZombieGirlThrowVomit::Start()
{
	m_HP = 8;
	m_MoveSpeed = 400.f;

	m_AniRender = CreateRender({ 256, 256 }, "ZombieManAttack(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("ThrowVomit", "ZombieManAttack", 12, 25, 0.06f, false);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 40, 40 }, ContentsEnum::COLTYPE::MONSTERBULLET);

	GJHGameEngineSound::PlayOneShot("ZombieVomit.mp3");

	m_Gravity = 20.f;
	m_FallingSpeed = -200.f;
	m_IsGravity = true;

	SetDebugRender(false);

	ChangeAnimation("ThrowVomit");

	SetAnimationData();
}

void ZombieGirlThrowVomit::Update()
{
	if (ColMap(50) == true)
	{
		CreateEndEffect();
		Death();
	}

	__super::Move(m_MoveSpeed);
	__super::Update();
	__super::AnimationDataCheck("ThrowVomit");
}

void ZombieGirlThrowVomit::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		InstanceObjectData Data;
		Data.Size = GJHVector(256, 256);
		Data.Pos = GetPos();
		Data.ImageFileName = "ZombieManAttack";
		Data.ImageDir = m_ImageDir;
		Data.ActorPivot = { 0, 0 };
		Data.StartFrame = 45;
		Data.EndFrame = 60;
		Data.FrameTime = 0.05f;

		AniDataMap Map;
		float Delay = 0.05f;
		Map[45] = { PivotData(5, 0), Delay };
		Map[46] = { PivotData(2, -3), Delay };
		Map[47] = { PivotData(-2, 0), Delay };
		Map[48] = { PivotData(-2, 1), Delay };
		Map[49] = { PivotData(6, 2), Delay };
		Map[51] = { PivotData(12, 0), Delay };
		Map[52] = { PivotData(-15, 5), Delay };
		Map[53] = { PivotData(-10, 5), Delay };
		Map[54] = { PivotData(-5, 0), Delay };
		Map[55] = { PivotData(-5, 0), Delay };
		Data.AniData = Map;

		InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
		NewObject->SetData(Data);

		Death();
	}
}

void ZombieGirlThrowVomit::CreateEndEffect()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(256, 256);
	Data.Pos = GetPos();
	Data.ImageFileName = "ZombieManAttack";
	Data.ImageDir = m_ImageDir;
	Data.ActorPivot = { 0, 40 };
	Data.StartFrame = 29;
	Data.EndFrame = 44;
	Data.FrameTime = 0.05f;

	AniDataMap Map;
	float Delay = 0.05f;
	Map[29] = { PivotData(0, -40), Delay };
	Map[30] = { PivotData(-3, -55), Delay };
	Map[31] = { PivotData(-10, -55), Delay };
	Map[32] = { PivotData(0, -70), Delay };
	Map[33] = { PivotData(-8, -69), Delay };
	Map[34] = { PivotData(0, -68), Delay };
	Map[35] = { PivotData(10, -83), Delay };
	Map[36] = { PivotData(21, -84), Delay };
	Map[37] = { PivotData(15, -83), Delay };
	Map[38] = { PivotData(25, -84), Delay };
	Map[39] = { PivotData(34, -82), Delay };
	Map[40] = { PivotData(25, -84), Delay };
	Map[41] = { PivotData(24, -84), Delay };
	Map[42] = { PivotData(30, -85), Delay };
	Map[43] = { PivotData(30, -85), Delay };
	Map[44] = { PivotData(30, -85), Delay };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}

void ZombieGirlThrowVomit::SetAnimationData()
{
	float Delay = 0.06f;
	PushAnimationData("ThrowVomit", 12, -10, 0, Delay);
	PushAnimationData("ThrowVomit", 13, -10, 5, Delay);
	PushAnimationData("ThrowVomit", 14, -2, 5, Delay);
	PushAnimationData("ThrowVomit", 15, -5, 5, Delay);
	PushAnimationData("ThrowVomit", 16, -6, 5, Delay);
	PushAnimationData("ThrowVomit", 17, 5, 5, Delay);
	PushAnimationData("ThrowVomit", 18, -11, 4, Delay);
	PushAnimationData("ThrowVomit", 19, -10, 2, Delay);
	PushAnimationData("ThrowVomit", 20, -5, 5, Delay);
	PushAnimationData("ThrowVomit", 21, 0, -10, Delay);
	PushAnimationData("ThrowVomit", 22, 0, -5, Delay);
	PushAnimationData("ThrowVomit", 23, 5, -10, Delay);
	PushAnimationData("ThrowVomit", 24, 5, 0, Delay);
	PushAnimationData("ThrowVomit", 25, 5, -10, Delay);
}