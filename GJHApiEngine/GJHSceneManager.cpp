#include "GJHSceneManager.h"
#include "GJHGameEngineScene.h"
#include <GJHGameEngineDebug.h>
#include <GJHGameEngineTime.h>

GJHSceneManager GJHSceneManager::Inst;

GJHSceneManager::GJHSceneManager() : m_pCurScene(nullptr), m_pNextScene(nullptr)
{

}

GJHSceneManager::~GJHSceneManager()
{
	std::map<GJHString, GJHGameEngineScene*>::iterator Start = SceneMap.begin();
	std::map<GJHString, GJHGameEngineScene*>::iterator End = SceneMap.end();

	for (; Start != End; ++Start)
	{
		if (Start->second != nullptr)
		{
			delete Start->second;
			Start->second = nullptr;
		}
		else
		{
			assert(false);
		}
	}
}

GJHGameEngineScene* GJHSceneManager::FindScene(const GJHString& _SceneName)
{
	std::map<GJHString, GJHGameEngineScene*>::iterator FindIter = SceneMap.find(_SceneName);

	if (FindIter != SceneMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

void GJHSceneManager::ChangeScene(const GJHString& _SceneName)
{
	m_pNextScene = FindScene(_SceneName);

	if (m_pNextScene == nullptr)
	{
		AssertMsg(false);
	}
}

void GJHSceneManager::Progress()
{
	if (m_pNextScene != nullptr)
	{
		if (m_pCurScene != nullptr)
		{
			m_pCurScene->SceneChangeEnd();
		}

		m_pCurScene = m_pNextScene;
		m_pNextScene = nullptr;

		if (m_pCurScene != nullptr)
		{
			m_pCurScene->SceneChangeStart();
		}

		GJHGameEngineTime::Reset();
	}

	if (m_pCurScene == nullptr)
	{
		assert(false);
	}

	m_pCurScene->Progress();
}