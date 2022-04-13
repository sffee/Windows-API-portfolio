#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class Monoeyes : public Monster
{
private:
	GJHStateUpdater<Monoeyes> State;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void SetAnimationData();
};

