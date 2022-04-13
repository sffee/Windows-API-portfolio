#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include <map>
#include <vector>
#include <set>
#include "define.h"
#include "ObjectBase.h"
#include "Weapon.h"

class Player : public ObjectBase
{
	static const float MOVESPEED;
	static const float SITMOVESPEED;
	static const float JUMPPOWER;
	
	enum class ENUM_BODYTYPE
	{
		TOP,
		BOTTOM
	};

private:
	static int m_Score;
	static int m_GranadeCount;
	static int m_Life;
	static Weapon* m_Weapon;

public:
	static int GetScore()
	{
		return m_Score;
	}

	static int GetGranadeCount()
	{
		return m_GranadeCount;
	}

	static Weapon* GetWeapon()
	{
		return m_Weapon;
	}

	static int GetLife()
	{
		return m_Life;
	}

	static void AddScore(int _Value)
	{
		m_Score += _Value;
	}

private:
	GJHRenderer* AniRenderTop;
	GJHRenderer* AniRenderBottom;
	GJHRenderer* AniRenderParachute;

	std::map<GJHString, std::map<int, AniData>> AnimationDataTop;
	std::map<GJHString, std::map<int, AniData>> AnimationDataBottom;

	std::map<GJHString, std::map<int, PivotData>> CorrectionTopBody;	// Bottom 바디 인덱스 기준으로 Top 바디 Pivot을 보정하는 변수

	ENUM_DIRECTION CurDirState;
	GJHString CurDirStateStr;
	ENUM_DIRECTION PrevDirState;
	GJHString PrevDirStateStr;
	ENUM_DIRECTION JumpDirState;

	GJHStateUpdater<Player> PlayerState;
	GJHString CurStateStr;

	std::set<GJHString> TopBodyDrawSkip;

	bool m_IsBounceOff;
	bool m_IsBounceOffStart;
	ENUM_DIRECTION m_BounceDir;
	float m_BounceOffCurTime;
	float m_BounceOffMaxTime;

	bool m_AttackCancleAble;

	bool m_TopBodyAttack;
	bool m_BottomBodyMove;

	bool m_ShootBullet;
	bool m_ThrowGranade;

	bool m_HeavymachineGunAttackReserve;
	int m_HeavyMachineGunShotCount;

	bool m_Sit;
	bool m_LookUp;
	bool m_JumpLookDown;

	bool m_BlockDirChange;

	float m_InvincibleTime;
	bool m_IsInvincible;

	~Player();

	void Start() override;
	void Update() override;
	void ColEnter(GJHCollision* _This, GJHCollision* _Other) override;
	void ColStay(GJHCollision* _This, GJHCollision* _Other) override;

	void Move(const GJHVector& _MoveValue);

	void CreateAnimation(const GJHString& _Name, int _TopStart, int _TopEnd, int _BottomStart, int _BottomEnd, float _FrameTime, bool _TopLoop = true, bool _BottomLoop = true, bool _TopReverse = false, bool _BottomReverse = false, const GJHString& _FileName = "Eri_Kasamoto");
	void ChangeAnimation(const GJHString& _Name, bool _Correction = false, const GJHVector& _Size = { 512, 512 });
	void ChangeAnimation(const GJHString& _Name, ENUM_BODYTYPE _BODYTYPE, bool _Correction = false, const GJHVector& _Size = { 512, 512 });
	void ChangeState(const GJHString& _StateName);
	
	void SetDefaultAniData();
	void PushAnimationData(const GJHString& _Name, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime, ENUM_BODYTYPE _BodyType = ENUM_BODYTYPE::TOP);
	void PushCorrectionTopBody(const GJHString& _Name, int _BottomFrameIndex, float _TopPivotX, float _TopPivotY);

	bool TopAnimationEnd();
	bool BottomAnimationEnd();
	bool AnimationEnd();

	void SetCurDirState(ENUM_DIRECTION _Dir);
	void SetPrevDirState(ENUM_DIRECTION _Dir);
	void SetCollisionPivot(GJHVector _Pivot);
	void SetCollisionSize(GJHVector _Size);

	void BounceOff();
	void AmmoCheck();

