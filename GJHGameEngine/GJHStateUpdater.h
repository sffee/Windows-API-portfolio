#pragma once
#include "GJHString.h"
#include <map>
#include "GJHGameEngineDebug.h"

template<typename Updater>
class GJHStateUpdater
{
public:
	class GJHUpdateFunc
	{
	public:
		Updater* Object;
		void (Updater::* StartFunc)();
		void (Updater::* ProgressFunc)();
		void (Updater::* EndFunc)();

	public:
		void Start()
		{
			(Object->*StartFunc)();
		}

		void Update()
		{
			(Object->*ProgressFunc)();
		}

		void End()
		{
			if (EndFunc != nullptr)
			{
				(Object->*EndFunc)();
			}
		}
	};

public:
	std::map<GJHString, GJHUpdateFunc> m_AllUpdateFunc;
	GJHUpdateFunc* m_pCurUpdate;
	GJHString CurState;
	GJHString PrevState;
	bool Pause;

public:
	void CreateState(const GJHString& _Name, void (Updater::* _Start)(), void (Updater::* _Progress)(), void (Updater::* _End)(), Updater* _Object)
	{
		GJHUpdateFunc NewUpdateFunc;
		NewUpdateFunc.StartFunc = _Start;
		NewUpdateFunc.ProgressFunc = _Progress;
		NewUpdateFunc.EndFunc = _End;
		NewUpdateFunc.Object = _Object;

		m_AllUpdateFunc.insert(std::map<GJHString, GJHUpdateFunc>::value_type(_Name, NewUpdateFunc));
	}

	void ChangeState(const GJHString& _Name)
	{
		if (m_AllUpdateFunc.find(_Name) == m_AllUpdateFunc.end())
		{
			AssertMsg("if (m_AllUpdateFunc.find(_Name) == m_AllUpdateFunc.end())");
		}

		if (m_pCurUpdate != nullptr)
		{
			m_pCurUpdate->End();
		}

		PrevState = CurState;
		CurState = _Name;

		Pause = false;

		m_pCurUpdate = &m_AllUpdateFunc[_Name];
		m_pCurUpdate->Start();
	}

	void Update()
	{
		if (Pause == true)
		{
			return;
		}

		if (m_pCurUpdate == nullptr)
		{
			return;
		}

		m_pCurUpdate->Update();
	}

	void SetPause(bool _Pause)
	{
		Pause = _Pause;
	}

public:
	GJHStateUpdater() : m_pCurUpdate(nullptr)
	{

	}

	~GJHStateUpdater()
	{

	}
};