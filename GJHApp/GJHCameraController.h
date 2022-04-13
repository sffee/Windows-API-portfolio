#pragma once
#include "GJHCollision.h"
#include "GJHGameEngineActor.h"
#include <vector>

// 모든 카메라의 기능들은
// 1번 실행된다.

class GJHCameraController : public GJHGameEngineActor
{
public:
	enum class CAMTYPE
	{
		NONE,
		RIGHTCAMLOCK,
		LEFTCAMLOCK,
		UPCAMLOCK,
		DOWNCAMLOCK,
		MOVE,
		NEXTLINEMOVEY,
		FREE,
		MONSTERSPAWN
	};

	struct SpawnMonsterData
	{
		GJHGameEngineActor* Actor;
		bool SpawnComplete;

		SpawnMonsterData() :
			Actor(nullptr),
			SpawnComplete(false)
		{
		}
	};

private:
	GJHCollision* m_Collision;
	GJHCameraController* m_PrevController;
	GJHCameraController* m_NextController;
	GJHCameraController* m_SpawnMonsterNextController;
	CAMTYPE m_CamType;
	GJHVector m_CamPos;

private:
	int m_EndMonsterCount;
	std::vector<std::pair<float, SpawnMonsterData>> m_SpawnMonsterVec;
	float m_SpawnMonsterTime;
	float m_SpawnMonsterMaxTime;
	bool m_SpawnMonsterEnd;

public:
	void SetCamType(CAMTYPE _CamType)
	{
		m_CamType = _CamType;
	}

	void SetNextController(GJHCameraController* _Controller)
	{
		m_NextController = _Controller;
	}

	void SetPrevController(GJHCameraController* _Controller)
	{
		m_PrevController = _Controller;
	}

	void SpawnMonsterNextController(GJHCameraController* _Controller)
	{
		m_SpawnMonsterNextController = _Controller;
	}

	void SetPivot(const GJHVector& _Pivot)
	{
		m_Collision->SetActorPivot(_Pivot);
	}

public:
	void Start() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
	void CamUpdate();

public:
	void ReturnCamComplete();

public:
	void PushSpawnMonster(GJHGameEngineActor* _Actor, float _SpawnTime = 0.f);

public:
	GJHCameraController();
};

