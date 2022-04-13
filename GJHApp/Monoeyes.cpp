#include "Monoeyes.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "InstanceObject.h"
#include "GJHCameraManager.h"

void Monoeyes::Start()
{
	m_AniRender = CreateRender({ 768, 768 }, "BossBody(Left).bmp", ContentsEnum::RENDERORDER::MONSTER);
	CreateAnimation("Front", "BossBody", 101, 101, 0.1f, true);

	ChangeAnimation("Front");
}

void Monoeyes::Update()
{
}

void Monoeyes::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
}


void Monoeyes::SetAnimationData()
{
}