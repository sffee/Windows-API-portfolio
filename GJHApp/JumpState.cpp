#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::JumpInit()
{
	ChangeAnimation("Jump");

	m_Jump = true;
	m_Falling = false;

	m_Gravity = 17.f;

	m_GravityForce = 0.f;
	m_FallingSpeed = -JUMPPOWER;

	JumpDirState = CurDirState;

	m_TopBodyAttack = false;
}

void Player::JumpState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		PlayerState.ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYDOWN("Attack") == true)
	{
		if (KEYPRESS("LJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation(PlayerState.CurState, true);

		PlayerState.ChangeState("JumpAttackBasic");
	}
}

void Player::MoveJumpInit()
{
	ChangeAnimation("MoveJump");

	m_Jump = true;
	m_Falling = false;

	m_Gravity = 17.f;

	m_GravityForce = 0.f;
	m_FallingSpeed = -JUMPPOWER;

	JumpDirState = CurDirState;
	
	m_TopBodyAttack = false;
}

void Player::MoveJumpState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		PlayerState.ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYDOWN("Attack") == true)
	{
		if (KEYPRESS("LJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation(PlayerState.CurState, true);

		PlayerState.ChangeState("MoveJumpAttackBasic");
	}
}

void Player::JumpAttackBasicInit()
{
	ChangeAnimation("JumpAttackBasic", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::JumpAttackBasicState()
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

		PlayerState.ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		if (KEYPRESS("LJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation(PlayerState.CurState, true);

		PlayerState.ChangeState("JumpAttackBasic");
	}
}

void Player::MoveJumpAttackBasicInit()
{
	ChangeAnimation("MoveJumpAttackBasic", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::MoveJumpAttackBasicState()
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

		PlayerState.ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		if (KEYPRESS("LJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("RJump") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation(PlayerState.CurState, true);

		PlayerState.ChangeState("MoveJumpAttackBasic");
	}
}