#include "TitleCharacter.h"
#include <GJHGameEngineScene.h>
#include <GJHGameEngineWindow.h>
#include <GJHResourcesManager.h>
#include <GJHRenderer.h>

void TitleCharacter::Start()
{
	{
		GJHRenderer* Render = CreateRender({ 44, 48 }, "Eri Kasamoto.bmp", 1);
		Render->SetImagePivot({ 7, 574 });
		Render->SetImageSize({ 22, 24 });
		Render->SetActorPivot({ -5, 12 });
		Render->SetTransColor(RGB(255, 255, 255));
	}

	{
		GJHRenderer* Render = CreateRender({ 62, 56 }, "Eri Kasamoto.bmp", 1);
		Render->SetImagePivot({ 130, 539 });
		Render->SetImageSize({ 31, 28 });
		Render->SetActorPivot({ 0, -12 });
		Render->SetTransColor(RGB(255, 255, 255));
	}
}

void TitleCharacter::Update()
{

}
