#pragma once
#include <assert.h>
#include <crtdbg.h>

#define AssertMsg(Text) assert(false && Text);

class GJHGameEngineDebug
{
public:
	static void LeckCheck()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

private:
	GJHGameEngineDebug() {}
	~GJHGameEngineDebug() {}
};