#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::Idle_HeavyMachineGunInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_Falling = false;

	ChangeAnimation("Idle");
}

void Player::Idle_HeavyMachineGunState()
{
	if (KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("Move");
	}

	if (KEYPRESS("LookUp") == true)
	{
		ChangeState("LookUpStart");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("SitStart");
	}

	if (KEYPRESS("Attack") == true)
	{
		ChangeState("IdleAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (KEYDOWN("Jump") == true)
	{
		ChangeState("Jump");
	}
}

void Player::IdleAttack_HeavyMachineGunInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("IdleAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_HeavymachineGunAttackReserve = false;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::IdleAttack_HeavyMachineGunState()
{
	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 72)
	{
		AniRenderTop->SetAnimationFrameIndex(70);

		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 1 &&
			 AniRenderTop->GetAnimationFrameIndex() == 72)
	{
		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
			 TopAnimationEnd() == true)
	{
		AniRenderTop->SetAnimationFrameIndex(72);

		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 3 &&
			 TopAnimationEnd() == true)
	{
		CreateHeavyMachineGunBullet(0.f);

		m_HeavyMachineGunShotCount = 0;
		if (m_HeavymachineGunAttackReserve == true)
		{
			m_TopBodyAttack = false;
			ChangeState("IdleAttack");
		}
		else
		{
			ChangeState("IdleAttackEnd");
		}
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		ChangeState("MoveAttack");
	}

	if (KEYPRESS("Sit") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("SitStart");
	}

	if (KEYPRESS("LookUp") == true)
	{
		m_TopBodyAttack = false;
		m_HeavyMachineGunShotCount = 0;

		ChangeState("IdleAttackUp");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYDOWN("Granade") == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;
		m_HeavyMachineGunShotCount = 0;

		ChangeState("ThrowGranade");
	}

	if (KEYDOWN("Jump") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("Jump");
	}
}

void Player::IdleAttackUp_HeavyMachineGunInit()
{
	ChangeAnimation("IdleAttackUp", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::IdleAttackUp_HeavyMachineGunState()
{
	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 77)
	{
		CreateHeavyMachineGunBullet(-10.f, GJHVector(-40.f * (int)CurDirState, -60.f));
		CreateHeavyMachineGunBullet(-22.f, GJHVector(-50.f * (int)CurDirState, -80.f));
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		AniRenderTop->GetAnimationFrameIndex() == 78)
	{
		CreateHeavyMachineGunBullet(-52.f, GJHVector(-60.f * (int)CurDirState, -130.f));
		CreateHeavyMachineGunBullet(-82.f, GJHVector(-100.f * (int)CurDirState, -170.f));
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		ChangeState("MoveAttackUp");
	}

	if (KEYPRESS("Sit") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("SitStart");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;
		m_HeavyMachineGunShotCount = 0;

		ChangeState("ThrowGranade");
	}

	if (KEYDOWN("Jump") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("Jump");
	}

	if (TopAnimationEnd() == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("LookUpLoop");
	}
}

void Player::IdleAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("IdleAttackEnd", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::IdleAttackEnd_HeavyMachineGunState()
{
	if (KEYPRESS("Sit") == true)
	{
		ChangeState("SitStart");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_TopBodyAttack = false;

		ChangeState("LookUpAttack");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_TopBodyAttack = false;

		ChangeState("IdleAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (KEYDOWN("Jump") == true)
	{
		ChangeState("Jump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Idle");
	}
}

void Player::ThrowGranade_HeavyMachineGunInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("ThrowGranade", ENUM_BODYTYPE::TOP);
	}

	m_AttackCancleAble = false;

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::ThrowGranade_HeavyMachineGunState()
{
	if (177 < AniRenderTop->GetAnimationFrameIndex())
	{
		if (m_AttackCancleAble == false)
		{
			m_AttackCancleAble = true;
		}

		if (m_ThrowGranade == false)
		{
			CreateGranade();
		}
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		ChangeState("MoveThrowGranade");
	}

	if (KEYPRESS("Jump") == true && m_AttackCancleAble == true)
	{
		ChangeState("Jump");
	}

	if (KEYPRESS("Sit") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitStart");
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;

		ChangeState("IdleAttack");
	}

	if (KEYDOWN("Granade") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Idle");
	}
}