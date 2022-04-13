#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include "define.h"

void Player::Parachute_BasicInit()
{
	ChangeAnimation("Parachute");
	AniRenderParachute->ChangeAnimation("Parachute");

	m_Gravity = 100.f;
	m_GravityAddValue = 0.f;
	m_Jump = true;
}

void Player::Parachute_BasicState()
{
	if (m_Jump == false)
	{
		AniRenderParachute->SetDraw(false);

		ChangeState("StopMove");
	}

	if (KEYDOWN("Attack") == true)
	{
		AniRenderParachute->SetDraw(false);
		m_Falling = true;
		m_Gravity = 300.f;
		m_GravityAddValue = 1000.f;

		ChangeState("JumpAttack");
	}
}

void Player::Idle_BasicInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = false;
	
	ChangeAnimation("Idle");
}

void Player::Idle_BasicState()
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
		m_ShootBullet = false;

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

void Player::IdleAttack_BasicInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("IdleAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_AttackCancleAble = false;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::IdleAttack_BasicState()
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
		ChangeState("MoveAttack");
	}

	if (KEYPRESS("Sit") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitStart");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("LookUpAttack");
	}

	if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("IdleAttack");
	}

	if (KEYDOWN("Granade") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (KEYDOWN("Jump") == true && m_AttackCancleAble == true)
	{
		ChangeState("Jump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Idle");
	}
}

void Player::ThrowGranade_BasicInit()
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

void Player::ThrowGranade_BasicState()
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
		m_ShootBullet = false;

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

void Player::Victory_BasicInit()
{
	ChangeAnimation("Victory");
}

void Player::Victory_BasicState()
{
}

void Player::Death_BasicInit()
{
	m_BlockDirChange = true;

	m_AniCollision->SetHitable(false);
	ChangeAnimation("Death");
}

void Player::Death_BasicState()
{
	if (BottomAnimationEnd() == true)
	{
		ChangeState("Alive");
	}
}

void Player::Alive_BasicInit()
{
	ChangeAnimation("Alive", false, GJHVector(150, 1800));

	DeathReset();
}

void Player::Alive_BasicState()
{
	if (BottomAnimationEnd() == true)
	{
		m_BlockDirChange = false;
		m_AniCollision->SetHitable(true);

		ChangeState("Idle");
	}
}