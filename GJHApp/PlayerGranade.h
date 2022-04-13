#pragma once
#include "ObjectBase.h"
#include "define.h"

class GJHRenderer;
class PlayerGranade : public ObjectBase
{
private:
	int m_BounceCount;

private:
	void Start() override;
	void Update() override;

private:
	virtual void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void CreateExplosion();

public:
	PlayerGranade() :
		m_BounceCount(0)
	{
	}
};

