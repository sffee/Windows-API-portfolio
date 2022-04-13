#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::JumpLookUpStart_HeavyMachineGunInit()
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

void Player::JumpLookUpStart_HeavyMachineGunState()
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
		ChangeState("JumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

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

void Player::JumpLookUpStart_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpLoop_HeavyMachineGunInit()
{
	SetCurDirState(JumpDirState);
	ChangeAnimation("JumpLookUpLoop", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::JumpLookUpLoop_HeavyMachineGunState()
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

void Player::JumpLookUpLoop_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpEnd_HeavyMachineGunInit()
{
	ChangeAnimation("JumpLookUpEnd", ENUM_BODYTYPE::TOP);
	AniRenderTop->SetAnimationFrameIndex(74);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::JumpLookUpEnd_HeavyMachineGunState()
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
		ChangeState("JumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

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
}

void Player::JumpLookUpEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpAttack_HeavyMachineGunInit()
{
	if (PlayerState.PrevState == "LookUpAttack_HeavyMachineGun")
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

	m_HeavymachineGunAttackReserve = false;

	m_LookUp = true;
}

void Player::JumpLookUpAttack_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 81)
	{
		AniRenderTop->SetAnimationFrameIndex(79);

		CreateHeavyMachineGunBullet(-90.f);
	}
	else if (m_HeavyMachineGunShotCount == 1 &&
		AniRenderTop->GetAnimationFrameIndex() == 81)
	{
		CreateHeavyMachineGunBullet(-90.f);
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		TopAnimationEnd() == true)
	{
		AniRenderTop->SetAnimationFrameIndex(81);

		CreateHeavyMachineGunBullet(-90.f);
	}
	else if (m_HeavyMachineGunShotCount == 3 &&
		TopAnimationEnd() == true)
	{
		CreateHeavyMachineGunBullet(-90.f);

		m_HeavyMachineGunShotCount = 0;
		if (m_HeavymachineGunAttackReserve == true)
		{
			m_TopBodyAttack = false;
			JumpDirState = CurDirState;
			SetCurDirState(JumpDirState);

			ChangeState("JumpLookUpAttack");
		}
		else
		{
			SetCurDirState(JumpDirState);

			ChangeState("JumpLookUpAttackEnd");
		}
	}
	else if (TopAnimationEnd() == true)
	{
		ChangeState("JumpLookUpAttackEnd");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYFREE("LookUp") == true)
	{
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeState("JumpLookUpAttackDown");
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
		m_HeavyMachineGunShotCount = 0;

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
}

void Player::JumpLookUpAttack_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("JumpLookUpAttackEnd", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::JumpLookUpAttackEnd_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
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

		ChangeAnimation("JumpLookUpAttack", true);

		ChangeState("JumpLookUpAttack");
	}
	else if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true)
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

		ChangeAnimation("JumpLookDownAttack", true);

		ChangeState("JumpLookDownAttack");
	}
	else if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true)
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

		ChangeAnimation("JumpLookUpAttack", true);

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
		ChangeState("JumpLookUpLoop");
	}
}

void Player::JumpLookUpAttackEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::JumpLookUpAttackDown_HeavyMachineGunInit()
{
	ChangeAnimation("JumpLookUpAttackDown");

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::JumpLookUpAttackDown_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 83)
	{
		CreateHeavyMachineGunBullet(-82.f, GJHVector(40.f * (int)CurDirState, 30.f));
		CreateHeavyMachineGunBullet(-52.f, GJHVector(60.f * (int)CurDirState, 80.f));
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		AniRenderTop->GetAnimationFrameIndex() == 84)
	{
		CreateHeavyMachineGunBullet(-22.f, GJHVector(50.f * (int)CurDirState, 130.f));
		CreateHeavyMachineGunBullet(-10.f, GJHVector(40.f * (int)CurDirState, 170.f));
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
		m_HeavyMachineGunShotCount = 0;

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
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}

	if (AniRenderTop->GetAnimationName() == "Idle_HeavyMachineGun" &&
		KEYDOWN("Attack") == true)
	{
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeState("JumpAttack");
	}
}

