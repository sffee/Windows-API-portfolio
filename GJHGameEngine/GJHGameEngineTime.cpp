#include "GJHGameEngineTime.h"
#include <Windows.h>

GJHGameEngineTimer GJHGameEngineTime::MainTimer;

GJHGameEngineTimer::GJHGameEngineTimer() :
	m_EventPause(false)
{
	Reset();
}

GJHGameEngineTimer::~GJHGameEngineTimer()
{

}

void GJHGameEngineTimer::Reset()
{
	QueryPerformanceFrequency(&m_CountTime);

	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_PrevTime);
}

bool GJHGameEngineTimer::CheckEventTime()
{
	if (m_EventCurTime < m_EventTime)
	{
		return false;
	}

	if (m_EventPause == true)
	{
		return false;
	}

	m_EventCurTime = 0;

	return true;
}

void GJHGameEngineTimer::ResetEventTime()
{
	Reset();

	m_EventCurTime = 0;
}

void GJHGameEngineTimer::CalDeltaTime()
{
	QueryPerformanceCounter(&m_CurTime);

	m_DoubleTime = ((double)m_CurTime.QuadPart - (double)m_PrevTime.QuadPart) / ((double)m_CountTime.QuadPart);
	m_PrevTime.QuadPart = m_CurTime.QuadPart;
	m_FloatTime = (float)m_DoubleTime;
}

void GJHGameEngineTimer::EventUpdate()
{
	if (m_EventPause == true)
	{
		return;
	}
	
	CalDeltaTime();

	m_EventCurTime += m_FloatTime;
}

void GJHGameEngineTime::Update()
{
	MainTimer.CalDeltaTime();
}

double GJHGameEngineTime::DDeltaTime(const double& _Speed)
{
	return MainTimer.GetDoubleTime() * _Speed;
}

float GJHGameEngineTime::FDeltaTime(const float& _Speed)
{
	return MainTimer.GetFloatTime() * _Speed;
}

void GJHGameEngineTime::Reset()
{
	MainTimer.Reset();
}