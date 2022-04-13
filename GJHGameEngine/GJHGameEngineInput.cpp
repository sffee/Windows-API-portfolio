#include "GJHGameEngineInput.h"
#include <Windows.h>

GJHGameEngineInput::GJHGameEngineKey::GJHGameEngineKey() :
	Down(false), Press(false), Up(false), Free(true)
{

}

GJHGameEngineInput::GJHGameEngineKey::~GJHGameEngineKey()
{

}

void GJHGameEngineInput::GJHGameEngineKey::Update()
{
	bool Check = true;
	for (size_t i = 0; i < m_CheckKeys.size(); i++)
	{
		if (GetAsyncKeyState(m_CheckKeys[i]) == 0)
		{
			Check = false;
			break;
		}
	}

	if (Check == true)
	{
		if (Free == true)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else
	{
		if (Press == true)
		{
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}

std::map<GJHString, GJHGameEngineInput::GJHGameEngineKey> GJHGameEngineInput::m_AllKey;

GJHGameEngineInput::GJHGameEngineKey* GJHGameEngineInput::FindKey(const GJHString& _KeyName)
{
	if (m_AllKey.end() == m_AllKey.find(_KeyName))
	{
		return nullptr;
	}

	return &m_AllKey[_KeyName];
}

void GJHGameEngineInput::Update()
{
	std::map<GJHString, GJHGameEngineKey>::iterator Start = m_AllKey.begin();
	std::map<GJHString, GJHGameEngineKey>::iterator End = m_AllKey.end();

	for (; Start != End; ++Start)
	{
		Start->second.Update();
	}
}

bool GJHGameEngineInput::Down(const GJHString& _Name)
{
	GJHGameEngineKey* FindKeyPtr = FindKey(_Name);

	if (FindKeyPtr == nullptr)
	{
		AssertMsg("if (FindKeyPtr == nullptr)");
		return false;
	}

	return FindKeyPtr->Down;
}

bool GJHGameEngineInput::Up(const GJHString& _Name)
{
	GJHGameEngineKey* FindKeyPtr = FindKey(_Name);

	if (FindKeyPtr == nullptr)
	{
		AssertMsg("if (FindKeyPtr == nullptr)");
		return false;
	}

	return FindKeyPtr->Up;
}

bool GJHGameEngineInput::Press(const GJHString& _Name)
{
	GJHGameEngineKey* FindKeyPtr = FindKey(_Name);

	if (FindKeyPtr == nullptr)
	{
		AssertMsg("if (FindKeyPtr == nullptr)");
		return false;
	}

	return FindKeyPtr->Press;
}

bool GJHGameEngineInput::Free(const GJHString& _Name)
{
	GJHGameEngineKey* FindKeyPtr = FindKey(_Name);

	if (FindKeyPtr == nullptr)
	{
		AssertMsg("if (FindKeyPtr == nullptr)");
		return false;
	}

	return FindKeyPtr->Free;
}