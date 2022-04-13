#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::SitStart_BasicInit()
{
	m_Sit = true;

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitStart", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitStart_BasicState()
{
	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

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

void Player::SitStart_BasicLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitLoop_BasicInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitLoop", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitLoop_BasicState()
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
		m_ShootBullet = false;

		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}
}

void Player::SitLoop_BasicLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitMove_BasicInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitMove", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitMove_BasicState()
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
		m_ShootBullet = false;

		ChangeState("SitAttack");
	}

	if (KEYDOWN("SitGranade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("SitThrowGranade");
	}
}

void Player::SitMove_BasicLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitAttack_BasicInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	m_AttackCancleAble = false;

	ChangeAnimation("SitAttack", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitAttack_BasicState()
{
	if (121 < AniRenderBottom->GetAnimationFrameIndex())
	{
		if (m_AttackCancleAble == false)
		{
			m_AttackCancleAble = true;
		}

		if (m_ShootBullet == false)
		{
			CreateBullet();
		}
	}

	if (KEYFREE("Sit") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitEnd");
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_ShootBullet = false;

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

void Player::SitAttack_BasicLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitAttackLoop_BasicInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitAttackLoop", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitAttackLoop_BasicState()
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
		m_ShootBullet = false;

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

void Player::SitAttackLoop_BasicLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitEnd_BasicInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitEnd", ENUM_BODYTYPE::BOTTOM);

	AniRenderBottom->SetAnimationFrameIndex(77);
}

void Player::SitEnd_BasicState()
{
	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

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

void Player::SitEnd_BasicLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}

void Player::SitThrowGranade_BasicInit()
{
	m_Sit = true;

	m_MoveSpeed = SITMOVESPEED;

	m_AttackCancleAble = false;

	ChangeAnimation("SitThrowGranade", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitThrowGranade_BasicState()
{
	if (151 < AniRenderBottom->GetAnimationFrameIndex())
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
		m_ShootBullet = false;

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

void Player::SitThrowGranade_BasicLeave()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;
}