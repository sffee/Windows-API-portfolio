#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class MordenMinigun : public Monster
{
private:
	GJHStateUpdater<MordenMinigun> State;

private:
	bool m_IsShotBullet;
	bool m_IsOneShot;
	bool m_Death;

	GJHGameEngineTimer CoolTimer;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void CreateAttackEffect();
	void CreateBullet();
	void CreateExplosion();

private:
	void SetAnimationData();

private:
	void IdleInit();
	void IdleState();

	void MoveInit();
	void MoveState();

	void AttackInit();
	void AttackState();

	void Death1Init();
	void Death1State();

	void Death2Init();
	void Death2State();

	void GranadeDeathJumpInit();
	void GranadeDeathJumpState();
};

