#pragma once
#include "ObjectBase.h"
#include "define.h"

class GJHRenderer;
class ZombieGirlThrowVomit : public ObjectBase
{
private:
	void Start() override;
	void Update() override;

private:
	virtual void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void SetAnimationData();
	void CreateEndEffect();
};

