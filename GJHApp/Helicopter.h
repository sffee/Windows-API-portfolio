#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include <map>
#include "Monster.h"

class Helicopter : public Monster
{
private:
	static float MOVE_MOVESPEED;
	static float ATTACK_MOVESPEED;
	static float SPEED_DOWN_DISTANCEX;
	static float SPEED_DOWN_DISTANCEY;

	enum class ENUM_ANGLE
	{
		ANGLE_NONE,
		ANGLE_24,
		ANGLE_26,
		ANGLE_33,
		ANGLE_41,
		ANGLE_46,
		ANGLE_62,
		ANGLE_74,
		ANGLE_90
	};

	enum class ENUM_KEEPPOS
	{
		KEEPPOS_150,
		KEEPPOS_250,
		KEEPPOS_350,
		KEEPPOS_450,
		KEEPPOS_550,
		KEEPPOS_650,
		KEEPPOS_750,
		KEEPPOS_850,
		KEEPPOS_950,
		KEEPPOS_1050,
		KEEPPOS_1150,
		KEEPPOS_MAX
	};

	enum class ENUM_HEIGHT
	{
		HEIGHT_650,
		HEIGHT_700,
		HEIGHT_750,
		HEIGHT_MAX
	};
	
private:
	GJHStateUpdater<Helicopter> State;
	GJHTimeUpdater<Helicopter> KeepPosUpdater;
	GJHTimeUpdater<Helicopter> KeepHeightUpdater;
	GJHTimeUpdater<Helicopter> UpDownUpdater;

private:
	GJHGameEngineTimer AttackCoolTimer;
	GJHGameEngineTimer FireCheckTimer;

private:
	ENUM_ANGLE CurAngle;
	GJHString CurAngleStateStr;
	float PrevKeepPosX;
	float KeepPosX;
	float KeepHeight;
	int FireBulletCount;

private:
	bool AppearSoundPlay;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
	void SceneStart() override;

private:
	void AngleUpdate();
	void ChangeKeepPos();
	void ChangeKeepHeight();
	void Up();
	void Down();

private:
	void Move();
	void CreateBullet();
	void CreateExplosion();
	void SetAnimationData();

private:
	void MoveInit();
	void MoveState();

	void AttackInit();
	void AttackState();
};