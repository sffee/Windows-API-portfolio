#include "CharacterSelectBackGround.h"
#include <GJHRenderer.h>

void CharacterSelectBackGround::Start()
{
	m_ImageDir = ENUM_DIRECTION::RIGHT;

	m_AniRender = CreateRender({ 1280, 960 }, "CharacterSelectBackGround.bmp", (int)ContentsEnum::RENDERORDER::UI + 1);
	
	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI + 10);
	m_AniRender->CreateAnimation("SoldierSelect", "CharacterSelectUI.bmp", 0, 0, 1.f);
	m_AniRender->SetActorPivot({ 0, -362 });
	m_AniRender->ChangeAnimation("SoldierSelect");

	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI);
	m_AniRender->CreateAnimation("Block", "CharacterSelectUI.bmp", 7, 7, 1.f);
	m_AniRender->SetActorPivot({ -435, 80 });
	m_AniRender->ChangeAnimation("Block");

	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI);
	m_AniRender->CreateAnimation("Block", "CharacterSelectUI.bmp", 7, 7, 1.f);
	m_AniRender->SetActorPivot({ -147, 80 });
	m_AniRender->ChangeAnimation("Block");

	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI);
	m_AniRender->CreateAnimation("Block", "CharacterSelectUI.bmp", 7, 7, 1.f);
	m_AniRender->SetActorPivot({ 140, 80 });
	m_AniRender->ChangeAnimation("Block");

	m_AniRender = CreateRender({ 1050, 600 }, "CharacterSelectUI.bmp", (int)ContentsEnum::RENDERORDER::UI - 1);
	m_AniRender->CreateAnimation("CharacterFace", "CharacterSelectUI.bmp", 3, 3, 1.f);
	m_AniRender->SetActorPivot({ 430, 112 });
	m_AniRender->ChangeAnimation("CharacterFace");
}

void CharacterSelectBackGround::Update()
{

}