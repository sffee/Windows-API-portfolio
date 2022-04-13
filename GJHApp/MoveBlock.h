#pragma once
#include "ObjectBase.h"

class GJHRenderer;
class MoveBlock : public ObjectBase
{
private:
	GJHRenderer* m_CharacterBackRender;
	GJHRenderer* m_CharacterRender;

private:
	GJHGameEngineTimer Timer;
	GJHStateUpdater<MoveBlock> State;

private:
	bool m_MoveDownCheck;
	float m_ShakeTime;
	int m_ShakeCount;
	bool m_MoveDownSound;

private:
	bool m_TimerEnd;

private:
	void CreateEffect();

private:
	void Start() override;
	void Update() override;
	void SceneStart() override;

private:
	void StartInit();
	void StartState();

	void MoveUpInit();
	void MoveUpState();

	void MoveDownInit();
	void MoveDownState();

	void UpDownInit();
	void UpDownState();

	void SceneChangeInit();
	void SceneChangeState();
};