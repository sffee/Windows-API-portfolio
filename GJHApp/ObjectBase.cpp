#include <GJHRenderer.h>
#include <GJHResourcesManager.h>
#include <GJHGameEngineScene.h>
#include <GJHCollision.h>
#include "Player.h"
#include "ObjectBase.h"
#include "GJHCameraManager.h"
#include "FadeInOut.h"
#include "GranadeBox.h"
#include "HeavyMachineGunBox.h"

GJHGameEngineImage* ObjectBase::m_MapColImage;
Player* ObjectBase::m_Player = nullptr;
HDC ObjectBase::m_HDC;
const float ObjectBase::FALLINGMAXSPEED = 1000.f;

void ObjectBase::LoadingMapCollImage()
{
	m_MapColImage = GJHResourcesManager::Inst()->FindBmp("MapPixel.bmp");
}

void ObjectBase::Update()
{
	if (m_IsPlayer == false)
	{
		if (GetPos().x <= MAPSTARTX)
		{
			SetPos({ MAPSTARTX, GetPos().y });
			Death();
		}
		else if (MAPENDX <= GetPos().x)
		{
			SetPos({ MAPENDX, GetPos().y });
			Death();
		}

		if (GetPos().y <= MAPSTARTY)
		{
			SetPos({ GetPos().x, MAPSTARTY });
			Death();
		}
	}

	Gravity();

	if (m_DrawDamageAnimation == true)
	{
		DamageAnimationUpdater.Update();
	}
}

void ObjectBase::DebugRender()
{
	if (m_AniRender == nullptr)
	{
		return;
	}

	GJHVector Pos = GetPos();
	GJHVector ShowPos = Pos - GJHCameraManager::GetCamPos();

	{
		char Text[100];
		sprintf_s(Text, "Pos x : %d\nPos y : %d", Pos.ix(), Pos.iy());
		TextOutA(m_HDC, (int)ShowPos.x, (int)ShowPos.y, Text, (int)strlen(Text));
	}

	{
		if (0 < m_HP)
		{
			char Text[100];
			sprintf_s(Text, "HP : %d", m_HP);
			TextOutA(m_HDC, (int)ShowPos.x, (int)ShowPos.y + 20, Text, (int)strlen(Text));
		}
	}
}

void ObjectBase::DeathFunc()
{
	DropItem();
}

void ObjectBase::PushAnimationData(const GJHString& _Name, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime, bool _IsSubAniRender)
{
	AniData Data;
	Data.Pivot.x = (float)_PivotX;
	Data.Pivot.y = (float)_PivotY;
	Data.FrameTime = _FrameTime;

	if (_IsSubAniRender == true)
	{
		std::map<GJHString, std::map<int, AniData>>::iterator Find = SubAnimationData.find(_Name);

		if (Find == SubAnimationData.end())
		{
			SubAnimationData.insert(std::map<GJHString, std::map<int, AniData>>::value_type(_Name, std::map<int, AniData>()));

			Find = SubAnimationData.find(_Name);
		}

		Find->second.insert(std::map<int, AniData>::value_type(_FrameIndex, Data));
	}
	else
	{
		std::map<GJHString, std::map<int, AniData>>::iterator Find = AnimationData.find(_Name);

		if (Find == AnimationData.end())
		{
			AnimationData.insert(std::map<GJHString, std::map<int, AniData>>::value_type(_Name, std::map<int, AniData>()));

			Find = AnimationData.find(_Name);
		}

		Find->second.insert(std::map<int, AniData>::value_type(_FrameIndex, Data));
	}
}

void ObjectBase::AnimationDataCheck(const GJHString& _StateName)
{
	{
		std::map<GJHString, std::map<int, AniData>>::iterator Find = AnimationData.find(_StateName);
		if (Find == AnimationData.end())
		{
			return;
		}

		int CurFrameIndex = m_AniRender->GetAnimationFrameIndex();
		std::map<int, AniData>::iterator Find2 = Find->second.find(CurFrameIndex);
		if (Find2 == Find->second.end())
		{
			return;
		}

		m_AniRender->SetAddActorPivot({ Find2->second.Pivot.x, Find2->second.Pivot.y });
		m_AniRender->SetFrameTime(CurFrameIndex, Find2->second.FrameTime);
	}

	{
		std::map<GJHString, std::map<int, AniData>>::iterator Find = SubAnimationData.find(_StateName);
		if (Find == SubAnimationData.end())
		{
			return;
		}

		int CurFrameIndex = m_SubAniRender->GetAnimationFrameIndex();
		std::map<int, AniData>::iterator Find2 = Find->second.find(CurFrameIndex);
		if (Find2 == Find->second.end())
		{
			return;
		}

		m_SubAniRender->SetAddActorPivot({ Find2->second.Pivot.x, Find2->second.Pivot.y });
		m_SubAniRender->SetFrameTime(CurFrameIndex, Find2->second.FrameTime);
	}
}