	void CreateBullet(float _Angle = 0.f);
	void CreateHeavyMachineGunBullet(float _Angle = 0.f, GJHVector _Pos = GJHVector::ZERO);
	void CreateGranade();

	void DirStateCheck();
	void AnimationDataCheck();
	void WalkMove();
	void Jump();
	void CheckMissionComplete();
	void Invincible();
	void DeathReset();

	void Idle_BasicInit();
	void Idle_BasicState();
	void IdleAttack_BasicInit();
	void IdleAttack_BasicState();

	void Move_BasicInit();
	void Move_BasicState();
	void MoveAttack_BasicInit();
	void MoveAttack_BasicState();
	void StopMove_BasicInit();
	void StopMove_BasicState();

	void LookUpStart_BasicInit();
	void LookUpStart_BasicState();
	void LookUpStart_BasicLeave();

	void LookUpLoop_BasicInit();
	void LookUpLoop_BasicState();
	void LookUpLoop_BasicLeave();

	void LookUpEnd_BasicInit();
	void LookUpEnd_BasicState();
	void LookUpEnd_BasicLeave();

	void LookUpAttack_BasicInit();
	void LookUpAttack_BasicState();
	void LookUpAttack_BasicLeave();

	void MoveLookUpStart_BasicInit();
	void MoveLookUpStart_BasicState();
	void MoveLookUpStart_BasicLeave();

	void MoveLookUpLoop_BasicInit();
	void MoveLookUpLoop_BasicState();
	void MoveLookUpLoop_BasicLeave();

	void MoveLookUpEnd_BasicInit();
	void MoveLookUpEnd_BasicState();
	void MoveLookUpEnd_BasicLeave();

	void MoveLookUpAttack_BasicInit();
	void MoveLookUpAttack_BasicState();
	void MoveLookUpAttack_BasicLeave();

	void SitStart_BasicInit();
	void SitStart_BasicState();
	void SitStart_BasicLeave();

	void SitLoop_BasicInit();
	void SitLoop_BasicState();
	void SitLoop_BasicLeave();

	void SitMove_BasicInit();
	void SitMove_BasicState();
	void SitMove_BasicLeave();

	void SitAttack_BasicInit();
	void SitAttack_BasicState();
	void SitAttack_BasicLeave();

	void SitAttackLoop_BasicInit();
	void SitAttackLoop_BasicState();
	void SitAttackLoop_BasicLeave();

	void SitEnd_BasicInit();
	void SitEnd_BasicState();
	void SitEnd_BasicLeave();

	void Jump_BasicInit();
	void Jump_BasicState();

	void MoveJump_BasicInit();
	void MoveJump_BasicState();

	void JumpAttack_BasicInit();
	void JumpAttack_BasicState();

	void MoveJumpAttack_BasicInit();
	void MoveJumpAttack_BasicState();

	void JumpLookUpStart_BasicInit();
	void JumpLookUpStart_BasicState();
	void JumpLookUpStart_BasicLeave();

	void JumpLookUpLoop_BasicInit();
	void JumpLookUpLoop_BasicState();
	void JumpLookUpLoop_BasicLeave();

	void JumpLookUpEnd_BasicInit();
	void JumpLookUpEnd_BasicState();
	void JumpLookUpEnd_BasicLeave();

	void JumpLookUpAttack_BasicInit();
	void JumpLookUpAttack_BasicState();
	void JumpLookUpAttack_BasicLeave();

	void MoveJumpLookUpStart_BasicInit();
	void MoveJumpLookUpStart_BasicState();
	void MoveJumpLookUpStart_BasicLeave();

	void MoveJumpLookUpLoop_BasicInit();
	void MoveJumpLookUpLoop_BasicState();
	void MoveJumpLookUpLoop_BasicLeave();

	void MoveJumpLookUpEnd_BasicInit();
	void MoveJumpLookUpEnd_BasicState();
	void MoveJumpLookUpEnd_BasicLeave();

	void MoveJumpLookUpAttack_BasicInit();
	void MoveJumpLookUpAttack_BasicState();
	void MoveJumpLookUpAttack_BasicLeave();

	void JumpLookDownStart_BasicInit();
	void JumpLookDownStart_BasicState();
	void JumpLookDownStart_BasicLeave();

