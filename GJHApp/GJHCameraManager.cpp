#include "GJHCameraManager.h"
#include "GJHGameEngineActor.h"
#include <EngineDefine.h>
#include "GJHCameraController.h"

GJHGameEngineActor* GJHCameraManager::m_Target = nullptr;
GJHVector GJHCameraManager::m_CamPos = GJHVector::ZERO;
GJHVector GJHCameraManager::m_CamPivotPos = GJHVector::ZERO;
GJHVector GJHCameraManager::m_CamPivot = GJHVector(0.5f, 0.5f);
std::map<GJHCameraManager::CAMLOCKDIR, bool> GJHCameraManager::m_CamMoveLock;
GJHCameraController* GJHCameraManager::CamCon = nullptr;
bool GJHCameraManager::m_ReturnCamXPos = false;
bool GJHCameraManager::m_IsCamShake = false;
GJHVector GJHCameraManager::m_CamShakeOriginalPos = GJHVector::ZERO;
float GJHCameraManager::m_CamShakePower = 0.f;
float GJHCameraManager::m_CamMinShakePower = 0.f;
float GJHCameraManager::m_CamShakeMaxTime = 0.f;
float GJHCameraManager::m_CamShakeTime = 0.f;
float GJHCameraManager::m_CamShakeY = 0.f;
float GJHCameraManager::m_CamShakeTerm = 0.f;
int GJHCameraManager::m_CamShakeCount = 0;

void GJHCameraManager::Init()
{
	for (int i = 0; i <= (int)CAMLOCKDIR::MAX; ++i)
	{
		m_CamMoveLock[(CAMLOCKDIR)i] = true;
	}

	m_CamPivotPos = m_CamPos + GJHVector(WINDOWWIDTH * m_CamPivot.x, WINDOWHEIGHT * m_CamPivot.y);
}

void GJHCameraManager::ReturnCamXPos()
{
	m_ReturnCamXPos = true;
}

void GJHCameraManager::ReturnCamXPosUpdate()
{
	float TargetCamXPos = m_Target->GetPos().x - WINDOWWIDTH * m_CamPivot.x;
	int XDir = m_CamPos.x < TargetCamXPos ? 1 : -1;

	float MoveXPos = m_CamPos.x + 3000.f * XDir * GJHGameEngineTime::FDeltaTime();

	if (XDir == -1)
	{
		if (MoveXPos <= TargetCamXPos)
		{
			MoveXPos= TargetCamXPos;
		}
	}
	else
	{
		if (TargetCamXPos <= MoveXPos)
		{
			MoveXPos = TargetCamXPos;
		}
	}

	m_CamPos.x = MoveXPos;
	m_CamPivotPos = m_CamPos + GJHVector(WINDOWWIDTH * m_CamPivot.x, WINDOWHEIGHT * m_CamPivot.y);

	if (MoveXPos == TargetCamXPos)
	{
		m_ReturnCamXPos = false;
		CamCon->ReturnCamComplete();
		CamCon = nullptr;
	}
}

void GJHCameraManager::Update()
{
	CamUpdate();
	CamShakeUpdate();
}

void GJHCameraManager::CamShake(float _Power, float _Time, float _MinPower)
{
	m_IsCamShake = true;
	m_CamShakePower = _Power;
	m_CamMinShakePower = _MinPower;
	m_CamShakeMaxTime = _Time;
	m_CamShakeTime = _Time;
	m_CamShakeOriginalPos = m_CamPos;
	m_CamShakeCount = 0;
	m_CamShakeTerm = 0.04f;
}

void GJHCameraManager::CamMove(const GJHVector& _CamPos)
{
	m_CamPos = _CamPos;
	m_CamPivotPos = m_CamPos + GJHVector(WINDOWWIDTH * m_CamPivot.x, WINDOWHEIGHT * m_CamPivot.y);
}

void GJHCameraManager::CamShakeMove(const GJHVector& _CamPos)
{
	if (m_IsCamShake == false)
	{
		return;
	}

	m_CamShakeOriginalPos = _CamPos;
}

void GJHCameraManager::CamUpdate()
{
	if (m_Target == nullptr)
	{
		return;
	}

	if (m_ReturnCamXPos == true)
	{
		ReturnCamXPosUpdate();
		return;
	}

	if (m_IsCamShake == true)
	{
		CamMove({ m_CamShakeOriginalPos.x, m_CamShakeOriginalPos.y + m_CamShakeY });
	}

	GJHVector TargetPos = m_Target->GetPos();

	if (TargetPos.x < m_CamPivotPos.x &&
		m_CamMoveLock[CAMLOCKDIR::LEFT] == false)
	{
		CamMove({ m_CamPos.x - (m_CamPivotPos.x - TargetPos.x), m_CamPos.y + m_CamShakeY });
		CamShakeMove({ m_CamPos.x - (m_CamPivotPos.x - TargetPos.x), m_CamPos.y });
	}

	if (m_CamPivotPos.x < TargetPos.x &&
		m_CamMoveLock[CAMLOCKDIR::RIGHT] == false)
	{
		CamMove({ m_CamPos.x + (TargetPos.x - m_CamPivotPos.x), m_CamPos.y + m_CamShakeY });
		CamShakeMove({ m_CamPos.x + (TargetPos.x - m_CamPivotPos.x), m_CamPos.y });
	}

	if (CamCon == nullptr)
	{
		if (TargetPos.y < m_CamPivotPos.y &&
			m_CamMoveLock[CAMLOCKDIR::UP] == false)
		{
			CamMove({ m_CamPos.x, m_CamPos.y - (m_CamPivotPos.y - TargetPos.y) + m_CamShakeY });
			CamShakeMove({ m_CamPos.x, m_CamPos.y - (m_CamPivotPos.y - TargetPos.y) });
		}

		if (m_CamPivotPos.y < TargetPos.y &&
			m_CamMoveLock[CAMLOCKDIR::DOWN] == false)
		{
			CamMove({ m_CamPos.x, m_CamPos.y + (TargetPos.y - m_CamPivotPos.y) + m_CamShakeY });
			CamShakeMove({ m_CamPos.x, m_CamPos.y + (TargetPos.y - m_CamPivotPos.y) });
		}
	}
	else 
	{
		CamCon->CamUpdate();
	}
}

void GJHCameraManager::CamShakeUpdate()
{
	if (m_IsCamShake == false)
	{
		return;
	}

	m_CamShakeTime -= GJHGameEngineTime::FDeltaTime();

	float Term = m_CamShakeMaxTime - (m_CamShakeTerm * m_CamShakeCount);

	if (m_CamShakeTime <= Term)
	{
		m_CamShakeY = (m_CamShakePower + m_CamMinShakePower) * (m_CamShakeTime / m_CamShakeMaxTime) * 3;
		m_CamShakeY = m_CamShakeCount % 2 == 0 ? -m_CamShakeY : m_CamShakeY;

		++m_CamShakeCount;
	}

	if (m_CamShakeTime <= 0.f)
	{
		m_CamShakeY = 0.f;
		m_IsCamShake = false;

		CamMove(m_CamShakeOriginalPos);
		return;
	}	
}