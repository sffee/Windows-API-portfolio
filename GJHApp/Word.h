#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include "Monster.h"

class Word : public ObjectBase
{
private:
	GJHStateUpdater<Word> State;
	GJHGameEngineTimer FlyTimer;

private:
	GJHVector m_DefaultPos;
	float m_YSize;
	float m_YAddSize;
	int m_WordCount;
	int m_WordMaxCount;
	bool m_IsSpeedUp;

public:
	void SetDefaultPos(const GJHVector& _Pos);

private:
	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;

public:
	void Damage();
	void SetYAddSize(float _Size);
	void SetWordMaxCount(int _Count);
	void SetSpeedUp();

private:
	void SizeUpInit();
	void SizeUpState();

	void FlyInit();
	void FlyState();
};