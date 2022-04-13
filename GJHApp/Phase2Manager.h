#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "ObjectBase.h"

class Mission;
class Phase2Manager : public ObjectBase
{
private:
	static bool m_MissionComplete;
	static bool m_BossAppear;
	static bool m_BossDie;

public:
	static void SetMissionComplete()
	{
		m_MissionComplete = true;
	}

	static bool IsMissionComplete()
	{
		return m_MissionComplete;
	}

	static void SetBossAppear(bool _Set)
	{
		m_BossAppear = _Set;
	}

	static void SetBossDie(bool _Set)
	{
		m_BossDie = _Set;
	}

private:
	Mission* MissionActor;
	GJHTimeUpdater<Phase2Manager> ItemTimer;

private:
	void CreateMapChanger();
	void CreateGrandFather();

private:
	GJHGameEngineTimer Timer;
	bool m_IsCol;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
};