#include "PivotTestMonsterScene.h"
#include "PivotTestMonster.h"
#include <GJHGameEngineWindow.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineTime.h>

void PivotTestMonsterScene::Loading()
{
	{
		GJHGameEngineActor* NewActor = CreateActor<PivotTestMonster>();
		NewActor->SetPos(GJHGameEngineWindow::MainWindow()->GetSize().HalfVector2D());
	}
}

void PivotTestMonsterScene::SceneUpdate()
{

}