void ObjectBase::Gravity()
{
	if (m_IsGravity == false)
		return;

	if (m_MapColImage == nullptr)
		AssertMsg("if (m_MapColImage == nullptr)");

	if (m_MapColImage->GetImagePixel(GetPos().ix(), GetPos().iy() + 1) == RGB(255, 0, 255)
		|| m_Jump == true)
	{
		m_Gravity += m_GravityAddValue * GJHGameEngineTime::FDeltaTime();

		float m_GravityForce = m_Gravity * GJHGameEngineTime::FDeltaTime();

		GJHVector MoveSpeed = GJHVector::DOWN * m_GravityForce;
		Move(MoveSpeed);
	}

	while (m_MapColImage->GetImagePixel(GetPos().ix(), GetPos().iy()) != RGB(255, 0, 255))
	{
		SetPos(GetPos() + GJHVector(0.f, -1.f));

		m_Gravity = 3.0f;
		m_Jump = false;
		m_Falling = false;
	}
}

void ObjectBase::ResetGravity()
{
	m_ColMap = false;
}

bool ObjectBase::ColMap(int YGap)
{
	if (m_Jump == true)
	{
		return false;
	}

	GJHVector CheckPos = GetPos() + m_AniRender->GetActorPivot() + m_AniRender->GetAddActorPivot();
	int YPos = 1;
	bool CheckCollision = false;

	while (true)
	{
		if (m_MapColImage->GetImagePixel(CheckPos.ix(), CheckPos.iy() + YPos) == RGB(255, 0, 255))
		{
			YPos += 1;
		}
		else
		{
			return true;
		}

		if (YGap <= YPos)
		{
			break;
		}
	}

	return false;
}

void ObjectBase::CreateAnimation(const GJHString& _StateName, const GJHString& _FileName, int _FrameStart, int _FrameEnd, float _FrameTime, bool _Loop, bool _Reverse, bool _IsSubAniRender)
{
	if (_IsSubAniRender == true && m_SubAniRender != nullptr)
	{
		m_SubAniRender->CreateAnimation(_StateName + "_Left", _FileName + "(Left).bmp", _FrameStart, _FrameEnd, _FrameTime, _Loop, _Reverse);
		m_SubAniRender->CreateAnimation(_StateName + "_Right", _FileName + "(Right).bmp", _FrameStart, _FrameEnd, _FrameTime, _Loop, _Reverse);
	}
	else
	{
		m_AniRender->CreateAnimation(_StateName + "_Left", _FileName + "(Left).bmp", _FrameStart, _FrameEnd, _FrameTime, _Loop, _Reverse);
		m_AniRender->CreateAnimation(_StateName + "_Right", _FileName + "(Right).bmp", _FrameStart, _FrameEnd, _FrameTime, _Loop, _Reverse);
	}
}

void ObjectBase::ChangeAnimation(const GJHString& _Name, bool _Correction, bool _IsSubAniRender)
{
	GJHString DirStr;
	if (m_ImageDir == ENUM_DIRECTION::LEFT)
	{
		DirStr = "_Left";
	}
	else
	{
		DirStr = "_Right";
	}

	if (_IsSubAniRender == true && m_SubAniRender != nullptr)
	{
		m_SubAniRender->ChangeAnimation(_Name + DirStr, _Correction);
	}
	else
	{
		m_AniRender->ChangeAnimation(_Name + DirStr, _Correction);
	}
}

void ObjectBase::Move(const float _MoveSpeed)
{
	Move(GJHVector(_MoveSpeed, 0) * GJHVector((float)m_ImageDir, 0));
}

void ObjectBase::Move(const GJHVector& _Value)
{
	if (m_Angle != 0.f)
	{
		__super::Move((_Value + GJHVector(0, abs(_Value.x))) * GJHMath::RotDirDeg(m_Angle));
	}
	else
	{
		__super::Move(_Value);
	}
}

