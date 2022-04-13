#include "GJHGameEngineMain.h"
#include "GJHSceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "EndingScene.h"
#include "PivotTestPlayerScene.h"
#include "PivotTestMonsterScene.h"
#include "CharacterSelectScene.h"
#include "ObjectBase.h"
#include <GJHCollision.h>
#include <GJHGameEngineImage.h>
#include <GJHGameEngineFile.h>
#include <GJHGameEngineDirectory.h>
#include <GJHResourcesManager.h>
#include <GJHGameEngineSound.h>

GJHGameEngineMain GJHGameEngineMain::Inst;

GJHGameEngineMain::GJHGameEngineMain()
{

}

void GJHGameEngineMain::ResourcesLoading()
{
    {
        GJHGameEngineDirectory NewDir = GJHGameEngineDirectory();

        // Stage 폴더의 하위 폴더까지 모두 탐색
        NewDir.MoveParent("Project");
        NewDir.Move("Res");

        std::vector<GJHGameEngineFile> FileList = NewDir.AllFile("bmp");
        for (size_t i = 0; i < FileList.size(); i++)
        {
            GJHResourcesManager::Inst()->LoadBmp(FileList[i]);
        }
    }

    {
        GJHGameEngineDirectory NewDir = GJHGameEngineDirectory();

        NewDir.MoveParent("Project");
        NewDir.Move("Res");
        NewDir.Move("Sound");

        std::vector<GJHGameEngineFile> FileList = NewDir.AllFile("mp3");
        for (size_t i = 0; i < FileList.size(); i++)
        {
            GJHGameEngineSound::LoadSound(FileList[i].FullPath());
        }
    }

    GJHCollision::m_HDC = GJHGameEngineWindow::MainWindow()->GetBackBuffer();
    ObjectBase::LoadingMapCollImage();
    ObjectBase::m_HDC = GJHGameEngineWindow::MainWindow()->GetBackBuffer();

    CutImage("Eri_Kasamoto", { 512, 512 });
    CutImage("Eri_Kasamoto_Weapon", { 512, 512 });
    CutImage("Eri_Kasamoto_Death", { 512, 512 });
    CutImage("Eri_Kasamoto_Alive", { 150, 1800 });
    CutImage("Bullet", { 256, 256 });
    CutImage("GranadeExplosion", { 768, 768 }, true);
    CutImage("BulletMapColEffect", { 256, 256 });
    CutImage("ZombieMan", { 512, 512 }, true);
    CutImage("ZombieManAttack", { 256, 256 }, true);
    CutImage("ZombieManDeath", { 512, 512 }, true);
    CutImage("ZombieGirl", { 512, 512 }, true);
    CutImage("ZombieGirlAttack", { 256, 256 }, true);
    CutImage("ZombieGirlDeath", { 512, 512 }, true);
    CutImage("ZombieDoctor", { 512, 512 }, true);
    CutImage("ZombieDoctorAttack", { 256, 256 }, true);
    CutImage("ZombieDoctorDeath", { 512, 512 }, true);
    CutImage("BulletHitEffect", { 128, 128 });
    CutImage("Blood", { 512, 512 });
    CutImage("Morden_Minigun", { 512, 512 }, true);
    CutImage("Morden_Death", { 512, 512 }, true);
    CutImage("MonsterBullet", { 64, 64 });
    CutImage("Explosion", { 512, 512 });
    CutImage("Helicopter", { 512, 512 }, true);
    CutImage("Helicopter_Damage", { 512, 512 }, true);
    CutImage("Bomber", { 512, 512 }, true);
    CutImage("Bomber_Damage", { 512, 512 }, true);
    CutImage("MonoeyeUFO", { 768, 768 }, true);
    CutImage("MonoeyeUFO_SpeedUp", { 768, 768 }, true);
    CutImage("MonoeyeUFO_Damage", { 768, 768 }, true);
    CutImage("MonoeyeUFO_Effect", { 128, 900 }, true);
    CutImage("TombStone", { 512, 512 }, true);
    CutImage("TombStone_Damage", { 512, 512 }, true);
    CutImage("ZombieMorden", { 512, 512 }, true);
    CutImage("ZombieMorden_Attack", { 256, 256 }, true);
    CutImage("Item", { 512, 512 }, true);
    CutImage("NPC", { 512, 512 }, true);

    GJHResourcesManager::Inst()->CutBmp("MapChange.bmp", { 1295, 951 });
    GJHResourcesManager::Inst()->CutBmp("HUD.bmp", { 348, 68 });
    GJHResourcesManager::Inst()->CutBmp("MissionText.bmp", { 128, 128 });
    GJHResourcesManager::Inst()->CutBmp("Parachute.bmp", { 512, 512 });
    GJHResourcesManager::Inst()->CutBmp("CharacterSelectUI.bmp", { 1050, 600 });
}

void GJHGameEngineMain::CutImage(GJHString _ImageName, GJHVector _ImageSize, bool _Reverse)
{
    if (_Reverse == true)
    {
        GJHResourcesManager::Inst()->CutBmp(_ImageName + "(Left).bmp", _ImageSize);
        GJHResourcesManager::Inst()->CutBmp(_ImageName + "(Right).bmp", _ImageSize, true);
    }
    else
    {
        GJHResourcesManager::Inst()->CutBmp(_ImageName + "(Left).bmp", _ImageSize, true);
        GJHResourcesManager::Inst()->CutBmp(_ImageName + "(Right).bmp", _ImageSize);
    }
}

void GJHGameEngineMain::SceneCreate()
{
    GJHSceneManager::Inst.CreateScene<TitleScene>("Title");
    GJHSceneManager::Inst.CreateScene<CharacterSelectScene>("CharacterSelect");
    GJHSceneManager::Inst.CreateScene<PlayScene>("Play");
    GJHSceneManager::Inst.CreateScene<EndingScene>("Ending");
    GJHSceneManager::Inst.CreateScene<PivotTestPlayerScene>("PivotTestPlayer");
    GJHSceneManager::Inst.CreateScene<PivotTestMonsterScene>("PivotTestMonster");

    GJHSceneManager::Inst.ChangeScene("Title");
}

void GJHGameEngineMain::InitProcess()
{
    ResourcesLoading();
    SceneCreate();
}

void GJHGameEngineMain::DeadTimeProcess()
{
	GJHGameEngineWindow::MainWindow()->ApiRenderStart();

	GJHSceneManager::Inst.Progress();

	GJHGameEngineWindow::MainWindow()->ApiRenderEnd();
}