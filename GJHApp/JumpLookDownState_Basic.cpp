#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::JumpLookDownStart_BasicInit()
{
	ChangeAnimation("JumpLookDownStart", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;

	m_JumpLookDown = true;
}

void Player::JumpLookDownStart_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("JumpLookDownAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookDownStart", true);

		ChangeState("JumpAttack");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("JumpLookDownLoop");
	}
}

void Player::JumpLookDownStart_BasicLeave()
{
	m_JumpLookDown = false;
}

void Player::JumpLookDownLoop_BasicInit()
{
	if (PlayerState.PrevState == "SitLoop_Basic" ||
		PlayerState.PrevState == "SitMove_Basic" ||
		PlayerState.PrevState == "SitAttack_Basic" ||
		PlayerState.PrevState == "SitThrowGranade_Basic")
	{
		Jump();
	}

	SetCurDirState(JumpDirState);

	if (PlayerState.PrevState == "SitLoop_Basic" ||
		PlayerState.PrevState == "SitMove_Basic" ||
		PlayerState.PrevState == "SitAttack_Basic" ||
		PlayerState.PrevState == "SitThrowGranade_Basic")
	{
		ChangeAnimation("JumpLookDownLoop");
	}
	else
	{
		ChangeAnimation("JumpLookDownLoop", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_JumpLookDown = true;
}

void Player::JumpLookDownLoop_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("Sit") == true)
	{
		ChangeState("JumpLookDownEnd");
	}

	if (KEYPRESS("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookDownLoop", true);

		ChangeState("JumpLookDownAttack");
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

		ChangeAnimation("JumpLookDownLoop", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpLookDownLoop_BasicLeave()
{
	m_JumpLookDown = false;
}

void Player::JumpLookDownEnd_BasicInit()
{
	ChangeAnimation("JumpLookDownEnd", ENUM_BODYTYPE::TOP);
	AniRenderTop->SetAnimationFrameIndex(82);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_JumpLookDown = true;
}

void Player::JumpLookDownEnd_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("JumpLookDownAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookDownEnd", true);

		ChangeState("JumpAttack");
	}

	if (TopAnimationEnd() == true &&
		KEYFREE("Sit") == true)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}
	else if (TopAnimationEnd() == true &&
			 KEYFREE("Sit") == true)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("JumpLookDownEnd", ENUM_BODYTYPE::TOP);
		AniRenderTop->SetAnimationFrameIndex(81);
	}
}

void Player::JumpLookDownEnd_BasicLeave()
{
	m_JumpLookDown = false;
}

void Player::JumpLookDownAttack_BasicInit()
{
	ChangeAnimation("JumpLookDownAttack", ENUM_BODYTYPE::BOTTOM);

	if (m_TopBodyAttack == false)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("JumpLookDownAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_AttackCancleAble = false;

	m_JumpLookDown = true;
}

void Player::JumpLookDownAttack_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (114 < AniRenderTop->GetAnimationFrameIndex())
	{
		if (m_AttackCancleAble == false)
		{
			m_AttackCancleAble = true;
		}

		if (m_ShootBullet == false)
		{
			CreateBullet(90.f);
		}
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("SitLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("SitRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookDownAttack", true);

		ChangeState("JumpLookDownAttack");
	}
	else if (KEYPRESS("LookUp") == true &&
			 KEYDOWN("Attack") == true &&
			 m_AttackCancleAble == true)
	{
		if (KEYPRESS("SitLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("SitRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookUpAttack", true);

		ChangeState("JumpLookUpAttack");
	}
	else if (KEYFREE("Sit") == true &&
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

		ChangeAnimation("JumpLookDownAttack", true);

		ChangeState("JumpAttack");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (TopAnimationEnd() == true)
	{
		SetCurDirState(JumpDirState);

		ChangeState("JumpLookDownEnd");
	}
}

void Player::JumpLookDownAttack_BasicLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownStart_BasicInit()
{
	ChangeAnimation("MoveJumpLookDownStart");

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_JumpLookDown = true;
}

void Player::MoveJumpLookDownStart_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveJumpLookDownAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpLookDownStart", true);

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

		ChangeAnimation("MoveJumpLookDownStart", true);

		ChangeState("JumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		SetCurDirState(JumpDirState);

		ChangeState("MoveJumpLookDownLoop");
	}
}

void Player::MoveJumpLookDownStart_BasicLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownLoop_BasicInit()
{
	if (PlayerState.PrevState == "SitMove_Basic")
	{
		Jump();
	}

	SetCurDirState(JumpDirState);

	if (PlayerState.PrevState == "SitMove_Basic")
	{
		ChangeAnimation("MoveJumpLookDownLoop");
	}
	else
	{
		ChangeAnimation("MoveJumpLookDownLoop", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_JumpLookDown = true;
}

void Player::MoveJumpLookDownLoop_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}
	if (KEYFREE("Sit") == true)
	{
		ChangeState("MoveJumpLookDownEnd");
	}

	if (KEYPRESS("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpLookDownLoop", true);

		ChangeState("MoveJumpLookDownAttack");
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

		ChangeAnimation("MoveJumpLookDownLoop", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::MoveJumpLookDownLoop_BasicLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownEnd_BasicInit()
{
	SetCurDirState(JumpDirState);

	ChangeAnimation("MoveJumpLookDownEnd", ENUM_BODYTYPE::TOP);
	AniRenderTop->SetAnimationFrameIndex(82);

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_JumpLookDown = true;
}

void Player::MoveJumpLookDownEnd_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveJumpLookDownAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpLookDownEnd", true);

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

		ChangeAnimation("MoveJumpLookDownEnd", true);

		ChangeState("JumpThrowGranade");
	}

	if (TopAnimationEnd() == true &&
		KEYFREE("Sit") == true)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}
	else if (TopAnimationEnd() == true &&
		KEYFREE("Sit") == true)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("MoveJumpLookDownEnd", ENUM_BODYTYPE::TOP);
		AniRenderTop->SetAnimationFrameIndex(81);
	}
}

void Player::MoveJumpLookDownEnd_BasicLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownAttack_BasicInit()
{
	if (m_TopBodyAttack == false)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("MoveJumpLookDownAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_AttackCancleAble = false;

	m_JumpLookDown = true;
}

void Player::MoveJumpLookDownAttack_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (114 < AniRenderTop->GetAnimationFrameIndex())
	{
		if (m_AttackCancleAble == false)
		{
			m_AttackCancleAble = true;
		}

		if (m_ShootBullet == false)
		{
			CreateBullet(90.f);
		}
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("SitLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("SitRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpLookDownAttack", true);

		ChangeState("MoveJumpLookDownAttack");
	}

	if (KEYFREE("Sit") == true &&
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

		ChangeAnimation("MoveJumpLookDownAttack", true);

		ChangeState("MoveJumpAttack");
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

		ChangeAnimation("MoveJumpLookDownAttack", true);

		ChangeState("JumpThrowGranade");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("MoveJumpLookDownEnd");
	}
}

void Player::MoveJumpLookDownAttack_BasicLeave()
{
	m_JumpLookDown = false;
}