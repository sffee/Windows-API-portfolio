#pragma once
#include "GJHGameEngineDebug.h"
#include "EngineDefine.h"
#include <math.h>

class GJHVector
{
public:
	static const GJHVector ZERO;
	static const GJHVector LEFT;
	static const GJHVector RIGHT;
	static const GJHVector UP;
	static const GJHVector DOWN;

public:
	float x;
	float y;
	float z;
	float w;

public:
	int ix() const
	{
		return (int)x;
	}

	int iy() const
	{
		return (int)y;
	}

	float hx() const
	{
		return (x * 0.5f);
	}

	float hy() const
	{
		return (y * 0.5f);
	}

	int hix() const
	{
		return (int)(x * 0.5f);
	}

	int hiy() const
	{
		return (int)(y * 0.5f);
	}

	GJHVector& operator+=(const GJHVector& _Other)
	{
		x += _Other.x;
		y += _Other.y;

		return *this;
	}

	GJHVector operator+(const GJHVector& _Value) const
	{
		return GJHVector(x + _Value.x, y + _Value.y);
	}

	GJHVector operator-=(const GJHVector& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;

		return *this;
	}

	GJHVector operator-(const GJHVector& _Value) const
	{
		return GJHVector(x - _Value.x, y - _Value.y);
	}

	GJHVector operator*(const float& _Value) const
	{
		return GJHVector(x * _Value, y * _Value);
	}

	GJHVector operator*(const GJHVector& _Value) const
	{
		return GJHVector(x * _Value.x, y * _Value.y);
	}

	GJHVector operator/(const int& _Value) const
	{
		return GJHVector(x / _Value, y / _Value);
	}

	bool operator==(const GJHVector& _Other) const
	{
		if (this->x == _Other.x &&
			this->y == _Other.y &&
			this->z == _Other.z &&
			this->w == _Other.w)
		{
			return true;
		}

		return false;
	}

	bool operator!=(const GJHVector& _Other) const
	{
		if (this->x != _Other.x)
		{
			return true;
		}

		if (this->y != _Other.y)
		{
			return true;
		}

		if (this->z != _Other.z)
		{
			return true;
		}

		if (this->w != _Other.w)
		{
			return true;
		}

		return false;
	}

	void RotDirDeg(float _DegAngle)
	{
		return RotDirRad(_DegAngle * D2R);
	}

	void RotDirRad(float _RadAngle)
	{
		GJHVector Vector = *this;

		Vector.x = (cosf(_RadAngle) * x) - (sinf(_RadAngle) * y);
		Vector.y = (sinf(_RadAngle) * x) + (cosf(_RadAngle) * y);

		x = Vector.x;
		y = Vector.y;
	}

	bool IsZero() const
	{
		return x == 0 || y == 0;
	}

	GJHVector XVector() const
	{
		return GJHVector(x, 0.0f, 0.0f, 1.0f);
	}

	GJHVector YVector() const
	{
		return GJHVector(0.0f, y, 0.0f, 1.0f);
	}

	GJHVector HalfVector2D() const
	{
		return GJHVector(x * 0.5f, y * 0.5f, 0.0f, 0.0f);
	}

public:
	GJHVector(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(0.0f), w(0.0f)
	{

	}

	GJHVector() :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
		
	}

	GJHVector(float _X, float _Y) :
		x(_X), y(_Y), z(0.0f), w(0.0f)
	{

	}
};

class GJHMath
{
public:
	static GJHVector RotDirDeg(float _DegAngle)
	{
		return RotDirRad(_DegAngle * D2R);
	}

	static GJHVector RotDirRad(float _RadAngle)
	{
		return GJHVector(cosf(_RadAngle), sinf(_RadAngle));
	}

	static float VecToVecAngle(const GJHVector& _Actor1, const GJHVector& _Actor2)
	{
		float x = _Actor2.x - _Actor1.x;
		float y = _Actor2.y - _Actor1.y;

		float rad = (float)atan2(y, x);

		return -rad * R2D;
	}

	static GJHVector RandomPlus(const GJHVector& _Vec, int _Value)
	{
		GJHVector Vec;

		while (true)
		{
			Vec.x = _Vec.x + rand() % _Value;
			Vec.y = _Vec.y + rand() % _Value;

			if (_Vec.x < MAPSTARTX)
			{
				Vec.x = MAPSTARTX;
			}
			if (MAPENDX < _Vec.x)
			{
				Vec.x = MAPENDX;
			}
			if (_Vec.y < MAPSTARTY)
			{
				Vec.y = MAPSTARTY;
			}

			if (MAPSTARTX <= Vec.x &&
				Vec.x <= MAPENDX &&
				MAPSTARTY <= Vec.y)
			{
				break;
			}
		}

		return Vec;
	}

	static GJHVector RandomPlus(const GJHVector& _Vec, int _ValueX, int _ValueY)
	{
		GJHVector Vec;

		Vec.x = _Vec.x + rand() % _ValueX;
		Vec.y = _Vec.y + rand() % _ValueY;

		return Vec;
	}

	static int Random(int _Value)
	{
		return rand() % (_Value) + 1;
	}

	static int Random(int _Start, int _End)
	{
		return rand() % (_End - _Start + 1) + _Start;
	}

	static GJHVector Random(const GJHVector& _Vec, int _Value)
	{
		GJHVector Vec;

		Vec.x = _Vec.x + rand() % (_Value * 2 + 1) - _Value;
		Vec.y = _Vec.y + rand() % (_Value * 2 + 1) - _Value;

		return Vec;
	}

	static int RandomRange(int _StartValue, int _EndValue)
	{
		int Value;
		Value = rand() % (_EndValue - _StartValue + 1) + _StartValue;

		return Value;
	}

