#pragma once
#include <GJHNameBase.h>
#include <list>
#include <map>
#include <GJHGameEngineMath.h>

class GJHRenderer;
class GJHCollision;
class GJHGameEngineActor;
class ObjectBase;
class GJHGameEngineScene : public GJHNameBase
{
private:
	std::list<GJHGameEngineActor*> m_Actors;
	
public:
	GJHGameEngineScene();
	virtual ~GJHGameEngineScene() = 0;

public:
	template<typename T>
	T* CreateActor(const GJHString& _Name = "")
	{
		T* NewPtr = new T();
		GJHGameEngineActor* NewGameActor = NewPtr;
		NewGameActor->SetName(_Name);
		NewGameActor->SetScene(this);
		NewGameActor->Start();
		m_Actors.push_back(NewGameActor);

		return NewPtr;
	}

private:
	bool m_IsDebugRender;

public:
	void SetDebugRender(bool _Set)
	{
		m_IsDebugRender = _Set;
	}

	void ToggleDebugRender()
	{
		m_IsDebugRender = !m_IsDebugRender;
	}

public:
	std::map<int, std::list<GJHRenderer*>> m_AllRenderer;

public:
	void PushRender(GJHRenderer* _Render);

public:
	class ColLink
	{
	public:
		int Left;
		int Right;
	};

	std::list<ColLink> m_LinkData;

public:
	void CollisionCheckLink(int _Left, int _Right)
	{
		m_LinkData.push_back({ _Left, _Right });
	}

public:
	std::map<int, std::list<GJHCollision*>> m_AllCollision;

public:
	void PushCollision(GJHCollision* _Render);

private:
	void ColThisGroupCheck(std::list<GJHCollision*>& _Left);
	void ColOtherGroupCheck(std::list<GJHCollision*>& _Left, std::list<GJHCollision*>& _Right);

public:
	virtual void SceneChangeStart();
	virtual void SceneChangeEnd() {}

	virtual void SceneUpdate() {}
	virtual void Loading();
	virtual void DebugRender() {}

public:
	void Progress();
	void Release();
};

