#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "Item.h"

void Item::Start()
{
	m_MoveSpeed = 0.f;

	m_AniRender = CreateRender({ 64, 64 }, "MonsterBullet(Left).bmp", ContentsEnum::RENDERORDER::OBJECT);
	CreateAnimation("Bullet", "MonsterBullet", 0, 1, 0.05f);

	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 20, 20 }, ContentsEnum::COLTYPE::MONSTERBULLET);
	m_AniCollision->SetBlockMove(false);
}

void Item::Update()
{

}

void Item::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
}