	void JumpLookDownLoop_BasicInit();
	void JumpLookDownLoop_BasicState();
	void JumpLookDownLoop_BasicLeave();

	void JumpLookDownEnd_BasicInit();
	void JumpLookDownEnd_BasicState();
	void JumpLookDownEnd_BasicLeave();

	void JumpLookDownAttack_BasicInit();
	void JumpLookDownAttack_BasicState();
	void JumpLookDownAttack_BasicLeave();

	void MoveJumpLookDownStart_BasicInit();
	void MoveJumpLookDownStart_BasicState();
	void MoveJumpLookDownStart_BasicLeave();

	void MoveJumpLookDownLoop_BasicInit();
	void MoveJumpLookDownLoop_BasicState();
	void MoveJumpLookDownLoop_BasicLeave();

	void MoveJumpLookDownEnd_BasicInit();
	void MoveJumpLookDownEnd_BasicState();
	void MoveJumpLookDownEnd_BasicLeave();

	void MoveJumpLookDownAttack_BasicInit();
	void MoveJumpLookDownAttack_BasicState();
	void MoveJumpLookDownAttack_BasicLeave();

	void ThrowGranade_BasicInit();
	void ThrowGranade_BasicState();

	void MoveThrowGranade_BasicInit();
	void MoveThrowGranade_BasicState();

	void SitThrowGranade_BasicInit();
	void SitThrowGranade_BasicState();
	void SitThrowGranade_BasicLeave();

	void JumpThrowGranade_BasicInit();
	void JumpThrowGranade_BasicState();

	void MoveJumpThrowGranade_BasicInit();
	void MoveJumpThrowGranade_BasicState();

	void Parachute_BasicInit();
	void Parachute_BasicState();

	void Victory_BasicInit();
	void Victory_BasicState();

	void Death_BasicInit();
	void Death_BasicState();

	void Alive_BasicInit();
	void Alive_BasicState();

///////////////////////////////////////////////

	void Idle_HeavyMachineGunInit();
	void Idle_HeavyMachineGunState();
	void IdleAttack_HeavyMachineGunInit();
	void IdleAttack_HeavyMachineGunState();
	void IdleAttackEnd_HeavyMachineGunInit();
	void IdleAttackEnd_HeavyMachineGunState();
	void IdleAttackUp_HeavyMachineGunInit();
	void IdleAttackUp_HeavyMachineGunState();

	void Move_HeavyMachineGunInit();
	void Move_HeavyMachineGunState();
	void MoveAttack_HeavyMachineGunInit();
	void MoveAttack_HeavyMachineGunState();
	void MoveAttackEnd_HeavyMachineGunInit();
	void MoveAttackEnd_HeavyMachineGunState();
	void MoveAttackUp_HeavyMachineGunInit();
	void MoveAttackUp_HeavyMachineGunState();
	void StopMove_HeavyMachineGunInit();
	void StopMove_HeavyMachineGunState();

	void LookUpStart_HeavyMachineGunInit();
	void LookUpStart_HeavyMachineGunState();
	void LookUpStart_HeavyMachineGunLeave();

	void LookUpLoop_HeavyMachineGunInit();
	void LookUpLoop_HeavyMachineGunState();
	void LookUpLoop_HeavyMachineGunLeave();

	void LookUpEnd_HeavyMachineGunInit();
	void LookUpEnd_HeavyMachineGunState();
	void LookUpEnd_HeavyMachineGunLeave();

	void LookUpAttack_HeavyMachineGunInit();
	void LookUpAttack_HeavyMachineGunState();
	void LookUpAttack_HeavyMachineGunLeave();

	void LookUpAttackEnd_HeavyMachineGunInit();
	void LookUpAttackEnd_HeavyMachineGunState();
	void LookUpAttackEnd_HeavyMachineGunLeave();

	void LookUpAttackDown_HeavyMachineGunInit();
	void LookUpAttackDown_HeavyMachineGunState();
	void LookUpAttackDown_HeavyMachineGunLeave();

	void MoveLookUpStart_HeavyMachineGunInit();
	void MoveLookUpStart_HeavyMachineGunState();
	void MoveLookUpStart_HeavyMachineGunLeave();

