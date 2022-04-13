#pragma once
#include "GJHString.h"
#include <map>
#include <vector>
#include "GJHGameEngineDebug.h"

class GJHGameEngineInput
{
private:
	class GJHGameEngineKey
	{
	public:
		bool Down;
		bool Press;
		bool Up;
		bool Free;

	public:
		std::vector<int> m_CheckKeys;

	public:
		void Update();

	public:
		GJHGameEngineKey();
		~GJHGameEngineKey();
	};

private:
	static std::map<GJHString, GJHGameEngineKey> m_AllKey;

public:
	static GJHGameEngineKey* FindKey(const GJHString& _KeyName);

public:
	template<typename KEY>
	static void PushKey(std::vector<int>& _Vector, KEY _Value)
	{
		_Vector.push_back(_Value);
	}

	template<typename KEY, typename ... REST>
	static void PushKey(std::vector<int>& _Vector, KEY _Value, REST ... _Arg)
	{
		_Vector.push_back(_Value);
		PushKey(_Vector, _Arg...);
	}

	template<typename ... REST>
	static void CreateKey(const GJHString& _KeyName, REST ... _Arg)
	{
		if (FindKey(_KeyName) != nullptr)
		{
			AssertMsg("if (FindKey(_KeyName) != nullptr)");
		}

		GJHGameEngineKey NewKey;
		NewKey.m_CheckKeys.reserve(sizeof...(_Arg));

		PushKey(NewKey.m_CheckKeys, _Arg...);

		m_AllKey.insert(std::map<GJHString, GJHGameEngineKey>::value_type(_KeyName, NewKey));
	}

public:
	static void Update();

	static bool Down(const GJHString& _Name);
	static bool Up(const GJHString& _Name);
	static bool Press(const GJHString& _Name);
	static bool Free(const GJHString& _Name);

private:
	GJHGameEngineInput() {}
	~GJHGameEngineInput() {}
};

