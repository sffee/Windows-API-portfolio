#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::IdleInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = false;
	
	ChangeAnimation("Idle");
}

void Player::IdleState()
{
	if (KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		PlayerState.ChangeState("Move");
	}

	if (KEYPRESS("Sit") == true)
	{
		PlayerState.ChangeState("SitStart");
	}

	if (KEYPRESS("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("IdleAttackBasic");
	}

	if (KEYDOWN("Jump") == true)
	{
		PlayerState.ChangeState("Jump");
	}
}

void Player::MoveInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	ChangeAnimation("Move");
}

void Player::MoveState()
{
	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LMove") == true
		&& KEYFREE("RMove") == true)
	{
		PlayerState.ChangeState("StopMove");
	}

	if (KEYPRESS("Sit") == true)
	{
		PlayerState.ChangeState("SitStart");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("MoveAttackBasic");
	}

	if (KEYDOWN("LJump") == true ||
		KEYDOWN("RJump") == true)
	{
		PlayerState.ChangeState("MoveJump");
	}
}

void Player::StopMoveInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	ChangeAnimation("StopMove");
}

void Player::StopMoveState()
{
	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		PlayerState.ChangeState("Move");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("IdleAttackBasic");
	}

	if (KEYPRESS("Sit") == true)
	{
		PlayerState.ChangeState("SitStart");
	}

	if (KEYDOWN("Jump") == true)
	{
		PlayerState.ChangeState("Jump");
	}

	if (AnimationEnd() == true)
	{
		PlayerState.ChangeState("Idle");
	}
}

void Player::IdleAttackBasicInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("IdleAttackBasic", ENUM_BODYTYPE::TOP);
	}
	
	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_AttackCancleAble = false;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::IdleAttackBasicState()
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
		PlayerState.ChangeState("MoveAttackBasic");
	}

	if (KEYPRESS("Sit") == true && m_AttackCancleAble == true)
	{
		PlayerState.ChangeState("SitStart");
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		PlayerState.ChangeState("IdleAttackBasic");
	}

	if (KEYDOWN("Jump") == true)
	{
		PlayerState.ChangeState("Jump");
	}

	if (TopAnimationEnd() == true)
	{
		PlayerState.ChangeState("Idle");
	}
}

void Player::MoveAttackBasicInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("MoveAttackBasic", ENUM_BODYTYPE::TOP);
	}

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_AttackCancleAble = false;
}

void Player::MoveAttackBasicState()
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
		PlayerState.ChangeState("IdleAttackBasic");
	}

	if (KEYPRESS("Sit") == true && m_AttackCancleAble == true)
	{
		PlayerState.ChangeState("SitStart");
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		PlayerState.ChangeState("MoveAttackBasic");
	}

	if (KEYDOWN("LJump") == true ||
		KEYDOWN("RJump") == true)
	{
		PlayerState.ChangeState("MoveJump");
	}

	if (TopAnimationEnd() == true)
	{
		PlayerState.ChangeState("Move");
	}
}

void Player::SitStartInit()
{
	m_Sit = true;

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_MoveSpeed = SITMOVESPEED;

	ChangeAnimation("SitStart", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitStartState()
{
	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("SitAttack");
	}

	if (BottomAnimationEnd() == true)
	{
		PlayerState.ChangeState("SitLoop");
	}
}

void Player::SitLoopInit()
{
	ChangeAnimation("SitLoop", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitLoopState()
{
	if (KEYFREE("Sit") == true)
	{
		PlayerState.ChangeState("SitEnd");
	}

	if (KEYPRESS("SitLMove") == true
		|| KEYPRESS("SitRMove") == true)
	{
		PlayerState.ChangeState("SitMove");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("SitAttack");
	}
}

void Player::SitMoveInit()
{
	ChangeAnimation("SitMove", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitMoveState()
{
	if (KEYFREE("Sit") == true)
	{
		PlayerState.ChangeState("SitEnd");
	}

	if (KEYFREE("SitLMove") == true
		&& KEYFREE("SitRMove") == true)
	{
		PlayerState.ChangeState("SitLoop");
	}

	if (KEYPRESS("SitLMove") == true
		|| KEYPRESS("SitRMove") == true)
	{
		WalkMove();
	}

	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("SitAttack");
	}
}

void Player::SitAttackInit()
{
	m_AttackCancleAble = false;

	ChangeAnimation("SitAttack", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitAttackState()
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
		PlayerState.ChangeState("SitEnd");
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("SitAttack");
	}

	if (BottomAnimationEnd() == true)
	{
		PlayerState.ChangeState("SitAttackLoop");
	}
}

void Player::SitAttackLoopInit()
{
	ChangeAnimation("SitAttackLoop", ENUM_BODYTYPE::BOTTOM);
}

void Player::SitAttackLoopState()
{
	if (KEYFREE("Sit") == true)
	{
		PlayerState.ChangeState("SitEnd");
	}

	if (KEYPRESS("SitLMove") == true
		|| KEYPRESS("SitRMove") == true)
	{
		PlayerState.ChangeState("SitMove");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("SitAttack");
	}

	if (BottomAnimationEnd() == true)
	{
		PlayerState.ChangeState("SitAttackLoop");
	}
}

void Player::SitEndInit()
{
	m_Sit = false;

	m_MoveSpeed = MOVESPEED;

	ChangeAnimation("SitEnd", ENUM_BODYTYPE::BOTTOM);

	AniRenderBottom->SetAnimationFrameIndex(77);
}

void Player::SitEndState()
{
	if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		PlayerState.ChangeState("IdleAttackBasic");
	}

	if (BottomAnimationEnd() == true)
	{
		PlayerState.ChangeState("Idle");
	}
}