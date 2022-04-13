#pragma once
#include "ObjectBase.h"
#include "define.h"

class GrandFather : public ObjectBase
{
private:
	void Start() override;
	void Update() override;

private:
	GJHStateUpdater<GrandFather> State;
	GJHVector m_StartPos;
	ENUM_ITEMTYPE m_DropItemType;
	bool m_DropItem;

private:
	virtual void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
	virtual void ColStay(GJHCollision* _This, GJHCollision* _Other) override;

private:
	void SetAnimationData();
	void DropItem();

public:
	void SetDropItemType(ENUM_ITEMTYPE _Type)
	{
		m_DropItemType = _Type;
	}

	void SetFallingState()
	{
		State.ChangeState("Falling");
	}

private:
	void BindInit();
	void BindState();

	void BindOutInit();
	void BindOutState();

	void FallingInit();
	void FallingState();

	void WalkInit();
	void WalkState();

	void DropItemInit();
	void DropItemState();

	void SaluteInit();
	void SaluteState();

	void RunAwayInit();
	void RunAwayState();
};