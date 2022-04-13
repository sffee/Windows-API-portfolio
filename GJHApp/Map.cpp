#include "Map.h"
#include <GJHGameEngineScene.h>
#include <GJHGameEngineWindow.h>
#include <GJHResourcesManager.h>
#include <GJHRenderer.h>
#include <GJHGameEngineTime.h>

void Map::Start()
{
	AniRender = CreateRender("Map.bmp", ContentsEnum::RENDERORDER::MAP);
	MapPixelRender = CreateRender("MapPixel.bmp", (int)ContentsEnum::RENDERORDER::FOREGROUND + 1000);
	MapPixelRender->Off();
	
	AniRender = CreateRender("BackGround1.bmp", ContentsEnum::RENDERORDER::BACKGROUND);
	AniRender->SetActorPivot({ 10400, -1350 });
	AniRender->SetCamEffectRatio(0.45f);

	AniRender = CreateRender("BackGround2.bmp", ContentsEnum::RENDERORDER::BACKGROUND);
	AniRender->SetActorPivot({ 6300, -1030 });
	AniRender->SetCamEffectRatio(0.45f);

	AniRender = CreateRender("Object1.bmp", ContentsEnum::RENDERORDER::FOREGROUND);
	AniRender->SetActorPivot({ 7350, -980 });

	AniRender = CreateRender("Object2.bmp", ContentsEnum::RENDERORDER::FOREGROUND);
	AniRender->SetActorPivot({ 5000, -1100 });

	//AniRender = CreateRender("BossRoomGround.bmp", (int)ContentsEnum::RENDERORDER::MAPOBJECT + 4);
	//AniRender->SetActorPivot({ -11200, 1288 });
}

void Map::Update()
{
}

void Map::TogglePixelRender()
{
	DrawMapPixel = !DrawMapPixel;

	if (DrawMapPixel == true)
	{
		MapPixelRender->On();
	}
	else
	{
		MapPixelRender->Off();
	}
}