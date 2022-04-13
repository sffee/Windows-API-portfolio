#pragma once
#include "GJHGameEngineObjectBase.h"
#include <GJHGameEngineMath.h>
#include <GJHString.h>

class GJHGameEngineActor;
class GJHGameEngineScene;
class GJHActorSubObjectBase : public GJHGameEngineObjectBase
{
public:
	friend GJHGameEngineActor;
	friend GJHGameEngineScene;

protected:
	GJHGameEngineActor* m_Actor;
	GJHGameEngineScene* m_Scene;
	bool m_IsCameraEffect;
	float m_CamEffectRatioX;
	float m_CamEffectRatioY;

	GJHVector m_AddActorPivot;
	GJHVector m_ActorPivot;
	GJHGeometryInfo2D m_Geo;

public:
	GJHGameEngineActor* GetActor()
	{
		return m_Actor;
	}

	void SetCamEffectRatio(float _Ratio)
	{
		m_CamEffectRatioX = _Ratio;
		m_CamEffectRatioY = _Ratio;
	}

	void SetCamEffectRatioX(float _Ratio)
	{
		m_CamEffectRatioX = _Ratio;
	}

	void SetCamEffectRatioY(float _Ratio)
	{
		m_CamEffectRatioY = _Ratio;
	}

	void CameraEffectOn()
	{
		m_IsCameraEffect = true;
	}

	void CameraEffectOff()
	{
		m_IsCameraEffect = false;
	}

	void SetActorPivot(const GJHVector& _ActorPivot)
	{
		m_ActorPivot = _ActorPivot;
	}

	void SetAddActorPivot(const GJHVector& _ActorPivot)
	{
		m_AddActorPivot = _ActorPivot;
	}

	GJHVector GetActorPivot()
	{
		return m_ActorPivot;
	}

	GJHVector GetAddActorPivot()
	{
		return m_AddActorPivot;
	}

	GJHGeometryInfo2D GetGeo()
	{
		return m_Geo;
	}

	void SetSize(GJHVector _Size)
	{
		m_Geo.Size = _Size;
	}

	GJHVector GetSize()
	{
		return m_Geo.Size;
	}

public:
	GJHActorSubObjectBase() :
		m_Actor(nullptr),
		m_Scene(nullptr),
		m_IsCameraEffect(true),
		m_CamEffectRatioX(1.0f),
		m_CamEffectRatioY(1.0f),
		m_ActorPivot(GJHVector::ZERO),
		m_Geo()
	{

	}
};