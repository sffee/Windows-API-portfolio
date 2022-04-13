#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class Laser : public ObjectBase
{
private:
	GJHStateUpdater<Laser> State;
	GJHGameEngineTimer LoopTimer;

private:
	float m_LoopTime;

public:
	~Laser();

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void SetAnimationData();

private:
	void Move();
	void CreateTombStone();

public:
	void SetLoopTime(float _Time);

private:
	void StartInit();
	void StartState();

	void LoopInit();
	void LoopState();

	void EndInit();
	void EndState();
};