void Player::JumpLookUpAttackDown_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpStart_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpLookUpStart");

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpStart_HeavyMachineGunState()
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
		ChangeState("MoveJumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

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

void Player::MoveJumpLookUpStart_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpLoop_HeavyMachineGunInit()
{
	ChangeAnimation("JumpLookUpLoop", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpLoop_HeavyMachineGunState()
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

void Player::MoveJumpLookUpLoop_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpEnd_HeavyMachineGunInit()
{
	SetCurDirState(JumpDirState);

	ChangeAnimation("MoveJumpLookUpEnd", ENUM_BODYTYPE::TOP);
	AniRenderTop->SetAnimationFrameIndex(74);

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpEnd_HeavyMachineGunState()
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
		ChangeState("MoveJumpLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

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

void Player::MoveJumpLookUpEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpAttack_HeavyMachineGunInit()
{
	if (PlayerState.PrevState == "MoveLookUpAttack_HeavyMachineGun")
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

	m_HeavymachineGunAttackReserve = false;

	m_LookUp = true;
}

void Player::MoveJumpLookUpAttack_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 81)
	{
		AniRenderTop->SetAnimationFrameIndex(79);

		CreateHeavyMachineGunBullet(-90.f);
	}
	else if (m_HeavyMachineGunShotCount == 1 &&
		AniRenderTop->GetAnimationFrameIndex() == 81)
	{
		CreateHeavyMachineGunBullet(-90.f);
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		TopAnimationEnd() == true)
	{
		AniRenderTop->SetAnimationFrameIndex(81);

		CreateHeavyMachineGunBullet(-90.f);
	}
	else if (m_HeavyMachineGunShotCount == 3 &&
		TopAnimationEnd() == true)
	{
		CreateHeavyMachineGunBullet(-90.f);

		m_HeavyMachineGunShotCount = 0;
		if (m_HeavymachineGunAttackReserve == true)
		{
			m_TopBodyAttack = false;
			JumpDirState = CurDirState;
			m_HeavyMachineGunShotCount = 0;

			ChangeState("MoveJumpLookUpAttack");
		}
		else
		{
			SetCurDirState(JumpDirState);

			ChangeState("MoveJumpLookUpAttackEnd");
		}
	}
	else if (TopAnimationEnd() == true)
	{
		ChangeState("MoveJumpLookUpAttackEnd");
	}

	if (KEYFREE("LookUp") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJumpLookUpAttackDown");
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
		m_HeavyMachineGunShotCount = 0;

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
}

void Player::MoveJumpLookUpAttack_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpLookUpAttackEnd", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpAttackEnd_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
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

		ChangeAnimation("MoveJumpLookUpAttack", true);

		ChangeState("MoveJumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true)
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

void Player::MoveJumpLookUpAttackEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveJumpLookUpAttackDown_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpLookUpAttackDown", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveJumpLookUpAttackDown_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 83)
	{
		CreateHeavyMachineGunBullet(-82.f, GJHVector(40.f * (int)CurDirState, 30.f));
		CreateHeavyMachineGunBullet(-52.f, GJHVector(60.f * (int)CurDirState, 80.f));
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		AniRenderTop->GetAnimationFrameIndex() == 84)
	{
		CreateHeavyMachineGunBullet(-22.f, GJHVector(50.f * (int)CurDirState, 130.f));
		CreateHeavyMachineGunBullet(-10.f, GJHVector(40.f * (int)CurDirState, 170.f));
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
		m_HeavyMachineGunShotCount = 0;

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
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}

	if (AniRenderTop->GetAnimationName() == "Idle_HeavyMachineGun" &&
		KEYDOWN("Attack") == true)
	{
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeState("MoveJumpAttack");
	}
}

void Player::MoveJumpLookUpAttackDown_HeavyMachineGunLeave()
{
	m_LookUp = false;
}