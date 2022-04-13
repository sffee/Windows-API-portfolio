#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class ZombieDoctor : public Monster
{
private:
	GJHStateUpdater<ZombieDoctor> State;

private:
	bool IsThrowVomit;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void SetAnimationData();

private:
	void CreateThrowVomit();

private:
	void IdleInit();
	void IdleState();

	void MoveInit();
	void MoveState();

	void AttackInit();
	void AttackState();

	void BulletDeathInit();
	void BulletDeathState();

	void GranadeDeathInit();
	void GranadeDeathState();
};