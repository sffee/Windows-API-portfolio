#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class Word;
class Laser;
class MonoeyeUFO : public Monster
{
private:
	GJHStateUpdater<MonoeyeUFO> State;
	GJHGameEngineTimer Timer;
	GJHGameEngineTimer AttackTimer;
	GJHGameEngineTimer MissionCompleteTimer;

private:
	static Word* m_WordActor;
	static Laser* m_LaserActor;

public:
	static void DeleteWordActor();
	static void DeleteLaserActor();

private:
	bool m_IsAttackSpeedUp;
	int m_DeathExplosionCount;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void AttackSpeedUpCheck();
	void CreateLaser(bool _IsSpeedUp);
	void CreateWord(bool _IsSpeedUp);
	void CreateDeathExplosion(const GJHVector& _Pos, float _Gravity = 0.f, float _GravityAddValue = 0.f, float _MoveSpeed = 0.f, int _Order = (int)ContentsEnum::RENDERORDER::OBJECT);
	void CreateStartStone(ENUM_DIRECTION _Dir, float _MoveSpeed, float _Gravity);
	void CreateStone(ENUM_DIRECTION _Dir, float _MoveSpeed, float _Gravity);
	void ChangeDamageAnimation();

private:
	void SetAnimationData();

private:
	void AppearInit();
	void AppearState();

	void IdleInit();
	void IdleState();

	void FireInit();
	void FireState();

	void DeathInit();
	void DeathState();
};