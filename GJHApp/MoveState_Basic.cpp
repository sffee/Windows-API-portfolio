#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::Move_BasicInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	ChangeAnimation("Move");
}

void Player::Move_BasicState()
{
	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LMove") == true
		&& KEYFREE("RMove") == true)
	{
		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true)
	{
		ChangeState("MoveLookUpStart");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("SitStart");
	}

	if (KEYPRESS("Jump") == true)
	{
		ChangeState("MoveJump");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("MoveThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		ChangeState("MoveJump");
	}
}

void Player::StopMove_BasicInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	ChangeAnimation("StopMove");
}

void Player::StopMove_BasicState()
{
	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		ChangeState("Move");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("LookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("IdleAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("SitStart");
	}

	if (KEYDOWN("Jump") == true)
	{
		ChangeState("Jump");
	}

	if (AnimationEnd() == true)
	{
		ChangeState("Idle");
	}
}

void Player::MoveAttack_BasicInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("MoveAttack", ENUM_BODYTYPE::TOP);
	}

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_AttackCancleAble = false;
}

void Player::MoveAttack_BasicState()
{
	if (94 < AniRenderTop->GetAnimationFrameIndex())
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

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LMove") == true
		&& KEYFREE("RMove") == true)
	{
		ChangeState("IdleAttack");
	}

	if (KEYPRESS("Sit") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitStart");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("MoveAttack");
	}

	if (KEYDOWN("Granade") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeState("MoveThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		ChangeState("MoveJump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Move");
	}
}

void Player::MoveThrowGranade_BasicInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("MoveThrowGranade", ENUM_BODYTYPE::TOP);
	}

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_AttackCancleAble = false;
}

void Player::MoveThrowGranade_BasicState()
{
	if (143 < AniRenderTop->GetAnimationFrameIndex())
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
		WalkMove();
	}

	if (KEYFREE("LMove") == true
		&& KEYFREE("RMove") == true)
	{
		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Sit") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitStart");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("MoveAttack");
	}

	if (KEYDOWN("Granade") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		ChangeState("MoveJump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Move");
	}
}