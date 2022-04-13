#include "Player.h"
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHRenderer.h>
#include "define.h"

void Player::Move_HeavyMachineGunInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	ChangeAnimation("Move");
}

void Player::Move_HeavyMachineGunState()
{
	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LMove") == true
		&& KEYFREE("RMove") == true)
	{
		ChangeState("StopMove");
	}

	if (KEYPRESS("LookUpLMove") == true ||
		KEYPRESS("LookUpRMove") == true)
	{
		ChangeState("MoveLookUpStart");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("SitStart");
	}

	if (KEYPRESS("Jump") == true)
	{
		ChangeState("MoveJump");
	}

	if (KEYDOWN("Attack") == true)
	{
		ChangeState("MoveAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_ThrowGranade = false;

		ChangeState("MoveThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		ChangeState("MoveJump");
	}
}

void Player::StopMove_HeavyMachineGunInit()
{
	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	ChangeAnimation("StopMove");
}

void Player::StopMove_HeavyMachineGunState()
{
	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		ChangeState("Move");
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
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("SitStart");
	}

	if (KEYDOWN("Jump") == true)
	{
		ChangeState("Jump");
	}

	if (AnimationEnd() == true)
	{
		ChangeState("Idle");
	}
}

void Player::MoveAttack_HeavyMachineGunInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("MoveAttack", ENUM_BODYTYPE::TOP);
	}

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_HeavymachineGunAttackReserve = false;
}

void Player::MoveAttack_HeavyMachineGunState()
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
			ChangeState("MoveAttack");
		}
		else
		{
			ChangeState("MoveAttackEnd");
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
		ChangeState("IdleAttack");
	}

	if (KEYPRESS("Sit") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("SitStart");
	}

	if (KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true)
	{
		m_TopBodyAttack = false;
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveAttackUp");
	}
	
	if (KEYDOWN("Attack") == true)
	{
		m_HeavymachineGunAttackReserve = true;
	}

	if (KEYDOWN("Granade") == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJump");
	}
}

void Player::MoveAttackEnd_HeavyMachineGunInit()
{
	ChangeAnimation("MoveAttackEnd", ENUM_BODYTYPE::TOP);

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = false;
	m_BottomBodyMove = true;

	m_AttackCancleAble = false;
}

void Player::MoveAttackEnd_HeavyMachineGunState()
{
	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LMove") == true
		&& KEYFREE("RMove") == true)
	{
		ChangeState("StopMove");
	}

	if (KEYPRESS("Sit") == true)
	{
		ChangeState("SitStart");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true)
	{
		m_TopBodyAttack = false;

		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true)
	{
		m_TopBodyAttack = false;

		ChangeState("MoveAttack");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeState("MoveThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		ChangeState("MoveJump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Move");
	}
}

void Player::MoveAttackUp_HeavyMachineGunInit()
{
	ChangeAnimation("MoveAttackUp", ENUM_BODYTYPE::TOP);

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_HeavymachineGunAttackReserve = false;
}

void Player::MoveAttackUp_HeavyMachineGunState()
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

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYPRESS("Sit") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("SitStart");
	}

	if (KEYDOWN("Granade") == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveJump");
	}

	if (TopAnimationEnd() == true)
	{
		m_HeavyMachineGunShotCount = 0;

		ChangeState("MoveLookUpLoop");
	}
}

void Player::MoveThrowGranade_HeavyMachineGunInit()
{
	if (m_TopBodyAttack == false)
	{
		ChangeAnimation("MoveThrowGranade", ENUM_BODYTYPE::TOP);
	}

	if (m_BottomBodyMove == false)
	{
		ChangeAnimation("Move", ENUM_BODYTYPE::BOTTOM);
	}

	m_TopBodyAttack = true;
	m_BottomBodyMove = true;

	m_AttackCancleAble = false;
}

void Player::MoveThrowGranade_HeavyMachineGunState()
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

	if (KEYPRESS("LMove") == true
		|| KEYPRESS("RMove") == true)
	{
		WalkMove();
	}

	if (KEYFREE("LMove") == true
		&& KEYFREE("RMove") == true)
	{
		ChangeState("ThrowGranade");
	}

	if (KEYPRESS("Sit") == true && m_AttackCancleAble == true)
	{
		ChangeState("SitStart");
	}

	if ((KEYPRESS("LookUpLMove") == true || KEYPRESS("LookUpRMove") == true) &&
		KEYDOWN("Attack") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;

		ChangeState("MoveLookUpAttack");
	}
	else if (KEYDOWN("Attack") == true && m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;

		ChangeState("MoveAttack");
	}

	if (KEYDOWN("Granade") == true &&
		m_AttackCancleAble == true)
	{
		m_TopBodyAttack = false;
		m_ThrowGranade = false;

		ChangeState("ThrowGranade");
	}

	if (KEYDOWN("JumpLMove") == true ||
		KEYDOWN("JumpRMove") == true)
	{
		ChangeState("MoveJump");
	}

	if (TopAnimationEnd() == true)
	{
		ChangeState("Move");
	}
}