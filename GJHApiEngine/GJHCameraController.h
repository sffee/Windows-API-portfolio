#pragma once
#include "GJHCollision.h"
#include "GJHGameEngineActor.h"

// ��� ī�޶��� ��ɵ���
// 1�� ����ȴ�.

class GJHCameraController : public GJHGameEngineActor
{
public:
	enum class CAMTYPE
	{
		MOVE,
		NEXTLINERARMOVEY,
		MONSTERSTOP,
		FIX,
		FREE
	};

private:
	GJHCollision* m_Collision;
	GJHCameraController* m_NextController;
	CAMTYPE m_CamType;
	GJHVector CamPos;

public:
	void SetCamType(CAMTYPE _CamType)
	{
		m_CamType = _CamType;
	}

	void SetNextController(GJHCameraController* _NextController)
	{
		m_NextController = _NextController;
	}

public:
	void SetCol(const GJHVector& _Col);
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
	void CamUpdate();

	void DebugRender() override;


public:
	GJHCameraController();
};

