#include "GJHCameraController.h"
#include "GJHCameraManager.h"
#include "Monster.h"

GJHCameraController::GJHCameraController() :
	m_Collision(nullptr),
	m_PrevController(nullptr),
	m_NextController(nullptr),
	m_SpawnMonsterNextController(nullptr),
	m_CamType(CAMTYPE::NONE),
	m_CamPos(),
	m_EndMonsterCount(0),
	m_SpawnMonsterVec(),
	m_SpawnMonsterTime(0.f),
	m_SpawnMonsterMaxTime(0.f),
	m_SpawnMonsterEnd(false)
{
}

void GJHCameraController::Start()
{
	m_Collision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 100, 800 }, ContentsEnum::COLTYPE::CAMCONTROL);
}

void GJHCameraController::ColEnter(GJHCollision* _This, GJHCollision* _Other) 
{
	if (this == GJHCameraManager::GetCamCon())
	{
		return;
	}

	if (m_CamType == CAMTYPE::FREE)
	{
		m_PrevController->Death();
		Death();
		GJHCameraManager::SetCamCon(nullptr);
		return;
	}

	if (m_CamType == CAMTYPE::RIGHTCAMLOCK)
	{
		GJHCameraManager::RightCamLock();
		Death();
	}
	else if (m_CamType == CAMTYPE::LEFTCAMLOCK)
	{
		GJHCameraManager::LeftCamLock();
		Death();
	}
	else if (m_CamType == CAMTYPE::UPCAMLOCK)
	{
		GJHCameraManager::UpCamLock();
		Death();
	}
	else if (m_CamType == CAMTYPE::DOWNCAMLOCK)
	{
		GJHCameraManager::DownCamLock();
		Death();
	}
	else if (m_CamType == CAMTYPE::MONSTERSPAWN)
	{
		m_EndMonsterCount = Monster::GetMonsterCount() - (int)m_SpawnMonsterVec.size();
		
		GJHCameraManager::RightCamLock();
		GJHCameraManager::LeftCamLock();
		GJHCameraManager::UpCamLock();
		GJHCameraManager::DownCamLock();
	}

	GJHCameraManager::SetCamCon(this);
	m_CamPos = GJHCameraManager::GetCamPos();
}

void GJHCameraController::CamUpdate() 
{
	if (this != GJHCameraManager::GetCamCon())
		return;

	if (m_CamType == CAMTYPE::NEXTLINEMOVEY)
	{
		GJHVector TargetPos = GJHCameraManager::m_Target->GetPos();
		GJHVector ThisPos = GetPos();
		GJHVector NextPos = m_NextController->GetPos();
		float PlayerPivotX = (TargetPos.x - ThisPos.x);
		if (PlayerPivotX <= 0)
			return;

		float CamInterLenX = NextPos.x - ThisPos.x;
		float CamInterLenY = NextPos.y - ThisPos.y;
		float ratio = PlayerPivotX / CamInterLenX;

		GJHVector CalCamPos = GJHCameraManager::GetCamPos();
		CalCamPos.y = m_CamPos.y + (CamInterLenY * ratio);

		GJHCameraManager::SetCamPos(CalCamPos);
	}
	else if (m_CamType == CAMTYPE::MONSTERSPAWN)
	{
		if (m_SpawnMonsterEnd == true)
			return;

		m_SpawnMonsterTime += GJHGameEngineTime::FDeltaTime();

		std::vector<std::pair<float, SpawnMonsterData>>::iterator iter = m_SpawnMonsterVec.begin();
		std::vector<std::pair<float, SpawnMonsterData>>::iterator iterEnd = m_SpawnMonsterVec.end();

		for (; iter != iterEnd; ++iter)
		{
			if (iter->second.SpawnComplete == false &&
				iter->first <= m_SpawnMonsterTime)
			{
				iter->second.SpawnComplete = true;
				iter->second.Actor->SceneStart();
				iter->second.Actor->On();
			}
		}

		if (m_SpawnMonsterMaxTime <= m_SpawnMonsterTime)
		{
			if (m_EndMonsterCount == Monster::GetMonsterCount())
			{
				m_SpawnMonsterEnd = true;
				GJHCameraManager::ReturnCamXPos();
				return;
			}
		}
	}
}

void GJHCameraController::PushSpawnMonster(GJHGameEngineActor* _Actor, float _SpawnTime)
{
	_Actor->Off();

	SpawnMonsterData Data;
	Data.Actor = _Actor;
	Data.SpawnComplete = false;

	m_SpawnMonsterVec.push_back(std::pair<float, SpawnMonsterData>(_SpawnTime, Data));

	if (m_SpawnMonsterMaxTime < _SpawnTime)
	{
		m_SpawnMonsterMaxTime = _SpawnTime;
	}
}

void GJHCameraController::ReturnCamComplete()
{
	GJHCameraManager::RightCamUnlock();

	if (m_SpawnMonsterNextController != nullptr)
	{
		m_SpawnMonsterNextController->On();
		m_SpawnMonsterNextController->m_NextController->On();

		GJHCameraManager::SetCamCon(m_SpawnMonsterNextController);
		m_SpawnMonsterNextController->m_CamPos = GJHCameraManager::GetCamPos();
	}

	Death();
}