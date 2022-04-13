#pragma once
#include <map>
#include "GJHActorSubObjectBase.h"

class GJHGameEngineImage;
class GJHAnimation
{
public:
	enum class REVERSE_STATE
	{
		BACK = -1,
		FRONT = 1
	};

public:
	GJHGameEngineImage* m_Image;
	bool m_bLoop;
	GJHString Name;
	std::map<int, float> FrameTime;
	float CurFrameTime;
	int Start;
	int End;
	int CurFrameIndex;
	bool AnimationEnd;
	bool isReverse;
	REVERSE_STATE ReverseState;
	bool isPlay;
	bool MapCheck;

public:
	void Reset()
	{
		CurFrameIndex = Start;
		CurFrameTime = 0.0f;
		AnimationEnd = false;
		ReverseState = GJHAnimation::REVERSE_STATE::FRONT;
	}
	
	void SetData(const GJHAnimation& _Other)
	{
		CurFrameIndex = _Other.CurFrameIndex;
		CurFrameTime = _Other.CurFrameTime;
		AnimationEnd = _Other.AnimationEnd;
		ReverseState = _Other.ReverseState;
	}

public:
	GJHAnimation() : m_Image(nullptr), m_bLoop(true), Name(""), FrameTime(), CurFrameTime(0.f), Start(0), End(0), CurFrameIndex(0), AnimationEnd(false), isReverse(false), ReverseState(REVERSE_STATE::FRONT), isPlay(true), MapCheck(true)
	{
	}
};

class GJHGameEngineImage;
class GJHGameEngineActor;
class GJHGameEngineScene;
class GJHRenderer : public GJHActorSubObjectBase
{
public:
	friend GJHGameEngineActor;
	friend GJHGameEngineScene;

private:
	GJHGeometryInfo2D m_ImageRect;
	GJHGameEngineImage* m_Image;
	unsigned int m_TransColor;
	int m_Alpha;

private:
	bool isDraw;

public:
	void SetAlpha(int _Alpha)
	{
		m_Alpha = _Alpha;
	}

	int GetAlpha()
	{
		return m_Alpha;
	}

	void SetImageSize(GJHVector _ImageSize)
	{
		m_ImageRect.Size = _ImageSize;
	}

	void SetImagePivot(GJHVector _ImagePivot)
	{
		m_ImageRect.Pos = _ImagePivot;
	}

	void SetTransColor(unsigned int _TransColor)
	{
		m_TransColor = _TransColor;
	}

	void SetAnimationFrameIndex(int _Index);
	int GetAnimationFrameIndex();
	void SetFrameTime(float _Value);
	void SetFrameTime(int _Index, float _Value);
	float GetFrameTime(int _FrameIndex);

	void SetAnimationPlay(bool _Play)
	{
		m_pCurAnimation->isPlay = _Play;
	}

	void AnimationReset()
	{
		m_pCurAnimation->Reset();
	}

	int GetAnimationStartFrame()
	{
		return m_pCurAnimation->Start;
	}

	int GetAnimationEndFrame()
	{
		return m_pCurAnimation->End;
	}

	GJHString GetAnimationName()
	{
		return m_pCurAnimation->Name;
	}

	bool IsLoop()
	{
		return m_pCurAnimation->m_bLoop;
	}

	void SetMapCheck(bool _Check)
	{
		m_pCurAnimation->MapCheck = _Check;
	}

	void CalcRender();

	void SetImage(const GJHString& _ImageName);
	void SetImage(const GJHGameEngineImage* _ImageName);
	void SetImageIndex(unsigned int _Index);

public:
	void Render();

private:
	std::map<GJHString, GJHAnimation> m_AnimationMap;
	GJHAnimation* m_pCurAnimation;

public:
	void CreateAnimation(const GJHString& _AniName, const GJHString& _ImageName, int _Start, int _End, float _FrameTime, bool _Loop = true, bool _Reverse = false);
	void ChangeAnimation(const GJHString& _AniName, bool _Correction = false, const GJHVector& _Size = GJHVector::ZERO);
	bool AnimationEnd();
	void SetDraw(bool _Draw);

private:
	GJHRenderer();
	~GJHRenderer();
};