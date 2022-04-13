#pragma once
#include "GJHActorSubObjectBase.h"
#include <GJHGameEngineMath.h>
#include <EngineDefine.h>
#include <set>

class GJHGameEngineActor;
class GJHGameEngineScene;
class GJHCollision : public GJHActorSubObjectBase
{
public:
	friend GJHGameEngineActor;
	friend GJHGameEngineScene;

public:
	static HDC m_HDC;

private:
	COLGEOTYPE m_ColType;
	GJHGeometryInfo2D m_DebugGeo;

	std::set<GJHCollision*> m_OtherCollision;

	bool m_Hitable;
	bool m_IsBlockMove;

public:
	GJHCollision();
	~GJHCollision();

public:
	void SetGeoType(COLGEOTYPE _Type)
	{
		m_ColType = _Type;
	}

	COLGEOTYPE GetColType()
	{
		return m_ColType;
	}

	void SetBlockMove(bool _Set)
	{
		m_IsBlockMove = _Set;
	}

	bool GetBlockMove()
	{
		return m_IsBlockMove;
	}

	void SetHitable(bool _Hitable);

public:
	void CalPos();

public:
	void CollisionCheck(GJHCollision* _Other);

public:
	void DebugRender();

public:
	virtual void Enter() {}
	virtual void Stay() {}
	virtual void Exit() {}
};