#pragma once
#include "Item.h"
#include "define.h"

class HeavyMachineGunBox : public Item
{
private:
	void Start() override;
	void Update() override;

private:
	void PickUpEffect();

private:
	virtual void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
	virtual void ColStay(GJHCollision* _This, GJHCollision* _Other) override;
};

