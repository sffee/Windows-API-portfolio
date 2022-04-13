#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::MoveJump_BasicInit()
{
	ChangeAnimation("MoveJump");

	Jump();

	m_TopBodyAttack = false;
}

void Player::MoveJump_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYDOWN("Attack") == true)
	{
		if (KEYPRESS("JumpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("JumpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJump", true);

		ChangeState("MoveJumpAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		if (KEYPRESS("LMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeAnimation("MoveJump", true);

		ChangeState("MoveJumpThrowGranade");
	}

	if (KEYPRESS("LookUp") == true)
	{
		ChangeState("MoveJumpLookUpStart");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("MoveJumpLookDownStart");
	}
}

void Player::MoveJumpAttack_BasicInit()
{
	ChangeAnimation("MoveJumpAttack", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::MoveJumpAttack_BasicState()
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

	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("LookUpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("LookUpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("JumpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("JumpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpAttack");
	}

	if (KEYPRESS("SitAttack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("LMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpLookDownAttack");
	}

	if (KEYDOWN("Granade") == true && m_AttackCancleAble == true)
	{
		if (KEYPRESS("LMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpThrowGranade");
	}
}

void Player::MoveJumpThrowGranade_BasicInit()
{
	ChangeAnimation("MoveJumpThrowGranade", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::MoveJumpThrowGranade_BasicState()
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

	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("LookUpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("LookUpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("JumpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("JumpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpAttack");
	}

	if (KEYPRESS("SitAttack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("LMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpLookDownAttack");
	}

	if (KEYDOWN("Granade") == true &&
		m_AttackCancleAble == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpThrowGranade");
	}
}