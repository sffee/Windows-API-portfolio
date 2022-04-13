#pragma once
#include "ObjectBase.h"

class CharacterFace : public ObjectBase
{
private:
	float m_Alpha;

private:
	GJHGameEngineTimer Timer;
	GJHStateUpdater<CharacterFace> State;

private:
	void Start() override;
	void Update() override;
	void SceneStart() override;

private:
	void FaceColorChangeInit();
	void FaceColorChangeState();

	void SelectInit();
	void SelectState();
};