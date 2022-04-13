#include "InstanceObject.h"
#include <GJHRenderer.h>
#include <GJHGameEngineSound.h>
#include <GJHCollision.h>

void InstanceObject::SetData(InstanceObjectData _Data)
{
	m_Name = _Data.Name;
	m_Pos = _Data.Pos;
	m_Size = _Data.Size;
	m_Order = _Data.Order;
	m_ImageFileName = _Data.ImageFileName;
	m_ImageDir = _Data.ImageDir;
	m_ReverseImageDir = _Data.ReverseImageDir;
	m_ActorPivot = _Data.ActorPivot;
	m_CollisionPivot = _Data.CollisionPivot;
	m_CollisionSize = _Data.CollisionSize;
	m_CollisionType = _Data.CollisionType;
	m_CollisionEnableFrameIndex = _Data.CollisionEnableFrameIndex;
	m_CollisionDisableFrameIndex = _Data.CollisionDisableFrameIndex;
	m_StartFrame = _Data.StartFrame;
	m_EndFrame = _Data.EndFrame;
	m_FrameTime = _Data.FrameTime;
	m_IsLoop = _Data.IsLoop;
	m_StateName = _Data.StateName;
	m_AniData = _Data.AniData;
	m_SoundFrame = _Data.SoundFrame;
	m_SoundFileName = _Data.SoundFileName;
	m_SoundVolume = _Data.SoundVolume;
	m_IsGravity = _Data.IsGravity;
	m_MoveSpeed = _Data.MoveSpeed;
	m_CheckColMap = _Data.CheckColMap;

	if (m_Order == -1)
	{
		m_Order = (int)ContentsEnum::RENDERORDER::OBJECT;
	}

	if (_Data.NoDir == true)
	{
		m_AniRender = CreateRender(m_Size, m_ImageFileName + ".bmp", m_Order);
		m_AniRender->CreateAnimation("_Left", m_ImageFileName + ".bmp", m_StartFrame, m_EndFrame, m_FrameTime, m_IsLoop);
		m_AniRender->CreateAnimation("_Right", m_ImageFileName + ".bmp", m_StartFrame, m_EndFrame, m_FrameTime, m_IsLoop);
	}
	else
	{
		m_AniRender = CreateRender(m_Size, m_ImageFileName + "(Left).bmp", m_Order);
		m_AniRender->CreateAnimation("_Left", m_ImageFileName + "(Left).bmp", m_StartFrame, m_EndFrame, m_FrameTime, m_IsLoop);
		m_AniRender->CreateAnimation("_Right", m_ImageFileName + "(Right).bmp", m_StartFrame, m_EndFrame, m_FrameTime, m_IsLoop);
	}

	m_AniRender->SetActorPivot(m_ActorPivot);

	if (0 < m_CollisionSize.ix() &&
		0 < m_CollisionSize.iy())
	{
		m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, m_CollisionPivot, m_CollisionSize, m_CollisionType);
		m_AniCollision->SetBlockMove(false);
	}

	if (m_SoundFrame == 0)
	{
		GJHGameEngineSound::PlayOneShot(m_SoundFileName, m_SoundVolume);
		m_PlaySoundEnd = true;
	}
	else if (m_SoundFrame == -1)
	{
		m_PlaySoundEnd = true;
	}

	std::map<int, AniData>::iterator iter = m_AniData.begin();
	std::map<int, AniData>::iterator iterEnd = m_AniData.end();
	for (; iter != iterEnd; ++iter)
	{
		PushAnimationData(m_StateName, iter->first, (int)iter->second.Pivot.x, (int)iter->second.Pivot.y, iter->second.FrameTime);
	}

	m_Gravity = _Data.Gravity;
	m_GravityAddValue = _Data.GravityAddValue;
	ObjectBase::m_IsGravity = m_IsGravity;
	if (m_IsGravity == true)
	{
		m_Jump = true;
	}

	if (m_ReverseImageDir == true)
	{
		m_ImageDir = m_ImageDir == ENUM_DIRECTION::LEFT ? ENUM_DIRECTION::RIGHT : ENUM_DIRECTION::LEFT;
	}

	SetPos(m_Pos);
	SetDir("", m_ImageDir);
}

void InstanceObject::Start()
{
	m_PlaySoundEnd = false;
}

void InstanceObject::Update()
{
	if (m_IsGravity == true)
	{
		Gravity();
	}

	if (m_PlaySoundEnd == false)
	{
		if (m_AniRender->GetAnimationFrameIndex() == m_SoundFrame)
		{
			GJHGameEngineSound::PlayOneShot(m_SoundFileName, m_SoundVolume);
			m_PlaySoundEnd = true;
		}
	}

	if (m_CollisionEnableFrameIndex != -1 &&
		m_CollisionEnableFrameIndex == GetAnimationFrameIndex())
	{
		if (m_AniCollision != nullptr)
		{
			m_AniCollision->SetHitable(true);
		}
	}

	if (m_CollisionDisableFrameIndex != -1 &&
		m_CollisionDisableFrameIndex == GetAnimationFrameIndex())
	{
		if (m_AniCollision != nullptr)
		{
			m_AniCollision->SetHitable(false);
		}
	}

	Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());

	if (m_AniRender->AnimationEnd())
	{
		Death();
	}

	if (m_CheckColMap == true &&
		ColMap() == true)
	{
		Death();
	}

	__super::Update();
	__super::AnimationDataCheck(m_StateName);
}