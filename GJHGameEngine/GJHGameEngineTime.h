#pragma once

#include <Windows.h>
#include <vector>

class GJHGameEngineTimer
{
private:
	LARGE_INTEGER m_CountTime;
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_PrevTime;
	double m_DoubleTime;
	float m_FloatTime;

private:
	float m_EventTime;
	float m_EventCurTime;
	bool m_EventPause;

public:
	void SetEventTime(float _Time, bool _StartCoolTime = false)
	{
		if (_StartCoolTime == false)
		{
			m_EventCurTime = _Time;
		}
		else
		{
			m_EventCurTime = 0;
		}

		m_EventTime = _Time;
	}

	bool CheckEventTime();

	void SetEventPause(bool _Pause)
	{
		m_EventPause = _Pause;
	}

	double GetDoubleTime()
	{
		return m_DoubleTime;
	}

	float GetFloatTime()
	{
		return m_FloatTime;
	}

public:
	void Reset();
	void ResetEventTime();
	void CalDeltaTime();
	void EventUpdate();

public:
	GJHGameEngineTimer();
	~GJHGameEngineTimer();
};

class GJHGameEngineTime
{
private:
	static GJHGameEngineTimer MainTimer;

public:
	static void Reset();
	static void Update();
	static double DDeltaTime(const double& _Speed = 1.0f);
	static float FDeltaTime(const float& _Speed = 1.0f);
};

template<typename Updater>
class GJHTimeUpdater
{
public:
	class GJHUpdateFunc
	{
	public:
		Updater* Object;
		void (Updater::* m_UpdateFunc)();
		float m_CurTime;
		float m_UpdateTime;

	public:
		bool Update(float _DeltaTime)
		{
			m_CurTime += _DeltaTime;

			if (Object != nullptr)
			{
				(Object->*m_UpdateFunc)();
			}

			if (m_UpdateTime < m_CurTime)
			{
				m_CurTime = 0.0f;
				return true;
			}

			return false;
		}

		void SetUpdateTime(float _Time)
		{
			m_UpdateTime = _Time;
		}

		GJHUpdateFunc() : m_CurTime(0.0f), m_UpdateTime(0.0f), Object(nullptr), m_UpdateFunc(nullptr)
		{

		}
	};

public:
	GJHGameEngineTimer Timer;
	bool m_bStart;
	bool m_bLoop;
	bool m_IsEnd;
	bool m_Pause;
	int CurUpdateIndex;
	std::vector<GJHUpdateFunc> m_AllUpdateFunc;

public:
	bool GetIsEnd()
	{
		return m_IsEnd;
	}

public:
	void Reset()
	{
		m_IsEnd = false;
		m_bStart = false;
		CurUpdateIndex = 0;
		m_Pause = false;
	}

	void PushDelay(float _Time)
	{
		GJHUpdateFunc NewUpdateFunc;

		NewUpdateFunc.m_UpdateTime = _Time;
		NewUpdateFunc.m_UpdateFunc = nullptr;
		NewUpdateFunc.Object = nullptr;
		m_AllUpdateFunc.push_back(NewUpdateFunc);
	}

	void PushOneShotFunc(void (Updater::* _Func)(), Updater* _Object)
	{
		GJHUpdateFunc NewUpdateFunc;

		NewUpdateFunc.m_UpdateTime = 0.0f;
		NewUpdateFunc.m_UpdateFunc = _Func;
		NewUpdateFunc.Object = _Object;

		m_AllUpdateFunc.push_back(NewUpdateFunc);
	}

	void PushFunc(float _Time, void (Updater::* _Func)(), Updater* _Object)
	{
		GJHUpdateFunc NewUpdateFunc;

		NewUpdateFunc.m_UpdateTime = _Time;
		NewUpdateFunc.m_UpdateFunc = _Func;
		NewUpdateFunc.Object = _Object;

		m_AllUpdateFunc.push_back(NewUpdateFunc);
	}

	void Update()
	{
		if (m_AllUpdateFunc.empty() == true)
		{
			return;
		}

		if (m_Pause == true)
		{
			return;
		}

		if (m_IsEnd == true)
		{
			return;
		}

		if (m_bStart == false)
		{
			Timer.Reset();
			m_bStart = true;
		}

		Timer.CalDeltaTime();

		if (m_AllUpdateFunc[CurUpdateIndex].Update(Timer.GetFloatTime()))
		{
			++CurUpdateIndex;

			if (m_AllUpdateFunc.size() <= CurUpdateIndex)
			{
				if (m_bLoop == true)
				{
					CurUpdateIndex = 0;
				}
				else
				{
					m_IsEnd = true;
				}
			}
		}
	}

	void SetCountTime(int _UpdateIndex, float _Time)
	{
		m_AllUpdateFunc[_UpdateIndex].SetUpdateTime(_Time);
	}

	void SetPause(bool _Pause)
	{
		m_Pause = _Pause;
	}

public:
	GJHTimeUpdater() : m_bLoop(true), m_bStart(false), CurUpdateIndex(0), m_IsEnd(false)
	{

	}

	~GJHTimeUpdater()
	{

	}
};