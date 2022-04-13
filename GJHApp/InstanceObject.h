#pragma once
#include "ObjectBase.h"
#include <map>
#include "define.h"

class InstanceObject : public ObjectBase
{
private:
	GJHString m_Name;
	GJHVector m_Pos;
	GJHVector m_Size;
	int m_Order;
	GJHString m_ImageFileName;
	ENUM_DIRECTION m_ImageDir;
	bool m_ReverseImageDir;
	GJHVector m_ActorPivot;

private:
	GJHVector m_CollisionPivot;
	GJHVector m_CollisionSize;
	ContentsEnum::COLTYPE m_CollisionType;
	int m_CollisionEnableFrameIndex;
	int m_CollisionDisableFrameIndex;

private:
	int m_StartFrame;
	int m_EndFrame;
	float m_FrameTime;
	bool m_IsLoop;

private:
	GJHString m_StateName;
	std::map<int, AniData> m_AniData;

private:
	int m_SoundFrame;
	GJHString m_SoundFileName;
	float m_SoundVolume;

private:
	bool m_IsGravity;
	bool m_CheckColMap;

private:
	bool m_PlaySoundEnd;

public:
	void SetData(InstanceObjectData _Data);

private:
	virtual void Start() override;
	virtual void Update() override;

public:
	InstanceObject() :
		m_Name(""),
		m_Pos(),
		m_Size(),
		m_ImageFileName(""),
		m_ImageDir(),
		m_ReverseImageDir(false),
		m_ActorPivot(),
		m_CollisionPivot(),
		m_CollisionSize(),
		m_CollisionType(),
		m_CollisionEnableFrameIndex(),
		m_CollisionDisableFrameIndex(),
		m_StartFrame(),
		m_EndFrame(),
		m_FrameTime(),
		m_IsLoop(),
		m_SoundFrame(),
		m_SoundFileName(),
		m_SoundVolume(),
		m_IsGravity(),
		m_PlaySoundEnd()
	{
	}
};

