#include "PivotTestPlayerScene.h"
#include "PivotTestPlayer.h"
#include <GJHGameEngineWindow.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineTime.h>

void PivotTestPlayerScene::Loading()
{
	{
		GJHGameEngineActor* NewActor = CreateActor<PivotTestPlayer>();
		NewActor->SetPos(GJHGameEngineWindow::MainWindow()->GetSize().HalfVector2D());
	}
}

void PivotTestPlayerScene::SceneUpdate()
{
	
}