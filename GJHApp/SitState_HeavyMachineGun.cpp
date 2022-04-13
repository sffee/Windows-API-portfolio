#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::SitStart_HeavyMachineGunInit()
{
	m_Sit = true;

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitStart", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitStart_HeavyMachineGunState()
{
	if (KEYDOWN("Attack") == true)
	{
		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}

	if (BottomAnimationEnd() == true)
	{
		ChangeState("SitLoop");
	}
}

void Player::SitStart_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitLoop_HeavyMachineGunInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitLoop", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitLoop_HeavyMachineGunState()
{
	if (KEYFREE("Sit") == true)
	{
		ChangeState("SitEnd");
	}

	if (KEYPRESS("SitLMove") == true
		|| KEYPRESS("SitRMove") == true)
	{
		ChangeState("SitMove");
	}

	if (KEYPRESS("SitJump") == true)
	{
		ChangeState("JumpLookDownLoop");
	}

	if (KEYDOWN("Attack") == true)
	{
		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}
}

void Player::SitLoop_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitMove_HeavyMachineGunInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitMove", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitMove_HeavyMachineGunState()
{
	if (KEYFREE("Sit") == true)
	{
		ChangeState("SitEnd");
	}

	if (KEYFREE("SitLMove") == true
		&& KEYFREE("SitRMove") == true)
	{
		ChangeState("SitLoop");
	}

	if (KEYPRESS("SitLMove") == true
		|| KEYPRESS("SitRMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("SitJump") == true)
	{
		ChangeState("MoveJumpLookDownLoop");
	}

	if (KEYDOWN("Attack") == true)
	{
		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}
}

void Player::SitMove_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitAttack_HeavyMachineGunInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	m_HeavymachineGunAttackReserve = false;

	ChangeAnimation("SitAttack", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitAttack_HeavyMachineGunState()
{
	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderBottom->GetAnimationFrameIndex() == 98)
	{
		AniRenderBottom->SetAnimationFrameIndex(96);

		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 1 &&
		AniRenderBottom->GetAnimationFrameIndex() == 98)
	{
		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		BottomAnimationEnd() == true)
	{
		AniRenderBottom->SetAnimationFrameIndex(98);

		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 3 &&
		BottomAnimationEnd() == true)
	{
		CreateHeavyMachineGunBullet(0.f);

		m_HeavyMachineGunShotCount = 0;
		if (m_HeavymachineGunAttackReserve == true)
		{
			ChangeState("SitAttack");
		}
		else
		{
			ChangeState("SitAttackEnd");
		}
	}

	if (KEYFREE("Sit") == true)
	{
		ChangeState("SitEnd");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}

	if (KEYPRESS("SitJump") == true)
	{
		ChangeState("JumpLookDownLoop");
	}
}

void Player::SitAttack_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitAttackEnd_HeavyMachineGunInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	m_AttackCancleAble = false;

	ChangeAnimation("SitAttackEnd", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitAttackEnd_HeavyMachineGunState()
{
	if (KEYFREE("Sit") == true)
	{
		ChangeState("SitEnd");
	}

	if (KEYDOWN("Attack") == true)
	{
		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}

	if (KEYPRESS("SitJump") == true)
	{
		ChangeState("JumpLookDownLoop");
	}

	if (BottomAnimationEnd() == true)
	{
		ChangeState("SitAttackLoop");
	}
}

void Player::SitAttackEnd_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitAttackLoop_HeavyMachineGunInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitAttackLoop", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitAttackLoop_HeavyMachineGunState()
{
	if (KEYFREE("Sit") == true)
	{
		ChangeState("SitEnd");
	}

	if (KEYPRESS("SitLMove") == true
		|| KEYPRESS("SitRMove") == true)
	{
		ChangeState("SitMove");
	}

	if (KEYDOWN("Attack") == true)
	{
		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}

	if (BottomAnimationEnd() == true)
	{
		ChangeState("SitAttackLoop");
	}
}

void Player::SitAttackLoop_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitEnd_HeavyMachineGunInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitEnd", ENUM_BODYTYPE::BOTTOM);

	AniRenderBottom->SetAnimationFrameIndex(45);
}

void Player::SitEnd_HeavyMachineGunState()
{
	if (KEYDOWN("Attack") == true)
	{
		ChangeState("IdleAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (BottomAnimationEnd() == true)
	{
		ChangeState("Idle");
	}
}

void Player::SitEnd_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitThrowGranade_HeavyMachineGunInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	m_AttackCancleAble = false;

	ChangeAnimation("SitThrowGranade", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitThrowGranade_HeavyMachineGunState()
{
	if (184 < AniRenderBottom->GetAnimationFrameIndex())
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

	if (KEYFREE("Sit") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitEnd");
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true && m_AttackCancleAble == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}

	if (KEYPRESS("SitJump") == true)
	{
		ChangeState("JumpLookDownLoop");
	}

	if (BottomAnimationEnd() == true)
	{
		ChangeState("SitAttackLoop");
	}
}

void Player::SitThrowGranade_HeavyMachineGunLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}