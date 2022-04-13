#include "EndingScene.h"
#include <GJHGameEngineWindow.h>
#include "Ending.h"
#include "FadeInOut.h"

void EndingScene::Loading()
{
	{
		Ending* NewActor = CreateActor<Ending>();
		NewActor->SetPos(GJHGameEngineWindow::MainWindow()->GetSize().HalfVector2D());
	}
}

void EndingScene::SceneUpdate()
{

}

void EndingScene::SceneChangeStart()
{
	FadeInOut* m_FadeInOutActor = CreateActor<FadeInOut>();
	m_FadeInOutActor->SetPos({ WINDOWWIDTH / 2, WINDOWHEIGHT / 2 });
	m_FadeInOutActor->FadeOut(5.f);
}

void EndingScene::SceneChangeEnd()
{

}