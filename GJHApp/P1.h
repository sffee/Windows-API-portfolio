#pragma once
#include "ObjectBase.h"	

class P1 : public ObjectBase
{
private:
	bool m_IsShow;

private:
	GJHGameEngineTimer Timer;

private:
	void Start() override;
	void Update() override;
	void SceneStart() override;
};