void ObjectBase::SetDir(const GJHString& _AniName, ENUM_DIRECTION _ImageDir, bool _Correction)
{
	if (m_PrevImageDir == _ImageDir)
	{
		return;
	}

	m_PrevImageDir = m_ImageDir;
	m_ImageDir = _ImageDir;

	if (_ImageDir == ENUM_DIRECTION::LEFT)
	{
		m_AniRender->ChangeAnimation(_AniName + "_Left");

		if (m_SubAniRender != nullptr)
		{
			m_SubAniRender->ChangeAnimation(m_SubAniRender->GetAnimationName() + "_Left");
		}
	}
	else
	{
		m_AniRender->ChangeAnimation(_AniName + "_Right");
		
		if (m_SubAniRender != nullptr)
		{
			m_SubAniRender->ChangeAnimation(m_SubAniRender->GetAnimationName() + "_Right");
		}
	}
}

void ObjectBase::SetFrameTime(int _FrameIndex, float _Value)
{
	m_AniRender->SetFrameTime(_FrameIndex, _Value);
}

void ObjectBase::SetActorPivot(const GJHVector& _Pivot)
{
	m_AniRender->SetActorPivot(_Pivot);
}

void ObjectBase::SetAddActorPivot(const GJHVector& _Pivot)
{
	m_AniRender->SetAddActorPivot(_Pivot);
}

void ObjectBase::SetAngle(float _Angle)
{
	m_Angle = _Angle;
}

bool ObjectBase::MoveCheck(bool _MinCheck)
{
	GJHVector Distance = PlayerDistance();
	if (abs(Distance.x) < 50 && _MinCheck == true)
	{
		return false;
	}

	if (m_MoveCheckY < abs(Distance.y))
	{
		return false;
	}
	
	if (m_MoveCheckX <= abs(Distance.x))
	{
		return false;
	}

	return true;
}

void ObjectBase::DirUpdate(const GJHString& _StateName, bool _Correction)
{
	if (MoveCheck() == false || m_IsDirCheck == false)
	{
		return;
	}

	float Distance = m_Player->GetPos().x - GetPos().x;

	if (Distance < 0)
	{
		SetDir(_StateName, ENUM_DIRECTION::LEFT, _Correction);
	}
	else
	{
		SetDir(_StateName, ENUM_DIRECTION::RIGHT, _Correction);
	}
}

GJHVector ObjectBase::PlayerDistance()
{
	return GJHVector(m_Player->GetPos().x - GetPos().x, m_Player->GetPos().y - GetPos().y);
}

void ObjectBase::SetAnimationFrameIndex(int _FrameIndex, bool _IsSubAniRender)
{
	if (_IsSubAniRender == true)
	{
		m_SubAniRender->SetAnimationFrameIndex(_FrameIndex);
		return;
	}

	m_AniRender->SetAnimationFrameIndex(_FrameIndex);
}

int ObjectBase::GetAnimationFrameIndex()
{
	return m_AniRender->GetAnimationFrameIndex();
}

bool ObjectBase::AnimationEnd()
{
	return m_AniRender->AnimationEnd();
}

bool ObjectBase::IsDeath()
{
	if (m_HP <= 0)
	{
		return true;
	}

	return false;
}

void ObjectBase::Jump(float _Gravity, float _GravityAddValue)
{
	m_Jump = true;

	m_Gravity = _Gravity;

	if (_GravityAddValue != INT_MAX)
	{
		m_GravityAddValue = _GravityAddValue;
	}
}

void ObjectBase::SetDefaultHP(int _HP)
{
	m_MaxHP = _HP;
	m_HP = _HP;
}

bool ObjectBase::CheckInsideCam()
{
	GJHVector Pos = GetPos();
	GJHVector CamPos = GJHCameraManager::GetCamPos();
	GJHVector CamMaxPos = GJHCameraManager::GetCamMaxPos();

	if (Pos.x < CamPos.x ||
		CamMaxPos.x < Pos.x ||
		Pos.y < CamPos.y ||
		CamMaxPos.y < Pos.y)
	{
		return false;
	}

	return true;
}

void ObjectBase::SetMoveSpeed(float _Speed)
{
	m_MoveSpeed = _Speed;
}

void ObjectBase::SetGravity(float _Gravity)
{
	m_Gravity = _Gravity;
}

void ObjectBase::SetGravityAddValue(float _Gravity)
{
	m_GravityAddValue = _Gravity;
}

void ObjectBase::DrawDamageAnimation(const GJHString& _CurAniStr, const GJHString& _CurSubAniStr, bool _IsSubAniRender)
{
	if (m_DrawDamageAnimation == true)
	{
		return;
	}
	
	m_DamageAnimationStr = _CurAniStr;
	m_SubDamageAnimationStr = _CurSubAniStr;
	m_DrawDamageAnimation = true;
	m_IsSubAniDamageAnimation = _IsSubAniRender;

	DamageAniMationCount = 0;

	DamageAnimation();
}

