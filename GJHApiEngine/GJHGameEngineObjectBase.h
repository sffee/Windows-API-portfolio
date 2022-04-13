#pragma once
#include <GJHNameBase.h>

class GJHGameEngineObjectBase : public GJHNameBase
{
private:
	bool m_IsDeath;
	bool m_IsOn;
	bool m_IsDebug;
	int m_Order;

public:
	bool IsDebug()
	{
		return m_IsDebug;
	}

	void SetDebugRender(bool _Set)
	{
		m_IsDebug = _Set;
	}

	void On()
	{
		m_IsOn = true;
	}

	void Off()
	{
		m_IsOn = false;
	}

	bool IsOn()
	{
		return m_IsOn == true && m_IsDeath == false;
	}

	bool IsDeath()
	{
		return m_IsDeath == true;
	}

	void Death()
	{
		m_IsDeath = true;
	}

	void SetOrder(int _Order)
	{
		m_Order = _Order;
	}

	int GetOrder()
	{
		return (int)m_Order;
	}

protected:
	GJHGameEngineObjectBase() : m_IsOn(true), m_IsDeath(false), m_Order((int)ContentsEnum::RENDERORDER::NORMAL), m_IsDebug(false)
	{

	}
};

