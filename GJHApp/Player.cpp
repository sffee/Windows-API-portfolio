#include "Player.h"
#include <GJHGameEngineScene.h>
#include <GJHGameEngineWindow.h>
#include <GJHResourcesManager.h>
#include <GJHSceneManager.h>
#include <GJHRenderer.h>
#include <GJHGameEngineTime.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHCollision.h>
#include "PlayerBullet_Basic.h"
#include "PlayerBullet_MachineGun.h"
#include "PlayerGranade.h"
#include "define.h"
#include <GJHGameEngineSound.h>
#include "GJHCameraManager.h"
#include "Weapon.h"
#include "Phase2Manager.h"
#include "UI.h"

//const float Player::MOVESPEED = 1000.f;
const float Player::MOVESPEED = 400.f;
const float Player::SITMOVESPEED = 100.f;
int Player::m_Score = 0;
int Player::m_GranadeCount = 10;
int Player::m_Life = 2;
Weapon* Player::m_Weapon = new Weapon();

Player::~Player()
{
	SAFE_DELETE(m_Weapon);
}

void Player::Start()
{
	ObjectBase::m_Player = this;
	m_IsPlayer = true;

	{
		m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, -70 }, { 80, 130 }, ContentsEnum::COLTYPE::PLAYER);
	}

	AniRenderTop = CreateRender({ 512, 512 }, "Eri_Kasamoto(Right).bmp", (int)ContentsEnum::RENDERORDER::PLAYER + 1);
	AniRenderBottom = CreateRender({ 512, 512 }, "Eri_Kasamoto(Right).bmp", ContentsEnum::RENDERORDER::PLAYER);
	AniRenderParachute = CreateRender({ 512, 512 }, "Parachute.bmp", (int)ContentsEnum::RENDERORDER::PLAYER - 1);
	AniRenderParachute->SetAddActorPivot({ -10, -100.f });

	m_AniRender = AniRenderTop;

	CreateAnimation("Idle_Basic", 0, 3, 4, 4, 0.12f, true, true, true, true);
	CreateAnimation("Move_Basic", 9, 20, 25, 36, 0.05f);
	CreateAnimation("StopMove_Basic", -1, -1, 37, 40, 0.05f, false, false, true, true);
	CreateAnimation("IdleAttack_Basic", 102, 111, 4, 4, 0.04f, false, false);
	CreateAnimation("MoveAttack_Basic", 102, 111, 25, 36, 0.04f, false, true);
	CreateAnimation("LookUpStart_Basic", 73, 74, 4, 4, 0.12f, false, false);
	CreateAnimation("LookUpLoop_Basic", 75, 78, 4, 4, 0.12f, true, true, true);
	CreateAnimation("LookUpEnd_Basic", 73, 74, 4, 4, 0.12f, false, false, true);
	CreateAnimation("LookUpAttack_Basic", 112, 121, 4, 4, 0.04f, false, false);
	CreateAnimation("MoveLookUpStart_Basic", 73, 74, 25, 36, 0.12f, false, true);
	CreateAnimation("MoveLookUpLoop_Basic", 75, 78, 25, 36, 0.12f, true, true, true);
	CreateAnimation("MoveLookUpEnd_Basic", 73, 74, 25, 36, 0.12f, false, true, true);
	CreateAnimation("MoveLookUpAttack_Basic", 112, 121, 25, 36, 0.04f, false, true);
	CreateAnimation("SitStart_Basic", -1, -1, 84, 86, 0.03f, false, false);
	CreateAnimation("SitLoop_Basic", -1, -1, 91, 94, 0.2f, false, true, true, true);
	CreateAnimation("SitMove_Basic", -1, -1, 95, 101, 0.08f, false, true);
	CreateAnimation("SitAttack_Basic", -1, -1, 128, 137, 0.04f, false, false);
	CreateAnimation("SitAttackLoop_Basic", -1, -1, 138, 141, 0.15f, false, true, true, true);
	CreateAnimation("SitEnd_Basic", -1, -1, 84, 86, 0.03f, false, false, true, true);
	CreateAnimation("Jump_Basic", 42, 51, 58, 63, 0.06f, false, false, false, true);
	CreateAnimation("MoveJump_Basic", 52, 57, 64, 72, 0.03f, false, false);
	CreateAnimation("JumpAttack_Basic", 102, 111, 58, 63, 0.04f, false, false, false, true);
	CreateAnimation("MoveJumpAttack_Basic", 102, 111, 64, 72, 0.04f, false, false);
	CreateAnimation("JumpLookUpStart_Basic", 73, 74, 58, 63, 0.06f, false, false, false, true);
	CreateAnimation("JumpLookUpLoop_Basic", 75, 78, 58, 63, 0.11f, true, false, true, true);
	CreateAnimation("JumpLookUpEnd_Basic", 73, 74, 58, 63, 0.06f, false, false, true, true);
	CreateAnimation("JumpLookUpAttack_Basic", 112, 121, 58, 63, 0.04f, false, false, false, true);
	CreateAnimation("MoveJumpLookUpStart_Basic", 73, 74, 64, 72, 0.06f, false, false);
	CreateAnimation("MoveJumpLookUpLoop_Basic", 75, 78, 64, 72, 0.11f, true, false, true);
	CreateAnimation("MoveJumpLookUpEnd_Basic", 73, 74, 64, 72, 0.06f, false, false, true);
	CreateAnimation("MoveJumpLookUpAttack_Basic", 112, 121, 64, 72, 0.04f, false, true);
	CreateAnimation("JumpLookDownStart_Basic", 81, 82, 58, 63, 0.08f, false, false, false, true);
	CreateAnimation("JumpLookDownLoop_Basic", 83, 83, 58, 63, 0.1f, true, false, false, true);
	CreateAnimation("JumpLookDownEnd_Basic", 81, 82, 58, 63, 0.08f, false, false, false, true);
	CreateAnimation("JumpLookDownAttack_Basic", 122, 127, 58, 63, 0.04f, false, false, false, true);
	CreateAnimation("MoveJumpLookDownStart_Basic", 81, 82, 64, 72, 0.08f, false, false);
	CreateAnimation("MoveJumpLookDownLoop_Basic", 83, 83, 64, 72, 0.1f, true, false);
	CreateAnimation("MoveJumpLookDownEnd_Basic", 81, 82, 64, 72, 0.08f, false, false, true);
	CreateAnimation("MoveJumpLookDownAttack_Basic", 122, 127, 64, 72, 0.04f, false, false);
	CreateAnimation("ThrowGranade_Basic", 142, 147, 4, 4, 0.05f, false, false, false, false);
	CreateAnimation("MoveThrowGranade_Basic", 142, 147, 25, 36, 0.05f, false, true);
	CreateAnimation("SitThrowGranade_Basic", -1, -1, 150, 155, 0.06f, false, false, false, false);
	CreateAnimation("JumpThrowGranade_Basic", 142, 147, 58, 63, 0.05f, false, false, false, true);
	CreateAnimation("MoveJumpThrowGranade_Basic", 142, 147, 64, 72, 0.05f, false, false);
	CreateAnimation("Parachute_Basic", 41, 41, 58, 58, 0.05f, false, false);
	AniRenderParachute->CreateAnimation("Parachute", "Parachute.bmp", 4, 4, 1.f);
	CreateAnimation("Victory_Basic", -1, -1, 225, 230, 0.05f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("Death_Basic", -1, -1, 0, 20, 0.05f, false, false, false, false, "Eri_Kasamoto_Death");
	CreateAnimation("Alive_Basic", -1, -1, 0, 6, 0.05f, false, false, false, false, "Eri_Kasamoto_Alive");

	CreateAnimation("Idle_HeavyMachineGun", 0, 3, 231, 231, 0.1f, true, true, true, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("Move_HeavyMachineGun", 4, 15, 236, 247, 0.1f, true, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("StopMove_HeavyMachineGun", -1, -1, 16, 19, 0.05f, false, false, true, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("IdleAttack_HeavyMachineGun", 70, 73, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("IdleAttackEnd_HeavyMachineGun", 134, 138, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("IdleAttackUp_HeavyMachineGun", 77, 78, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveAttack_HeavyMachineGun", 70, 73, 236, 247, 0.04f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveAttackEnd_HeavyMachineGun", 134, 138, 236, 247, 0.04f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveAttackUp_HeavyMachineGun", 77, 78, 236, 247, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("LookUpStart_HeavyMachineGun", 31, 32, 231, 231, 0.12f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("LookUpLoop_HeavyMachineGun", 36, 39, 231, 231, 0.12f, true, true, true, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("LookUpEnd_HeavyMachineGun", 85, 87, 231, 231, 0.12f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("LookUpAttack_HeavyMachineGun", 79, 82, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("LookUpAttackDown_HeavyMachineGun", 83, 84, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("LookUpAttackEnd_HeavyMachineGun", 109, 114, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveLookUpStart_HeavyMachineGun", 31, 32, 236, 247, 0.12f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveLookUpLoop_HeavyMachineGun", 36, 39, 236, 247, 0.12f, true, true, true, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveLookUpEnd_HeavyMachineGun", 85, 87, 236, 247, 0.12f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveLookUpAttack_HeavyMachineGun", 79, 82, 236, 247, 0.12f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveLookUpAttackEnd_HeavyMachineGun", 109, 114, 236, 247, 0.12f, false, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveLookUpAttackDown_HeavyMachineGun", 83, 84, 236, 247, 0.12f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitStart_HeavyMachineGun", -1, -1, 43, 45, 0.1f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitLoop_HeavyMachineGun", -1, -1, 46, 49, 0.12f, true, true, true, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitMove_HeavyMachineGun", -1, -1, 58, 64, 0.08f, true, true, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitEnd_HeavyMachineGun", -1, -1, 43, 45, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitAttack_HeavyMachineGun", -1, -1, 96, 99, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitAttackLoop_HeavyMachineGun", -1, -1, 50, 53, 0.15f, true, true, true, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitAttackEnd_HeavyMachineGun", -1, -1, 121, 123, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("SitThrowGranade_HeavyMachineGun", -1, -1, 181, 186, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("Jump_HeavyMachineGun", 20, 30, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJump_HeavyMachineGun", 263, 268, 254, 262, 0.1f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpAttack_HeavyMachineGun", 70, 73, 248, 253, 0.04f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpAttackEnd_HeavyMachineGun", 134, 138, 248, 253, 0.04f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpAttackUp_HeavyMachineGun", 77, 78, 248, 253, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpAttackDown_HeavyMachineGun", 88, 89, 248, 253, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpAttack_HeavyMachineGun", 70, 73, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpAttackEnd_HeavyMachineGun", 134, 138, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpAttackUp_HeavyMachineGun", 77, 78, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpAttackDown_HeavyMachineGun", 88, 89, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookUpStart_HeavyMachineGun", 31, 32, 248, 253, 0.12f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookUpLoop_HeavyMachineGun", 36, 39, 248, 253, 0.12f, true, true, true, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookUpEnd_HeavyMachineGun", 85, 87, 248, 253, 0.12f, false, true, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookUpAttack_HeavyMachineGun", 79, 82, 248, 253, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookUpAttackEnd_HeavyMachineGun", 109, 114, 248, 253, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookUpAttackDown_HeavyMachineGun", 83, 84, 248, 253, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookUpStart_HeavyMachineGun", 31, 32, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookUpLoop_HeavyMachineGun", 36, 39, 254, 262, 0.12f, true, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookUpEnd_HeavyMachineGun", 85, 87, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookUpAttack_HeavyMachineGun", 79, 82, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookUpAttackEnd_HeavyMachineGun", 109, 114, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookUpAttackDown_HeavyMachineGun", 83, 84, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookDownStart_HeavyMachineGun", 40, 41, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookDownLoop_HeavyMachineGun", 42, 42, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookDownAttack_HeavyMachineGun", 90, 93, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpLookDownAttackUp_HeavyMachineGun", 94, 95, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookDownStart_HeavyMachineGun", 40, 41, 254, 262, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookDownLoop_HeavyMachineGun", 42, 42, 254, 262, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookDownAttack_HeavyMachineGun", 90, 93, 254, 262, 0.1f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpLookDownAttackUp_HeavyMachineGun", 94, 95, 254, 262, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("ThrowGranade_HeavyMachineGun", 175, 180, 231, 231, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveThrowGranade_HeavyMachineGun", 175, 180, 236, 247, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");
	CreateAnimation("JumpThrowGranade_HeavyMachineGun", 175, 180, 248, 253, 0.05f, false, false, false, true, "Eri_Kasamoto_Weapon");
	CreateAnimation("MoveJumpThrowGranade_HeavyMachineGun", 175, 180, 254, 262, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");

	CREATEKEY("LMove", VK_LEFT);
	CREATEKEY("RMove", VK_RIGHT);
	CREATEKEY("LookUp", VK_UP);
	CREATEKEY("LookUpLMove", VK_UP, VK_LEFT);
	CREATEKEY("LookUpRMove", VK_UP, VK_RIGHT);
	CREATEKEY("Sit", VK_DOWN);
	CREATEKEY("SitLMove", VK_LEFT, VK_DOWN);
	CREATEKEY("SitRMove", VK_RIGHT, VK_DOWN);
	CREATEKEY("SitAttack", VK_DOWN, 'A');
	CREATEKEY("SitJump", VK_DOWN, 'S');
	CREATEKEY("SitGranade", VK_DOWN, 'D');
	CREATEKEY("Jump", 'S');
	CREATEKEY("JumpLMove", 'S', VK_LEFT);
	CREATEKEY("JumpRMove", 'S', VK_RIGHT);
	CREATEKEY("Attack", 'A');
	CREATEKEY("Granade", 'D');

	CREATEKEY("Invincible", VK_F2);
	CREATEKEY("HeavyMachineGun", VK_F3);
	CREATEKEY("BasicGun", VK_F4);

	m_MoveSpeed = MOVESPEED;

	m_TopBodyAttack = false;
	m_BottomBodyMove = false;

	m_AttackCancleAble = false;
	m_ShootBullet = false;
	m_ThrowGranade = false;
	m_HeavyMachineGunShotCount = 0;

	m_Sit = false;
	m_LookUp = false;
	m_Jump = false;

	SetCurDirState(ENUM_DIRECTION::RIGHT);
	JumpDirState = ENUM_DIRECTION::RIGHT;

	PlayerState.CreateState("Idle_Basic", &Player::Idle_BasicInit, &Player::Idle_BasicState, nullptr, this);
	PlayerState.CreateState("Move_Basic", &Player::Move_BasicInit, &Player::Move_BasicState, nullptr, this);
	PlayerState.CreateState("StopMove_Basic", &Player::StopMove_BasicInit, &Player::StopMove_BasicState, nullptr, this);
	PlayerState.CreateState("IdleAttack_Basic", &Player::IdleAttack_BasicInit, &Player::IdleAttack_BasicState, nullptr, this);
	PlayerState.CreateState("MoveAttack_Basic", &Player::MoveAttack_BasicInit, &Player::MoveAttack_BasicState, nullptr, this);
	PlayerState.CreateState("LookUpStart_Basic", &Player::LookUpStart_BasicInit, &Player::LookUpStart_BasicState, &Player::LookUpStart_BasicLeave, this);
	PlayerState.CreateState("LookUpLoop_Basic", &Player::LookUpLoop_BasicInit, &Player::LookUpLoop_BasicState, &Player::LookUpLoop_BasicLeave, this);
	PlayerState.CreateState("LookUpEnd_Basic", &Player::LookUpEnd_BasicInit, &Player::LookUpEnd_BasicState, &Player::LookUpEnd_BasicLeave, this);
	PlayerState.CreateState("LookUpAttack_Basic", &Player::LookUpAttack_BasicInit, &Player::LookUpAttack_BasicState, &Player::LookUpAttack_BasicLeave, this);
	PlayerState.CreateState("MoveLookUpStart_Basic", &Player::MoveLookUpStart_BasicInit, &Player::MoveLookUpStart_BasicState, &Player::MoveLookUpStart_BasicLeave, this);
	PlayerState.CreateState("MoveLookUpLoop_Basic", &Player::MoveLookUpLoop_BasicInit, &Player::MoveLookUpLoop_BasicState, &Player::MoveLookUpLoop_BasicLeave, this);
	PlayerState.CreateState("MoveLookUpEnd_Basic", &Player::MoveLookUpEnd_BasicInit, &Player::MoveLookUpEnd_BasicState, &Player::MoveLookUpEnd_BasicLeave, this);
	PlayerState.CreateState("MoveLookUpAttack_Basic", &Player::MoveLookUpAttack_BasicInit, &Player::MoveLookUpAttack_BasicState, &Player::MoveLookUpAttack_BasicLeave, this);
	PlayerState.CreateState("SitStart_Basic", &Player::SitStart_BasicInit, &Player::SitStart_BasicState, &Player::SitStart_BasicLeave, this);
	PlayerState.CreateState("SitLoop_Basic", &Player::SitLoop_BasicInit, &Player::SitLoop_BasicState, &Player::SitLoop_BasicLeave, this);
	PlayerState.CreateState("SitMove_Basic", &Player::SitMove_BasicInit, &Player::SitMove_BasicState, &Player::SitMove_BasicLeave, this);
	PlayerState.CreateState("SitAttack_Basic", &Player::SitAttack_BasicInit, &Player::SitAttack_BasicState, &Player::SitAttack_BasicLeave, this);
	PlayerState.CreateState("SitAttackLoop_Basic", &Player::SitAttackLoop_BasicInit, &Player::SitAttackLoop_BasicState, &Player::SitAttackLoop_BasicLeave, this);
	PlayerState.CreateState("SitEnd_Basic", &Player::SitEnd_BasicInit, &Player::SitEnd_BasicState, &Player::SitEnd_BasicLeave, this);
	PlayerState.CreateState("Jump_Basic", &Player::Jump_BasicInit, &Player::Jump_BasicState, nullptr, this);
	PlayerState.CreateState("MoveJump_Basic", &Player::MoveJump_BasicInit, &Player::MoveJump_BasicState, nullptr, this);
	PlayerState.CreateState("JumpAttack_Basic", &Player::JumpAttack_BasicInit, &Player::JumpAttack_BasicState, nullptr, this);
	PlayerState.CreateState("MoveJumpAttack_Basic", &Player::MoveJumpAttack_BasicInit, &Player::MoveJumpAttack_BasicState, nullptr, this);
	PlayerState.CreateState("JumpLookUpStart_Basic", &Player::JumpLookUpStart_BasicInit, &Player::JumpLookUpStart_BasicState, &Player::JumpLookUpStart_BasicLeave, this);
	PlayerState.CreateState("JumpLookUpLoop_Basic", &Player::JumpLookUpLoop_BasicInit, &Player::JumpLookUpLoop_BasicState, &Player::JumpLookUpLoop_BasicLeave, this);
	PlayerState.CreateState("JumpLookUpEnd_Basic", &Player::JumpLookUpEnd_BasicInit, &Player::JumpLookUpEnd_BasicState, &Player::JumpLookUpEnd_BasicLeave, this);
	PlayerState.CreateState("JumpLookUpAttack_Basic", &Player::JumpLookUpAttack_BasicInit, &Player::JumpLookUpAttack_BasicState, &Player::JumpLookUpAttack_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookUpStart_Basic", &Player::MoveJumpLookUpStart_BasicInit, &Player::MoveJumpLookUpStart_BasicState, &Player::MoveJumpLookUpStart_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookUpLoop_Basic", &Player::MoveJumpLookUpLoop_BasicInit, &Player::MoveJumpLookUpLoop_BasicState, &Player::MoveJumpLookUpLoop_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookUpEnd_Basic", &Player::MoveJumpLookUpEnd_BasicInit, &Player::MoveJumpLookUpEnd_BasicState, &Player::MoveJumpLookUpEnd_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookUpAttack_Basic", &Player::MoveJumpLookUpAttack_BasicInit, &Player::MoveJumpLookUpAttack_BasicState, &Player::MoveJumpLookUpAttack_BasicLeave, this);
	PlayerState.CreateState("JumpLookDownStart_Basic", &Player::JumpLookDownStart_BasicInit, &Player::JumpLookDownStart_BasicState, &Player::JumpLookDownStart_BasicLeave, this);
	PlayerState.CreateState("JumpLookDownLoop_Basic", &Player::JumpLookDownLoop_BasicInit, &Player::JumpLookDownLoop_BasicState, &Player::JumpLookDownLoop_BasicLeave, this);
	PlayerState.CreateState("JumpLookDownEnd_Basic", &Player::JumpLookDownEnd_BasicInit, &Player::JumpLookDownEnd_BasicState, &Player::JumpLookDownEnd_BasicLeave, this);
	PlayerState.CreateState("JumpLookDownAttack_Basic", &Player::JumpLookDownAttack_BasicInit, &Player::JumpLookDownAttack_BasicState, &Player::JumpLookDownAttack_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookDownStart_Basic", &Player::MoveJumpLookDownStart_BasicInit, &Player::MoveJumpLookDownStart_BasicState, &Player::MoveJumpLookDownStart_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookDownLoop_Basic", &Player::MoveJumpLookDownLoop_BasicInit, &Player::MoveJumpLookDownLoop_BasicState, &Player::MoveJumpLookDownLoop_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookDownEnd_Basic", &Player::MoveJumpLookDownEnd_BasicInit, &Player::MoveJumpLookDownEnd_BasicState, &Player::MoveJumpLookDownEnd_BasicLeave, this);
	PlayerState.CreateState("MoveJumpLookDownAttack_Basic", &Player::MoveJumpLookDownAttack_BasicInit, &Player::MoveJumpLookDownAttack_BasicState, &Player::MoveJumpLookDownAttack_BasicLeave, this);
	PlayerState.CreateState("ThrowGranade_Basic", &Player::ThrowGranade_BasicInit, &Player::ThrowGranade_BasicState, nullptr, this);
	PlayerState.CreateState("MoveThrowGranade_Basic", &Player::MoveThrowGranade_BasicInit, &Player::MoveThrowGranade_BasicState, nullptr, this);
	PlayerState.CreateState("SitThrowGranade_Basic", &Player::SitThrowGranade_BasicInit, &Player::SitThrowGranade_BasicState, &Player::SitThrowGranade_BasicLeave, this);
	PlayerState.CreateState("JumpThrowGranade_Basic", &Player::JumpThrowGranade_BasicInit, &Player::JumpThrowGranade_BasicState, nullptr, this);
	PlayerState.CreateState("MoveJumpThrowGranade_Basic", &Player::MoveJumpThrowGranade_BasicInit, &Player::MoveJumpThrowGranade_BasicState, nullptr, this);
	PlayerState.CreateState("Parachute_Basic", &Player::Parachute_BasicInit, &Player::Parachute_BasicState, nullptr, this);
	PlayerState.CreateState("Victory_Basic", &Player::Victory_BasicInit, &Player::Victory_BasicState, nullptr, this);
	PlayerState.CreateState("Death_Basic", &Player::Death_BasicInit, &Player::Death_BasicState, nullptr, this);
	PlayerState.CreateState("Alive_Basic", &Player::Alive_BasicInit, &Player::Alive_BasicState, nullptr, this);

	PlayerState.CreateState("Idle_HeavyMachineGun", &Player::Idle_HeavyMachineGunInit, &Player::Idle_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("Move_HeavyMachineGun", &Player::Move_HeavyMachineGunInit, &Player::Move_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("StopMove_HeavyMachineGun", &Player::StopMove_HeavyMachineGunInit, &Player::StopMove_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("IdleAttack_HeavyMachineGun", &Player::IdleAttack_HeavyMachineGunInit, &Player::IdleAttack_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("IdleAttackEnd_HeavyMachineGun", &Player::IdleAttackEnd_HeavyMachineGunInit, &Player::IdleAttackEnd_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("IdleAttackUp_HeavyMachineGun", &Player::IdleAttackUp_HeavyMachineGunInit, &Player::IdleAttackUp_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveAttack_HeavyMachineGun", &Player::MoveAttack_HeavyMachineGunInit, &Player::MoveAttack_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveAttackEnd_HeavyMachineGun", &Player::MoveAttackEnd_HeavyMachineGunInit, &Player::MoveAttackEnd_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveAttackUp_HeavyMachineGun", &Player::MoveAttackUp_HeavyMachineGunInit, &Player::MoveAttackUp_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("LookUpStart_HeavyMachineGun", &Player::LookUpStart_HeavyMachineGunInit, &Player::LookUpStart_HeavyMachineGunState, &Player::LookUpStart_HeavyMachineGunLeave, this);
	PlayerState.CreateState("LookUpLoop_HeavyMachineGun", &Player::LookUpLoop_HeavyMachineGunInit, &Player::LookUpLoop_HeavyMachineGunState, &Player::LookUpLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("LookUpEnd_HeavyMachineGun", &Player::LookUpEnd_HeavyMachineGunInit, &Player::LookUpEnd_HeavyMachineGunState, &Player::LookUpEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("LookUpAttack_HeavyMachineGun", &Player::LookUpAttack_HeavyMachineGunInit, &Player::LookUpAttack_HeavyMachineGunState, &Player::LookUpAttack_HeavyMachineGunLeave, this);
	PlayerState.CreateState("LookUpAttackEnd_HeavyMachineGun", &Player::LookUpAttackEnd_HeavyMachineGunInit, &Player::LookUpAttackEnd_HeavyMachineGunState, &Player::LookUpAttackEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("LookUpAttackDown_HeavyMachineGun", &Player::LookUpAttackDown_HeavyMachineGunInit, &Player::LookUpAttackDown_HeavyMachineGunState, &Player::LookUpAttackDown_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveLookUpStart_HeavyMachineGun", &Player::MoveLookUpStart_HeavyMachineGunInit, &Player::MoveLookUpStart_HeavyMachineGunState, &Player::MoveLookUpStart_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveLookUpLoop_HeavyMachineGun", &Player::MoveLookUpLoop_HeavyMachineGunInit, &Player::MoveLookUpLoop_HeavyMachineGunState, &Player::MoveLookUpLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveLookUpEnd_HeavyMachineGun", &Player::MoveLookUpEnd_HeavyMachineGunInit, &Player::MoveLookUpEnd_HeavyMachineGunState, &Player::MoveLookUpEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveLookUpAttack_HeavyMachineGun", &Player::MoveLookUpAttack_HeavyMachineGunInit, &Player::MoveLookUpAttack_HeavyMachineGunState, &Player::MoveLookUpAttack_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveLookUpAttackEnd_HeavyMachineGun", &Player::MoveLookUpAttackEnd_HeavyMachineGunInit, &Player::MoveLookUpAttackEnd_HeavyMachineGunState, &Player::MoveLookUpAttackEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveLookUpAttackDown_HeavyMachineGun", &Player::MoveLookUpAttackDown_HeavyMachineGunInit, &Player::MoveLookUpAttackDown_HeavyMachineGunState, &Player::MoveLookUpAttackDown_HeavyMachineGunLeave, this);
	PlayerState.CreateState("SitStart_HeavyMachineGun", &Player::SitStart_HeavyMachineGunInit, &Player::SitStart_HeavyMachineGunState, &Player::SitStart_HeavyMachineGunLeave, this);
	PlayerState.CreateState("SitLoop_HeavyMachineGun", &Player::SitLoop_HeavyMachineGunInit, &Player::SitLoop_HeavyMachineGunState, &Player::SitLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("SitMove_HeavyMachineGun", &Player::SitMove_HeavyMachineGunInit, &Player::SitMove_HeavyMachineGunState, &Player::SitMove_HeavyMachineGunLeave, this);
	PlayerState.CreateState("SitAttack_HeavyMachineGun", &Player::SitAttack_HeavyMachineGunInit, &Player::SitAttack_HeavyMachineGunState, &Player::SitAttack_HeavyMachineGunLeave, this);
	PlayerState.CreateState("SitAttackLoop_HeavyMachineGun", &Player::SitAttackLoop_HeavyMachineGunInit, &Player::SitAttackLoop_HeavyMachineGunState, &Player::SitAttackLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("SitAttackEnd_HeavyMachineGun", &Player::SitAttackEnd_HeavyMachineGunInit, &Player::SitAttackEnd_HeavyMachineGunState, &Player::SitAttackEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("SitEnd_HeavyMachineGun", &Player::SitEnd_HeavyMachineGunInit, &Player::SitEnd_HeavyMachineGunState, &Player::SitEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("Jump_HeavyMachineGun", &Player::Jump_HeavyMachineGunInit, &Player::Jump_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveJump_HeavyMachineGun", &Player::MoveJump_HeavyMachineGunInit, &Player::MoveJump_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("JumpAttack_HeavyMachineGun", &Player::JumpAttack_HeavyMachineGunInit, &Player::JumpAttack_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("JumpAttackEnd_HeavyMachineGun", &Player::JumpAttackEnd_HeavyMachineGunInit, &Player::JumpAttackEnd_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("JumpAttackUp_HeavyMachineGun", &Player::JumpAttackUp_HeavyMachineGunInit, &Player::JumpAttackUp_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("JumpAttackDown_HeavyMachineGun", &Player::JumpAttackDown_HeavyMachineGunInit, &Player::JumpAttackDown_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveJumpAttack_HeavyMachineGun", &Player::MoveJumpAttack_HeavyMachineGunInit, &Player::MoveJumpAttack_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveJumpAttackEnd_HeavyMachineGun", &Player::MoveJumpAttackEnd_HeavyMachineGunInit, &Player::MoveJumpAttackEnd_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveJumpAttackUp_HeavyMachineGun", &Player::MoveJumpAttackUp_HeavyMachineGunInit, &Player::MoveJumpAttackUp_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveJumpAttackDown_HeavyMachineGun", &Player::MoveJumpAttackDown_HeavyMachineGunInit, &Player::MoveJumpAttackDown_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("JumpLookUpStart_HeavyMachineGun", &Player::JumpLookUpStart_HeavyMachineGunInit, &Player::JumpLookUpStart_HeavyMachineGunState, &Player::JumpLookUpStart_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookUpLoop_HeavyMachineGun", &Player::JumpLookUpLoop_HeavyMachineGunInit, &Player::JumpLookUpLoop_HeavyMachineGunState, &Player::JumpLookUpLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookUpEnd_HeavyMachineGun", &Player::JumpLookUpEnd_HeavyMachineGunInit, &Player::JumpLookUpEnd_HeavyMachineGunState, &Player::JumpLookUpEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookUpAttack_HeavyMachineGun", &Player::JumpLookUpAttack_HeavyMachineGunInit, &Player::JumpLookUpAttack_HeavyMachineGunState, &Player::JumpLookUpAttack_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookUpAttackEnd_HeavyMachineGun", &Player::JumpLookUpAttackEnd_HeavyMachineGunInit, &Player::JumpLookUpAttackEnd_HeavyMachineGunState, &Player::JumpLookUpAttackEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookUpAttackDown_HeavyMachineGun", &Player::JumpLookUpAttackDown_HeavyMachineGunInit, &Player::JumpLookUpAttackDown_HeavyMachineGunState, &Player::JumpLookUpAttackDown_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookUpStart_HeavyMachineGun", &Player::MoveJumpLookUpStart_HeavyMachineGunInit, &Player::MoveJumpLookUpStart_HeavyMachineGunState, &Player::MoveJumpLookUpStart_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookUpLoop_HeavyMachineGun", &Player::MoveJumpLookUpLoop_HeavyMachineGunInit, &Player::MoveJumpLookUpLoop_HeavyMachineGunState, &Player::MoveJumpLookUpLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookUpEnd_HeavyMachineGun", &Player::MoveJumpLookUpEnd_HeavyMachineGunInit, &Player::MoveJumpLookUpEnd_HeavyMachineGunState, &Player::MoveJumpLookUpEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookUpAttack_HeavyMachineGun", &Player::MoveJumpLookUpAttack_HeavyMachineGunInit, &Player::MoveJumpLookUpAttack_HeavyMachineGunState, &Player::MoveJumpLookUpAttack_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookUpAttackEnd_HeavyMachineGun", &Player::MoveJumpLookUpAttackEnd_HeavyMachineGunInit, &Player::MoveJumpLookUpAttackEnd_HeavyMachineGunState, &Player::MoveJumpLookUpAttackEnd_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookUpAttackDown_HeavyMachineGun", &Player::MoveJumpLookUpAttackDown_HeavyMachineGunInit, &Player::MoveJumpLookUpAttackDown_HeavyMachineGunState, &Player::MoveJumpLookUpAttackDown_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookDownStart_HeavyMachineGun", &Player::JumpLookDownStart_HeavyMachineGunInit, &Player::JumpLookDownStart_HeavyMachineGunState, &Player::JumpLookDownStart_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookDownLoop_HeavyMachineGun", &Player::JumpLookDownLoop_HeavyMachineGunInit, &Player::JumpLookDownLoop_HeavyMachineGunState, &Player::JumpLookDownLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookDownAttack_HeavyMachineGun", &Player::JumpLookDownAttack_HeavyMachineGunInit, &Player::JumpLookDownAttack_HeavyMachineGunState, &Player::JumpLookDownAttack_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpLookDownAttackUp_HeavyMachineGun", &Player::JumpLookDownAttackUp_HeavyMachineGunInit, &Player::JumpLookDownAttackUp_HeavyMachineGunState, &Player::JumpLookDownAttackUp_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookDownStart_HeavyMachineGun", &Player::MoveJumpLookDownStart_HeavyMachineGunInit, &Player::MoveJumpLookDownStart_HeavyMachineGunState, &Player::MoveJumpLookDownStart_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookDownLoop_HeavyMachineGun", &Player::MoveJumpLookDownLoop_HeavyMachineGunInit, &Player::MoveJumpLookDownLoop_HeavyMachineGunState, &Player::MoveJumpLookDownLoop_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookDownAttack_HeavyMachineGun", &Player::MoveJumpLookDownAttack_HeavyMachineGunInit, &Player::MoveJumpLookDownAttack_HeavyMachineGunState, &Player::MoveJumpLookDownAttack_HeavyMachineGunLeave, this);
	PlayerState.CreateState("MoveJumpLookDownAttackUp_HeavyMachineGun", &Player::MoveJumpLookDownAttackUp_HeavyMachineGunInit, &Player::MoveJumpLookDownAttackUp_HeavyMachineGunState, &Player::MoveJumpLookDownAttackUp_HeavyMachineGunLeave, this);
	PlayerState.CreateState("ThrowGranade_HeavyMachineGun", &Player::ThrowGranade_HeavyMachineGunInit, &Player::ThrowGranade_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveThrowGranade_HeavyMachineGun", &Player::MoveThrowGranade_HeavyMachineGunInit, &Player::MoveThrowGranade_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("SitThrowGranade_HeavyMachineGun", &Player::SitThrowGranade_HeavyMachineGunInit, &Player::SitThrowGranade_HeavyMachineGunState, &Player::SitThrowGranade_HeavyMachineGunLeave, this);
	PlayerState.CreateState("JumpThrowGranade_HeavyMachineGun", &Player::JumpThrowGranade_HeavyMachineGunInit, &Player::JumpThrowGranade_HeavyMachineGunState, nullptr, this);
	PlayerState.CreateState("MoveJumpThrowGranade_HeavyMachineGun", &Player::MoveJumpThrowGranade_HeavyMachineGunInit, &Player::MoveJumpThrowGranade_HeavyMachineGunState, nullptr, this);
	
	SetDefaultAniData();

	m_Weapon->SetWeaponType(Weapon::ENUM_WEAPONTYPE::BASIC);

	ChangeState("Parachute");
	PlayerState.PrevState = "";

	m_IsBounceOff = false;
	m_IsBounceOffStart = false;
	m_BounceOffCurTime = 0.f;
	m_BounceOffMaxTime = 0.5f;

	m_BlockDirChange = false;
}

void Player::Update()
{
	if (KEYDOWN("Invincible") == true)
	{
		if (m_InvincibleTime < 10.f)
		{
			GJHGameEngineSound::PlayOneShot("CharacterPick.mp3", 1.f);

			m_InvincibleTime = 1000000.f;
		}
		else
		{
			m_InvincibleTime = 0.f;
		}
	}

	if (KEYDOWN("HeavyMachineGun") == true)
	{
		GJHGameEngineSound::PlayOneShot("GetHeavyMachineGunBox.mp3", 0.7f);
		m_Weapon->SetWeaponType(Weapon::ENUM_WEAPONTYPE::HEAVYMACHINEGUN);
		m_Weapon->SetAmmo(999);
		m_BlockDirChange = false;

		ChangeState("Idle");
	}

	if (KEYDOWN("BasicGun") == true)
	{
		GJHGameEngineSound::PlayOneShot("CharacterPick.mp3", 1.f);
		m_Weapon->SetWeaponType(Weapon::ENUM_WEAPONTYPE::BASIC);
		m_Weapon->SetAmmo(0);
		m_BlockDirChange = false;

		ChangeState("Idle");
	}

	//BounceOff();
	DirStateCheck();
	PlayerState.Update();
	AnimationDataCheck();
	CheckMissionComplete();
	Invincible();
	AmmoCheck();
	__super::Update();
}

void Player::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::MONSTER &&
		_Other->GetBlockMove() == true)
	{
		if (m_Jump == true)
		{
			return;
		}

		SetPos(GetPrevPos());
	}
	else if (_Other->GetActor()->GetName() == "GranadeBox")
	{
		m_GranadeCount += 10;
	}
	else if (_Other->GetActor()->GetName() == "HeavyMachineGunBox")
	{
		m_Weapon->SetWeaponType(Weapon::ENUM_WEAPONTYPE::HEAVYMACHINEGUN);
		if (m_Weapon->GetAmmo() < 200)
		{
			m_Weapon->SetAmmo(200);
		}

		m_Falling = true;
		if (m_Jump == true && m_BottomBodyMove == true)
		{
			ChangeState("MoveJump");
		}
		else if (m_Jump == true)
		{
			ChangeState("Jump");
		}
		else
		{
			ChangeState("Idle");
		}
	}
	else if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::MONSTERBULLET)
	{
		if (m_IsInvincible == true)
		{
			return;
		}

		GJHGameEngineSound::PlayOneShot("PlayerDeath.mp3", 0.7f);
		m_Weapon->SetWeaponType(Weapon::ENUM_WEAPONTYPE::BASIC);

		if (0 < m_Life)
		{
			m_Life--;
		}
		
		ChangeState("Death");
	}
}

void Player::ColStay(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::MONSTER &&
		_Other->GetBlockMove() == true)
	{
		if (m_Jump == true)
		{
			return;
		}

		SetPos(GetPrevPos());
	}
}

void Player::CreateAnimation(const GJHString& _Name, int _TopStart, int _TopEnd, int _BottomStart, int _BottomEnd, float _FrameTime, bool _TopLoop, bool _BottomLoop, bool _TopReverse, bool _BottomReverse, const GJHString& _FileName)
{
	if (_TopStart == -1 || _TopEnd == -1)
	{
		TopBodyDrawSkip.insert(_Name);

		_TopStart = 0;
		_TopEnd = 0;
	}

	AniRenderTop->CreateAnimation(_Name + "_Right", _FileName + "(Right).bmp", _TopStart, _TopEnd, _FrameTime, _TopLoop, _TopReverse);
	AniRenderTop->CreateAnimation(_Name + "_Left", _FileName + "(Left).bmp", _TopStart, _TopEnd, _FrameTime, _TopLoop, _TopReverse);

	AniRenderBottom->CreateAnimation(_Name + "_Right", _FileName + "(Right).bmp", _BottomStart, _BottomEnd, _FrameTime, _BottomLoop, _BottomReverse);
	AniRenderBottom->CreateAnimation(_Name + "_Left", _FileName + "(Left).bmp", _BottomStart, _BottomEnd, _FrameTime, _BottomLoop, _BottomReverse);
}

void Player::ChangeAnimation(const GJHString& _Name, bool _Correction, const GJHVector& _Size)
{
	GJHVector Pivot = { 0, 0 };
	AniRenderTop->SetActorPivot(Pivot);
	AniRenderBottom->SetActorPivot(Pivot);

	AniRenderTop->ChangeAnimation(_Name + "_" + m_Weapon->GetWeaponTypeStr() + "_" + CurDirStateStr, _Correction);
	AniRenderBottom->ChangeAnimation(_Name + "_" + m_Weapon->GetWeaponTypeStr() + "_" + CurDirStateStr, _Correction);

	AniRenderTop->SetSize(_Size);
	AniRenderBottom->SetSize(_Size);
}

void Player::ChangeAnimation(const GJHString& _Name, ENUM_BODYTYPE _BODYTYPE, bool _Correction, const GJHVector& _Size)
{
	GJHVector Pivot = { 0, 0 };

	AniRenderTop->SetActorPivot(Pivot);
	AniRenderBottom->SetActorPivot(Pivot);

	if (_BODYTYPE == ENUM_BODYTYPE::TOP)
	{
		AniRenderTop->ChangeAnimation(_Name + "_" + m_Weapon->GetWeaponTypeStr() + "_" + CurDirStateStr, _Correction, _Size);
	}
	else
	{
		AniRenderBottom->ChangeAnimation(_Name + "_" + m_Weapon->GetWeaponTypeStr() + "_" + CurDirStateStr, _Correction, _Size);
	}
	AniRenderTop->SetSize(_Size);
	AniRenderBottom->SetSize(_Size);

}

void Player::ChangeState(const GJHString& _StateName)
{
	CurStateStr = _StateName;
	PlayerState.ChangeState(GJHString(_StateName) + "_" + m_Weapon->GetWeaponTypeStr());
}

bool Player::TopAnimationEnd()
{
	return AniRenderTop->AnimationEnd();
}

bool Player::BottomAnimationEnd()
{
	return AniRenderBottom->AnimationEnd();
}

bool Player::AnimationEnd()
{
	return AniRenderTop->AnimationEnd() && AniRenderBottom->AnimationEnd();
}

void Player::SetCurDirState(ENUM_DIRECTION _Dir)
{
	m_PrevImageDir = m_ImageDir;
	m_ImageDir = _Dir;
	
	CurDirState = _Dir;

	if (_Dir == ENUM_DIRECTION::LEFT)
	{
		CurDirStateStr = "Left";
	}
	else
	{
		CurDirStateStr = "Right";
	}
}

void Player::SetPrevDirState(ENUM_DIRECTION _Dir)
{
	PrevDirState = _Dir;

	if (_Dir == ENUM_DIRECTION::LEFT)
	{
		PrevDirStateStr = "Left";
	}
	else
	{
		PrevDirStateStr = "Right";
	}
}

void Player::SetCollisionPivot(GJHVector _Pivot)
{
	m_AniCollision->SetActorPivot(_Pivot);
}

void Player::SetCollisionSize(GJHVector _Size)
{
	m_AniCollision->SetSize(_Size);
}

void Player::BounceOff()
{
	if (m_IsBounceOff == false)
	{
		return;
	}

	if (m_IsBounceOffStart == false)
	{
		m_IsBounceOffStart = true;

		__super::Jump(-1.f);
	}

	m_BounceOffCurTime += GJHGameEngineTime::FDeltaTime();
	if (m_BounceOffMaxTime <= m_BounceOffCurTime)
	{
		m_BounceOffCurTime = 0.f;
		m_IsBounceOff = false;
		m_IsBounceOffStart = false;

		SetPrevDirState(CurDirState);
		return;
	}

	Move(GJHVector::RIGHT * (float)m_BounceDir * GJHGameEngineTime::FDeltaTime((m_BounceOffMaxTime - m_BounceOffCurTime) * 1500.f));
}

void Player::AmmoCheck()
{
	if (m_Weapon->GetWeaponType() != Weapon::ENUM_WEAPONTYPE::HEAVYMACHINEGUN)
	{
		return;
	}

	if (m_Weapon->GetAmmo() <= 0)
	{
		m_Weapon->SetWeaponType(Weapon::ENUM_WEAPONTYPE::BASIC);
		if (m_Jump == true && m_BottomBodyMove == true)
		{
			ChangeState("MoveJump");
		}
		else if (m_Jump == true)
		{
			ChangeState("Jump");
		}
		else
		{
			ChangeState("Idle");
		}
	}
}

void Player::DirStateCheck()
{
	if (m_BlockDirChange == true)
	{
		return;
	}

	if (m_IsBounceOff == true)
	{
		return;
	}

	if (KEYPRESS("LMove") == true)
	{
		SetCurDirState(ENUM_DIRECTION::LEFT);
	}
	if (KEYPRESS("RMove") == true)
	{
		SetCurDirState(ENUM_DIRECTION::RIGHT);
	}

	if (CurDirState != PrevDirState && m_Jump == false)
	{
		AniRenderTop->ChangeAnimation(PlayerState.CurState + "_" + CurDirStateStr, true);
		AniRenderBottom->ChangeAnimation(PlayerState.CurState + "_" + CurDirStateStr, true);
	}

	SetPrevDirState(CurDirState);
}

void Player::Move(const GJHVector& _MoveValue)
{
	GJHVector MovePos = GetPos() + _MoveValue;

	if (MovePos.x < GJHCameraManager::GetCamPos().x + 40 ||
		GJHCameraManager::GetCamMaxPos().x - 40 < MovePos.x ||
		MovePos.y < GJHCameraManager::GetCamPos().y)
	{
		return;
	}

	ObjectBase::Move(_MoveValue);
}

void Player::WalkMove()
{	
	if (m_IsBounceOff == true)
	{
		return;
	}

	int XPos = (int)CurDirState;
	bool MoveAble = false;
	while (m_MapColImage->GetImagePixel(GetPos().ix() + XPos, GetPos().iy()) != RGB(0, 0, 255))
	{
		XPos += (int)CurDirState;

		if (30 <= abs(XPos))
		{
			MoveAble = true;
			break;
		}
	}

	if (MoveAble == true)
	{
		GJHVector MoveSpeed = GJHVector((float)CurDirState, 0) * GJHGameEngineTime::FDeltaTime(m_MoveSpeed);

		Move(MoveSpeed);

		if (GetPos().x < MAPSTARTX)
		{
			SetPos({ MAPSTARTX, GetPos().y });
			return;
		}
		else if (MAPENDX < GetPos().x)
		{
			SetPos({ MAPENDX, GetPos().y });
			return;
		}
	}

	int YPos = 0;
	bool IsFalling = false;
	while (m_MapColImage->GetImagePixel(GetPos().ix(), GetPos().iy() + YPos) == RGB(255, 0, 255) && m_Jump == false)
	{
		YPos += 1;

		if (30 <= YPos)
		{
			YPos = 0;
			IsFalling = true;
			break;
		}
	}

	if (IsFalling == true)
	{
		m_Falling = true;
		m_Jump = true;
		m_GravityAddValue = 600.f;
		ChangeState("Jump");
	}
	else
	{
		SetPos(GetPos() + GJHVector(0, (float)YPos));
	}
}

void Player::Jump()
{
	__super::Jump(-500.f);

	m_GravityAddValue = 1000.f;

	JumpDirState = CurDirState;
}

void Player::CheckMissionComplete()
{
	if (Phase2Manager::IsMissionComplete() == true &&
		m_BlockDirChange == false)
	{
		m_BlockDirChange = true;

		m_Weapon->SetWeaponType(Weapon::ENUM_WEAPONTYPE::BASIC);
		ChangeState("Victory");
	}
}

void Player::Invincible()
{
	m_InvincibleTime -= GJHGameEngineTime::FDeltaTime();
	if (m_InvincibleTime <= 0.f)
	{
		m_InvincibleTime = 0.f;
		m_IsInvincible = false;
		return;
	}

	m_IsInvincible = true;
}

void Player::DeathReset()
{
	m_Falling = false;

	m_GranadeCount = 10;
	m_InvincibleTime = 2.f;
	UI::SetGameTime(60);
}

void Player::CreateBullet(float _Angle)
{
	GJHVector BulletPos;

	if (m_Jump == true)
	{
		CurDirState = JumpDirState;
	}
	
	if (m_Sit == true)
	{
		BulletPos = GetPos() + GJHVector(100 * (float)CurDirState, -63);
	}
	else if (m_LookUp == true)
	{
		BulletPos = GetPos() + GJHVector(0, -170);
	}
	else if (m_JumpLookDown == true)
	{
		BulletPos = GetPos() + GJHVector(15, 50);

		if (JumpDirState == ENUM_DIRECTION::LEFT)
		{
			BulletPos += GJHVector(-30, -10);
		}
	}
	else
	{
		BulletPos = GetPos() + GJHVector(100 * (float)CurDirState, -95);
	}
	
	PlayerBullet_Basic* NewBullet = GetScene()->CreateActor<PlayerBullet_Basic>();
	NewBullet->SetName("PlayerBullet_Basic");
	NewBullet->SetPos(BulletPos);
	NewBullet->SetDir("Bullet", CurDirState);
	NewBullet->SetAngle(_Angle);

	m_ShootBullet = true;
}

void Player::CreateHeavyMachineGunBullet(float _Angle, GJHVector _Pos)
{
	GJHVector BulletPos;
	float BulletDistance = 0.f;
	float Angle = _Angle;

	switch (m_HeavyMachineGunShotCount)
	{
	case 0:
		BulletDistance = 0.f;
		break;
	case 1:
		BulletDistance = -10.f;
		Angle -= 1.f;
		break;
	case 2:
		BulletDistance = 5.f;
		Angle += 1.f;
		break;
	case 3:
		BulletDistance = -2.f;
		Angle -= 0.5f;
		break;
	}

	if (m_Jump == true)
	{
		CurDirState = JumpDirState;
	}

	if (m_Sit == true)
	{
		BulletPos = GetPos() + GJHVector(150 * (float)CurDirState, -60) + GJHVector(0, BulletDistance);
	}
	else if (m_LookUp == true && m_Jump == true)
	{
		BulletPos = GetPos() + GJHVector(0, -250) + GJHVector(BulletDistance, 0);

		if (JumpDirState == ENUM_DIRECTION::LEFT)
		{
			BulletPos += GJHVector(10, 0);
		}
	}
	else if (m_LookUp == true)
	{
		BulletPos = GetPos() + GJHVector(10 * (float)CurDirState, -250) + GJHVector(BulletDistance, 0);
	}
	else if (m_JumpLookDown == true)
	{
		BulletPos = GetPos() + GJHVector(-10 * (float)CurDirState, 50) + GJHVector(BulletDistance, 0);
	}
	else
	{
		BulletPos = GetPos() + GJHVector(150 * (float)CurDirState, -70) + GJHVector(0, BulletDistance);
	}

	BulletPos += _Pos;

	PlayerBullet_MachineGun* NewBullet = GetScene()->CreateActor<PlayerBullet_MachineGun>();
	NewBullet->SetName("PlayerBullet_MachineGun");
	NewBullet->SetPos(BulletPos);
	NewBullet->SetDir("Bullet0", CurDirState);
	NewBullet->SetAngle(Angle);

	if (m_HeavyMachineGunShotCount == 0)
	{
		GJHGameEngineSound::PlayOneShot("HeavyMachineGunAttack.mp3", 0.7f);
	}

	++m_HeavyMachineGunShotCount;
	m_Weapon->SubAmmo();
}

void Player::CreateGranade()
{
	GJHVector GranadePos;

	if (m_Jump == true)
	{
		CurDirState = JumpDirState;
	}

	if (m_Sit == true)
	{
		GranadePos = GetPos() + GJHVector(40 * (float)CurDirState, -68);
	}
	else
	{
		GranadePos = GetPos() + GJHVector(40 * (float)CurDirState, -100);
	}

	ENUM_DIRECTION Dir;
	if (m_Jump == true)
	{
		Dir = JumpDirState;
	}
	else
	{
		Dir = CurDirState;
	}

	if (m_GranadeCount <= 0)
	{
		return;
	}

	--m_GranadeCount;

	PlayerGranade* NewGranade = GetScene()->CreateActor<PlayerGranade>();
	NewGranade->SetName("PlayerGranade");
	NewGranade->SetPos(GranadePos);
	NewGranade->SetDir("Bullet", Dir);

	m_ThrowGranade = true;
}

void Player::AnimationDataCheck()
{
	int TopFrameIndex = -1, BottomFrameIndex = -1;
	float TopFrameTime = -1.f, BottomFrameTime = -1.f;

	PivotData TopBodyPivot, BottomBodyPivot;

	while (true)
	{
		std::map<GJHString, std::map<int, AniData>>::iterator Find = AnimationDataTop.find(PlayerState.CurState);
		if (Find == AnimationDataTop.end())
		{
			break;
		}

		std::map<int, AniData>::iterator Find2 = Find->second.find(AniRenderTop->GetAnimationFrameIndex());
		if (Find2 == Find->second.end())
		{
			break;
		}

		TopBodyPivot = Find2->second.Pivot;

		TopFrameIndex = Find2->first;
		TopFrameTime = Find2->second.FrameTime;
		break;
	}

	while (true)
	{
		std::map<GJHString, std::map<int, AniData>>::iterator Find = AnimationDataBottom.find(PlayerState.CurState);
		if (Find == AnimationDataBottom.end())
		{
			break;
		}

		std::map<int, AniData>::iterator Find2 = Find->second.find(AniRenderBottom->GetAnimationFrameIndex());
		if (Find2 == Find->second.end())
		{
			break;
		}

		BottomBodyPivot = Find2->second.Pivot;

		BottomFrameIndex = Find2->first;
		BottomFrameTime = Find2->second.FrameTime;
		break;
	}

	while (true)
	{
		std::map<GJHString, std::map<int, PivotData>>::iterator Find = CorrectionTopBody.find(PlayerState.CurState);
		if (Find == CorrectionTopBody.end())
		{
			break;
		}

		std::map<int, PivotData>::iterator Find2 = Find->second.find(AniRenderBottom->GetAnimationFrameIndex());
		if (Find2 == Find->second.end())
		{
			break;
		}

		TopBodyPivot += Find2->second;
		break;
	}

	if (TopFrameIndex != -1)
	{
		AniRenderTop->SetFrameTime(TopFrameIndex, TopFrameTime);
	}
	if (BottomFrameIndex != -1)
	{
		AniRenderBottom->SetFrameTime(BottomFrameIndex, BottomFrameTime);
	}

	if (m_Jump == true)
	{
		SetCurDirState(JumpDirState);
	}

	AniRenderTop->SetAddActorPivot({ TopBodyPivot.x, TopBodyPivot.y });
	AniRenderBottom->SetAddActorPivot({ BottomBodyPivot.x, BottomBodyPivot.y });

	std::set<GJHString>::iterator Find = TopBodyDrawSkip.find(PlayerState.CurState);
	if (Find == TopBodyDrawSkip.end())
	{
		AniRenderTop->SetDraw(true);
	}
	else
	{
		AniRenderTop->SetDraw(false);
	}

	if (m_Sit == true)
	{
		SetCollisionPivot({ 0, -40 });
		SetCollisionSize({ 80, 50 });
	}
	else
	{
		SetCollisionPivot({ 0, -70 });
		SetCollisionSize({ 80, 130 });
	}
}

void Player::PushAnimationData(const GJHString& _Name, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime, ENUM_BODYTYPE _BodyType)
{
	if (_BodyType == ENUM_BODYTYPE::TOP)
	{
		AniData Data;
		Data.Pivot.x = (float)_PivotX;
		Data.Pivot.y = (float)_PivotY;
		Data.FrameTime = _FrameTime;

		std::map<GJHString, std::map<int, AniData>>::iterator Find = AnimationDataTop.find(_Name);

		if (Find == AnimationDataTop.end())
		{
			AnimationDataTop.insert(std::map<GJHString, std::map<int, AniData>>::value_type(_Name, std::map<int, AniData>()));

			Find = AnimationDataTop.find(_Name);
		}

		Find->second.insert(std::map<int, AniData>::value_type(_FrameIndex, Data));
	}
	else
	{
		AniData Data;
		Data.Pivot.x = (float)_PivotX;
		Data.Pivot.y = (float)_PivotY;
		Data.FrameTime = _FrameTime;

		std::map<GJHString, std::map<int, AniData>>::iterator Find = AnimationDataBottom.find(_Name);

		if (Find == AnimationDataBottom.end())
		{
			AnimationDataBottom.insert(std::map<GJHString, std::map<int, AniData>>::value_type(_Name, std::map<int, AniData>()));

			Find = AnimationDataBottom.find(_Name);
		}

		Find->second.insert(std::map<int, AniData>::value_type(_FrameIndex, Data));
	}
}

void Player::PushCorrectionTopBody(const GJHString& _Name, int _BottomFrameIndex, float _TopPivotX, float _TopPivotY)
{
	{
		PivotData Data;
		Data.x = _TopPivotX;
		Data.y = _TopPivotY;

		std::map<GJHString, std::map<int, PivotData>>::iterator Find = CorrectionTopBody.find(_Name);

		if (Find == CorrectionTopBody.end())
		{
			CorrectionTopBody.insert(std::map<GJHString, std::map<int, PivotData>>::value_type(_Name, std::map<int, PivotData>()));

			Find = CorrectionTopBody.find(_Name);
		}

		std::map<int, PivotData>::iterator Find2 = Find->second.find(_BottomFrameIndex);

		if (Find2 != Find->second.end())
		{
			AssertMsg("if (Find2 != Find->second.end())");
		}

		Find->second.insert(std::map<int, PivotData>::value_type(_BottomFrameIndex, Data));
	}
}

void Player::SetDefaultAniData()
{
	float Delay;

	{
		Delay = 0.12f;
		PushAnimationData("Idle_Basic", 0, 11, -34, 0.18f);
		PushAnimationData("Idle_Basic", 1, 11, -34, Delay);
		PushAnimationData("Idle_Basic", 2, 12, -34, Delay);
		PushAnimationData("Idle_Basic", 3, 12, -34, Delay);
		PushAnimationData("Idle_Basic", 15, 0, 0, 0.18f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Idle_Basic", 16, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Idle_Basic", 17, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Idle_Basic", 18, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.05f;
		PushAnimationData("Move_Basic", 9, 19, -37, Delay);
		PushAnimationData("Move_Basic", 10, 14, -39, Delay);
		PushAnimationData("Move_Basic", 11, 14, -37, Delay);
		PushAnimationData("Move_Basic", 12, 15, -39, Delay);
		PushAnimationData("Move_Basic", 13, 13, -37, Delay);
		PushAnimationData("Move_Basic", 14, 10, -36, Delay);
		PushAnimationData("Move_Basic", 15, 15, -38, Delay);
		PushAnimationData("Move_Basic", 16, 19, -39, Delay);
		PushAnimationData("Move_Basic", 17, 20, -38, Delay);
		PushAnimationData("Move_Basic", 18, 17, -37, Delay);
		PushAnimationData("Move_Basic", 19, 15, -34, Delay);
		PushAnimationData("Move_Basic", 20, 16, -36, Delay);
		PushAnimationData("Move_Basic", 25, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 26, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 27, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 28, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 29, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 30, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 31, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 32, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 33, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 34, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 35, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Move_Basic", 36, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("StopMove_Basic", 37, 14, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("StopMove_Basic", 38, 14, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("StopMove_Basic", 39, 14, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("StopMove_Basic", 40, 14, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("IdleAttack_Basic", 102, 51, -55, Delay);
		PushAnimationData("IdleAttack_Basic", 103, 50, -55, Delay);
		PushAnimationData("IdleAttack_Basic", 104, 49, -55, Delay);
		PushAnimationData("IdleAttack_Basic", 105, 11, -55, Delay);
		PushAnimationData("IdleAttack_Basic", 106, 13, -55, Delay);
		PushAnimationData("IdleAttack_Basic", 107, 22, -55, Delay * 2.f);
		PushAnimationData("IdleAttack_Basic", 108, 21, -55, Delay * 2.f);
		PushAnimationData("IdleAttack_Basic", 109, 21, -55, Delay * 2.f);
		PushAnimationData("IdleAttack_Basic", 110, 17, -41, Delay * 2.f);
		PushAnimationData("IdleAttack_Basic", 111, 12, -37, Delay * 2.f);
	}

	{
		Delay = 0.04f;
		PushAnimationData("MoveAttack_Basic", 102, 51, -55, Delay);
		PushAnimationData("MoveAttack_Basic", 103, 50, -55, Delay);
		PushAnimationData("MoveAttack_Basic", 104, 49, -55, Delay);
		PushAnimationData("MoveAttack_Basic", 105, 11, -55, Delay);
		PushAnimationData("MoveAttack_Basic", 106, 13, -55, Delay);
		PushAnimationData("MoveAttack_Basic", 107, 22, -55, Delay * 2.f);
		PushAnimationData("MoveAttack_Basic", 108, 21, -55, Delay * 2.f);
		PushAnimationData("MoveAttack_Basic", 109, 21, -55, Delay * 2.f);
		PushAnimationData("MoveAttack_Basic", 110, 17, -41, Delay * 2.f);
		PushAnimationData("MoveAttack_Basic", 111, 12, -37, Delay * 2.f);
		PushCorrectionTopBody("MoveAttack_Basic", 25, 5, -4);
		PushCorrectionTopBody("MoveAttack_Basic", 26, 2, -2);
		PushCorrectionTopBody("MoveAttack_Basic", 27, 3, -3);
		PushCorrectionTopBody("MoveAttack_Basic", 28, 3, -6);
		PushCorrectionTopBody("MoveAttack_Basic", 29, 3, -6);
		PushCorrectionTopBody("MoveAttack_Basic", 30, -2, -1);
		PushCorrectionTopBody("MoveAttack_Basic", 31, 5, -3);
		PushCorrectionTopBody("MoveAttack_Basic", 32, 9, 1);
		PushCorrectionTopBody("MoveAttack_Basic", 33, 7, -5);
		PushCorrectionTopBody("MoveAttack_Basic", 34, 4, -6);
		PushCorrectionTopBody("MoveAttack_Basic", 35, 4, -6);
		PushCorrectionTopBody("MoveAttack_Basic", 36, 4, -6);

		Delay = 0.05f;
		PushAnimationData("MoveAttack_Basic", 25, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 26, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 27, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 28, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 29, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 30, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 31, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 32, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 33, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 34, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 35, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveAttack_Basic", 36, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("LookUpStart_Basic", 73, 17, -55, Delay);
		PushAnimationData("LookUpStart_Basic", 74, 21, -55, Delay);
	}

	{
		Delay = 0.11f;
		PushAnimationData("LookUpLoop_Basic", 75, 8, -55, Delay * 1.5f);
		PushAnimationData("LookUpLoop_Basic", 76, 8, -55, Delay);
		PushAnimationData("LookUpLoop_Basic", 77, 10, -55, Delay);
		PushAnimationData("LookUpLoop_Basic", 78, 10, -55, Delay);
	}

	{
		Delay = 0.06f;
		PushAnimationData("LookUpEnd_Basic", 73, 17, -55, Delay);
		PushAnimationData("LookUpEnd_Basic", 74, 21, -55, Delay);
	}

	{
		Delay = 0.04f;
		PushAnimationData("LookUpAttack_Basic", 112, -8, -56, Delay);
		PushAnimationData("LookUpAttack_Basic", 113, -11, -56, Delay);
		PushAnimationData("LookUpAttack_Basic", 114, -11, -56, Delay);
		PushAnimationData("LookUpAttack_Basic", 115, -11, -56, Delay);
		PushAnimationData("LookUpAttack_Basic", 116, -11, -56, Delay * 2.f);
		PushAnimationData("LookUpAttack_Basic", 117, -13, -56, Delay * 2.f);
		PushAnimationData("LookUpAttack_Basic", 118, -9, -56, Delay * 2.f);
		PushAnimationData("LookUpAttack_Basic", 119, -4, -56, Delay * 2.f);
		PushAnimationData("LookUpAttack_Basic", 120, -3, -56, Delay * 2.f);
		PushAnimationData("LookUpAttack_Basic", 121, 1, -56, Delay * 2.f);
	}

	{
		Delay = 0.06f;
		PushAnimationData("MoveLookUpStart_Basic", 73, 17, -50,Delay);
		PushAnimationData("MoveLookUpStart_Basic", 74, 21, -50,Delay);

		Delay = 0.05f;
		PushAnimationData("MoveLookUpStart_Basic", 25, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 26, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 27, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 28, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 29, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 30, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 31, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 32, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 33, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 34, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 35, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpStart_Basic", 36, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.11f;
		PushAnimationData("MoveLookUpLoop_Basic", 75, 8, -50, Delay * 1.5f);
		PushAnimationData("MoveLookUpLoop_Basic", 76, 8, -50, Delay);
		PushAnimationData("MoveLookUpLoop_Basic", 77, 10, -50, Delay);
		PushAnimationData("MoveLookUpLoop_Basic", 78, 10, -50, Delay);

		Delay = 0.05f;
		PushAnimationData("MoveLookUpLoop_Basic", 25, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 26, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 27, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 28, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 29, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 30, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 31, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 32, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 33, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 34, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 35, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpLoop_Basic", 36, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 25, 2, -11);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 26, 2, -9);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 27, 2, -9);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 28, 2, -11);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 29, 2, -8);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 30, 0, -5);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 31, 1, -8);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 32, -1, -10);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 33, 0, -10);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 34, 1, -8);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 35, -2, -6);
		PushCorrectionTopBody("MoveLookUpLoop_Basic", 36, -1, -8);
	}

	{
		Delay = 0.06f;
		PushAnimationData("MoveLookUpEnd_Basic", 73, 17, -50, Delay);
		PushAnimationData("MoveLookUpEnd_Basic", 74, 21, -50, Delay);

		Delay = 0.05f;
		PushAnimationData("MoveLookUpEnd_Basic", 25, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 26, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 27, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 28, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 29, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 30, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 31, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 32, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 33, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 34, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 35, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpEnd_Basic", 36, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("MoveLookUpAttack_Basic", 112, -8, -51, Delay);
		PushAnimationData("MoveLookUpAttack_Basic", 113, -11, -51, Delay);
		PushAnimationData("MoveLookUpAttack_Basic", 114, -11, -51, Delay);
		PushAnimationData("MoveLookUpAttack_Basic", 115, -11, -51, Delay);
		PushAnimationData("MoveLookUpAttack_Basic", 116, -11, -51, Delay * 2.f);
		PushAnimationData("MoveLookUpAttack_Basic", 117, -13, -51, Delay * 2.f);
		PushAnimationData("MoveLookUpAttack_Basic", 118, -9, -51, Delay * 2.f);
		PushAnimationData("MoveLookUpAttack_Basic", 119, -4, -51, Delay * 2.f);
		PushAnimationData("MoveLookUpAttack_Basic", 120, -3, -51, Delay * 2.f);
		PushAnimationData("MoveLookUpAttack_Basic", 121, 1, -51, Delay * 2.f);

		Delay = 0.05f;
		PushAnimationData("MoveLookUpAttack_Basic", 25, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 26, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 27, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 28, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 29, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 30, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 31, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 32, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 33, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 34, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 35, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveLookUpAttack_Basic", 36, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 25, 2, -11);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 26, 2, -9);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 27, 2, -9);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 28, 2, -11);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 29, 2, -8);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 30, 0, -5);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 31, 1, -8);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 32, -1, -10);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 33, 0, -10);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 34, 1, -8);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 35, -2, -6);
		PushCorrectionTopBody("MoveLookUpAttack_Basic", 36, -1, -8);
	}

	{
		Delay = 0.03f;
		PushAnimationData("SitStart_Basic", 84, 12, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitStart_Basic", 85, 9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitStart_Basic", 86, 24, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.12f;
		PushAnimationData("SitLoop_Basic", 91, 10, 4, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitLoop_Basic", 92, 10, 4, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitLoop_Basic", 93, 10, 4, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitLoop_Basic", 94, 10, 4, 0.16f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.08f;
		PushAnimationData("SitMove_Basic", 95, 10, 5, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 96, 10, 5, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 97, 10, 5, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 98, 10, 5, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 99, 10, 5, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 100, 10, 5, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 101, 10, 5, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("SitAttack_Basic", 128, 51, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 129, 51, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 130, 49, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 131, 11, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 132, 12, 0, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 133, 22, 0, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 134, 22, 0, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 135, 22, 0, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 136, 18, 0, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 137, 21, 0, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.15f;
		PushAnimationData("SitAttackLoop_Basic", 138, 16, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttackLoop_Basic", 139, 13, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttackLoop_Basic", 140, 10, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttackLoop_Basic", 141, 13, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.03f;
		PushAnimationData("SitEnd_Basic", 84, 12, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitEnd_Basic", 85, 9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitEnd_Basic", 86, 24, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("Jump_Basic", 41, -5, -78, Delay);
		PushAnimationData("Jump_Basic", 42, -7, -78, Delay);
		PushAnimationData("Jump_Basic", 43, -7, -78, Delay);
		PushAnimationData("Jump_Basic", 44, -7, -78, Delay * 5.5f);
		PushAnimationData("Jump_Basic", 45, -7, -78, Delay);
		PushAnimationData("Jump_Basic", 46, -7, -78, Delay);
		PushAnimationData("Jump_Basic", 47, -6, -78, Delay);
		PushAnimationData("Jump_Basic", 48, -9, -78, Delay);
		PushAnimationData("Jump_Basic", 49, -9, -74, Delay * 2.f);
		PushAnimationData("Jump_Basic", 50, -9, -77, Delay * 2.f);
		PushAnimationData("Jump_Basic", 51, -5, -77, Delay);

		PushAnimationData("Jump_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("MoveJump_Basic", 52, -25, -30,Delay);
		PushAnimationData("MoveJump_Basic", 53, -19, -27,Delay * 2.f);
		PushAnimationData("MoveJump_Basic", 54, -15, -31,Delay * 6.f);
		PushAnimationData("MoveJump_Basic", 55, -13, -26,Delay * 2.f);
		PushAnimationData("MoveJump_Basic", 56, -20, -34,Delay * 2.f);
		PushAnimationData("MoveJump_Basic", 57, -20, -44,Delay);

		PushAnimationData("MoveJump_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("JumpAttack_Basic", 102, 51, -75,Delay);
		PushAnimationData("JumpAttack_Basic", 103, 50, -75,Delay);
		PushAnimationData("JumpAttack_Basic", 104, 49, -75,Delay);
		PushAnimationData("JumpAttack_Basic", 105, 11, -75,Delay);
		PushAnimationData("JumpAttack_Basic", 106, 13, -75,Delay);
		PushAnimationData("JumpAttack_Basic", 107, 22, -75,Delay * 2.f);
		PushAnimationData("JumpAttack_Basic", 108, 21, -75,Delay * 2.f);
		PushAnimationData("JumpAttack_Basic", 109, 21, -71,Delay * 2.f);
		PushAnimationData("JumpAttack_Basic", 110, 17, -61,Delay * 2.f);
		PushAnimationData("JumpAttack_Basic", 111, 12, -57,Delay * 2.f);

		Delay = 0.06f;
		PushAnimationData("JumpAttack_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("MoveJumpAttack_Basic", 102, 36, -65, Delay);
		PushAnimationData("MoveJumpAttack_Basic", 103, 35, -65, Delay);
		PushAnimationData("MoveJumpAttack_Basic", 104, 34, -65, Delay);
		PushAnimationData("MoveJumpAttack_Basic", 105, -4, -65, Delay);
		PushAnimationData("MoveJumpAttack_Basic", 106, -2, -65, Delay);
		PushAnimationData("MoveJumpAttack_Basic", 107, 7, -65, Delay * 2.f);
		PushAnimationData("MoveJumpAttack_Basic", 108, 6, -65, Delay * 2.f);
		PushAnimationData("MoveJumpAttack_Basic", 109, 6, -61, Delay * 2.f);
		PushAnimationData("MoveJumpAttack_Basic", 110, 2, -51, Delay * 2.f);
		PushAnimationData("MoveJumpAttack_Basic", 111, -3, -47, Delay * 2.f);

		Delay = 0.06f;
		PushAnimationData("MoveJumpAttack_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("JumpLookUpStart_Basic", 73, 17, -75, Delay);
		PushAnimationData("JumpLookUpStart_Basic", 74, 21, -75, Delay);

		PushAnimationData("JumpLookUpStart_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpStart_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpStart_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpStart_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpStart_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpStart_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}
	
	{
		Delay = 0.11f;
		PushAnimationData("JumpLookUpLoop_Basic", 75, 8, -75, Delay * 1.5f);
		PushAnimationData("JumpLookUpLoop_Basic", 76, 8, -75, Delay);
		PushAnimationData("JumpLookUpLoop_Basic", 77, 10, -75, Delay);
		PushAnimationData("JumpLookUpLoop_Basic", 78, 10, -75, Delay);

		Delay = 0.06f;
		PushAnimationData("JumpLookUpLoop_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("JumpLookUpEnd_Basic", 73, 17, -75,Delay);
		PushAnimationData("JumpLookUpEnd_Basic", 74, 21, -75,Delay);

		PushAnimationData("JumpLookUpEnd_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);

		Delay = 0.12f;
		PushAnimationData("JumpLookUpEnd_Basic", 0, 11, -54, 0.18f);
		PushAnimationData("JumpLookUpEnd_Basic", 1, 11, -54, Delay);
		PushAnimationData("JumpLookUpEnd_Basic", 2, 12, -54, Delay);
		PushAnimationData("JumpLookUpEnd_Basic", 3, 12, -54, Delay);
		PushAnimationData("JumpLookUpEnd_Basic", 15, 0, 0, 0.18f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 16, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 17, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpEnd_Basic", 18, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("JumpLookUpAttack_Basic", 112, -8, -76, Delay);
		PushAnimationData("JumpLookUpAttack_Basic", 113, -11, -76, Delay);
		PushAnimationData("JumpLookUpAttack_Basic", 114, -11, -76, Delay);
		PushAnimationData("JumpLookUpAttack_Basic", 115, -11, -76, Delay);
		PushAnimationData("JumpLookUpAttack_Basic", 116, -11, -76, Delay * 2.f);
		PushAnimationData("JumpLookUpAttack_Basic", 117, -13, -76, Delay * 2.f);
		PushAnimationData("JumpLookUpAttack_Basic", 118, -9, -76, Delay * 2.f);
		PushAnimationData("JumpLookUpAttack_Basic", 119, -4, -76, Delay * 2.f);
		PushAnimationData("JumpLookUpAttack_Basic", 120, -3, -76, Delay * 2.f);
		PushAnimationData("JumpLookUpAttack_Basic", 121, 1, -76, Delay * 2.f);

		Delay = 0.06f;
		PushAnimationData("JumpLookUpAttack_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpAttack_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpAttack_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpAttack_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpAttack_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpAttack_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("MoveJumpLookUpStart_Basic", 73, 17, -65, Delay);
		PushAnimationData("MoveJumpLookUpStart_Basic", 74, 21, -65, Delay);

		PushAnimationData("MoveJumpLookUpStart_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpStart_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpStart_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpStart_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpStart_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpStart_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpStart_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpStart_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookUpStart_Basic", 72, -9, 6);
	}

	{
		Delay = 0.11f;
		PushAnimationData("MoveJumpLookUpLoop_Basic", 75, 8, -65, Delay * 1.5f);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 76, 8, -65, Delay);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 77, 10, -65, Delay);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 78, 10, -65, Delay);

		Delay = 0.06f;
		PushAnimationData("MoveJumpLookUpLoop_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookUpLoop_Basic", 72, -9, 6);
	}

	{
		Delay = 0.06f;
		PushAnimationData("MoveJumpLookUpEnd_Basic", 73, 17, -65, Delay);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 74, 21, -65, Delay);

		PushAnimationData("MoveJumpLookUpEnd_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookUpEnd_Basic", 72, -9, 6);

		Delay = 0.12f;
		PushAnimationData("MoveJumpLookUpEnd_Basic", 0, 11, -54, 0.18f);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 1, 11, -54, Delay);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 2, 12, -54, Delay);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 3, 12, -54, Delay);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 15, 0, 0, 0.18f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 16, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 17, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpEnd_Basic", 18, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("MoveJumpLookUpAttack_Basic", 112, -8, -66,  Delay);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 113, -11, -66, Delay);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 114, -11, -66, Delay);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 115, -11, -66, Delay);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 116, -11, -66, Delay * 2.f);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 117, -13, -66, Delay * 2.f);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 118, -9, -66, Delay * 2.f);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 119, -4, -66, Delay * 2.f);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 120, -3, -66, Delay * 2.f);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 121, 1, -66, Delay * 2.f);

		Delay = 0.06f;
		PushAnimationData("MoveJumpLookUpAttack_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpAttack_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookUpAttack_Basic", 72, -9, 6);
	}

	{
		Delay = 0.08f;
		PushAnimationData("JumpLookDownStart_Basic", 81, 0, -50, Delay);
		PushAnimationData("JumpLookDownStart_Basic", 82, 2, -33, Delay);

		Delay = 0.06f;
		PushAnimationData("JumpLookDownStart_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("JumpLookDownLoop_Basic", 83, 2, -28, Delay);

		PushAnimationData("JumpLookDownLoop_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.08f;
		PushAnimationData("JumpLookDownEnd_Basic", 81, 0, -50,Delay);
		PushAnimationData("JumpLookDownEnd_Basic", 82, 2, -33,Delay);

		Delay = 0.06f;
		PushAnimationData("JumpLookDownEnd_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);

		Delay = 0.12f;
		PushAnimationData("JumpLookDownEnd_Basic", 0, 11, -54, 0.18f);
		PushAnimationData("JumpLookDownEnd_Basic", 1, 11, -54, Delay);
		PushAnimationData("JumpLookDownEnd_Basic", 2, 12, -54, Delay);
		PushAnimationData("JumpLookDownEnd_Basic", 3, 12, -54, Delay);
		PushAnimationData("JumpLookDownEnd_Basic", 15, 0, 0, 0.18f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 16, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 17, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownEnd_Basic", 18, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("JumpLookDownAttack_Basic", 122, 4, 31, Delay);
		PushAnimationData("JumpLookDownAttack_Basic", 123, 2, 37, Delay);
		PushAnimationData("JumpLookDownAttack_Basic", 124, 4, 44, Delay);
		PushAnimationData("JumpLookDownAttack_Basic", 125, 9, -52, Delay);
		PushAnimationData("JumpLookDownAttack_Basic", 126, 5, -36, Delay * 2.f);
		PushAnimationData("JumpLookDownAttack_Basic", 127, 3, -34, Delay * 2.f);

		Delay = 0.06f;
		PushAnimationData("JumpLookDownAttack_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.08f;
		PushAnimationData("MoveJumpLookDownStart_Basic", 81, 0, -40, Delay);
		PushAnimationData("MoveJumpLookDownStart_Basic", 82, 2, -23, Delay);

		Delay = 0.06f;
		PushAnimationData("MoveJumpLookDownStart_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownStart_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownStart_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownStart_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownStart_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownStart_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownStart_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownStart_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookDownStart_Basic", 72, -9, 6);
	}

	{
		Delay = 0.06f;
		PushAnimationData("MoveJumpLookDownLoop_Basic", 83, 2, -18, Delay);

		PushAnimationData("MoveJumpLookDownLoop_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownLoop_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownLoop_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownLoop_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownLoop_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownLoop_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownLoop_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownLoop_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookDownLoop_Basic", 72, -9, 6);
	}

	{
		Delay = 0.08f;
		PushAnimationData("MoveJumpLookDownEnd_Basic", 81, 0, -40, Delay);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 82, 2, -23, Delay);

		Delay = 0.06f;
		PushAnimationData("MoveJumpLookDownEnd_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookDownEnd_Basic", 72, -9, 6);

		Delay = 0.12f;
		PushAnimationData("MoveJumpLookDownEnd_Basic", 0, 11, -54, 0.18f);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 1, 11, -54, Delay);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 2, 12, -54, Delay);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 3, 12, -54, Delay);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 15, 0, 0, 0.18f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 16, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 17, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownEnd_Basic", 18, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.04f;
		PushAnimationData("MoveJumpLookDownAttack_Basic", 122, 4, 41, Delay);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 123, 2, 47, Delay);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 124, 4, 54, Delay);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 125, 9, -42, Delay);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 126, 5, -26, Delay * 2.f);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 127, 3, -24, Delay * 2.f);

		Delay = 0.06f;
		PushAnimationData("MoveJumpLookDownAttack_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookDownAttack_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpLookDownAttack_Basic", 72, -9, 6);
	}

	{
		Delay = 0.05f;
		PushAnimationData("ThrowGranade_Basic", 142, 10, -34, Delay);
		PushAnimationData("ThrowGranade_Basic", 143, 15, -34, Delay);
		PushAnimationData("ThrowGranade_Basic", 144, 13, -34, Delay);
		PushAnimationData("ThrowGranade_Basic", 145, 13, -34, Delay);
		PushAnimationData("ThrowGranade_Basic", 146, 13, -34, Delay * 4.f);
		PushAnimationData("ThrowGranade_Basic", 147, 13, -34, Delay);
	}

	{
		Delay = 0.05f;
		PushAnimationData("MoveThrowGranade_Basic", 142, 10, -34, Delay);
		PushAnimationData("MoveThrowGranade_Basic", 143, 15, -34, Delay);
		PushAnimationData("MoveThrowGranade_Basic", 144, 13, -34, Delay);
		PushAnimationData("MoveThrowGranade_Basic", 145, 13, -34, Delay);
		PushAnimationData("MoveThrowGranade_Basic", 146, 13, -34, Delay * 4.f);
		PushAnimationData("MoveThrowGranade_Basic", 147, 13, -34, Delay);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 25, 5, -4);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 26, 2, -2);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 27, 3, -3);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 28, 3, -6);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 29, 3, -6);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 30, -2, -1);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 31, 5, -3);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 32, 9, 1);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 33, 7, -5);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 34, 4, -6);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 35, 4, -6);
		PushCorrectionTopBody("MoveThrowGranade_Basic", 36, 4, -6);

		Delay = 0.05f;
		PushAnimationData("MoveThrowGranade_Basic", 25, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 26, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 27, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 28, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 29, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 30, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 31, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 32, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 33, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 34, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 35, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveThrowGranade_Basic", 36, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.15f;
		PushAnimationData("SitThrowGranade_Basic", 155, 0, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.05f;
		PushAnimationData("JumpThrowGranade_Basic", 142, 10, -54, Delay);
		PushAnimationData("JumpThrowGranade_Basic", 143, 15, -54, Delay);
		PushAnimationData("JumpThrowGranade_Basic", 144, 13, -54, Delay);
		PushAnimationData("JumpThrowGranade_Basic", 145, 13, -54, Delay);
		PushAnimationData("JumpThrowGranade_Basic", 146, 13, -54, Delay * 4.f);
		PushAnimationData("JumpThrowGranade_Basic", 147, 13, -54, Delay);

		Delay = 0.06f;
		PushAnimationData("JumpThrowGranade_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpThrowGranade_Basic", 59, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpThrowGranade_Basic", 60, 0, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpThrowGranade_Basic", 61, 3, -7, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpThrowGranade_Basic", 62, 5, -20, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpThrowGranade_Basic", 63, 5, -30, Delay * 3.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.05f;
		PushAnimationData("MoveJumpThrowGranade_Basic", 142, 10, -44, Delay);
		PushAnimationData("MoveJumpThrowGranade_Basic", 143, 15, -44, Delay);
		PushAnimationData("MoveJumpThrowGranade_Basic", 144, 13, -44, Delay);
		PushAnimationData("MoveJumpThrowGranade_Basic", 145, 13, -44, Delay);
		PushAnimationData("MoveJumpThrowGranade_Basic", 146, 13, -44, Delay * 4.f);
		PushAnimationData("MoveJumpThrowGranade_Basic", 147, 13, -44, Delay);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 64, -13, 5);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 65, -13, -5);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 66, -8, 0);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 67, -5, 0);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 68, -6, -4);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 69, -2, 6);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 70, -2, 6);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 71, -5, 6);
		PushCorrectionTopBody("MoveJumpThrowGranade_Basic", 72, -9, 6);

		Delay = 0.06f;
		PushAnimationData("MoveJumpThrowGranade_Basic", 65, 0, -15, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpThrowGranade_Basic", 66, 0, -15, Delay * 2.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpThrowGranade_Basic", 67, 0, -25, Delay * 5.f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpThrowGranade_Basic", 68, -5, -25, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpThrowGranade_Basic", 69, -5, -15, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpThrowGranade_Basic", 70, -9, -5, Delay * 1.5f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpThrowGranade_Basic", 71, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpThrowGranade_Basic", 72, -9, 0, Delay, ENUM_BODYTYPE::BOTTOM);
	}

	{
		Delay = 0.06f;
		PushAnimationData("Parachute_Basic", 41, -5, -78, Delay);
		PushAnimationData("Parachute_Basic", 58, 0, 0, Delay * 0.5f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("Victory_Basic", 225, 0, 0, 0.19f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Victory_Basic", 226, 0, 0, 0.13f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Victory_Basic", 227, 0, 0, 0.13f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Victory_Basic", 228, 2, 0, 0.13f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Victory_Basic", 229, 0, 0, 0.13f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Victory_Basic", 230, -3, 0, 0.13f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("Death_Basic", 0, 10, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 1, 5, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 2, 5, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 3, -2, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 4, -16, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 5, -20, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 6, -17, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 7, -17, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 8, -11, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 9, -15, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 10, -15, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 11, -18, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 12, -24, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 13, -20, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 14, -17, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 15, -16, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 16, -18, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 17, -18, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 18, -9, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 19, 0, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 20, 0, 0, 0.25f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("Alive_Basic", 0, 0, 0, 0.025f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Alive_Basic", 1, 0, 0, 0.025f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Alive_Basic", 2, 0, 0, 0.025f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Alive_Basic", 3, 0, 0, 0.025f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Alive_Basic", 4, 0, 0, 0.025f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Alive_Basic", 5, 0, 0, 0.025f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Alive_Basic", 6, 0, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
	}

	PushAnimationData("Idle_HeavyMachineGun", 0, 29, -38, 0.15f);
	PushAnimationData("Idle_HeavyMachineGun", 1, 30, -34, 0.12f);
	PushAnimationData("Idle_HeavyMachineGun", 2, 28, -34, 0.12f);
	PushAnimationData("Idle_HeavyMachineGun", 3, 28, -34, 0.12f);
	PushAnimationData("Idle_HeavyMachineGun", 231, 0, 0, 0.20f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("Move_HeavyMachineGun", 4, 38, -44, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 5, 32, -46, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 6, 34, -44, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 7, 35, -46, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 8, 32, -44, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 9, 29, -43, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 10, 35, -45, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 11, 38, -45, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 12, 39, -44, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 13, 36, -44, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 14, 36, -44, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 15, 37, -46, 0.05f);
	PushAnimationData("Move_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Move_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("StopMove_HeavyMachineGun", 0, 0, 0, 0.05f);
	PushAnimationData("StopMove_HeavyMachineGun", 16, 29, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("StopMove_HeavyMachineGun", 17, 28, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("StopMove_HeavyMachineGun", 18, 26, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("StopMove_HeavyMachineGun", 19, 22, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("IdleAttack_HeavyMachineGun", 70, 67, -37, 0.03f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 71, 69, -34, 0.03f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 72, 65, -37, 0.03f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 73, 65, -34, 0.03f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 231, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 134, 25, -40, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 135, 23, -37, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 136, 27, -42, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 137, 25, -39, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 138, 29, -39, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("IdleAttackUp_HeavyMachineGun", 77, 55, -55, 0.05f);
	PushAnimationData("IdleAttackUp_HeavyMachineGun", 78, 53, -55, 0.05f);
	PushAnimationData("IdleAttackUp_HeavyMachineGun", 231, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveAttack_HeavyMachineGun", 70, 72, -42, 0.03f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 71, 72, -37, 0.03f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 72, 68, -40, 0.03f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 73, 68, -40, 0.03f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 236, 5, -4);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 237, 2, -2);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 238, 3, -3);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 239, 3, -6);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 240, 3, -6);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 241, -2, -1);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 242, 5, -3);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 243, 9, 1);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 244, 7, -5);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 245, 4, -6);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 246, 4, -6);
	PushCorrectionTopBody("MoveAttack_HeavyMacineGun", 247, 4, -6);

	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 134, 30, -44, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 135, 28, -43, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 136, 33, -51, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 137, 30, -46, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 138, 35, -47, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveAttackUp_HeavyMachineGun", 77, 59, -60, 0.04f);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 78, 58, -60, 0.04f);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpStart_HeavyMachineGun", 31, 17, -55, 0.06f);
	PushAnimationData("LookUpStart_HeavyMachineGun", 32, 17, -55, 0.06f);
	PushAnimationData("LookUpStart_HeavyMachineGun", 231, 0, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpLoop_HeavyMachineGun", 36, 18, -55, 0.11f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 37, 21, -55, 0.11f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 38, 22, -55, 0.11f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 39, 22, -55, 0.11f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 231, 0, 0, 0.11f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpEnd_HeavyMachineGun", 85, 15, -55, 0.06f);
	PushAnimationData("LookUpEnd_HeavyMachineGun", 86, 15, -55, 0.06f);
	PushAnimationData("LookUpEnd_HeavyMachineGun", 87, 17, -55, 0.06f);
	PushAnimationData("LookUpEnd_HeavyMachineGun", 231, 0, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpAttack_HeavyMachineGun", 79, -7, -55, 0.03f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 80, -13, -55, 0.03f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 81, -11, -55, 0.03f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 82, -11, -55, 0.03f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpAttackDown_HeavyMachineGun", 83, 33, -55, 0.04f);
	PushAnimationData("LookUpAttackDown_HeavyMachineGun", 84, 50, -55, 0.04f);
	PushAnimationData("LookUpAttackDown_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 109, -6, -56, 0.06f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 110, -10, -56, 0.06f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 111, -10, -56, 0.06f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 112, -10, -56, 0.06f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 113, -12, -56, 0.06f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 114, -10, -56, 0.06f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 31, 17, -55, 0.05f);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 32, 18, -55, 0.05f);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 36, 18, -55, 0.05f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 37, 21, -55, 0.05f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 38, 23, -55, 0.05f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 39, 23, -55, 0.05f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 236, 2, -11);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 237, 2, -9);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 238, 2, -9);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 239, 2, -11);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 240, 2, -8);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 241, 0, -5);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 242, 1, -8);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 243, -1, -10);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 244, 0, -10);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 245, 1, -8);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 246, -2, -6);
	PushCorrectionTopBody("MoveLookUpLoop_HeavyMachineGun", 247, -1, -8);

	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 85, 15, -50, 0.05f);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 86, 16, -50, 0.05f);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 87, 18, -50, 0.05f);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 79, 0, -60, 0.03f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 80, -6, -60, 0.03f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 81, -4, -60, 0.03f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 82, -4, -60, 0.03f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 236, 2, -3);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 237, 2, -1);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 238, 2, -1);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 239, 2, -3);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 240, 2, 0);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 241, 0, 3);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 242, 1, 0);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 243, -1, -2);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 244, 0, -2);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 245, 1, 0);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 246, -2, 2);
	PushCorrectionTopBody("MoveLookUpAttack_HeavyMachineGun", 247, -1, 0);

	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 109, 1, -61, 0.06f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 110, -3, -61, 0.06f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 111, -3, -61, 0.06f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 112, -3, -61, 0.06f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 113, -5, -61, 0.06f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 114, -3, -61, 0.06f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 236, 2, -3);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 237, 2, -1);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 238, 2, -1);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 239, 2, -3);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 240, 2, 0);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 241, 0, 3);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 242, 1, 0);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 243, -1, -2);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 244, 0, -2);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 245, 1, 0);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 246, -2, 2);
	PushCorrectionTopBody("MoveLookUpAttackEnd_HeavyMachineGun", 247, -1, 0);

	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 83, 41, -60, 0.04f);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 84, 58, -60, 0.04f);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 254, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 255, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 256, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 257, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 258, -5, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 259, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 260, -9, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 261, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 262, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitStart_HeavyMachineGun", 43, 29, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitStart_HeavyMachineGun", 44, 26, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitStart_HeavyMachineGun", 45, 34, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitLoop_HeavyMachineGun", 46, 28, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitLoop_HeavyMachineGun", 47, 27, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitLoop_HeavyMachineGun", 48, 28, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitLoop_HeavyMachineGun", 49, 28, 0, 0.16f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitMove_HeavyMachineGun", 58, 28, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitMove_HeavyMachineGun", 59, 29, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitMove_HeavyMachineGun", 60, 29, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitMove_HeavyMachineGun", 61, 30, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitMove_HeavyMachineGun", 62, 27, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitMove_HeavyMachineGun", 63, 29, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitMove_HeavyMachineGun", 64, 30, 0, 0.08f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitEnd_HeavyMachineGun", 43, 29, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitEnd_HeavyMachineGun", 44, 26, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitEnd_HeavyMachineGun", 45, 34, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitAttack_HeavyMachineGun", 96, 64, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttack_HeavyMachineGun", 97, 63, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttack_HeavyMachineGun", 98, 63, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttack_HeavyMachineGun", 99, 61, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitAttackLoop_HeavyMachineGun", 50, 15, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttackLoop_HeavyMachineGun", 51, 13, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttackLoop_HeavyMachineGun", 52, 13, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttackLoop_HeavyMachineGun", 53, 15, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitAttackEnd_HeavyMachineGun", 121, 3, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttackEnd_HeavyMachineGun", 122, 6, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttackEnd_HeavyMachineGun", 123, 8, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("SitThrowGranade_HeavyMachineGun", 181, -3, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitThrowGranade_HeavyMachineGun", 182, -5, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitThrowGranade_HeavyMachineGun", 183, -7, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitThrowGranade_HeavyMachineGun", 184, 5, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitThrowGranade_HeavyMachineGun", 185, -4, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitThrowGranade_HeavyMachineGun", 186, -3, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("Jump_HeavyMachineGun", 20, 9, -72, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 21, 11, -76, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 22, 11, -76, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 23, 9, -79, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 24, 10, -76, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 25, 10, -76, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 26, 8, -72, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 27, 6, -68, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 28, 6, -64, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 29, 6, -68, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 30, 8, -72, 0.10f);
	PushAnimationData("Jump_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Jump_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Jump_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Jump_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Jump_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("Jump_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJump_HeavyMachineGun", 263, -10, -55, 0.10f);
	PushAnimationData("MoveJump_HeavyMachineGun", 264, -17, -53, 0.10f);
	PushAnimationData("MoveJump_HeavyMachineGun", 265, -15, -60, 0.10f);
	PushAnimationData("MoveJump_HeavyMachineGun", 266, -10, -55, 0.10f);
	PushAnimationData("MoveJump_HeavyMachineGun", 267, -5, -59, 0.10f);
	PushAnimationData("MoveJump_HeavyMachineGun", 268, 1, -55, 0.10f);
	PushAnimationData("MoveJump_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJump_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpAttack_HeavyMachineGun", 70, 66, -57, 0.03f);
	PushAnimationData("JumpAttack_HeavyMachineGun", 71, 69, -55, 0.03f);
	PushAnimationData("JumpAttack_HeavyMachineGun", 72, 66, -58, 0.03f);
	PushAnimationData("JumpAttack_HeavyMachineGun", 73, 66, -55, 0.03f);
	PushAnimationData("JumpAttack_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttack_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttack_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttack_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttack_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttack_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 134, 25, -60, 0.04f);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 135, 24, -57, 0.04f);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 136, 28, -63, 0.04f);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 137, 28, -59, 0.04f);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 138, 31, -59, 0.04f);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 248, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 249, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 250, 0, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 251, 0, -7, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 252, 0, -20, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 253, 0, -30, 0.1f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpAttackUp_HeavyMachineGun", 77, 53, -75, 0.04f);
	PushAnimationData("JumpAttackUp_HeavyMachineGun", 78, 52, -75, 0.04f);
	PushAnimationData("JumpAttackUp_HeavyMachineGun", 248, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackUp_HeavyMachineGun", 249, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackUp_HeavyMachineGun", 250, 0, -5, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackUp_HeavyMachineGun", 251, 0, -7, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackUp_HeavyMachineGun", 252, 0, -20, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackUp_HeavyMachineGun", 253, 0, -30, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpAttackDown_HeavyMachineGun", 88, 52, 5, 0.04f);
	PushAnimationData("JumpAttackDown_HeavyMachineGun", 89, 58, 62, 0.04f);
	PushAnimationData("JumpAttackDown_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackDown_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackDown_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackDown_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackDown_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackDown_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 70, 52, -47, 0.03f);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 71, 54, -44, 0.03f);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 72, 49, -46, 0.03f);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 73, 50, -44, 0.03f);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 134, 10, -50, 0.04f);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 135, 8, -49, 0.04f);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 136, 12, -57, 0.04f);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 137, 10, -52, 0.04f);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 138, 15, -54, 0.04f);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 254, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 255, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 256, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 257, 0, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 258, -5, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 259, -5, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 260, -9, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 261, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 262, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 77, 40, -65, 0.04f);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 78, 39, -65, 0.04f);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 254, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 255, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 256, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 257, 0, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 258, -5, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 259, -5, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 260, -9, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 261, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 262, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 88, 35, 15, 0.04f);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 89, 42, 70, 0.04f);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 254, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 255, 0, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 256, 0, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 257, 0, -25, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 258, -5, -25, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 259, -5, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 260, -9, -5, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 261, -9, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackDown_HeavyMachineGun", 262, -9, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 31, 15, -76, 0.06f);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 32, 15, -76, 0.06f);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 36, 19, -76, 0.11f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 37, 22, -76, 0.11f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 38, 23, -76, 0.11f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 39, 23, -76, 0.11f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 85, 16, -74, 0.06f);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 86, 16, -74, 0.06f);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 87, 18, -74, 0.06f);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 79, -5, -75, 0.03f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 80, -11, -75, 0.03f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 81, -9, -75, 0.03f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 82, -9, -75, 0.03f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 109, -5, -76, 0.06f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 110, -9, -76, 0.06f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 111, -9, -76, 0.06f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 112, -9, -76, 0.06f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 113, -11, -76, 0.06f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 114, -10, -76, 0.06f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 0, 29, -58, 0.15f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 1, 30, -54, 0.12f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 2, 28, -54, 0.12f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 3, 28, -54, 0.12f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 83, 35, -75, 0.04f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 84, 52, -75, 0.04f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 31, 0, -60, 0.06f);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 32, 0, -60, 0.06f);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 36, 0, -60, 0.11f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 37, 3, -59, 0.11f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 38, 5, -59, 0.11f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 39, 5, -59, 0.11f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 0, 19, -48, 0.15f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 1, 20, -44, 0.12f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 2, 18, -44, 0.12f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 3, 18, -44, 0.12f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 85, 5, -60, 0.06f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 86, 5, -60, 0.06f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 87, 7, -60, 0.06f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 254, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 255, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 256, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 257, 0, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 258, -5, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 259, -5, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 260, -9, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 261, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 262, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 79, -20, -65, 0.03f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 80, -26, -65, 0.03f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 81, -24, -65, 0.03f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 82, -24, -65, 0.03f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 254, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 255, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 256, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 257, 0, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 258, -5, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 259, -5, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 260, -9, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 261, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 262, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 109, -20, -66, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 110, -24, -66, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 111, -23, -66, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 112, -23, -66, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 113, -25, -66, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 114, -23, -66, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 254, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 255, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 256, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 257, 0, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 258, -5, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 259, -5, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 260, -9, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 261, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 262, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 77, 42, -65, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 78, 42, -65, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 254, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 255, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 256, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 257, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 258, -5, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 259, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 260, -9, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 261, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackUp_HeavyMachineGun", 262, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 0, 19, -48, 0.15f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 1, 20, -44, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 2, 18, -44, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 3, 18, -44, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 83, 23, -64, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 84, 40, -64, 0.04f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 254, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 255, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 256, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 257, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 258, -5, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 259, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 260, -9, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 261, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 262, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 40, 8, -45, 0.06f);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 41, -2, -10, 0.06f);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookDownLoop_HeavyMachineGun", 42, 13, -11, 0.10f);
	PushAnimationData("JumpLookDownLoop_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownLoop_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownLoop_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownLoop_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownLoop_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownLoop_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 90, 13, 67, 0.03f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 91, 13, 67, 0.03f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 92, 9, 73, 0.03f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 93, 8, 73, 0.03f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 0, 19, -48, 0.15f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 1, 20, -44, 0.12f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 2, 18, -44, 0.12f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 3, 18, -44, 0.12f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 94, 10, 65, 0.03f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 95, 36, 33, 0.03f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 94, 25, 55, 0.03f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 95, 53, 23, 0.03f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 40, 1, -32, 0.06f);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 41, -9, 3, 0.06f);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 42, 0, 5, 0.10f);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownLoop_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 90, 0, 82, 0.03f);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 91, 0, 82, 0.03f);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 92, -3, 86, 0.03f);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 93, -4, 86, 0.03f);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttack_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 0, 19, -48, 0.15f);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 1, 20, -44, 0.12f);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 2, 18, -44, 0.12f);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 3, 18, -44, 0.12f);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 94, 10, 65, 0.03f);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 95, 36, 33, 0.03f);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("ThrowGranade_HeavyMachineGun", 175, 31, -38, 0.05f);
	PushAnimationData("ThrowGranade_HeavyMachineGun", 176, 32, -38, 0.05f);
	PushAnimationData("ThrowGranade_HeavyMachineGun", 177, 28, -38, 0.05f);
	PushAnimationData("ThrowGranade_HeavyMachineGun", 178, 30, -38, 0.05f);
	PushAnimationData("ThrowGranade_HeavyMachineGun", 179, 30, -38, 0.05f);
	PushAnimationData("ThrowGranade_HeavyMachineGun", 180, 31, -39, 0.05f);
	PushAnimationData("ThrowGranade_HeavyMachineGun", 231, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 175, 37, -42, 0.05f);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 176, 38, -42, 0.05f);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 177, 34, -42, 0.05f);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 178, 37, -42, 0.05f);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 179, 36, -42, 0.05f);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 180, 37, -42, 0.05f);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 175, 31, -58, 0.05f);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 176, 32, -58, 0.05f);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 177, 28, -58, 0.05f);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 178, 31, -58, 0.05f);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 179, 30, -58, 0.05f);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 180, 31, -58, 0.05f);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpThrowGranade_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 175, 16, -48, 0.05f);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 176, 17, -48, 0.05f);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 177, 14, -48, 0.05f);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 178, 15, -48, 0.05f);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 179, 15, -48, 0.05f);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 180, 16, -48, 0.05f);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 254, 0, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 255, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 256, 0, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 257, 0, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 258, -5, -25, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 259, -5, -15, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 260, -9, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 261, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 262, -9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
}