void ObjectBase::DamageAnimation()
{
	DamageAnimationUpdater.PushOneShotFunc(&ObjectBase::DamageAnimationOn, this);
	DamageAnimationUpdater.PushDelay(0.01f);
	DamageAnimationUpdater.PushOneShotFunc(&ObjectBase::DamageAnimationOff, this);
	DamageAnimationUpdater.PushDelay(0.01f);
	DamageAnimationUpdater.PushOneShotFunc(&ObjectBase::DamageAnimationOn, this);
	DamageAnimationUpdater.PushDelay(0.01f);
	DamageAnimationUpdater.PushOneShotFunc(&ObjectBase::DamageAnimationOff, this);
}

void ObjectBase::DamageAnimationOn()
{
	++DamageAniMationCount;

	GJHString AniName = m_AniRender->GetAnimationName().Cut(0, m_AniRender->GetAnimationName().LastFind('_'));;
	if (AniName == m_DamageAnimationStr)
	{
		ChangeAnimation(m_DamageAnimationStr + "_Damage", true);
	}
	else
	{
		m_DamageAnimationStr = m_AniRender->GetAnimationName();
		ChangeAnimation(m_DamageAnimationStr + "_Damage");
	}
	
	if (m_IsSubAniDamageAnimation == true && m_SubAniRender != nullptr)
	{
		AniName = m_SubAniRender->GetAnimationName().Cut(0, m_SubAniRender->GetAnimationName().LastFind('_'));;
		if (AniName == m_SubDamageAnimationStr)
		{
			ChangeAnimation(AniName + "_Damage", true, true);
		}
		else
		{
			m_SubDamageAnimationStr = m_SubAniRender->GetAnimationName();
			ChangeAnimation(m_SubDamageAnimationStr + "_Damage", true, true);
		}
	}
}

void ObjectBase::DamageAnimationOff()
{
	GJHString AniName = m_AniRender->GetAnimationName().Cut(0, m_AniRender->GetAnimationName().LastFind('_'));;
	if (AniName == m_DamageAnimationStr)
	{
		ChangeAnimation(m_DamageAnimationStr, true);
	}
	else
	{
		ChangeAnimation(m_AniRender->GetAnimationName());
	}

	if (m_IsSubAniDamageAnimation == true && m_SubAniRender != nullptr)
	{
		AniName = m_SubAniRender->GetAnimationName().Cut(0, m_SubAniRender->GetAnimationName().LastFind('_'));;
		if (AniName == m_SubDamageAnimationStr)
		{
			ChangeAnimation(m_SubDamageAnimationStr, true, true);
		}
		else
		{
			ChangeAnimation(m_SubAniRender->GetAnimationName(), true, true);
		}
	}

	if (DamageAniMationCount == 2)
	{
		m_DrawDamageAnimation = false;
	}
}

void ObjectBase::FadeIn(float _Time)
{
	if (m_FadeInOutActor != nullptr)
	{
		return;
	}

	m_FadeInOutActor = GetScene()->CreateActor<FadeInOut>();
	m_FadeInOutActor->SetPos({ WINDOWWIDTH / 2, WINDOWHEIGHT / 2 });
	m_FadeInOutActor->FadeIn(_Time);

	m_FadeInStart = true;
}

void ObjectBase::FadeOut(float _Time)
{
	if (m_FadeInOutActor != nullptr)
	{
		return;
	}

	m_FadeInOutActor = GetScene()->CreateActor<FadeInOut>();
	m_FadeInOutActor->SetPos({ WINDOWWIDTH / 2, WINDOWHEIGHT / 2 });
	m_FadeInOutActor->FadeOut(_Time);

	m_FadeOutStart = true;
}

bool ObjectBase::IsFadeInOutOver()
{
	return m_FadeInOutActor->IsOver();
}

void ObjectBase::DropItem()
{
	if (m_DropItemType == ENUM_ITEMTYPE::NONE)
		return;

	GJHGameEngineActor* NewItem;
	switch (m_DropItemType)
	{
	case ENUM_ITEMTYPE::GRANADE:
		NewItem = GetScene()->CreateActor<GranadeBox>();
		NewItem->SetName("GranadeBox");
		NewItem->SetPos(GetPos() + GJHVector(0, -30.f));
		break;
	case ENUM_ITEMTYPE::HEAVYMACHINEGUN:
		NewItem = GetScene()->CreateActor<HeavyMachineGunBox>();
		NewItem->SetName("HeavyMachineGunBox");
		NewItem->SetPos(GetPos() + GJHVector(0, -30.f));
		break;
	}
}