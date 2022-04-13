#include "Ending.h"
#include <GJHRenderer.h>

void Ending::Start()
{
	m_AniRender = CreateRender({ 1280, 960 }, "EndingScene.bmp", (int)ContentsEnum::RENDERORDER::UI);
}

void Ending::Update()
{
}