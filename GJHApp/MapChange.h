#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class MapChange : public ObjectBase
{
private:
	GJHStateUpdater<MapChange> State;
	GJHGameEngineTimer Timer;

private:
	void Start() override;
	void Update() override;

private:
	int AniIndex;

private:
	void CreateEffect(const GJHVector& _Pos);

private:
	void MapChange0Init();
	void MapChange0State();

	void MapChange1Init();
	void MapChange1State();

	void MapChange2Init();
	void MapChange2State();

	void MapChange3Init();
	void MapChange3State();

	void MapChangeEndInit();
	void MapChangeEndState();
};