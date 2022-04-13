#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::JumpLookDownStart_HeavyMachineGunInit()
{
	ChangeAnimation("JumpLookDownStart", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = false;

	m_JumpLookDown = true;
}

void Player::JumpLookDownStart_HeavyMachineGunState()
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
		ChangeState("JumpLookDownAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

		ChangeAnimation("JumpLookDownStart", true);

		ChangeState("JumpAttack");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("JumpLookDownLoop");
	}
}

void Player::JumpLookDownStart_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}

void Player::JumpLookDownLoop_HeavyMachineGunInit()
{
	if (PlayerState.PrevState == "SitLoop_HeavyMachineGun" ||
		PlayerState.PrevState == "SitMove_HeavyMachineGun" ||
		PlayerState.PrevState == "SitAttack_HeavyMachineGun" ||
		PlayerState.PrevState == "SitThrowGranade_HeavyMachineGun")
	{
		Jump();
	}

	SetCurDirState(JumpDirState);

	if (PlayerState.PrevState == "SitLoop_HeavyMachineGun" ||
		PlayerState.PrevState == "SitMove_HeavyMachineGun" ||
		PlayerState.PrevState == "SitAttack_HeavyMachineGun" ||
		PlayerState.PrevState == "SitThrowGranade_HeavyMachineGun")
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

void Player::JumpLookDownLoop_HeavyMachineGunState()
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

	if (KEYPRESS("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

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

void Player::JumpLookDownLoop_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}

void Player::JumpLookDownAttack_HeavyMachineGunInit()
{
	ChangeAnimation("JumpLookDownAttack", ENUM_BODYTYPE::BOTTOM);

	if (m_TopBodyAttack == false)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("JumpLookDownAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_HeavymachineGunAttackReserve = false;

	m_JumpLookDown = true;
}

void Player::JumpLookDownAttack_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 92)
	{
		AniRenderTop->SetAnimationFrameIndex(90);

		CreateHeavyMachineGunBullet(90.f);
	}
	else if (m_HeavyMachineGunShotCount == 1 &&
		AniRenderTop->GetAnimationFrameIndex() == 92)
	{
		CreateHeavyMachineGunBullet(90.f);
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		TopAnimationEnd() == true)
	{
		AniRenderTop->SetAnimationFrameIndex(92);

		CreateHeavyMachineGunBullet(90.f);
	}
	else if (m_HeavyMachineGunShotCount == 3 &&
		TopAnimationEnd() == true)
	{
		CreateHeavyMachineGunBullet(90.f);

		m_HeavyMachineGunShotCount = 0;
		if (m_HeavymachineGunAttackReserve == true)
		{
			m_TopBodyAttack = false;
			JumpDirState = CurDirState;
			SetCurDirState(JumpDirState);

			ChangeState("JumpLookDownAttack");
		}
		else
		{
			SetCurDirState(JumpDirState);

			ChangeState("JumpLookDownLoop");
		}
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}
	else if (KEYPRESS("LookUp") == true &&
		KEYDOWN("Attack") == true)
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
		m_HeavyMachineGunShotCount = 0;

		ChangeAnimation("JumpLookUpAttack", true);

		ChangeState("JumpLookUpAttack");
	}
	
	if (KEYFREE("Sit") == true )
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("JumpLookDownAttackUp");
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
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

		ChangeAnimation("JumpLookDownAttack", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpLookDownAttack_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}

void Player::JumpLookDownAttackUp_HeavyMachineGunInit()
{
	ChangeAnimation("JumpLookDownAttackUp", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_JumpLookDown = true;
}

void Player::JumpLookDownAttackUp_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 94)
	{
		CreateHeavyMachineGunBullet(80.f, GJHVector(40.f * (int)CurDirState, 50.f));
		CreateHeavyMachineGunBullet(57.f, GJHVector(70.f * (int)CurDirState, 30.f));
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		AniRenderTop->GetAnimationFrameIndex() == 95)
	{
		CreateHeavyMachineGunBullet(47.f, GJHVector(100.f * (int)CurDirState, -20.f));
		CreateHeavyMachineGunBullet(20.f, GJHVector(130.f * (int)CurDirState, -60.f));
	}

	if (KEYPRESS("SitLMove") == true ||
		KEYPRESS("SitRMove") == true ||
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

		ChangeAnimation("JumpLookDownAttack", true);

		ChangeState("JumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}

	if (AniRenderTop->GetAnimationName() == "Idle_HeavyMachineGun" &&
		KEYDOWN("Attack") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJumpAttack");
	}
}

void Player::JumpLookDownAttackUp_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownStart_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpLookDownStart");

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_JumpLookDown = true;
}

void Player::MoveJumpLookDownStart_HeavyMachineGunState()
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
		ChangeState("MoveJumpLookDownAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

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

void Player::MoveJumpLookDownStart_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownLoop_HeavyMachineGunInit()
{
	if (PlayerState.PrevState == "SitMove_HeavyMachineGun")
	{
		Jump();
	}

	SetCurDirState(JumpDirState);

	if (PlayerState.PrevState == "SitMove_HeavyMachineGun")
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

void Player::MoveJumpLookDownLoop_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
		return;
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
		ChangeState("MoveJumpLookDownLoop");
	}

	if (KEYPRESS("Attack") == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

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

		ChangeState("MoveJumpThrowGranade");
	}
}

void Player::MoveJumpLookDownLoop_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownAttack_HeavyMachineGunInit()
{
	if (m_TopBodyAttack == false)
	{
		SetCurDirState(JumpDirState);
		ChangeAnimation("MoveJumpLookDownAttack", ENUM_BODYTYPE::TOP);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_HeavymachineGunAttackReserve = false;

	m_JumpLookDown = true;
}

void Player::MoveJumpLookDownAttack_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 92)
	{
		AniRenderTop->SetAnimationFrameIndex(90);

		CreateHeavyMachineGunBullet(90.f);
	}
	else if (m_HeavyMachineGunShotCount == 1 &&
		AniRenderTop->GetAnimationFrameIndex() == 92)
	{
		CreateHeavyMachineGunBullet(90.f);
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		TopAnimationEnd() == true)
	{
		AniRenderTop->SetAnimationFrameIndex(92);

		CreateHeavyMachineGunBullet(90.f);
	}
	else if (m_HeavyMachineGunShotCount == 3 &&
		TopAnimationEnd() == true)
	{
		CreateHeavyMachineGunBullet(90.f);

		m_HeavyMachineGunShotCount = 0;
		if (m_HeavymachineGunAttackReserve == true)
		{
			m_TopBodyAttack = false;
			JumpDirState = CurDirState;

			ChangeState("MoveJumpLookDownAttack");
		}
		else
		{
			ChangeState("MoveJumpLookDownLoop");
		}
	}

	if (KEYPRESS("Sit") == true &&
		KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYFREE("Sit") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJumpLookDownAttackUp");
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

		ChangeAnimation("MoveJumpLookDownAttack", true);

		ChangeState("MoveJumpThrowGranade");
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

		ChangeState("MoveJumpLookDownLoop");
	}
}

