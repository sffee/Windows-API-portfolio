#pragma once
#include <GJHGameEngineActor.h>
#include <GJHStateUpdater.h>
#include "define.h"

class GJHGameEngineImage;
class Player;
class ObjectBase : public GJHGameEngineActor
{	
protected:
	struct PivotData
	{
		float x;
		float y;

		PivotData() :
			x(0), y(0)
		{
		}

		PivotData(float x, float y) :
			x(x), y(y)
		{
		}

		PivotData& operator+=(const PivotData& _Other)
		{
			x += _Other.x;
			y += _Other.y;

			return *this;
		}
	};

	struct AniData
	{
		PivotData Pivot;
		float FrameTime;
	};

	struct InstanceObjectData
	{
		GJHString Name;
		GJHVector Pos;
		GJHVector Size;
		int Order;
		GJHString ImageFileName;
		ENUM_DIRECTION ImageDir;
		bool ReverseImageDir;
		GJHVector ActorPivot;
		GJHVector CollisionPivot;
		GJHVector CollisionSize;
		ContentsEnum::COLTYPE CollisionType;
		int CollisionEnableFrameIndex;
		int CollisionDisableFrameIndex;
		int StartFrame;
		int EndFrame;
		float FrameTime;
		bool IsLoop;
		GJHString StateName;
		std::map<int, AniData> AniData;
		int SoundFrame;
		GJHString SoundFileName;
		float SoundVolume;
		float Gravity;
		float GravityAddValue;
		bool IsGravity;
		float MoveSpeed;
		bool CheckColMap;
		bool NoDir;

		InstanceObjectData() :
			Size(GJHVector::ZERO),
			Order(-1),
			ImageFileName(""),
			ImageDir(),
			ReverseImageDir(false),
			ActorPivot(GJHVector::ZERO),
			CollisionPivot(GJHVector(0, 0)),
			CollisionSize(GJHVector(-1, -1)),
			CollisionType(ContentsEnum::COLTYPE::NONE),
			CollisionEnableFrameIndex(-1),
			CollisionDisableFrameIndex(-1),
			StartFrame(0),
			EndFrame(0),
			FrameTime(1.f),
			IsLoop(false),
			StateName(""),
			AniData(),
			SoundFrame(-1),
			SoundFileName(""),
			SoundVolume(1.f),
			Gravity(0.f),
			GravityAddValue(0.f),
			IsGravity(false),
			MoveSpeed(0.f),
			CheckColMap(false),
			NoDir(false)
		{
		}
	};
	typedef std::map<int, AniData> AniDataMap;

protected:
	static GJHGameEngineImage* m_MapColImage;
	static Player* m_Player;

public:
	static HDC m_HDC;

public:
	static void LoadingMapCollImage();

protected:
	static const float FALLINGMAXSPEED;

protected:
	std::map<GJHString, std::map<int, AniData>> AnimationData;
	std::map<GJHString, std::map<int, AniData>> SubAnimationData;

protected:
	void PushAnimationData(const GJHString& _Name, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime, bool _IsSubAniRender = false);
	void AnimationDataCheck(const GJHString& _StateName);

protected:
	GJHRenderer* m_AniRender;
	GJHRenderer* m_SubAniRender;
	GJHCollision* m_AniCollision;

protected:
	bool m_IsPlayer;

protected:
	float m_MoveSpeed;
	float m_Angle;
	float m_Gravity;
	float m_GravityAddValue;
	bool m_Falling;
	bool m_IsGravity;
	bool m_ColMap;
	bool m_Jump;
	bool m_IsDirCheck;

protected:
	GJHString m_DamageAnimationStr;
	GJHString m_SubDamageAnimationStr;
	bool m_DrawDamageAnimation;
	bool m_IsSubAniDamageAnimation;

protected:
	int m_MaxHP;
	int m_HP;

private:
	GJHTimeUpdater<ObjectBase> DamageAnimationUpdater;

private:
	int m_MoveCheckX;
	int m_MoveCheckY;

private:
	ENUM_ITEMTYPE m_DropItemType;

public:
	void SetDropItem(ENUM_ITEMTYPE _Type)
	{
		m_DropItemType = _Type;
	}

public:
	void SetMoveCheckX(int _X)
	{
		m_MoveCheckX = _X;
	}

	void SetMoveCheckY(int _Y)
	{
		m_MoveCheckY = _Y;
	}

	bool MoveCheck(bool _MinCheck = true);

protected:
	void Gravity();
	void ResetGravity();
	bool ColMap(int YGap = 2);

protected:
	void CreateAnimation(const GJHString& _StateName, const GJHString& _FileName, int _FrameStart, int _FrameEnd, float _FrameTime, bool _Loop = true, bool _Reverse = false, bool _IsSubAniRender = false);
	void ChangeAnimation(const GJHString& _Name, bool _Correction = false, bool _IsSubAniRender = false);

public:
	virtual void Update() override;
	virtual void DebugRender() override;
	virtual void DeathFunc() override;

public:
	void Move(const float _MoveSpeed);
	void Move(const GJHVector& _Value);
	void DirUpdate(const GJHString& _StateName, bool _Correction = false);
	void Jump(float _Gravity = -1.5f, float _GravityAddValue = INT_MAX);

public:
	void SetDefaultHP(int _HP);

public:
	bool CheckInsideCam();

public:
	void SetDir(const GJHString& _AniName, ENUM_DIRECTION _ImageDir, bool _Correction = false);
	void SetFrameTime(const int _FrameIndex, const float _Value);
	void SetAddActorPivot(const GJHVector& _Pivot);
	void SetActorPivot(const GJHVector& _Pivot);
	void SetAngle(float _Angle);
	void SetMoveSpeed(float _Speed);
	void SetGravity(float _Gravity);
	void SetGravityAddValue(float _Gravity);
	void DrawDamageAnimation(const GJHString& _CurAniStr, const GJHString& _CurSubAniStr = "", bool _IsSubAniRender = false);

private:
	int DamageAniMationCount;

private:
	void DamageAnimation();
	void DamageAnimationOn();
	void DamageAnimationOff();

protected:
	GJHVector PlayerDistance();
	
public:
	void SetAnimationFrameIndex(int _FrameIndex, bool _IsSubAniRender = false);
	int GetAnimationFrameIndex();
	bool AnimationEnd();

public:
	bool IsDeath();

private:
	class FadeInOut* m_FadeInOutActor;

protected:
	bool m_FadeInStart;
	bool m_FadeOutStart;

public:
	void FadeIn(float _Time);
	void FadeOut(float _Time);

public:
	bool IsFadeInOutOver();

private:
	void DropItem();

public:
	ObjectBase() :
		m_MaxHP(-1),
		m_HP(-1),
		m_IsGravity(true),
		m_MoveSpeed(0.f),
		m_Angle(0.f),
		m_Gravity(800.f),
		m_GravityAddValue(1600.f),
		m_MoveCheckX(1000),
		m_MoveCheckY(200),
		m_ColMap(false),
		m_AniRender(nullptr),
		m_SubAniRender(nullptr),
		m_AniCollision(nullptr),
		m_Jump(false),
		m_IsDirCheck(true),
		m_DrawDamageAnimation(false),
		m_DamageAnimationStr(""),
		m_SubDamageAnimationStr(""),
		m_IsSubAniDamageAnimation(false),
		DamageAniMationCount(0),
		m_Falling(false),
		m_FadeInStart(false),
		m_FadeOutStart(false),
		m_FadeInOutActor(nullptr),
		m_IsPlayer(false),
		m_DropItemType(ENUM_ITEMTYPE::NONE)
	{
	}
};