#pragma once
#include <GJHGameEngineScene.h>

class TitleScene : public GJHGameEngineScene
{
public:
	void Loading() override;
	void SceneUpdate() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
};