#pragma once
#include "GJHGameEngineScene.h"

class PlayScene : public GJHGameEngineScene
{
public:
	float m_CamMoveSpeed;

private:
	GJHGameEngineActor* PlayerActor;
	class Map* MapActor;
	class UI* UIActor;

private:
	GJHGameEngineTimer MissionStartTimer;

public:
	void Loading() override;
	void SceneUpdate() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void DebugRender() override;

public:
	PlayScene() :
		m_CamMoveSpeed(0.f),
		PlayerActor(nullptr),
		MapActor(nullptr),
		UIActor(nullptr)
	{
	}
};