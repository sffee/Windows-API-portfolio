#pragma once
#include "ObjectBase.h"

class Monster : public ObjectBase
{
private:
	static int MonsterCount;

public:
	static int GetMonsterCount()
	{
		return MonsterCount;
	}

	static void MinusMonsterCount()
	{
		--MonsterCount;
	}

protected:
	void CreateBlood(const GJHVector& _ActorPivot = { 0, 0 }, int _RandomXStart = 0, int _RandomXEnd = 0, int _RandomYStart = 0, int _RandomYEnd = 0);

public:
	Monster();
};