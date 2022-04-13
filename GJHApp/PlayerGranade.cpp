#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "GJHCameraManager.h"
#include "PlayerGranade.h"
#include "InstanceObject.h"
#include "Player.h"

void PlayerGranade::Start()
{
	m_BounceCount = 0;

	m_Gravity = -500.f;
	m_GravityAddValue = 1300.f;

	m_MoveSpeed = 400.f;

	m_AniRender = CreateRender({ 256, 256 }, "Bullet(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Bullet", "Bullet", 35, 66, 0.02f);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 40, 40 }, ContentsEnum::COLTYPE::PLAYERGRANADE);
	m_AniCollision->SetBlockMove(false);
}

void PlayerGranade::Update()
{
	Move(GJHGameEngineTime::FDeltaTime(m_MoveSpeed));

	if (ColMap(3) == true)
	{
		if (m_BounceCount < 1)
		{
			ResetGravity();

			m_MoveSpeed = 450.f;
			m_Gravity = -300.f;
			m_BounceCount++;

			SetPos(GetPos() + GJHVector(2, -2));
		}
		else
		{
			CreateExplosion();
			Death();
		}
	}

	if (GetPos().x < GJHCameraManager::GetCamPos().x - 200.f ||
		GJHCameraManager::GetCamMaxPos().x + 200.f < GetPos().x)
	{
		Death();
	}

	__super::Update();
}

void PlayerGranade::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::MONSTER ||
		_Other->GetOrder() == (int)ContentsEnum::COLTYPE::NPC)
	{
		Player::AddScore(100);

		CreateExplosion();
		Death();
	}
}

void PlayerGranade::CreateExplosion()
{
	InstanceObjectData Data;
	Data.Pos = GetPos();
	Data.Size = GJHVector(768, 768);
	Data.ImageFileName = "GranadeExplosion";
	Data.ImageDir = m_ImageDir;
	Data.ActorPivot = GJHVector(0, -20);
	Data.StartFrame = 0;
	Data.EndFrame = 26;
	Data.FrameTime = 0.025f;
	Data.CollisionPivot = GJHVector(0, -170);
	Data.CollisionSize = GJHVector(150, 350);
	Data.CollisionDisableFrameIndex = 15;
	Data.SoundFrame = 0;
	Data.SoundFileName = "GranadeExplosion.mp3";
	Data.SoundVolume = 0.7f;

	AniDataMap Map;
	Map[0] = { PivotData(0, -5), 0.025f };
	Map[1] = { PivotData(0, -5), 0.025f };
	Map[2] = { PivotData(0, -6), 0.025f };
	Map[3] = { PivotData(0, -7), 0.025f };
	Map[4] = { PivotData(0, -39), 0.025f };
	Map[5] = { PivotData(0, -69), 0.025f };
	Map[6] = { PivotData(0, -112), 0.025f };
	Map[7] = { PivotData(0, -160), 0.025f };
	Map[8] = { PivotData(5, -155), 0.025f };
	Map[9] = { PivotData(5, -155), 0.025f };
	Map[10] = { PivotData(5, -155), 0.025f };
	Map[11] = { PivotData(5, -155), 0.025f };
	Map[12] = { PivotData(3, -157), 0.025f };
	Map[13] = { PivotData(5, -155), 0.025f };
	Map[14] = { PivotData(5, -153), 0.025f };
	Map[15] = { PivotData(5, -157), 0.025f };
	Map[16] = { PivotData(5, -169), 0.025f };
	Map[17] = { PivotData(5, -180), 0.025f };
	Map[18] = { PivotData(4, -188), 0.025f };
	Map[19] = { PivotData(4, -186), 0.025f };
	Map[20] = { PivotData(4, -190), 0.025f };
	Map[21] = { PivotData(4, -199), 0.025f };
	Map[22] = { PivotData(3, -207), 0.025f };
	Map[23] = { PivotData(3, -215), 0.025f };
	Map[24] = { PivotData(3, -216), 0.025f };
	Map[25] = { PivotData(3, -215), 0.025f };
	Map[26] = { PivotData(3, -230), 0.025f };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}