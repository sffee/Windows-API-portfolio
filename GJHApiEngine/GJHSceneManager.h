#pragma once
#include <GJHString.h>
#include <map>

class GJHGameEngineScene;
class GJHSceneManager
{
public:
	static GJHSceneManager Inst;

private:
	std::map<GJHString, GJHGameEngineScene*> SceneMap;
	GJHGameEngineScene* m_pCurScene;
	GJHGameEngineScene* m_pNextScene;

public:
	template<typename T>
	void CreateScene(const GJHString& _SceneName)
	{
		GJHGameEngineScene* NewScene = new T();
		NewScene->SetName(_SceneName);
		NewScene->Loading();

		SceneMap.insert(std::map<GJHString, GJHGameEngineScene*>::value_type(_SceneName, NewScene));
	}

	GJHGameEngineScene* FindScene(const GJHString& _SceneName);
	void ChangeScene(const GJHString& _SceneName);

public:
	void Progress();

private:
	GJHSceneManager();
	~GJHSceneManager();
};