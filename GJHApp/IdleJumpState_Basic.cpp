#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::Jump_BasicInit()
{
	ChangeAnimation("Jump");

	if (m_Falling == false)
	{
		Jump();
	}

	m_Falling = false;

	m_TopBodyAttack = false;
}

void Player::Jump_BasicState()
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

	if (KEYPRESS("LookUp") == true)
	{
		ChangeState("JumpLookUpStart");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("JumpLookDownStart");
	}

	if (KEYDOWN("Attack") == true)
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

		ChangeAnimation("Jump", true);

		ChangeState("JumpAttack");
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

		ChangeAnimation("Jump", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpAttack_BasicInit()
{
	ChangeAnimation("JumpAttack", ENUM_BODYTYPE::TOP);

	if (PlayerState.PrevState == "Parachute_Basic")
	{
		ChangeAnimation("JumpAttack", ENUM_BODYTYPE::BOTTOM);
	}

	m_Falling = false;

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::JumpAttack_BasicState()
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYFREE("Sit") == true &&
		KEYDOWN("Attack") == true &&
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpAttack");
	}

	if (KEYPRESS("Sit") == true &&
		KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true &&
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpLookDownAttack");
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpThrowGranade_BasicInit()
{
	ChangeAnimation("JumpThrowGranade", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::JumpThrowGranade_BasicState()
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

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYFREE("Sit") == true &&
		KEYDOWN("Attack") == true &&
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

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpAttack");
	}

	if (KEYPRESS("Sit") == true &&
		KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true &&
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

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpLookDownAttack");
	}

	if (KEYDOWN("Granade") == true &&
		m_AttackCancleAble == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpThrowGranade");
	}
}