	void MoveLookUpLoop_HeavyMachineGunInit();
	void MoveLookUpLoop_HeavyMachineGunState();
	void MoveLookUpLoop_HeavyMachineGunLeave();

	void MoveLookUpEnd_HeavyMachineGunInit();
	void MoveLookUpEnd_HeavyMachineGunState();
	void MoveLookUpEnd_HeavyMachineGunLeave();

	void MoveLookUpAttack_HeavyMachineGunInit();
	void MoveLookUpAttack_HeavyMachineGunState();
	void MoveLookUpAttack_HeavyMachineGunLeave();

	void MoveLookUpAttackEnd_HeavyMachineGunInit();
	void MoveLookUpAttackEnd_HeavyMachineGunState();
	void MoveLookUpAttackEnd_HeavyMachineGunLeave();

	void MoveLookUpAttackDown_HeavyMachineGunInit();
	void MoveLookUpAttackDown_HeavyMachineGunState();
	void MoveLookUpAttackDown_HeavyMachineGunLeave();

	void SitStart_HeavyMachineGunInit();
	void SitStart_HeavyMachineGunState();
	void SitStart_HeavyMachineGunLeave();

	void SitLoop_HeavyMachineGunInit();
	void SitLoop_HeavyMachineGunState();
	void SitLoop_HeavyMachineGunLeave();

	void SitMove_HeavyMachineGunInit();
	void SitMove_HeavyMachineGunState();
	void SitMove_HeavyMachineGunLeave();

	void SitAttack_HeavyMachineGunInit();
	void SitAttack_HeavyMachineGunState();
	void SitAttack_HeavyMachineGunLeave();

	void SitAttackLoop_HeavyMachineGunInit();
	void SitAttackLoop_HeavyMachineGunState();
	void SitAttackLoop_HeavyMachineGunLeave();

	void SitAttackEnd_HeavyMachineGunInit();
	void SitAttackEnd_HeavyMachineGunState();
	void SitAttackEnd_HeavyMachineGunLeave();

	void SitEnd_HeavyMachineGunInit();
	void SitEnd_HeavyMachineGunState();
	void SitEnd_HeavyMachineGunLeave();

	void Jump_HeavyMachineGunInit();
	void Jump_HeavyMachineGunState();

	void MoveJump_HeavyMachineGunInit();
	void MoveJump_HeavyMachineGunState();

	void JumpAttack_HeavyMachineGunInit();
	void JumpAttack_HeavyMachineGunState();

	void JumpAttackEnd_HeavyMachineGunInit();
	void JumpAttackEnd_HeavyMachineGunState();

	void JumpAttackUp_HeavyMachineGunInit();
	void JumpAttackUp_HeavyMachineGunState();

	void JumpAttackDown_HeavyMachineGunInit();
	void JumpAttackDown_HeavyMachineGunState();

	void MoveJumpAttack_HeavyMachineGunInit();
	void MoveJumpAttack_HeavyMachineGunState();

	void MoveJumpAttackEnd_HeavyMachineGunInit();
	void MoveJumpAttackEnd_HeavyMachineGunState();

	void MoveJumpAttackUp_HeavyMachineGunInit();
	void MoveJumpAttackUp_HeavyMachineGunState();

	void MoveJumpAttackDown_HeavyMachineGunInit();
	void MoveJumpAttackDown_HeavyMachineGunState();

	void JumpLookUpStart_HeavyMachineGunInit();
	void JumpLookUpStart_HeavyMachineGunState();
	void JumpLookUpStart_HeavyMachineGunLeave();

	void JumpLookUpLoop_HeavyMachineGunInit();
	void JumpLookUpLoop_HeavyMachineGunState();
	void JumpLookUpLoop_HeavyMachineGunLeave();

	void JumpLookUpEnd_HeavyMachineGunInit();
	void JumpLookUpEnd_HeavyMachineGunState();
	void JumpLookUpEnd_HeavyMachineGunLeave();

	void JumpLookUpAttack_HeavyMachineGunInit();
	void JumpLookUpAttack_HeavyMachineGunState();
	void JumpLookUpAttack_HeavyMachineGunLeave();

