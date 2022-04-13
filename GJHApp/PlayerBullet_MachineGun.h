#pragma once
#include "ObjectBase.h"
#include "define.h"

class GJHRenderer;
class PlayerBullet_MachineGun : public ObjectBase
{
private:
	float m_CurTime;
	float m_MaxTime;

private:
	void Start() override;
	void Update() override;

private:
	virtual void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

public:
	void SetAngle(float _Angle);

public:
	PlayerBullet_MachineGun() :
		m_CurTime(0.f),
		m_MaxTime(0.f)
	{}
};

