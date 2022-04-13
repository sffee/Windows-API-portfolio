#pragma once
#include <GJHGameEngineActor.h>

class UI : public GJHGameEngineActor
{
private:
	static int m_GameTime;

public:
	static void SetGameTime(int _Time)
	{
		m_GameTime = _Time;
	}

private:
	GJHTimeUpdater<UI> GameTimeUpdater;

private:
	void SubGameTime();

private:
	GJHRenderer* m_ScoreRender[6];
	GJHRenderer* m_AmmoRender[3];
	GJHRenderer* m_GranadeRender[2];
	GJHRenderer* m_GameTimeRender[2];
	GJHRenderer* m_LifeRender;
	GJHRenderer* m_PressStartRender;

private:
	GJHTimeUpdater<UI> PressStartUpdater;

private:
	void Start() override;
	void Update() override;

private:
	void CreateHUDRender(GJHRenderer*& _Render, const GJHString& _AniName, int _Frame, const GJHVector& _ActorPivot);

private:
	void ScoreUpdate();
	void AmmoUpdate();
	void GranadeUpdate();
	void LifeUpdate();
	void GameTimeUpdate();

private:
	void PressStartOn();
	void PressStartOff();

public:
	void MissionStart();
	void MissionComplete();
};