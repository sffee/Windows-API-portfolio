#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::Jump_HeavyMachineGunInit()
{
	ChangeAnimation("Jump");

	if (m_Falling == false)
	{
		Jump();
	}

	m_Falling = false;

	m_TopBodyAttack = false;
}

void Player::Jump_HeavyMachineGunState()
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

	if (KEYPRESS("LookUp") == true)
	{
		ChangeState("JumpLookUpStart");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("JumpLookDownStart");
	}

	if (KEYDOWN("Attack") == true)
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

		ChangeAnimation("Jump", true);

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

		ChangeAnimation("Jump", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpAttack_HeavyMachineGunInit()
{
	ChangeAnimation("JumpAttack", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_HeavymachineGunAttackReserve = false;
}

void Player::JumpAttack_HeavyMachineGunState()
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

			ChangeState("JumpAttack");
		}
		else
		{
			SetCurDirState(JumpDirState);

			ChangeState("JumpAttackEnd");
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

		ChangeState("JumpAttackUp");
	}

	if (KEYFREE("LookUp") == true &&
		KEYFREE("Sit") == true &&
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

		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYPRESS("Sit") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("JumpAttackDown");
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("JumpAttackEnd", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
}

void Player::JumpAttackEnd_HeavyMachineGunState()
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYFREE("Sit") == true &&
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpAttack");
	}

	if (KEYPRESS("Sit") == true &&
		KEYFREE("LookUp") == true &&
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

		ChangeAnimation("JumpAttack", true);

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
		SetCurDirState(JumpDirState);

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpThrowGranade");
	}
}

void Player::JumpAttackUp_HeavyMachineGunInit()
{
	ChangeAnimation("JumpAttackUp", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
}

void Player::JumpAttackUp_HeavyMachineGunState()
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

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("JumpLookUpLoop");
	}
}

void Player::JumpThrowGranade_HeavyMachineGunInit()
{
	ChangeAnimation("JumpThrowGranade", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_AttackCancleAble = false;
}

void Player::JumpAttackDown_HeavyMachineGunInit()
{
	ChangeAnimation("JumpAttackDown", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
}

void Player::JumpAttackDown_HeavyMachineGunState()
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
		m_HeavyMachineGunShotCount = 0;

		ChangeAnimation("JumpAttack", true);

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
		m_HeavyMachineGunShotCount = 0;
		SetCurDirState(JumpDirState);

		ChangeAnimation("JumpAttack", true);

		ChangeState("JumpThrowGranade");
	}

	if (TopAnimationEnd() == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("JumpLookDownLoop");
	}
}

void Player::JumpThrowGranade_HeavyMachineGunState()
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

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpLookUpAttack");
	}

	if (KEYFREE("LookUp") == true &&
		KEYFREE("Sit") == true &&
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

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpAttack");
	}

	if (KEYPRESS("Sit") == true &&
		KEYFREE("LookUp") == true &&
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

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpLookDownAttack");
	}

	if (KEYDOWN("Granade") == true &&
		m_AttackCancleAble == true)
	{
		JumpDirState = CurDirState;

		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeAnimation("JumpThrowGranade", true);

		ChangeState("JumpThrowGranade");
	}
}