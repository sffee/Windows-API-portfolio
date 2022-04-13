#include "GJHGameEngineActor.h"
#include "GJHRenderer.h"
#include "GJHCollision.h"
#include "GJHGameEngineScene.h"
#include "GJHResourcesManager.h"
#include <EngineDefine.h>

GJHGameEngineActor::GJHGameEngineActor() :
	m_Scene(nullptr),
	m_PrevImageDir(ENUM_DIRECTION::NONE),
	m_ImageDir(ENUM_DIRECTION::LEFT)
{

}

GJHGameEngineActor::~GJHGameEngineActor()
{
	{
		std::list<GJHRenderer*>::iterator Start = m_Renderer.begin();
		std::list<GJHRenderer*>::iterator End = m_Renderer.end();

		for (; Start != End; ++Start)
		{
			if ((*Start) != nullptr)
			{
				delete (*Start);
				(*Start) = nullptr;
			}
		}
	}

	{
		std::list<GJHCollision*>::iterator Start = m_Collision.begin();
		std::list<GJHCollision*>::iterator End = m_Collision.end();

		for (; Start != End; ++Start)
		{
			if ((*Start) != nullptr)
			{
				delete (*Start);
				(*Start) = nullptr;
			}
		}
	}
}

void GJHGameEngineActor::Start()
{

}

void GJHGameEngineActor::Update()
{

}

void GJHGameEngineActor::DebugRender()
{

}

GJHRenderer* GJHGameEngineActor::CreateRender(const GJHVector& _Size, ContentsEnum::RENDERORDER _Order)
{
	return CreateRender(_Size, (int)_Order);
}

GJHRenderer* GJHGameEngineActor::CreateRender(const GJHVector& _Size, int _Order)
{
	GJHRenderer* NewRender = new GJHRenderer();

	NewRender->SetOrder(_Order);
	NewRender->isDraw = true;
	NewRender->m_Actor = this;
	NewRender->m_Geo.Size = _Size;
	m_Scene->PushRender(NewRender);
	m_Renderer.push_back(NewRender);

	return NewRender;
}

GJHRenderer* GJHGameEngineActor::CreateRender(const GJHVector& _Size, const GJHString& _Image, ContentsEnum::RENDERORDER _Order)
{
	return CreateRender(_Size, _Image, (int)_Order);
}

GJHRenderer* GJHGameEngineActor::CreateRender(const GJHVector& _Size, const GJHString& _Image, int _Order)
{
	GJHRenderer* NewRender = CreateRender(_Size, _Order);
	NewRender->SetImage(_Image);

	return NewRender;
}

GJHRenderer* GJHGameEngineActor::CreateRender(const GJHString& _Image, ContentsEnum::RENDERORDER _Order)
{
	return CreateRender(_Image, (int)_Order);
}

GJHRenderer* GJHGameEngineActor::CreateRender(const GJHString& _Image, int _Order)
{
	GJHGameEngineImage* Image = GJHResourcesManager::Inst()->FindBmp(_Image);
	GJHRenderer* NewRender = CreateRender(Image->Size(), _Order);
	NewRender->SetImage(_Image);

	return NewRender;
}

GJHCollision* GJHGameEngineActor::CreateCollision(COLGEOTYPE _Type, const GJHVector& _PivotPos, const GJHVector& _Size, ContentsEnum::COLTYPE _Order)
{
	return CreateCollision(_Type, _PivotPos, _Size, (int)_Order);
}

GJHCollision* GJHGameEngineActor::CreateCollision(COLGEOTYPE _Type, const GJHVector& _PivotPos, const GJHVector& _Size, int _Order)
{
	GJHCollision* NewCollision = new GJHCollision();
	NewCollision->SetOrder(_Order);
	NewCollision->SetGeoType(_Type);
	NewCollision->m_Actor = this;
	NewCollision->m_ActorPivot = _PivotPos;
	NewCollision->m_Geo.Size = _Size;
	NewCollision->m_Hitable = true;
	m_Scene->PushCollision(NewCollision);
	m_Collision.push_back(NewCollision);

	return NewCollision;
}

void GJHGameEngineActor::Release()
{
	{
		std::list<GJHRenderer*>::iterator Start = m_Renderer.begin();
		std::list<GJHRenderer*>::iterator End = m_Renderer.end();

		for (; Start != End; )
		{
			if ((*Start)->IsDeath() == true)
			{
				SAFE_DELETE(*Start);
				Start = m_Renderer.erase(Start);
			}
			else
			{
				++Start;
			}
		}
	}

	{
		std::list<GJHCollision*>::iterator Start = m_Collision.begin();
		std::list<GJHCollision*>::iterator End = m_Collision.end();

		for (; Start != End; )
		{
			if ((*Start)->IsDeath() == true)
			{
				SAFE_DELETE(*Start);
				Start = m_Collision.erase(Start);
			}
			else
			{
				++Start;
			}
		}
	}
}