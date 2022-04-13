#pragma once
#include "GJHString.h"
#include "EngineDefine.h"

class GJHNameBase
{
private:
	GJHString m_Name;

public:
	inline void SetName(const GJHString& _Name)
	{
		m_Name = _Name;
	}

	inline GJHString GetName() const
	{
		return m_Name;
	}
};