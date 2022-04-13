#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class TombStone : public ObjectBase
{
private:
	GJHCollision* m_ThisDamageCollision;
	GJHCollision* m_AttackCollision;
	
private:
	GJHStateUpdater<TombStone> State;
	GJHTimeUpdater<TombStone> UpDownUpdater;
	GJHTimeUpdater<TombStone> DamageAniChangeUpdater;
	GJHGameEngineTimer AniChangeTimer;

private:
	bool m_IsDamage;

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
	void ColStay(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void CollisionSizeChange();
	void SetAnimationData();

private:
	void Drop();
	void Up();
	void Down();

public:
	void Damage();
	void LoopDamage();
	void AniIndexChange();
	void CreateStone(ENUM_DIRECTION _Dir, float _MoveSpeed, float _Gravity);

private:
	void DropInit();
	void DropState();

	void LandInit();
	void LandState();
};