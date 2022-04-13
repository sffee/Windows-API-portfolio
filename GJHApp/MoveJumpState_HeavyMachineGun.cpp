#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::MoveJump_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJump");

	if (m_Falling == false)
	{
		Jump();
	}

	m_Falling = false;

	m_TopBodyAttack = false;
}

void Player::MoveJump_HeavyMachineGunState()
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

	if (KEYDOWN("Attack") == true)
	{
		if (KEYPRESS("JumpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("JumpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

		ChangeAnimation("MoveJump", true);

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

		ChangeAnimation("MoveJump", true);

		ChangeState("MoveJumpThrowGranade");
	}

	if (KEYPRESS("LookUp") == true)
	{
		ChangeState("MoveJumpLookUpStart");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("MoveJumpLookDownStart");
	}
}

void Player::MoveJumpAttack_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpAttack", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;

	m_AttackCancleAble = false;
	m_HeavymachineGunAttackReserve = false;
}

void Player::MoveJumpAttack_HeavyMachineGunState()
{
	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 72)
	{
		AniRenderTop->SetAnimationFrameIndex(70);

		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 1 &&
		AniRenderTop->GetAnimationFrameIndex() == 72)
	{
		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		TopAnimationEnd() == true)
	{
		AniRenderTop->SetAnimationFrameIndex(72);

		CreateHeavyMachineGunBullet(0.f);
	}
	else if (m_HeavyMachineGunShotCount == 3 &&
		TopAnimationEnd() == true)
	{
		CreateHeavyMachineGunBullet(0.f);

		m_HeavyMachineGunShotCount = 0;
		if (m_HeavymachineGunAttackReserve == true)
		{
			m_TopBodyAttack = false;
			JumpDirState = CurDirState;
			SetCurDirState(JumpDirState);

			ChangeState("MoveJumpAttack");
		}
		else
		{
			SetCurDirState(JumpDirState);

			ChangeState("MoveJumpAttackEnd");
		}
	}

	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

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
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeState("MoveJumpAttackUp");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		if (KEYPRESS("JumpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("JumpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYPRESS("Sit") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJumpAttackDown");
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

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpThrowGranade");
	}
}

void Player::MoveJumpAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpAttackEnd", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
}

void Player::MoveJumpAttackEnd_HeavyMachineGunState()
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

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true)
	{
		if (KEYPRESS("JumpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("JumpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpAttack");
	}

	if (KEYPRESS("SitAttack") == true)
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

		ChangeAnimation("MoveJumpAttack", true);

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

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpThrowGranade");
	}
}

void Player::MoveJumpThrowGranade_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpThrowGranade", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::MoveJumpThrowGranade_HeavyMachineGunState()
{
	if (177 < AniRenderTop->GetAnimationFrameIndex())
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

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		if (KEYPRESS("JumpLMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::LEFT);
		}
		else if (KEYPRESS("JumpRMove") == true)
		{
			SetCurDirState(ENUM_DIRECTION::RIGHT);
		}

		JumpDirState = CurDirState;

		m_TopBodyAttack = false;

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpAttack");
	}

	if (KEYPRESS("SitAttack") == true &&
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

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpLookDownAttack");
	}

	if (KEYDOWN("Granade") == true &&
		m_AttackCancleAble == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		SetCurDirState(JumpDirState);

		ChangeAnimation("MoveJumpThrowGranade", true);

		ChangeState("MoveJumpThrowGranade");
	}
}

void Player::MoveJumpAttackUp_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpAttackUp", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
}

void Player::MoveJumpAttackUp_HeavyMachineGunState()
{
	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 77)
	{
		CreateHeavyMachineGunBullet(-10.f, GJHVector(-40.f * (int)CurDirState, -60.f));
		CreateHeavyMachineGunBullet(-22.f, GJHVector(-50.f * (int)CurDirState, -80.f));
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		AniRenderTop->GetAnimationFrameIndex() == 78)
	{
		CreateHeavyMachineGunBullet(-52.f, GJHVector(-60.f * (int)CurDirState, -130.f));
		CreateHeavyMachineGunBullet(-82.f, GJHVector(-100.f * (int)CurDirState, -170.f));
	}

	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
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

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeState("MoveJumpLookUpLoop");
	}
}

void Player::MoveJumpAttackDown_HeavyMachineGunInit()
{
	ChangeAnimation("MoveJumpAttackDown", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
}

void Player::MoveJumpAttackDown_HeavyMachineGunState()
{
	if (m_HeavyMachineGunShotCount == 0 &&
		AniRenderTop->GetAnimationFrameIndex() == 88)
	{
		CreateHeavyMachineGunBullet(20.f, GJHVector(40.f * (int)CurDirState, 30.f));
		CreateHeavyMachineGunBullet(47.f, GJHVector(10.f * (int)CurDirState, 80.f));
	}
	else if (m_HeavyMachineGunShotCount == 2 &&
		AniRenderTop->GetAnimationFrameIndex() == 89)
	{
		CreateHeavyMachineGunBullet(57.f, GJHVector(-30.f * (int)CurDirState, 130.f));
		CreateHeavyMachineGunBullet(80.f, GJHVector(-70.f * (int)CurDirState, 170.f));
	}

	if (m_Jump == false)
	{
		m_HeavyMachineGunShotCount = 0;

		SetCurDirState(JumpDirState);

		ChangeState("StopMove");
	}

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
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

		SetCurDirState(JumpDirState);

		ChangeAnimation("MoveJumpAttack", true);

		ChangeState("MoveJumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJumpLookDownLoop");
	}
}