#include "TitleScene.h"
#include "TitleBackGround.h"
#include "Player.h"
#include <GJHGameEngineWindow.h>
#include <GJHGameEngineInput.h>
#include <GJHSceneManager.h>
#include <GJHGameEngineSound.h>

void TitleScene::SceneUpdate()
{
	if (GJHGameEngineInput::Down("Enter") == true)
	{
		GJHSceneManager::Inst.ChangeScene("CharacterSelect");
	}

	if (GJHGameEngineInput::Down("ChangeCharacterPivotToolScene") == true)
	{
		GJHSceneManager::Inst.ChangeScene("PivotTestPlayer");
	}

	if (GJHGameEngineInput::Down("ChangeMonsterPivotToolScene") == true)
	{
		GJHSceneManager::Inst.ChangeScene("PivotTestMonster");
	}
}

void TitleScene::Loading()
{
	GJHGameEngineInput::CreateKey("Enter", VK_RETURN);
	GJHGameEngineInput::CreateKey("Control", VK_CONTROL);
	GJHGameEngineInput::CreateKey("Escape", VK_ESCAPE);
	GJHGameEngineInput::CreateKey("ChangeCharacterPivotToolScene", '1');
	GJHGameEngineInput::CreateKey("ChangeMonsterPivotToolScene", '2');

	{
		GJHGameEngineActor* NewActor = CreateActor<TitleBackGround>("TitleBackGround");
		NewActor->SetPos(GJHGameEngineWindow::MainWindow()->GetSize().HalfVector2D());
	}
}

void TitleScene::SceneChangeStart()
{
	GJHGameEngineSound::PlayManagement("TitleBgm", "Title.mp3", 1.f, true);
}

void TitleScene::SceneChangeEnd()
{
	GJHGameEngineSound::StopManagement("TitleBgm");
}