#pragma once
#include <GJHGameEngineScene.h>
#include <GJHGameEngineTime.h>

class CharacterSelectScene : public GJHGameEngineScene
{
private:
	bool m_PlayBGM;
	GJHGameEngineTimer Timer;

public:
	void Loading() override;
	void SceneUpdate() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;


private:
	void BlackBox();
};