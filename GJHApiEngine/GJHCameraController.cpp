#include "GJHCameraController.h"
#include "GJHCameraManager.h"

GJHCameraController::GJHCameraController()  : m_CamType(CAMTYPE::FIX)
{

}

void GJHCameraController::SetCol(const GJHVector& _ColSize) 
{
	m_Collision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, _ColSize, ContentsEnum::COLTYPE::CAMCONTROL);
}

void GJHCameraController::ColEnter(GJHCollision* _This, GJHCollision* _Other) 
{
	if (this == GJHCameraManager::GetCamCon())
	{
		return;
	}

	if (m_CamType == CAMTYPE::FREE)
	{
		GJHCameraManager::SetCamCon(nullptr);
		return;
	}

	// 내가 메인입니다.
	// 요거 되는 순간의 campos를 저장해 놔야 합니다.

	GJHCameraManager::SetCamCon(this);
	CamPos = GJHCameraManager::GetCamPos();
	// 충돌한 순간의 캠의 위치를 받아요.
}

void GJHCameraController::CamUpdate() 
{
	if (this != GJHCameraManager::GetCamCon())
	{
		return;
	}

	if (CAMTYPE::NEXTLINERARMOVEY == m_CamType)
	{
		GJHVector TargetPos = GJHCameraManager::m_Target->GetPos();
		GJHVector ThisPos = GetPos();
		GJHVector NextPos = m_NextController->GetPos();
		float PlayerPivotX = (TargetPos.x - ThisPos.x);
		float CamInterLenX = (NextPos.x - ThisPos.x);

		if (0 >= PlayerPivotX)
		{
			return;
		}
		float ratio = (PlayerPivotX) / (CamInterLenX);

		float CamInterLenY = (NextPos.y - ThisPos.y);
		// 플레이어의 x로 이동하는건 그대로 해야죠?
		// 나를 기준으로한 캠포스를 받습니다.
		GJHVector CalCamPos = CamPos;

		CalCamPos.x += PlayerPivotX;
		CalCamPos.y += CamInterLenY * ratio;

		GJHCameraManager::SetCamPos(CalCamPos);

		int a = 0;

	}


}

void GJHCameraController::DebugRender() 
{
	int a = 0;
}