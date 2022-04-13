#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class ZombieMorden : public Monster
{
private:
	GJHStateUpdater<ZombieMorden> State;

private:
	bool m_AttackStart;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void CreateAttackExplosion();

private:
	void SetAnimationData();

	void IdleInit();
	void IdleState();

	void MoveInit();
	void MoveState();

	void AttackInit();
	void AttackState();

	void DeathInit();
	void DeathState();
};