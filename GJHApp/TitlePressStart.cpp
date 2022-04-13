#include "TitlePressStart.h"
#include <GJHGameEngineScene.h>
#include <GJHGameEngineWindow.h>
#include <GJHResourcesManager.h>

void TitlePressStart::Start()
{
	Image = GJHResourcesManager::Inst()->FindBmp("PressStart.bmp");

	m_Geo.Size = { 348, 60 };

	ImagePivot = { 0, 0 };
	ImageSize = { 174, 30 };

	TransColor = RGB(0, 253, 24);

	Time = clock();
	isDraw = true;
}

void TitlePressStart::Update()
{
	int DeltaTime = clock() - Time;
	if (DeltaTime > 700)
	{
		Time = clock();
		isDraw = !isDraw;
	}
}

void TitlePressStart::Render()
{
	m_Geo.Pos = GetPos();

	if (isDraw)
	{
		GJHGameEngineWindow::MainWindow()->GetBackBuffer().TransCopy(*Image,
			m_Geo.LeftUp(), m_Geo.Size, ImagePivot, ImageSize, TransColor);
	}
}
