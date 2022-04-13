#pragma once
#include "GJHGameEngineObjectBase.h"
#include <GJHGameEngineMath.h>
#include <list>
#include <EngineDefine.h>

class GJHCollision;
class GJHRenderer;
class GJHGameEngineScene;
class GJHGameEngineActor : public GJHGameEngineObjectBase
{
public:
	friend GJHGameEngineScene;

private:
	GJHGameEngineScene* m_Scene;

private:
	void SetScene(GJHGameEngineScene* _Scene)
	{
		m_Scene = _Scene;
	}

private:
	GJHVector m_Pos;
	GJHVector m_PrevPos;

protected:
	ENUM_DIRECTION m_PrevImageDir;
	ENUM_DIRECTION m_ImageDir;

public:
	inline void SetPos(const GJHVector& _Pos)
	{
		m_Pos = _Pos;
	}

	GJHVector GetPos()
	{
		return m_Pos;
	}

	inline void SetPrevPos(const GJHVector& _Pos)
	{
		m_PrevPos = _Pos;
	}

	GJHVector GetPrevPos()
	{
		return m_PrevPos;
	}

	ENUM_DIRECTION GetPrevImageDir()
	{
		return m_PrevImageDir;
	}

	ENUM_DIRECTION GetImageDir()
	{
		return m_ImageDir;
	}

	void Move(const GJHVector& _MoveValue)
	{
		m_PrevPos = m_Pos;
		m_Pos += _MoveValue;
	}

public:
	inline GJHGameEngineScene* GetScene()
	{
		return m_Scene;
	}

public:
	virtual void Start();
	virtual void Update();
	virtual void DebugRender();
	virtual void SceneStart() {};

public:
	std::list<GJHRenderer*> m_Renderer;

public:
	GJHRenderer* CreateRender(const GJHVector& _Size, ContentsEnum::RENDERORDER _Order = ContentsEnum::RENDERORDER::NORMAL);
	GJHRenderer* CreateRender(const GJHVector& _Size, int _Order = (int)ContentsEnum::RENDERORDER::NORMAL);
	GJHRenderer* CreateRender(const GJHVector& _Size, const GJHString& _Image, ContentsEnum::RENDERORDER _Order = ContentsEnum::RENDERORDER::NORMAL);
	GJHRenderer* CreateRender(const GJHVector& _Size, const GJHString& _Image, int _Order = (int)ContentsEnum::RENDERORDER::NORMAL);
	GJHRenderer* CreateRender(const GJHString& _Image, ContentsEnum::RENDERORDER _Order = ContentsEnum::RENDERORDER::NORMAL);
	GJHRenderer* CreateRender(const GJHString& _Image, int _Order = (int)ContentsEnum::RENDERORDER::NORMAL);

public:
	std::list<GJHCollision*> m_Collision;

public:
	GJHCollision* CreateCollision(COLGEOTYPE _Type, const GJHVector& _PivotPos, const GJHVector& _Size, ContentsEnum::COLTYPE _Order = ContentsEnum::COLTYPE::NORMAL);
	GJHCollision* CreateCollision(COLGEOTYPE _Type, const GJHVector& _PivotPos, const GJHVector& _Size, int _Order = (int)ContentsEnum::COLTYPE::NORMAL);

public:
	virtual void ColEnter(GJHCollision* _This, GJHCollision* _Other) {}
	virtual void ColStay(GJHCollision* _This, GJHCollision* _Other) {}
	virtual void ColExit(GJHCollision* _This, GJHCollision* _Other) {}

public:
	virtual void DeathFunc() {};

public:
	void Release();

public:
	GJHGameEngineActor();
	virtual ~GJHGameEngineActor() = 0;
};

