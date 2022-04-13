#include "PlayScene.h"
#include <GJHGameEngineWindow.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineTime.h>
#include <GJHGameEngineSound.h>
#include "define.h"
#include "GJHCameraManager.h"
#include "GJHCameraController.h"
#include "Map.h"
#include "Player.h"
#include "ZombieMan.h"
#include "ZombieGirl.h"
#include "ZombieDoctor.h"
#include "MordenMinigun.h"
#include "Helicopter.h"
#include "Bomber.h"
#include "MonoeyeUFO.h"
#include "ZombieMorden.h"
#include "Phase2Manager.h"
#include "UI.h"
#include "GranadeBox.h"
#include "HeavyMachineGunBox.h"
#include "GrandFather.h"
#include "FadeInOut.h"

void PlayScene::Loading()
{
	GJHCameraManager::Init();

	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYER, (int)ContentsEnum::COLTYPE::MONSTER);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYERBULLET, (int)ContentsEnum::COLTYPE::MONSTER);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYERGRANADE, (int)ContentsEnum::COLTYPE::MONSTER);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::MONSTERBULLET, (int)ContentsEnum::COLTYPE::PLAYER);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::CAMCONTROL, (int)ContentsEnum::COLTYPE::PLAYER);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYER, (int)ContentsEnum::COLTYPE::NONE);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::MONSTER, (int)ContentsEnum::COLTYPE::NONE);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYER, (int)ContentsEnum::COLTYPE::ITEM);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYER, (int)ContentsEnum::COLTYPE::NPC);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYERBULLET, (int)ContentsEnum::COLTYPE::NPC);
	CollisionCheckLink((int)ContentsEnum::COLTYPE::PLAYERGRANADE, (int)ContentsEnum::COLTYPE::NPC);

	m_CamMoveSpeed = 4000.0f;

	//CREATEKEY("CamMoveD", 'K');
	//CREATEKEY("CamMoveL", 'J');
	//CREATEKEY("CamMoveR", 'L');
	//CREATEKEY("CamMoveU", 'I');

	CREATEKEY("DebugRenderToggle", VK_F1);

	{
		UIActor = CreateActor<UI>();
		UIActor->SetPos({ 0, 0 });
	}

	{
		MapActor = CreateActor<Map>();
		MapActor->SetPos({ 11730, 1790 });
	}

	{
		PlayerActor = CreateActor<Player>();
		PlayerActor->SetPos({ 150, 300 });
		//PlayerActor->SetPos({ 22700, 3000 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 1350, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 1400, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 1500, 800 });
	}

	{
		GrandFather* NewActor = CreateActor<GrandFather>();
		NewActor->SetPos({ 1640, 800 });
		NewActor->SetDropItemType(ENUM_ITEMTYPE::GRANADE);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 1880, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 2000, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 2300, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 2909, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 2950, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 3800, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 3900, 800 });
	}

	{
		GrandFather* NewActor = CreateActor<GrandFather>();
		NewActor->SetPos({ 4070, 890 });
		NewActor->SetDropItemType(ENUM_ITEMTYPE::HEAVYMACHINEGUN);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 5200, 500 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 5500, 500 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 5600, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 6200, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 6400, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 6800, 500 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 6900, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 7750, 500 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 7850, 500 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 8000, 800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 8200, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 8800, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 9200, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 9600, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 9800, 300 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 9900, 300 });
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 5100, 850 });

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->SetPos({ 7000, 634 });

		Con1->SetNextController(Con2);
		Con2->SetPrevController(Con1);
		Con1->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);

		Con2->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 8500, 830 });

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->SetPos({ 9000, 1000 });

		Con1->SetNextController(Con2);
		Con2->SetPrevController(Con1);
		Con1->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);

		Con2->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 9000, 1000 });

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->SetPos({ 10000, 1290 });

		Con1->SetNextController(Con2);
		Con2->SetPrevController(Con1);
		Con1->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);

		Con2->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 10000, 1300 });

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->SetPos({ 10400, 1750 });
		Con2->SetPivot({ 0, -500 });

		Con1->SetNextController(Con2);
		Con2->SetPrevController(Con1);
		Con1->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);

		Con2->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 11300, 1750 });
		Con1->SetCamType(GJHCameraController::CAMTYPE::MONSTERSPAWN);

		Helicopter* NewActor = CreateActor<Helicopter>();
		NewActor->SetPos({ 10400, 1000 });
		NewActor->SetDropItem(ENUM_ITEMTYPE::HEAVYMACHINEGUN);
		Con1->PushSpawnMonster(NewActor);

		NewActor = CreateActor<Helicopter>();
		NewActor->SetPos({ 12100, 1300 });
		Con1->PushSpawnMonster(NewActor);

		ZombieMan* NewZombieMan = CreateActor<ZombieMan>();
		NewZombieMan->SetPos({ 10400, 1000 });
		NewZombieMan->SetMoveCheckX(5000);
		NewZombieMan->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieMan);

		ZombieDoctor* NewZombieDoctor = CreateActor<ZombieDoctor>();
		NewZombieDoctor->SetPos({ 12100, 1300 });
		NewZombieDoctor->SetMoveCheckX(5000);
		NewZombieDoctor->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieDoctor);

		MordenMinigun* NewMinigun = CreateActor<MordenMinigun>();
		NewMinigun->SetPos({ 12100, 1300 });
		NewMinigun->SetMoveCheckX(5000);
		NewMinigun->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewMinigun);

		ZombieGirl* NewZombieGirl = CreateActor<ZombieGirl>();
		NewZombieGirl->SetPos({ 10400, 1000 });
		NewZombieGirl->SetMoveCheckX(5000);
		NewZombieGirl->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieGirl, 1.f);

		NewZombieMan = CreateActor<ZombieMan>();
		NewZombieMan->SetPos({ 12100, 1300 });
		NewZombieMan->SetMoveCheckX(5000);
		NewZombieMan->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieMan, 2.f);

		NewMinigun = CreateActor<MordenMinigun>();
		NewMinigun->SetPos({ 10400, 1000 });
		NewMinigun->SetMoveCheckX(5000);
		NewMinigun->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewMinigun, 4.f);

		NewZombieDoctor = CreateActor<ZombieDoctor>();
		NewZombieDoctor->SetPos({ 12100, 1300 });
		NewZombieDoctor->SetMoveCheckX(5000);
		NewZombieDoctor->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieDoctor, 6.f);

		NewZombieMan = CreateActor<ZombieMan>();
		NewZombieMan->SetPos({ 10400, 1000 });
		NewZombieMan->SetMoveCheckX(5000);
		NewZombieMan->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieMan, 8.f);

		NewZombieGirl = CreateActor<ZombieGirl>();
		NewZombieGirl->SetPos({ 10400, 1000 });
		NewZombieGirl->SetMoveCheckX(5000);
		NewZombieGirl->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieGirl, 10.f);

		NewMinigun = CreateActor<MordenMinigun>();
		NewMinigun->SetPos({ 12100, 1300 });
		NewMinigun->SetMoveCheckX(5000);
		NewMinigun->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewMinigun, 12.f);

		NewZombieDoctor = CreateActor<ZombieDoctor>();
		NewZombieDoctor->SetPos({ 12100, 1300 });
		NewZombieDoctor->SetMoveCheckX(5000);
		NewZombieDoctor->SetMoveCheckY(5000);
		Con1->PushSpawnMonster(NewZombieDoctor, 14.f);

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->Off();
		Con2->SetPos({ 11600, 1750 });
		Con2->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);
		Con1->SpawnMonsterNextController(Con2);

		GJHCameraController* Con3 = CreateActor<GJHCameraController>();
		Con3->Off();
		Con3->SetPos({ 12100, 2500 });
		Con3->SetPivot({ 0, -600 });

		Con2->SetNextController(Con3);
		Con3->SetPrevController(Con2);
		Con3->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GrandFather* NewActor = CreateActor<GrandFather>();
		NewActor->SetPos({ 11000, 1400 });
		NewActor->SetDropItemType(ENUM_ITEMTYPE::HEAVYMACHINEGUN);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 12400, 2000 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 12600, 2000 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 12800, 2000 });
	}

	{
		GrandFather* NewActor = CreateActor<GrandFather>();
		NewActor->SetPos({ 12800, 2000 });
		NewActor->SetDropItemType(ENUM_ITEMTYPE::GRANADE);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 12900, 2000 });
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 12900, 2700 });
		Con1->SetPivot({ 0, -900 });

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->SetPos({ 13800, 3450 });
		Con2->SetPivot({ 0, -900 });

		Con1->SetNextController(Con2);
		Con2->SetPrevController(Con1);
		Con1->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);

		Con2->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 14000, 2800 });
	}

	{
		GrandFather* NewActor = CreateActor<GrandFather>();
		NewActor->SetPos({ 14300, 2000 });
		NewActor->SetDropItemType(ENUM_ITEMTYPE::HEAVYMACHINEGUN);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 14400, 2000 });
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 15000, 2700 });
		Con1->SetCamType(GJHCameraController::CAMTYPE::MONSTERSPAWN);

		Bomber* NewActor = CreateActor<Bomber>();
		NewActor->SetPos({ 15800, 2400 });
		NewActor->SetDropItem(ENUM_ITEMTYPE::HEAVYMACHINEGUN);
		Con1->PushSpawnMonster(NewActor);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 16500, 2400 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieGirl>();
		NewActor->SetPos({ 16900, 2400 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 17800, 2400 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 18500, 2400 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<MordenMinigun>();
		NewActor->SetPos({ 18900, 2400 });
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 17500, 3400 });
		Con1->SetPivot({ 0, -900 });

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->SetPos({ 18900, 3455 });
		Con2->SetPivot({ 0, -900 });

		Con1->SetNextController(Con2);
		Con2->SetPrevController(Con1);
		Con1->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);

		Con2->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 19200, 3450 });
		Con1->SetPivot({ 0, -900 });

		GJHCameraController* Con2 = CreateActor<GJHCameraController>();
		Con2->SetPos({ 21300, 3690 });
		Con2->SetPivot({ 0, -900 });

		Con1->SetNextController(Con2);
		Con2->SetPrevController(Con1);
		Con1->SetCamType(GJHCameraController::CAMTYPE::NEXTLINEMOVEY);

		Con2->SetCamType(GJHCameraController::CAMTYPE::FREE);
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMorden>();
		NewActor->SetPos({ 19430, 2800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMorden>();
		NewActor->SetPos({ 19800, 2800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMorden>();
		NewActor->SetPos({ 20100, 2800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMorden>();
		NewActor->SetPos({ 20500, 2800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMorden>();
		NewActor->SetPos({ 21000, 2800 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieMan>();
		NewActor->SetPos({ 21800, 2400 });
	}

	{
		GJHGameEngineActor* NewActor = CreateActor<ZombieDoctor>();
		NewActor->SetPos({ 22500, 2400 });
	}

	{
		GrandFather* NewActor = CreateActor<GrandFather>();
		NewActor->SetPos({ 22400, 2400 });
		NewActor->SetDropItemType(ENUM_ITEMTYPE::HEAVYMACHINEGUN);
	}

	{
		GJHCameraController* Con1 = CreateActor<GJHCameraController>();
		Con1->SetPos({ 22900, 3695 });
		Con1->SetPivot({ 0, -500 });
		Con1->SetCamType(GJHCameraController::CAMTYPE::RIGHTCAMLOCK);

		GJHGameEngineActor* NewActor = CreateActor<Phase2Manager>();
		NewActor->SetPos({ 22900, 3195 });
	}
}

void PlayScene::SceneChangeStart()
{
	__super::SceneChangeStart();

	{
		FadeInOut* NewActor = CreateActor<FadeInOut>();
		NewActor->SetPos(GJHGameEngineWindow::MainWindow()->GetSize().HalfVector2D());
		NewActor->FadeOut(0.5f);
	}
	
	UIActor->MissionStart();

	GJHCameraManager::SetTarget(PlayerActor);
	GJHCameraManager::SetCamPos({ 0, 102 });
	//GJHCameraManager::SetCamPos({ 22169, 2216 });
	GJHCameraManager::RightCamUnlock();

	//GJHCameraManager::SetCamPos({ 22142, 2223 });
	//GJHCameraManager::LeftCamUnlock();
	//GJHCameraManager::UpCamUnlock();
	//GJHCameraManager::DownCamUnlock();

	GJHGameEngineSound::PlayManagement("StageBGM", "Stage.mp3", 1.f, true);
}

void PlayScene::SceneChangeEnd()
{
	GJHCameraManager::SetTarget(nullptr);
	GJHCameraManager::SetCamPos(GJHVector::ZERO);
	GJHGameEngineSound::StopManagement("StageBGM");
}

void PlayScene::SceneUpdate()
{
	//if (KEYPRESS("CamMoveU"))
	//{
	//	GJHCameraManager::SetTarget(nullptr);
	//	GJHCameraManager::CamMove(GJHCameraManager::GetCamPos() + GJHVector::UP * GJHGameEngineTime::FDeltaTime(m_CamMoveSpeed));
	//}
	//if (KEYPRESS("CamMoveD"))
	//{
	//	GJHCameraManager::SetTarget(nullptr);
	//	GJHCameraManager::CamMove(GJHCameraManager::GetCamPos() + GJHVector::DOWN * GJHGameEngineTime::FDeltaTime(m_CamMoveSpeed));
	//}
	//if (KEYPRESS("CamMoveL"))
	//{
	//	GJHCameraManager::SetTarget(nullptr);
	//	GJHCameraManager::CamMove(GJHCameraManager::GetCamPos() + GJHVector::LEFT * GJHGameEngineTime::FDeltaTime(m_CamMoveSpeed));
	//}
	//if (KEYPRESS("CamMoveR"))
	//{
	//	GJHCameraManager::SetTarget(nullptr);
	//	GJHCameraManager::CamMove(GJHCameraManager::GetCamPos() + GJHVector::RIGHT * GJHGameEngineTime::FDeltaTime(m_CamMoveSpeed));
	//}

	if (KEYDOWN("DebugRenderToggle"))
	{
		ToggleDebugRender();
		MapActor->TogglePixelRender();
	}

	__super::SceneUpdate();
}

void PlayScene::DebugRender()
{
	{
		char Text[200];
		sprintf_s(Text, "FPS %d", GJHGameEngineWindow::GetFPS());
		TextOutA(GJHGameEngineWindow::MainWindow()->GetBackBuffer(), 10, 20, Text, (int)strlen(Text));
	}

	{
		char Text[200];
		sprintf_s(Text, "CamPos %d, %d", GJHCameraManager::GetCamPos().ix(), GJHCameraManager::GetCamPos().iy());
		TextOutA(GJHGameEngineWindow::MainWindow()->GetBackBuffer(), 10, 40, Text, (int)strlen(Text));
	}

	{
		char Text[200];
		sprintf_s(Text, "CharacterPos %d, %d", PlayerActor->GetPos().ix(), PlayerActor->GetPos().iy());
		TextOutA(GJHGameEngineWindow::MainWindow()->GetBackBuffer(), 10, 60, Text, (int)strlen(Text));
	}

	{
		GJHVector MousePos = GJHGameEngineWindow::MainWindow()->GetMousePos() + GJHCameraManager::GetCamPos();

		char Text[200];
		sprintf_s(Text, "MousePos %d, %d", MousePos.ix(), MousePos.iy());
		TextOutA(GJHGameEngineWindow::MainWindow()->GetBackBuffer(), 10, 80, Text, (int)strlen(Text));
	}
}