	void JumpLookUpAttackEnd_HeavyMachineGunInit();
	void JumpLookUpAttackEnd_HeavyMachineGunState();
	void JumpLookUpAttackEnd_HeavyMachineGunLeave();

	void JumpLookUpAttackDown_HeavyMachineGunInit();
	void JumpLookUpAttackDown_HeavyMachineGunState();
	void JumpLookUpAttackDown_HeavyMachineGunLeave();

	void MoveJumpLookUpStart_HeavyMachineGunInit();
	void MoveJumpLookUpStart_HeavyMachineGunState();
	void MoveJumpLookUpStart_HeavyMachineGunLeave();

	void MoveJumpLookUpLoop_HeavyMachineGunInit();
	void MoveJumpLookUpLoop_HeavyMachineGunState();
	void MoveJumpLookUpLoop_HeavyMachineGunLeave();

	void MoveJumpLookUpEnd_HeavyMachineGunInit();
	void MoveJumpLookUpEnd_HeavyMachineGunState();
	void MoveJumpLookUpEnd_HeavyMachineGunLeave();

	void MoveJumpLookUpAttack_HeavyMachineGunInit();
	void MoveJumpLookUpAttack_HeavyMachineGunState();
	void MoveJumpLookUpAttack_HeavyMachineGunLeave();

	void MoveJumpLookUpAttackEnd_HeavyMachineGunInit();
	void MoveJumpLookUpAttackEnd_HeavyMachineGunState();
	void MoveJumpLookUpAttackEnd_HeavyMachineGunLeave();

	void MoveJumpLookUpAttackDown_HeavyMachineGunInit();
	void MoveJumpLookUpAttackDown_HeavyMachineGunState();
	void MoveJumpLookUpAttackDown_HeavyMachineGunLeave();

	void JumpLookDownStart_HeavyMachineGunInit();
	void JumpLookDownStart_HeavyMachineGunState();
	void JumpLookDownStart_HeavyMachineGunLeave();

	void JumpLookDownLoop_HeavyMachineGunInit();
	void JumpLookDownLoop_HeavyMachineGunState();
	void JumpLookDownLoop_HeavyMachineGunLeave();

	void JumpLookDownAttack_HeavyMachineGunInit();
	void JumpLookDownAttack_HeavyMachineGunState();
	void JumpLookDownAttack_HeavyMachineGunLeave();

	void JumpLookDownAttackUp_HeavyMachineGunInit();
	void JumpLookDownAttackUp_HeavyMachineGunState();
	void JumpLookDownAttackUp_HeavyMachineGunLeave();

	void MoveJumpLookDownStart_HeavyMachineGunInit();
	void MoveJumpLookDownStart_HeavyMachineGunState();
	void MoveJumpLookDownStart_HeavyMachineGunLeave();

	void MoveJumpLookDownLoop_HeavyMachineGunInit();
	void MoveJumpLookDownLoop_HeavyMachineGunState();
	void MoveJumpLookDownLoop_HeavyMachineGunLeave();

	void MoveJumpLookDownAttack_HeavyMachineGunInit();
	void MoveJumpLookDownAttack_HeavyMachineGunState();
	void MoveJumpLookDownAttack_HeavyMachineGunLeave();

	void MoveJumpLookDownAttackUp_HeavyMachineGunInit();
	void MoveJumpLookDownAttackUp_HeavyMachineGunState();
	void MoveJumpLookDownAttackUp_HeavyMachineGunLeave();

	void ThrowGranade_HeavyMachineGunInit();
	void ThrowGranade_HeavyMachineGunState();

	void MoveThrowGranade_HeavyMachineGunInit();
	void MoveThrowGranade_HeavyMachineGunState();

	void SitThrowGranade_HeavyMachineGunInit();
	void SitThrowGranade_HeavyMachineGunState();
	void SitThrowGranade_HeavyMachineGunLeave();

	void JumpThrowGranade_HeavyMachineGunInit();
	void JumpThrowGranade_HeavyMachineGunState();

	void MoveJumpThrowGranade_HeavyMachineGunInit();
	void MoveJumpThrowGranade_HeavyMachineGunState();
};