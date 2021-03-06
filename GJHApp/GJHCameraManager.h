#pragma once
#include "GJHGameEngineMath.h"
#include <map>

class GJHCameraController;
class GJHGameEngineActor;
class GJHCameraManager
{
public:
	enum class CAMLOCKDIR
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		MAX
	};

private:
	static GJHGameEngineActor* m_Target;
	static GJHVector m_CamPos;
	static GJHVector m_CamPivotPos;
	static GJHVector m_CamPivot;
	static GJHCameraController* CamCon;
	static bool m_ReturnCamXPos;

private:
	static bool m_IsCamShake;
	static GJHVector m_CamShakeOriginalPos;
	static float m_CamShakePower;
	static float m_CamMinShakePower;
	static float m_CamShakeMaxTime;
	static float m_CamShakeTime;
	static float m_CamShakeY;
	static int m_CamShakeCount;
	static float m_CamShakeTerm;

private:
	friend GJHCameraController;

public:
	static GJHGameEngineActor* GetTarget() 
	{
		return m_Target;
	}

	static void SetCamCon(GJHCameraController* _CamCon)
	{
		CamCon = _CamCon;
	}

	static GJHCameraController* GetCamCon() 
	{
		return CamCon;
	}

	static void ReturnCamXPos();
	static void ReturnCamXPosUpdate();

private:
	static std::map<CAMLOCKDIR, bool> m_CamMoveLock;

public:
	static void SetTarget(GJHGameEngineActor* _Target)
	{
		m_Target = _Target;
	}

	static void SetCamPos(const GJHVector& _CamPos)
	{
		m_CamPos = _CamPos;
		m_CamPivotPos = m_CamPos + GJHVector(WINDOWWIDTH * m_CamPivot.x, WINDOWHEIGHT * m_CamPivot.y);
	}

	static void LeftCamLock()
	{
		m_CamMoveLock[CAMLOCKDIR::LEFT] = true;
	}

	static void LeftCamUnlock()
	{
		m_CamMoveLock[CAMLOCKDIR::LEFT] = false;
	}

	static void RightCamLock()
	{
		m_CamMoveLock[CAMLOCKDIR::RIGHT] = true;
	}

	static void RightCamUnlock()
	{
		m_CamMoveLock[CAMLOCKDIR::RIGHT] = false;
	}

	static void UpCamLock()
	{
		m_CamMoveLock[CAMLOCKDIR::UP] = true;
	}

	static void UpCamUnlock()
	{
		m_CamMoveLock[CAMLOCKDIR::UP] = false;
	}

	static void DownCamLock()
	{
		m_CamMoveLock[CAMLOCKDIR::DOWN] = true;
	}

	static void DownCamUnlock()
	{
		m_CamMoveLock[CAMLOCKDIR::DOWN] = false;
	}

	static GJHVector GetCamPos()
	{
		return m_CamPos;
	}

	static GJHVector GetCamMaxPos()
	{
		return GJHVector(m_CamPos.x + WINDOWWIDTH, m_CamPos.y + WINDOWHEIGHT);
	}

public:
	static void Init();
	static void Update();

public:
	static void CamShake(float _Power, float _Time, float _MinPower = 0.f);
	static void CamShakeMove(const GJHVector& _CamPos);
	static void CamMove(const GJHVector& _CamPos);

private:
	static void CamUpdate();
	static void CamShakeUpdate();
};

