#pragma once
#include "ObjectBase.h"
#include <map>

class Mission : public ObjectBase
{
private:
	GJHStateUpdater<Mission> State;

private:
	GJHGameEngineTimer Timer;
	GJHTimeUpdater<Mission> BlinkUpdater;
	int m_MissionCount;
	std::map<int, GJHVector> m_MissionArrivalPos;
	std::map<int, float> m_MissionArrivalAngle;

private:
	class MissionText* m_MissionStartActor[18];
	class MissionText* m_MissionCompleteActor[17];

private:
	bool m_MissionCompleteEnd;

public:
	bool IsMissionCompleteEnd()
	{
		return m_MissionCompleteEnd;
	}

private:
	void Start() override;
	void Update() override;

public:
	void MissionStart();
	void MissionStart_On();
	void MissionStart_Off();

public:
	void MissionComplete();
	void MissionComplete_On();
	void MissionComplete_Off();

private:
	void MissionStart_StartMoveInit();
	void MissionStart_StartMoveState();

	void MissionStart_BlinkInit();
	void MissionStart_BlinkState();

	void MissionStart_EndInit();
	void MissionStart_EndState();

	void MissionComplete_StartMoveInit();
	void MissionComplete_StartMoveState();

	void MissionComplete_BlinkInit();
	void MissionComplete_BlinkState();

	void MissionComplete_EndInit();
	void MissionComplete_EndState();
};