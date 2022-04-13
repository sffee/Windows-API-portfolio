#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::LookUpStart_BasicInit()
{
	ChangeAnimation("LookUpStart");

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::LookUpStart_BasicState()
{
	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("MoveLookUpStart");
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

		ChangeAnimation("LookUpStart", true);

		ChangeState("ThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("LookUpLoop");
	}
}

void Player::LookUpStart_BasicLeave()
{
	m_LookUp = false;
}

void Player::LookUpLoop_BasicInit()
{
	ChangeAnimation("LookUpLoop");

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::LookUpLoop_BasicState()
{
	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("MoveLookUpLoop");

	}
	if (KEYFREE("LookUp") == true)
	{
		ChangeState("LookUpEnd");
	}

	if (KEYPRESS("Jump") == true)
	{
		ChangeState("Jump");
	}

	if (KEYPRESS("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("LookUpAttack");
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

		ChangeAnimation("LookUpLoop", true);

		ChangeState("ThrowGranade");
	}
}

void Player::LookUpLoop_BasicLeave()
{
	m_LookUp = false;
}

void Player::LookUpEnd_BasicInit()
{
	ChangeAnimation("LookUpEnd");
	AniRenderTop->SetAnimationFrameIndex(74);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::LookUpEnd_BasicState()
{
	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("MoveLookUpEnd");
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

		ChangeAnimation("LookUpEnd", true);

		ChangeState("ThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Idle");
	}
}

void Player::LookUpEnd_BasicLeave()
{
	m_LookUp = false;
}

void Player::LookUpAttack_BasicInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("LookUpAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_AttackCancleAble = false;

	m_LookUp = true;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::LookUpAttack_BasicState()
{
	if (112 < AniRenderTop->GetAnimationFrameIndex())
	{
		if (m_AttackCancleAble == false)
		{
			m_AttackCancleAble = true;
		}

		if (m_ShootBullet == false)
		{
			CreateBullet(-90.f);
		}
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("MoveLookUpAttack");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("LookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("IdleAttack");
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

		ChangeAnimation("LookUpAttack", true);

		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		if (KEYPRESS("LookUp") == true)
		{
			ChangeState("JumpLookUpAttack");
		}
		else
		{
			ChangeState("Jump");
		}
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("LookUpLoop");
	}
}

void Player::LookUpAttack_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpStart_BasicInit()
{
	if (m_BottomBodyMove == true)
	{
		ChangeAnimation("MoveLookUpStart", ENUM_BODYTYPE::TOP);
	}
	else
	{
		ChangeAnimation("MoveLookUpStart");
	}

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveLookUpStart_BasicState()
{
	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LookUpLMove") == true &&
		KEYFREE("LookUpRMove") == true &&
		KEYFREE("LMove") == true &&
		KEYFREE("RMove") == true)
	{
		ChangeState("LookUpStart");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveAttack");
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

		ChangeAnimation("MoveLookUpStart", true);

		ChangeState("MoveThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		ChangeState("MoveJumpLookUpStart");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("MoveLookUpLoop");
	}
}

void Player::MoveLookUpStart_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpLoop_BasicInit()
{
	if (m_BottomBodyMove == true)
	{
		ChangeAnimation("MoveLookUpLoop", ENUM_BODYTYPE::TOP);
	}
	else
	{
		ChangeAnimation("MoveLookUpLoop");
	}

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveLookUpLoop_BasicState()
{
	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("LookUp") == true &&
		KEYFREE("LookUpLMove") == true &&
		KEYFREE("LookUpRMove") == true &&
		KEYFREE("LMove") == true &&
		KEYFREE("RMove") == true)
	{
		ChangeState("LookUpLoop");
	}
	else if (KEYFREE("LookUpLMove") == true &&
		KEYFREE("LookUpRMove") == true)
	{
		ChangeState("MoveLookUpEnd");
	}

	if (KEYPRESS("Jump") == true)
	{
		ChangeState("MoveJumpLookUpStart");
	}

	if (KEYDOWN("Attack") == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("MoveLookUpAttack");
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

		ChangeAnimation("MoveLookUpLoop", true);

		ChangeState("MoveThrowGranade");
	}
}

void Player::MoveLookUpLoop_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpEnd_BasicInit()
{
	if (m_BottomBodyMove == true)
	{
		ChangeAnimation("MoveLookUpEnd", ENUM_BODYTYPE::TOP);
	}
	else
	{
		ChangeAnimation("MoveLookUpEnd");
	}
	AniRenderTop->SetAnimationFrameIndex(74);

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveLookUpEnd_BasicState()
{
	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LookUpLMove") == true &&
		KEYFREE("LookUpRMove") == true &&
		KEYFREE("LMove") == true &&
		KEYFREE("RMove") == true)
	{
		ChangeState("LookUpEnd");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveAttack");
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

		ChangeAnimation("MoveLookUpEnd", true);

		ChangeState("MoveThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		ChangeState("MoveJump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Move");
	}
}

void Player::MoveLookUpEnd_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpAttack_BasicInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("MoveLookUpAttack", ENUM_BODYTYPE::TOP);
	}

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_AttackCancleAble = false;

	m_LookUp = true;
}

void Player::MoveLookUpAttack_BasicState()
{
	if (112 < AniRenderTop->GetAnimationFrameIndex())
	{
		if (m_AttackCancleAble == false)
		{
			m_AttackCancleAble = true;
		}

		if (m_ShootBullet == false)
		{
			CreateBullet(-90.f);
		}
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LookUpLMove") == true &&
		KEYFREE("LookUpRMove") == true &&
		KEYFREE("LMove") == true &&
		KEYFREE("RMove") == true)
	{
		ChangeState("LookUpAttack");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("MoveLookUpAttack");
	}

	if (KEYFREE("LookUpLMove") == true &&
		KEYFREE("LookUpRMove") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeState("MoveAttack");
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

		ChangeAnimation("MoveLookUpAttack", true);

		ChangeState("MoveThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		if (KEYPRESS("LookUp") == true)
		{
			ChangeState("MoveJumpLookUpAttack");
		}
		else
		{
			ChangeState("MoveJumpAttack");
		}
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("MoveLookUpLoop");
	}
}

void Player::MoveLookUpAttack_BasicLeave()
{
	m_LookUp = false;
}