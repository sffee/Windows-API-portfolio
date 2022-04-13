#pragma once

#include "GJHGameEngineTime.h"

#define SAFE_DELETE(p)	if (p) { delete p; p = nullptr; }

#define CREATEKEY GJHGameEngineInput::CreateKey

#define KEYDOWN GJHGameEngineInput::Down
#define KEYUP GJHGameEngineInput::Up
#define KEYPRESS GJHGameEngineInput::Press
#define KEYFREE GJHGameEngineInput::Free

#define PI 3.141592653589793238462643383279502884197f
#define D2R PI / 180.0f
#define R2D 180.0f / PI

#define GRAVITY 25.f

#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 960

#define MAPSTARTX 0
#define MAPENDX 23420
#define MAPSTARTY 0

enum class ENUM_DIRECTION
{
	NONE = 0,
	LEFT = -1,
	RIGHT = 1
};

class ContentsEnum
{
public:
	enum class COLTYPE
	{
		NONE,
		NORMAL,
		PLAYER,
		PLAYERBULLET,
		PLAYERGRANADE,
		MONSTER,
		MONSTERBULLET,
		CAMCONTROL,
		BLOCKMOVE,
		ITEM,
		NPC
	};

	enum class RENDERORDER
	{
		BACKGROUND = -100,
		NORMAL = 0,
		MAP = 100,
		MAPOBJECT = 200,
		PLAYER = 300,
		MONSTER = 400,
		OBJECT = 500,
		FOREGROUND = 1000,
		UI = 10000
	};
};