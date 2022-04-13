#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::JumpLookUpStart_BasicInit()
{
	if (m_LookUp == true)
	{
		Jump();
	}
	else
	{
		ChangeAnimation("JumpLookUpStart");
	}

	m_TopBodyAttack = false;

	m_Jump = true;
	m_LookUp = true;
}

void Player::JumpLookUpStart_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("JumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookUpStart", true);

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

		ChangeAnimation("JumpLookUpStart", true);

		ChangeState("JumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		SetCurDirState(JumpDirState);
		ChangeState("JumpLookUpLoop");
	}
}

void Player::JumpLookUpStart_BasicLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpLoop_BasicInit()
{
	SetCurDirState(JumpDirState);
	ChangeAnimation("JumpLookUpLoop", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::JumpLookUpLoop_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LookUp") == true)
	{
		ChangeState("JumpLookUpEnd");
	}

	if (KEYPRESS("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookUpLoop", true);

		ChangeState("JumpLookUpAttack");
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

		ChangeAnimation("JumpLookUpLoop", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpLookUpLoop_BasicLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpEnd_BasicInit()
{
	ChangeAnimation("JumpLookUpEnd", ENUM_BODYTYPE::TOP);
	AniRenderTop->SetAnimationFrameIndex(74);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::JumpLookUpEnd_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("JumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("JumpLookUpEnd", true);

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

		ChangeAnimation("JumpLookUpEnd", true);

		ChangeState("JumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}
}

void Player::JumpLookUpEnd_BasicLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpAttack_BasicInit()
{
	if (PlayerState.PrevState == "LookUpAttack_Basic")	
	{
		Jump();

		ChangeAnimation("JumpLookUpAttack", ENUM_BODYTYPE::BOTTOM);
	}

	if (m_TopBodyAttack == false)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("JumpLookUpAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_AttackCancleAble = false;

	m_LookUp = true;
}

void Player::JumpLookUpAttack_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

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

		ChangeAnimation("JumpLookUpAttack", true);

		ChangeState("JumpLookUpAttack");
	}
	else if (KEYPRESS("Sit") == true &&
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

		ChangeAnimation("JumpLookDownAttack", true);

		ChangeState("JumpLookDownAttack");
	}
	else if (KEYFREE("LookUp") == true &&
			 KEYDOWN("Attack") == true &&
			 m_AttackCancleAble == true)
	{
		if(KEYPRESS("LMove") == true)
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

		ChangeAnimation("JumpLookUpAttack", true);

		ChangeState("JumpAttack");
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

		ChangeAnimation("JumpLookUpAttack", true);

		ChangeState("JumpThrowGranade");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("JumpLookUpEnd");
	}
}

void Player::JumpLookUpAttack_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpStart_BasicInit()
{
	ChangeAnimation("MoveJumpLookUpStart");

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpStart_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveJumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpLookUpStart", true);

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

		ChangeAnimation("MoveJumpLookUpStart", true);

		ChangeState("MoveJumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		SetCurDirState(JumpDirState);
		ChangeState("MoveJumpLookUpLoop");
	}
}

void Player::MoveJumpLookUpStart_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpLoop_BasicInit()
{
	ChangeAnimation("JumpLookUpLoop", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpLoop_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}
	if (KEYFREE("LookUp") == true)
	{
		ChangeState("MoveJumpLookUpEnd");
	}

	if (KEYPRESS("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpLookUpLoop", true);

		ChangeState("MoveJumpLookUpAttack");
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

		ChangeAnimation("MoveJumpLookUpLoop", true);

		ChangeState("MoveJumpThrowGranade");
	}
}

void Player::MoveJumpLookUpLoop_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpEnd_BasicInit()
{
	SetCurDirState(JumpDirState);

	ChangeAnimation("MoveJumpLookUpEnd", ENUM_BODYTYPE::TOP);
	AniRenderTop->SetAnimationFrameIndex(74);

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpEnd_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_ShootBullet = false;

		ChangeState("MoveJumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ShootBullet = false;

		ChangeAnimation("MoveJumpLookUpEnd", true);

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

		ChangeAnimation("MoveJumpLookUpEnd", true);

		ChangeState("MoveJumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}
}

void Player::MoveJumpLookUpEnd_BasicLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpAttack_BasicInit()
{
	if (PlayerState.PrevState == "MoveLookUpAttack")
	{
		Jump();

		ChangeAnimation("MoveJumpLookUpAttack", ENUM_BODYTYPE::BOTTOM);
	}

	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("MoveJumpLookUpAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_AttackCancleAble = false;

	m_LookUp = true;
}

void Player::MoveJumpLookUpAttack_BasicState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

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

		ChangeAnimation("MoveJumpLookUpAttack", true);

		ChangeState("MoveJumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
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

		ChangeAnimation("MoveJumpLookUpAttack", true);

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

		ChangeAnimation("MoveJumpLookUpAttack", true);

		ChangeState("MoveJumpThrowGranade");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("MoveJumpLookUpEnd");
	}
}

void Player::MoveJumpLookUpAttack_BasicLeave()
{
	m_LookUp = false;
}