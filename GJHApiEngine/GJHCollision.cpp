#include "GJHCollision.h"
#include "GJHGameEngineActor.h"
#include "GJHGameEngineScene.h"
#include "GJHGameEngineWindow.h"
#include <GJHCameraManager.h>

HDC GJHCollision::m_HDC;

GJHCollision::GJHCollision() : m_ColType(COLGEOTYPE::CGT_MAX), m_IsBlockMove(true)
{

}

GJHCollision::~GJHCollision()
{

}

void GJHCollision::DebugRender()
{
	if (m_Hitable == false)
	{
		return;
	}

	m_DebugGeo.Size = m_Geo.Size;

	if (m_IsCameraEffect == true)
	{
		m_DebugGeo.Pos = m_Actor->GetPos() - GJHVector(GJHCameraManager::GetCamPos().x * m_CamEffectRatioX, GJHCameraManager::GetCamPos().y * m_CamEffectRatioY);
	}
	else
	{
		m_DebugGeo.Pos = m_Actor->GetPos();
	}

	m_DebugGeo.Pos += m_ActorPivot;

	HBRUSH Brush, oBrush;

	switch (GetOrder())
	{
	case (int)ContentsEnum::COLTYPE::MONSTER:
	case (int)ContentsEnum::COLTYPE::MONSTERBULLET:
		Brush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case (int)ContentsEnum::COLTYPE::CAMCONTROL:
		Brush = CreateSolidBrush(RGB(217, 65, 140));
		break;
	case (int)ContentsEnum::COLTYPE::NONE:
		return;
		break;
	default:
		Brush = CreateSolidBrush(RGB(255, 255, 255));
	}
	
	oBrush = (HBRUSH)SelectObject(m_HDC, Brush);

	Rectangle(GJHGameEngineWindow::MainWindow()->GetBackBuffer(),
		m_DebugGeo.LeftUp().ix(),
		m_DebugGeo.LeftUp().iy(),
		m_DebugGeo.RightDown().ix(),
		m_DebugGeo.RightDown().iy());

	SelectObject(m_HDC, oBrush);
	DeleteObject(Brush);
}

void GJHCollision::SetHitable(bool _Hitable)
{
	m_Hitable = _Hitable;
}

void GJHCollision::CalPos()
{
	m_Geo.Pos = m_Actor->GetPos() + m_ActorPivot;
}

void GJHCollision::CollisionCheck(GJHCollision* _Other)
{
	if (m_Hitable == false || _Other->m_Hitable == false)
	{
		return;
	}

	if (GJHColCheckFunc::ColCheck2D[(int)m_ColType][(int)_Other->m_ColType](m_Geo, _Other->m_Geo) == true)
	{
		if (m_OtherCollision.find(_Other) == m_OtherCollision.end())
		{
			m_OtherCollision.insert(_Other);
			_Other->m_OtherCollision.insert(this);

			m_Actor->ColEnter(this, _Other);
			_Other->m_Actor->ColEnter(_Other, this);
		}
		else
		{
			m_Actor->ColStay(this, _Other);
			_Other->m_Actor->ColStay(_Other, this);
		}
	}
	else
	{
		if (m_OtherCollision.find(_Other) != m_OtherCollision.end())
		{
			m_OtherCollision.erase(_Other);
			_Other->m_OtherCollision.erase(this);

			m_Actor->ColExit(this, _Other);
			_Other->m_Actor->ColExit(_Other, this);
		}
	}
}