	static GJHVector RandomRange(const GJHVector& _Vec, int _StartValue, int _EndValue)
	{
		GJHVector Vec;

		Vec.x = _Vec.x + rand() % (_EndValue - _StartValue + 1) + _StartValue;
		Vec.y = _Vec.y + rand() % (_EndValue - _StartValue + 1) + _StartValue;

		return Vec;
	}

	static GJHVector RandomRange(const GJHVector& _Vec, int _StartValueX, int _EndValueX, int _StartValueY, int _EndValueY)
	{
		GJHVector Vec;

		Vec.x = _Vec.x + rand() % (_EndValueX - _StartValueX + 1) + _StartValueX;
		Vec.y = _Vec.y + rand() % (_EndValueY - _StartValueY + 1) + _StartValueY;

		return Vec;
	}

	static GJHVector Random(const GJHVector& _Vec, int _ValueX, int _ValueY)
	{
		GJHVector Vec;

		Vec.x = _Vec.x + rand() % (_ValueX * 2 + 1) - _ValueX;
		Vec.y = _Vec.y + rand() % (_ValueY * 2 + 1) - _ValueY;

		return Vec;
	}
};

enum class GEOMETRYPIVOT2D
{
	CENTER,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTUP,
	RIGHTUP,
	LEFTDOWN,
	RIGHTDOWN,
};

class GJHGeometryInfo2D
{
public:
	GJHVector Pos;
	GJHVector Size;
	GEOMETRYPIVOT2D Pivot;

public:
	GJHVector Left() const
	{
		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			GJHVector Result = Pos - Size.XVector().HalfVector2D();
			return Result;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

	GJHVector Right() const
	{
		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			GJHVector Result = Pos + Size.XVector().HalfVector2D();
			return Result;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

	GJHVector Up() const
	{
		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			GJHVector Result = Pos - Size.YVector().HalfVector2D();
			return Result;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}
	
	GJHVector Down() const
	{
		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			GJHVector Result = Pos + Size.YVector().HalfVector2D();
			return Result;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

	GJHVector Center() const
	{
		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
			return Pos;
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

	GJHVector LeftUp() const
	{
		GJHVector ReturnVector = Pos;
		GJHVector HVector = Size.HalfVector2D();

		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			ReturnVector.x -= HVector.x;
			ReturnVector.y -= HVector.y;
			return ReturnVector;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

	GJHVector RightUp() const
	{
		GJHVector ReturnVector = Pos;
		GJHVector HVector = Size.HalfVector2D();

		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			ReturnVector.x += HVector.x;
			ReturnVector.y -= HVector.y;
			return ReturnVector;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

	GJHVector LeftDown() const
	{
		GJHVector ReturnVector = Pos;
		GJHVector HVector = Size.HalfVector2D();

		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			ReturnVector.x -= HVector.x;
			ReturnVector.y += HVector.y;
			return ReturnVector;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

	GJHVector RightDown() const
	{
		GJHVector ReturnVector = Pos;
		GJHVector HVector = Size.HalfVector2D();

		switch (Pivot)
		{
		case GEOMETRYPIVOT2D::CENTER:
		{
			ReturnVector.x += HVector.x;
			ReturnVector.y += HVector.y;
			return ReturnVector;
		}
		case GEOMETRYPIVOT2D::LEFT:
		case GEOMETRYPIVOT2D::RIGHT:
		case GEOMETRYPIVOT2D::UP:
		case GEOMETRYPIVOT2D::DOWN:
		case GEOMETRYPIVOT2D::LEFTUP:
		case GEOMETRYPIVOT2D::RIGHTUP:
		case GEOMETRYPIVOT2D::LEFTDOWN:
		case GEOMETRYPIVOT2D::RIGHTDOWN:
		default:
			AssertMsg("Geo Error Type");
			break;
		}

		AssertMsg("Geo Error Type");
		return GJHVector::ZERO;
	}

public:
	GJHGeometryInfo2D(GEOMETRYPIVOT2D _Pivot = GEOMETRYPIVOT2D::CENTER)
		: Pos(GJHVector::ZERO), Size(GJHVector::ZERO), Pivot(_Pivot)
	{
		
	}

	GJHGeometryInfo2D(const GJHVector& _Pos, const GJHVector& _Size, GEOMETRYPIVOT2D _Pivot = GEOMETRYPIVOT2D::CENTER)
		: Pos(_Pos), Size(_Size), Pivot(_Pivot)
	{

	}
};

enum class COLGEOTYPE
{
	CGT_RECT,
	CGT_CIRCLE,
	CGT_POINT,
	CGT_MAX,
};

class GJHColCheckFunc
{
public:
	static bool (*ColCheck2D[(int)COLGEOTYPE::CGT_MAX][(int)COLGEOTYPE::CGT_MAX])(GJHGeometryInfo2D, GJHGeometryInfo2D);

public:
	class ColCheckFuncStaticInit
	{
	public:
		ColCheckFuncStaticInit();
		~ColCheckFuncStaticInit();
	};

	static ColCheckFuncStaticInit Inst;

private:
	static bool RectToRect2D(GJHGeometryInfo2D _Left, GJHGeometryInfo2D _Right)
	{
		if (_Left.Up().y > _Right.Down().y)
		{
			return false;
		}

		if (_Left.Down().y < _Right.Up().y)
		{
			return false;
		}

		if (_Left.Left().x > _Right.Right().x)
		{
			return false;
		}

		if (_Left.Right().x < _Right.Left().x)
		{
			return false;
		}

		return true;
	}

	static bool RectToCircle2D(GJHGeometryInfo2D _Left, GJHGeometryInfo2D _Right)
	{
		return false;
	}

	static bool RectToPoint2D(GJHGeometryInfo2D _Left, GJHGeometryInfo2D _Right)
	{
		return false;
	}
};