void Player::MoveJumpLookDownAttack_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}

void Player::MoveJumpLookDownAttackUp_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpLookDownAttackUp", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = false;

	m_JumpLookDown = true;
}

void Player::MoveJumpLookDownAttackUp_HeavyMachineGunState()
{
	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 94)
	{
		CreateHeavyMachineGunBullet(80.f, GJHVector(40.f * (int)CurDirState, 50.f));
		CreateHeavyMachineGunBullet(57.f, GJHVector(70.f * (int)CurDirState, 30.f));
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		AniRenderTop->GetAnimationFrameIndex() == 95)
	{
		CreateHeavyMachineGunBullet(47.f, GJHVector(100.f * (int)CurDirState, -20.f));
		CreateHeavyMachineGunBullet(20.f, GJHVector(130.f * (int)CurDirState, -60.f));
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

		ChangeAnimation("MoveJumpLookDownAttack", true);

		ChangeState("MoveJumpThrowGranade");
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
		m_HeavyMachineGunShotCount = 0;

		ChangeAnimation("Idle", ENUM_BODYTYPE::TOP);
	}

	if (AniRenderTop->GetAnimationName() == "Idle_HeavyMachineGun" &&
		KEYDOWN("Attack") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJumpAttack");
	}
}

void Player::MoveJumpLookDownAttackUp_HeavyMachineGunLeave()
{
	m_JumpLookDown = false;
}