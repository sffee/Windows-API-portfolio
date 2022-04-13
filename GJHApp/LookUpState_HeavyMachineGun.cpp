#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::LookUpStart_HeavyMachineGunInit()
{
	ChangeAnimation("LookUpStart");

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::LookUpStart_HeavyMachineGunState()
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
		ChangeState("LookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
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

void Player::LookUpStart_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::LookUpLoop_HeavyMachineGunInit()
{
	ChangeAnimation("LookUpLoop");

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::LookUpLoop_HeavyMachineGunState()
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

void Player::LookUpLoop_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::LookUpEnd_HeavyMachineGunInit()
{
	ChangeAnimation("LookUpEnd");
	AniRenderTop->SetAnimationFrameIndex(74);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;
}

void Player::LookUpEnd_HeavyMachineGunState()
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
		ChangeState("LookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
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

void Player::LookUpEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::LookUpAttack_HeavyMachineGunInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("LookUpAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_HeavymachineGunAttackReserve = false;

	m_LookUp = true;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::LookUpAttack_HeavyMachineGunState()
{
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
			ChangeState("LookUpAttack");
		}
		else
		{
			ChangeState("LookUpAttackEnd");
		}
	}
	else if (TopAnimationEnd() == true)
	{
		ChangeState("LookUpAttackEnd");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("MoveLookUpAttack");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYFREE("LookUp") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("LookUpAttackDown");
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

		ChangeAnimation("LookUpAttack", true);

		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		if (KEYPRESS("LookUp") == true)
		{
			ChangeState("JumpLookUpAttack");
		}
		else
		{
			ChangeState("Jump");
		}
	}
}

void Player::LookUpAttack_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::LookUpAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("LookUpAttackEnd", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_LookUp = true;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::LookUpAttackEnd_HeavyMachineGunState()
{
	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("MoveLookUpLoop");
	}

	if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		ChangeState("LookUpLoop");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		ChangeState("LookUpEnd");
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

		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		ChangeState("Jump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("LookUpLoop");
	}
}

void Player::LookUpAttackEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::LookUpAttackDown_HeavyMachineGunInit()
{
	ChangeAnimation("LookUpAttackDown", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_LookUp = true;

	ChangeAnimation("Idle", ENUM_BODYTYPE::BOTTOM);
}

void Player::LookUpAttackDown_HeavyMachineGunState()
{
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

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		ChangeState("MoveLookUpAttackDown");
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

		ChangeAnimation("LookUpAttack", true);

		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		m_HeavyMachineGunShotCount = 0;

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
		m_HeavyMachineGunShotCount = 0;

		ChangeState("Idle");
	}
}

void Player::LookUpAttackDown_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpStart_HeavyMachineGunInit()
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

void Player::MoveLookUpStart_HeavyMachineGunState()
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
		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
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

void Player::MoveLookUpStart_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpLoop_HeavyMachineGunInit()
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

void Player::MoveLookUpLoop_HeavyMachineGunState()
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

void Player::MoveLookUpLoop_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpEnd_HeavyMachineGunInit()
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

void Player::MoveLookUpEnd_HeavyMachineGunState()
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
		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
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

void Player::MoveLookUpEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpAttack_HeavyMachineGunInit()
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

	m_HeavymachineGunAttackReserve = false;

	m_LookUp = true;
}

void Player::MoveLookUpAttack_HeavyMachineGunState()
{
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
			ChangeState("MoveLookUpAttack");
		}
		else
		{
			ChangeState("MoveLookUpAttackEnd");
		}
	}
	else if (TopAnimationEnd() == true)
	{
		ChangeState("MoveLookUpAttackEnd");
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
		KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYFREE("LookUp") == true)
	{
		m_TopBodyAttack = false;
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveLookUpAttackDown");
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

		ChangeAnimation("MoveLookUpAttack", true);

		ChangeState("MoveThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		if (KEYPRESS("LookUp") == true)
		{
			ChangeState("MoveJumpLookUpAttack");
		}
		else
		{
			ChangeState("MoveJumpAttack");
		}
	}
}

void Player::MoveLookUpAttack_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("MoveLookUpAttackEnd", ENUM_BODYTYPE::TOP);

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveLookUpAttackEnd_HeavyMachineGunState()
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
		ChangeState("LookUpLoop");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true)
	{
		m_TopBodyAttack = false;

		ChangeState("MoveLookUpAttack");
	}

	if (KEYFREE("LookUpLMove") == true &&
		KEYFREE("LookUpRMove") == true &&
		KEYDOWN("Attack") == true)
	{
		m_TopBodyAttack = false;

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

void Player::MoveLookUpAttackEnd_HeavyMachineGunLeave()
{
	m_LookUp = false;
}

void Player::MoveLookUpAttackDown_HeavyMachineGunInit()
{
	ChangeAnimation("MoveLookUpAttackDown", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_LookUp = true;
}

void Player::MoveLookUpAttackDown_HeavyMachineGunState()
{
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

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true ||
		KEYPRESS("LMove") == true ||
		KEYPRESS("RMove") == true)
	{
		WalkMove();
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

		ChangeAnimation("MoveLookUpAttack", true);

		ChangeState("MoveThrowGranade");
	}

	if (KEYPRESS("Jump") == true)
	{
		m_HeavyMachineGunShotCount = 0;

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
		m_HeavyMachineGunShotCount = 0;

		ChangeState("Move");
	}
}

void Player::MoveLookUpAttackDown_HeavyMachineGunLeave()
{
	m_LookUp = false;
}