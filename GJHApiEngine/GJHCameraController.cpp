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

	// ���� �����Դϴ�.
	// ��� �Ǵ� ������ campos�� ������ ���� �մϴ�.

	GJHCameraManager::SetCamCon(this);
	CamPos = GJHCameraManager::GetCamPos();
	// �浹�� ������ ķ�� ��ġ�� �޾ƿ�.
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
		// �÷��̾��� x�� �̵��ϴ°� �״�� �ؾ���?
		// ���� ���������� ķ������ �޽��ϴ�.
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