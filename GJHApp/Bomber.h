#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include <map>
#include "Monster.h"

class Bomber : public Monster
{
private:
	static float ANIMATION_CHANGE_DISTANCE;
	static float SPEED_DOWN_DISTANCEX;
	static float SPEED_DOWN_DISTANCEY;

private:
	GJHStateUpdater<Bomber> State;

private:
	int m_CurPropellerIndex;
	GJHString m_CurPropellerAniStr;
	std::map<GJHString, std::map<int, AniData>> m_PropellerAnimationData;

private:
	GJHGameEngineTimer AttackCoolTimer;
	GJHTimeUpdater<Bomber> BombDropUpdater;
	GJHTimeUpdater<Bomber> UpDownUpdater;

private:
	float m_KeepHeight;
	bool AppearSoundPlay;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void SetAnimationData();
	void PushPropellerAnimationData(const GJHString& _Name, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime);
	void PropellerAnimationDataCheck();
	void PropellerAnimationIndexChanger();
	void ChangePropellerAnimation(int _Index);

private:
	void Move();
	void Up();
	void Down();

private:
	void CreateExplosion();
	void Attack();
	void CreateBomb();

private:
	void IdleInit();
	void IdleState();

	void BackStartInit();
	void BackStartState();

	void BackEndInit();
	void BackEndState();

	void FrontStartInit();
	void FrontStartState();

	void FrontEndInit();
	void FrontEndState();
};