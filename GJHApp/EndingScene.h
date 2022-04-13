#pragma once
#include <GJHGameEngineScene.h>

class EndingScene : public GJHGameEngineScene
{
public:
	void Loading() override;
	void SceneUpdate() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
};