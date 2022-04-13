#include "GJHCameraManager.h"
#include "GJHGameEngineActor.h"
#include <EngineDefine.h>
#include "GJHCameraController.h"

GJHGameEngineActor* GJHCameraManager::m_Target = nullptr;
GJHVector GJHCameraManager::m_CamPos = GJHVector::ZERO;
GJHVector GJHCameraManager::m_WindowCamPos = GJHVector::ZERO;
GJHVector GJHCameraManager::m_CamPivot = GJHVector(0.5f, 0.5f);
std::map<GJHCameraManager::CAMLOCKDIR, bool> GJHCameraManager::m_CamMoveLock;
GJHCameraController* GJHCameraManager::CamCon = nullptr;

void GJHCameraManager::Init()
{
	for (int i = 0; i <= (int)CAMLOCKDIR::MAX; ++i)
	{
		m_CamMoveLock[(CAMLOCKDIR)i] = true;
	}

	m_WindowCamPos = m_CamPos + GJHVector(WINDOWWIDTH * m_CamPivot.x, WINDOWHEIGHT * m_CamPivot.y);
}

void GJHCameraManager::Update()
{
	CamUpdate();
}

void GJHCameraManager::CamMove(const GJHVector& _CamPos)
{
	m_CamPos = _CamPos;
	m_WindowCamPos = m_CamPos + GJHVector(WINDOWWIDTH * m_CamPivot.x, WINDOWHEIGHT * m_CamPivot.y);
}

void GJHCameraManager::CamUpdate()
{
	if (m_Target == nullptr)
	{
		return;
	}

	GJHVector TargetPos = m_Target->GetPos();

	if (nullptr == CamCon)
	{
		if (TargetPos.x < m_WindowCamPos.x &&
			m_CamMoveLock[CAMLOCKDIR::LEFT] == false)
		{
			CamMove({ m_CamPos.x - (m_WindowCamPos.x - TargetPos.x), m_CamPos.y });
		}

		if (m_WindowCamPos.x < TargetPos.x &&
			m_CamMoveLock[CAMLOCKDIR::RIGHT] == false)
		{
			CamMove({ m_CamPos.x + (TargetPos.x - m_WindowCamPos.x), m_CamPos.y });
		}

		if (TargetPos.y < m_WindowCamPos.y &&
			m_CamMoveLock[CAMLOCKDIR::UP] == false)
		{
			CamMove({ m_CamPos.x, m_CamPos.y - (m_WindowCamPos.y - TargetPos.y) });
		}

		if (m_WindowCamPos.y < TargetPos.y &&
			m_CamMoveLock[CAMLOCKDIR::DOWN] == false)
		{
			CamMove({ m_CamPos.x, m_CamPos.y + (TargetPos.y - m_WindowCamPos.y) });
		}
	}
	else 
	{
		CamCon->CamUpdate();
	}
}