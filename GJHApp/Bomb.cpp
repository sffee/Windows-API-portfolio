#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "Bomb.h"
#include "InstanceObject.h"

void Bomb::Start()
{
	SetDefaultHP(3);
	m_Gravity = 20.f;
	m_GravityAddValue = 700.f;
	
	m_AniRender = CreateRender({ 512, 512 }, "Bomber(Left).bmp", (int)ContentsEnum::RENDERORDER::MONSTER - 1);
	CreateAnimation("Bomb", "Bomber", 42, 48, 0.06f, true, true);
	CreateAnimation("Bomb_Damage", "Bomber_Damage", 42, 48, 0.06f, true, true);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 30, 30 }, ContentsEnum::COLTYPE::MONSTER);
	m_AniCollision->SetBlockMove(false);
}

void Bomb::Update()
{
	__super::Update();

	if (ColMap() == true)
	{
		CreateExplosion();
		Death();
	}
}

void Bomb::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERBULLET)
	{
		m_HP--;
		DrawDamageAnimation(m_AniRender->GetAnimationName());

		GJHGameEngineSound::PlayOneShot("HelicopterDamage.mp3", 0.2f);

		if (IsDeath() == true)
		{
			CreateDeathExplosion();
			Death();
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYERGRANADE)
	{
		m_HP--;
		DrawDamageAnimation(m_AniRender->GetAnimationName());

		if (IsDeath() == true)
		{
			CreateDeathExplosion();
			Death();
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		GJHGameEngineSound::PlayOneShot("HelicopterDamage.mp3", 0.2f);

		CreateExplosion();
		Death();
	}
}

void Bomb::CreateDeathExplosion()
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = GetPos();
	Data.ImageFileName = "Explosion";
	Data.ImageDir = m_ImageDir;
	Data.StartFrame = 0;
	Data.EndFrame = 27;
	Data.SoundFrame = 0;
	Data.SoundFileName = "HelicopterExplosion.mp3";
	Data.SoundVolume = 0.05f;

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

void Bomb::CreateExplosion()
{
	GJHGameEngineSound::PlayOneShot("HelicopterExplosion.mp3", 0.1f);

	InstanceObjectData Data;
	Data.Pos = GetPos();
	Data.Size = GJHVector(768, 768);
	Data.ImageFileName = "GranadeExplosion";
	Data.ImageDir = m_ImageDir;
	Data.ActorPivot = GJHVector(0, -20);
	Data.StartFrame = 27;
	Data.EndFrame = 56;
	Data.FrameTime = 0.025f;
	Data.CollisionPivot = GJHVector(0, -170);
	Data.CollisionSize = GJHVector(150, 350);
	Data.CollisionDisableFrameIndex = 36;
	Data.SoundFrame = 0;
	Data.SoundFileName = "GranadeExplosion.mp3";
	Data.SoundVolume = 0.7f;

	AniDataMap Map;
	Map[27] = { PivotData(0, 15), 0.03f };
	Map[28] = { PivotData(0, 15), 0.03f };
	Map[29] = { PivotData(0, 14), 0.03f };
	Map[30] = { PivotData(0, 15), 0.03f };
	Map[31] = { PivotData(0, -33), 0.03f };
	Map[32] = { PivotData(0, -81), 0.03f };
	Map[33] = { PivotData(0, -145), 0.03f };
	Map[34] = { PivotData(0, -205), 0.03f };
	Map[35] = { PivotData(-5, -220), 0.03f };
	Map[36] = { PivotData(5, -215), 0.03f };
	Map[37] = { PivotData(0, -211), 0.03f };
	Map[38] = { PivotData(0, -206), 0.03f };
	Map[39] = { PivotData(0, -187), 0.03f };
	Map[40] = { PivotData(-5, -185), 0.03f };
	Map[41] = { PivotData(-5, -180), 0.03f };
	Map[42] = { PivotData(-5, -180), 0.03f };
	Map[43] = { PivotData(-5, -188), 0.03f };
	Map[44] = { PivotData(-5, -204), 0.03f };
	Map[45] = { PivotData(-5, -212), 0.03f };
	Map[46] = { PivotData(-5, -225), 0.03f };
	Map[47] = { PivotData(-5, -228), 0.03f };
	Map[48] = { PivotData(-5, -240), 0.03f };
	Map[49] = { PivotData(0, -245), 0.03f };
	Map[50] = { PivotData(0, -255), 0.03f };
	Map[51] = { PivotData(0, -275), 0.03f };
	Map[52] = { PivotData(0, -275), 0.03f };
	Map[53] = { PivotData(0, -285), 0.03f };
	Map[54] = { PivotData(0, -290), 0.03f };
	Map[55] = { PivotData(0, -303), 0.03f };
	Map[56] = { PivotData(0, -310), 0.03f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}