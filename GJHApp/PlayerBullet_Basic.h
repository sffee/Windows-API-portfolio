#pragma once
#include "ObjectBase.h"
#include "define.h"

class GJHRenderer;
class PlayerBullet_Basic : public ObjectBase
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
	PlayerBullet_Basic() :
		m_CurTime(0.f),
		m_MaxTime(0.f)
	{}
};

