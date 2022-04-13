#include "PivotTestPlayer.h"
#include <GJHGameEngineScene.h>
#include <GJHGameEngineWindow.h>
#include <GJHResourcesManager.h>
#include <GJHRenderer.h>
#include <GJHSceneManager.h>
#include <GJHGameEngineTime.h>
#include <GJHGameEngineInput.h>
#include <GJHGameEngineScene.h>
#include <GJHGameEngineDebug.h>
#include "define.h"
#include <stdio.h>
#include <string>

PivotTestPlayer::~PivotTestPlayer()
{
	std::vector<std::pair<GJHString, State*>>::iterator iter = StateVec.begin();
	std::vector<std::pair<GJHString, State*>>::iterator iterEnd = StateVec.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
}

void PivotTestPlayer::Start()
{
	AniRenderTop = CreateRender({ 512, 512 }, "Eri_Kasamoto(Right).bmp", (int)ContentsEnum::RENDERORDER::PLAYER + 1);
	AniRenderBottom = CreateRender({ 512, 512 }, "Eri_Kasamoto(Right).bmp", ContentsEnum::RENDERORDER::PLAYER);

	ControlBody = ENUM_BODYTYPE::TOP;

	m_ImageDir = ENUM_DIRECTION::RIGHT;
	
	{
		CreateState("Idle_Basic", 0, 3, 4, 4, 0.1f, true, true, true);
		CreateState("MoveLoop_Basic", 9, 20, 25, 36, 0.05f, true, true);
		CreateState("StopMove_Basic", -1, -1, 37, 40, 0.05f, false, false, true, true);
		CreateState("IdleAttack_Basic", 102, 111, 4, 4, 0.04f, true, true);
		CreateState("MoveAttack_Basic", 102, 111, 25, 36, 0.04f, true, true);
		CreateState("LookUpStart_Basic", 73, 74, 4, 4, 0.12f, false, false);
		CreateState("LookUpLoop_Basic", 75, 78, 4, 4, 0.12f, true, true, true, true);
		CreateState("LookUpAttack_Basic", 112, 121, 4, 4, 0.04f, false, false);
		CreateState("MoveLookUpStart_Basic", 73, 74, 25, 36, 0.12f, false, true);
		CreateState("MoveLookUpLoop_Basic", 75, 78, 25, 36, 0.12f, true, true, true);
		CreateState("MoveLookUpEnd_Basic", 73, 74, 25, 36, 0.12f, false, true, true);
		CreateState("SitStart_Basic", -1, -1, 84, 86, 0.1f, false, false);
		CreateState("SitLoop_Basic", -1, -1, 91, 94, 0.12f, true, true, true, true);
		CreateState("SitMove_Basic", -1, -1, 95, 101, 0.08f, true, true, false, false);
		CreateState("SitAttack_Basic", -1, -1, 128, 137, 0.04f, false, false, false, false);
		CreateState("SitAttackLoop_Basic", -1, -1, 138, 141, 0.15f, true, true, true, true);
		CreateState("SitThrowGranade_Basic", -1, -1, 150, 155, 0.05f, false, false, false, false);
		CreateState("Jump_Basic", 41, 51, 58, 63, 0.1f, false, false, false, true);
		CreateState("MoveJump_Basic", 52, 57, 64, 72, 0.1f, false, false);
		CreateState("JumpAttack_Basic", 102, 111, 58, 63, 0.04f, false, false);
		CreateState("MoveJumpAttack_Basic", 102, 111, 64, 72, 0.04f, false, false);
		CreateState("JumpLookUpStart_Basic", 73, 74, 58, 63, 0.12f, false, false);
		CreateState("JumpLookUpLoop_Basic", 75, 78, 58, 63, 0.12f, true, true, true, true);
		CreateState("MoveJumpLookUpLoop_Basic", 75, 75, 64, 72, 0.12f, true, false, false, true);
		CreateState("JumpLookDownStart_Basic", 81, 82, 58, 63, 0.1f, false, false, false, true);
		CreateState("JumpLookDownLoop_Basic", 83, 83, 58, 63, 0.1f, false, false, false, true);
		CreateState("JumpLookDownAttack_Basic", 122, 127, 58, 63, 0.1f, false, false, false, true);
		CreateState("ThrowGranade_Basic", 142, 147, 4, 4, 0.05f, false, false, false, false);
		CreateState("MoveThrowGranade_Basic", 142, 147, 25, 36, 0.05f, false, false);
		CreateState("JumpThrowGranade_Basic", 142, 147, 58, 63, 0.05f, false, false, false, true);
		CreateState("MoveJumpThrowGranade_Basic", 142, 147, 64, 72, 0.05f, false, false);
		CreateState("Victory_Basic", -1, -1, 225, 230, 0.05f, false, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("Death_Basic", -1, -1, 0, 20, 0.05f, false, true, false, false, "Eri_Kasamoto_Death");
		//CreateState("Alive_Basic", -1, -1, 0, 6, 0.05f, false, true, false, false, "Eri_Kasamoto_Alive");

		CreateState("Idle_HeavyMachineGun", 0, 3, 231, 231, 0.1f, true, true, true, false, "Eri_Kasamoto_Weapon");
		CreateState("StopMove_HeavyMachineGun", -1, -1, 16, 19, 0.05f, false, false, true, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveLoop_HeavyMachineGun", 4, 15, 236, 247, 0.1f, true, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("IdleAttack_HeavyMachineGun", 70, 73, 231, 231, 0.04f, true, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("IdleAttackEnd_HeavyMachineGun", 134, 138, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("IdleAttackUp_HeavyMachineGun", 77, 78, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveAttack_HeavyMachineGun", 70, 73, 236, 247, 0.04f, false, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveAttackEnd_HeavyMachineGun", 134, 138, 236, 247, 0.04f, false, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveAttackUp_HeavyMachineGun", 77, 78, 236, 247, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("LookUpStart_HeavyMachineGun", 31, 32, 231, 231, 0.12f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("LookUpLoop_HeavyMachineGun", 36, 39, 231, 231, 0.12f, true, true, true, true, "Eri_Kasamoto_Weapon");
		CreateState("LookUpEnd_HeavyMachineGun", 85, 87, 231, 231, 0.12f, false, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("LookUpAttack_HeavyMachineGun", 79, 82, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("LookUpAttackEnd_HeavyMachineGun", 109, 114, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("LookUpAttackDown_HeavyMachineGun", 83, 84, 231, 231, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveLookUpStart_HeavyMachineGun", 31, 32, 236, 247, 0.12f, false, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveLookUpLoop_HeavyMachineGun", 36, 39, 236, 247, 0.12f, true, true, true, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveLookUpEnd_HeavyMachineGun", 85, 87, 236, 247, 0.12f, false, true, true, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveLookUpAttack_HeavyMachineGun", 79, 82, 236, 247, 0.12f, false, true, true, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveLookUpAttackEnd_HeavyMachineGun", 109, 114, 236, 247, 0.12f, false, true, true, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveLookUpAttackDown_HeavyMachineGun", 83, 84, 236, 247, 0.04f, false, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("SitStart_HeavyMachineGun", -1, -1, 43, 45, 0.1f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("SitLoop_HeavyMachineGun", -1, -1, 46, 49, 0.12f, true, true, true, true, "Eri_Kasamoto_Weapon");
		CreateState("SitMove_HeavyMachineGun", -1, -1, 58, 64, 0.08f, true, true, false, false, "Eri_Kasamoto_Weapon");
		CreateState("SitEnd_HeavyMachineGun", -1, -1, 43, 45, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("SitAttack_HeavyMachineGun", -1, -1, 96, 99, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("SitAttackEnd_HeavyMachineGun", -1, -1, 121, 123, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("SitAttackLoop_HeavyMachineGun", -1, -1, 50, 53, 0.15f, true, true, true, true, "Eri_Kasamoto_Weapon");
		CreateState("SitThrowGranade_HeavyMachineGun", -1, -1, 181, 186, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("Jump_HeavyMachineGun", 20, 30, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJump_HeavyMachineGun", 263, 268, 254, 262, 0.1f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("JumpAttack_HeavyMachineGun", 70, 73, 248, 253, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("JumpAttackUp_HeavyMachineGun", 77, 78, 248, 253, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("JumpAttackEnd_HeavyMachineGun", 134, 138, 248, 253, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("JumpAttackDown_HeavyMachineGun", 88, 89, 248, 253, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpAttack_HeavyMachineGun", 70, 73, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpAttackEnd_HeavyMachineGun", 134, 138, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpAttackUp_HeavyMachineGun", 77, 78, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpAttackDown_HeavyMachineGun", 88, 89, 254, 262, 0.04f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookUpStart_HeavyMachineGun", 31, 32, 248, 253, 0.12f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookUpLoop_HeavyMachineGun", 36, 39, 248, 253, 0.12f, true, true, true, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookUpEnd_HeavyMachineGun", 85, 87, 248, 253, 0.12f, true, true, true, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookUpAttack_HeavyMachineGun", 79, 82, 248, 253, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookUpAttackDown_HeavyMachineGun", 83, 84, 248, 253, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookUpAttackEnd_HeavyMachineGun", 109, 114, 248, 253, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookUpStart_HeavyMachineGun", 31, 32, 254, 262, 0.12f, true, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookUpLoop_HeavyMachineGun", 36, 39, 254, 262, 0.12f, true, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookUpEnd_HeavyMachineGun", 85, 87, 254, 262, 0.12f, true, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookUpAttack_HeavyMachineGun", 79, 82, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookUpAttackEnd_HeavyMachineGun", 109, 114, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookUpAttackDown_HeavyMachineGun", 83, 84, 254, 262, 0.12f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookDownStart_HeavyMachineGun", 40, 41, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookDownLoop_HeavyMachineGun", 42, 42, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookDownAttack_HeavyMachineGun", 90, 93, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("JumpLookDownAttackUp_HeavyMachineGun", 94, 95, 248, 253, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookDownStart_HeavyMachineGun", 40, 41, 254, 262, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookDownLoop_HeavyMachineGun", 42, 42, 254, 262, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookDownAttack_HeavyMachineGun", 90, 93, 254, 262, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpLookDownAttackUp_HeavyMachineGun", 94, 95, 254, 262, 0.1f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("ThrowGranade_HeavyMachineGun", 175, 180, 231, 231, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("MoveThrowGranade_HeavyMachineGun", 175, 180, 236, 247, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");
		CreateState("JumpThrowGranade_HeavyMachineGun", 175, 180, 248, 253, 0.05f, false, false, false, true, "Eri_Kasamoto_Weapon");
		CreateState("MoveJumpThrowGranade_HeavyMachineGun", 175, 180, 254, 262, 0.05f, false, false, false, false, "Eri_Kasamoto_Weapon");

		ChangeState("Idle_Basic");

		SetDefaultPivot();
	}

	AniRenderTop->SetAnimationPlay(false);
	AniRenderBottom->SetAnimationPlay(false);

	PlayAnimation = false;

	CREATEKEY("PivotCharLMove", 'A');
	CREATEKEY("PivotCharRMove", 'D');

	CREATEKEY("PivotRMove", VK_NUMPAD6);
	CREATEKEY("PivotLMove", VK_NUMPAD4);
	CREATEKEY("PivotUpMove", VK_NUMPAD8);
	CREATEKEY("PivotDownMove", VK_NUMPAD5);

	CREATEKEY("PivotRMicroMove", VK_NUMPAD6, VK_CONTROL);
	CREATEKEY("PivotLMicroMove", VK_NUMPAD4, VK_CONTROL);
	CREATEKEY("PivotUpMicroMove", VK_NUMPAD8, VK_CONTROL);
	CREATEKEY("PivotDownMicroMove", VK_NUMPAD5, VK_CONTROL);

	CREATEKEY("PrevAnimation", VK_NUMPAD1);
	CREATEKEY("NextAnimation", VK_NUMPAD3);

	CREATEKEY("PrevState", VK_NUMPAD7);
	CREATEKEY("NextState", VK_NUMPAD9);

	CREATEKEY("ControlBodyChange", VK_DECIMAL);

	CREATEKEY("PlayAnimation", VK_NUMPAD0);

	CREATEKEY("ChangeAllPivot", VK_DIVIDE, VK_CONTROL);

	CREATEKEY("SavePivotFile", VK_MULTIPLY);
	CREATEKEY("AnimationSpeedDown", VK_SUBTRACT);
	CREATEKEY("AnimationSpeedUp", VK_ADD);
	CREATEKEY("AnimationSpeedMicroDown", VK_SUBTRACT, VK_CONTROL);
	CREATEKEY("AnimationSpeedMicroUp", VK_ADD, VK_CONTROL);
	CREATEKEY("AllAnimationSpeedDown", VK_SUBTRACT, VK_SHIFT);
	CREATEKEY("AllAnimationSpeedUp", VK_ADD, VK_SHIFT);
	CREATEKEY("AllAnimationSpeedMicroDown", VK_SUBTRACT, VK_SHIFT, VK_CONTROL);
	CREATEKEY("AllAnimationSpeedMicroUp", VK_ADD, VK_SHIFT, VK_CONTROL);
}

void PivotTestPlayer::Update()
{
	DirStateCheck();
	Information();
	KeyChecker();

	AnimationChangeChecker();
}

void PivotTestPlayer::Information()
{
	HDC hDC = GJHGameEngineWindow::MainWindow()->GetBackBuffer();

	HBRUSH Brush, oBrush;

	Brush = CreateSolidBrush(RGB(255, 0, 0));
	oBrush = (HBRUSH)SelectObject(hDC, Brush);

	Rectangle(hDC, 0, 0, 1280, 960);

	SelectObject(hDC, oBrush);
	DeleteObject(Brush);

	{
		POINT Arr[2];
		Arr[0] = { GJHGameEngineWindow::MainWindow()->GetSize().hix(), 350 };
		Arr[1] = { GJHGameEngineWindow::MainWindow()->GetSize().hix(), 610 };
		Polygon(GJHGameEngineWindow::MainWindow()->GetBackBuffer(), Arr, 2);
	}

	{
		POINT Arr[2];
		Arr[0] = { 510, GJHGameEngineWindow::MainWindow()->GetSize().hiy() };
		Arr[1] = { 770, GJHGameEngineWindow::MainWindow()->GetSize().hiy() };
		Polygon(GJHGameEngineWindow::MainWindow()->GetBackBuffer(), Arr, 2);
	}

	char CurStateStr[100];
	sprintf_s(CurStateStr, "State : %s", CurStateName.operator LPCSTR());
	TextOutA(hDC, 300, 280, CurStateStr, (int)strlen(CurStateStr));

	int TopAnimationFrameIndex = AniRenderTop->GetAnimationFrameIndex();
	int BottomAnimationFrameIndex = AniRenderBottom->GetAnimationFrameIndex();

	char TopBodyIndex[100];
	sprintf_s(TopBodyIndex, "TopBodyIndex : %d / %d / %d", CurState->TopIndex.Start, TopAnimationFrameIndex, CurState->TopIndex.End);
	TextOutA(hDC, 300, 300, TopBodyIndex, (int)strlen(TopBodyIndex));

	char BottomBodyIndex[100];
	sprintf_s(BottomBodyIndex, "BottomBodyIndex : %d / %d / %d", CurState->BottomIndex.Start, BottomAnimationFrameIndex, CurState->BottomIndex.End);
	TextOutA(hDC, 300, 320, BottomBodyIndex, (int)strlen(BottomBodyIndex));

	char TopBodyPivot[100];
	sprintf_s(TopBodyPivot, "TopBodyPivot : x = %d / y = %d", (int)CurState->TopPivot[TopAnimationFrameIndex].X * (int)m_ImageDir, (int)CurState->TopPivot[TopAnimationFrameIndex].Y);
	TextOutA(hDC, 300, 340, TopBodyPivot, (int)strlen(TopBodyPivot));

	char BottomBodyPivot[100];
	sprintf_s(BottomBodyPivot, "BottomBodyPivot : x = %d / y = %d", (int)CurState->BottomPivot[BottomAnimationFrameIndex].X * (int)m_ImageDir, (int)CurState->BottomPivot[BottomAnimationFrameIndex].Y);
	TextOutA(hDC, 300, 360, BottomBodyPivot, (int)strlen(BottomBodyPivot));

	std::string Str = ControlBody == ENUM_BODYTYPE::TOP ? "Top" : "Bottom";
	char ControlBodyStr[100];
	sprintf_s(ControlBodyStr, "ControlBody : %s", Str.c_str());
	TextOutA(hDC, 300, 380, ControlBodyStr, (int)strlen(ControlBodyStr));

	char AnimationFrameTime[100];
	sprintf_s(AnimationFrameTime, "AnimationFrameTime : %.2f", AniRenderTop->GetFrameTime(TopAnimationFrameIndex));
	TextOutA(hDC, 300, 400, AnimationFrameTime, (int)strlen(AnimationFrameTime));

	Str = AniRenderTop->IsLoop() == true ? "true" : "false";
	char AnimationLoop[100];
	sprintf_s(AnimationLoop, "AnimationLoop : %s", Str.c_str());
	TextOutA(hDC, 300, 420, AnimationLoop, (int)strlen(AnimationLoop));

	char ch[] = "Ctrl + Pivot 이동시 1픽셀씩 이동(기본은 5픽셀)\n"
		"Numpad8 : Pivot 위로 이동\n"
		"Numpad4 : Pivot 왼쪽으로 이동\n"
		"Numpad5 : Pivot 아래로 이동\n"
		"Numpad6 : Pivot 오른쪽으로 이동\n"
		"Ctrl + Numpad/ : 현재 프레임의 Pivot을 모든 프레임에 적용\n\n"

		"Ctrl + 애니메이션 딜레이 조정시 0.1초씩 변동\n"
		"Shift + 애니메이션 딜레이 조정시 전체 애니메이션 변동\n"
		"Numpad- : 애니메이션 딜레이 0.01초 감소\n"
		"Numpad+ : 애니메이션 딜레이 0.01초 증가\n"
		"Numpad0 : 애니메이션 재생 토글 (On/Off)\n"
		"Numpad1 : 애니메이션 이전 프레임\n"
		"Numpad3 : 애니메이션 다음 프레임\n\n"
		"Numpad7 : 이전 State\n"
		"Numpad9 : 다음 State\n\n"
		"A : 캐릭터 방향 좌측\n"
		"D : 캐릭터 방향 우측\n\n"
		"Numpad* : 현재 피봇 상태를 txt 파일로 저장";
	RECT rc = { 800, 280, 1200, 700 };
	DrawTextA(hDC, ch, -1, &rc, DT_LEFT);
}

void PivotTestPlayer::KeyChecker()
{
	{
		if (KEYDOWN("Escape") == true)
		{
			GJHSceneManager::Inst.ChangeScene("Title");
		}
	}

	{
		if (KEYDOWN("PivotCharLMove") == true)
		{
			m_ImageDir = ENUM_DIRECTION::LEFT;
			ChangeAnimation(CurStateName);
		}
		if (KEYDOWN("PivotCharRMove") == true)
		{
			m_ImageDir = ENUM_DIRECTION::RIGHT;
			ChangeAnimation(CurStateName);
		}
	}

	{
		float* PivotX = nullptr;
		float* PivotY = nullptr;

		if (ControlBody == ENUM_BODYTYPE::TOP)
		{
			PivotX = &CurState->TopPivot[CurState->TopIndex.Cur].X;
			PivotY = &CurState->TopPivot[CurState->TopIndex.Cur].Y;
		}
		else if ((ControlBody == ENUM_BODYTYPE::BOTTOM))
		{
			PivotX = &CurState->BottomPivot[CurState->BottomIndex.Cur].X;
			PivotY = &CurState->BottomPivot[CurState->BottomIndex.Cur].Y;
		}

		if (PivotX == nullptr || PivotY == nullptr)
			return;

		if (KEYDOWN("PivotLMicroMove"))
			*PivotX -= 1;
		else if (KEYDOWN("PivotLMove"))
			*PivotX -= 5;

		if (KEYDOWN("PivotRMicroMove"))
			*PivotX += 1;
		else if (KEYDOWN("PivotRMove"))
			*PivotX += 5;

		if (KEYDOWN("PivotUpMicroMove"))
			*PivotY -= 1;
		else if (KEYDOWN("PivotUpMove"))
			*PivotY -= 5;

		if (KEYDOWN("PivotDownMicroMove"))
			*PivotY += 1;
		else if (KEYDOWN("PivotDownMove"))
			*PivotY += 5;
	}

	{
		if (KEYDOWN("PrevAnimation"))
		{
			if (CurState->TopIndex.Start < CurState->TopIndex.Cur)
				CurState->TopIndex.Cur--;
			
			if (CurState->BottomIndex.Start < CurState->BottomIndex.Cur)
				CurState->BottomIndex.Cur--;
		}

		if (KEYDOWN("NextAnimation"))
		{
			if (CurState->TopIndex.Cur < CurState->TopIndex.End)
				CurState->TopIndex.Cur++;

			if (CurState->BottomIndex.Cur < CurState->BottomIndex.End)
				CurState->BottomIndex.Cur++;
		}
	}

	{
		if (KEYDOWN("PrevState"))
			PrevState();

		if (KEYDOWN("NextState"))
			NextState();
	}

	{
		if (KEYDOWN("ControlBodyChange"))
			ControlBody = ControlBody == ENUM_BODYTYPE::TOP ? ENUM_BODYTYPE::BOTTOM : ENUM_BODYTYPE::TOP;
	}

	{
		if (KEYDOWN("PlayAnimation"))
		{
			if (PlayAnimation == false)
			{
				AniRenderTop->SetAnimationPlay(true);
				AniRenderBottom->SetAnimationPlay(true);

				AniRenderTop->SetAnimationFrameIndex(CurState->TopIndex.Start);
				AniRenderBottom->SetAnimationFrameIndex(CurState->BottomIndex.Start);

				AniRenderTop->AnimationReset();
				AniRenderBottom->AnimationReset();
			}
			else
			{
				AniRenderTop->SetAnimationPlay(false);
				AniRenderBottom->SetAnimationPlay(false);

				AniRenderTop->SetAnimationFrameIndex(CurState->TopIndex.Cur);
				AniRenderBottom->SetAnimationFrameIndex(CurState->BottomIndex.Cur);
			}

			PlayAnimation = !PlayAnimation;
		}
	}

	{
		if (KEYDOWN("ChangeAllPivot"))
			ChangeAllPivot();
	}

	{
		if (KEYDOWN("SavePivotFile"))
			Save();
	}

	{
		if (KEYDOWN("AllAnimationSpeedMicroDown"))
			AllAnimationSpeedDown(0.01f);
		else if (KEYDOWN("AllAnimationSpeedDown"))
			AllAnimationSpeedDown(0.1f);
		else if (KEYDOWN("AnimationSpeedMicroDown"))
			AnimationSpeedDown(0.01f);
		else if (KEYDOWN("AnimationSpeedDown"))
			AnimationSpeedDown(0.1f);
		else if (KEYDOWN("AllAnimationSpeedMicroUp"))
			AllAnimationSpeedUp(0.01f);
		else if (KEYDOWN("AllAnimationSpeedUp"))
			AllAnimationSpeedUp(0.1f);
		else if (KEYDOWN("AnimationSpeedMicroUp"))
			AnimationSpeedUp(0.01f);
		else if (KEYDOWN("AnimationSpeedUp"))
			AnimationSpeedUp(0.1f);
	}
}

void PivotTestPlayer::CreateAnimation(const GJHString& _Name, int _TopStart, int _TopEnd, int _BottomStart, int _BottomEnd, float _FrameTime, bool _TopLoop, bool _BottomLoop, bool _TopReverse, bool _BottomReverse, const GJHString& _FileName)
{
	AniRenderTop->CreateAnimation(_Name + "_Right", _FileName + "(Right).bmp", _TopStart, _TopEnd, _FrameTime, _TopLoop, _TopReverse);
	AniRenderTop->CreateAnimation(_Name + "_Left", _FileName + "(Left).bmp", _TopStart, _TopEnd, _FrameTime, _TopLoop, _TopReverse);

	AniRenderBottom->CreateAnimation(_Name + "_Right", _FileName + "(Right).bmp", _BottomStart, _BottomEnd, _FrameTime, _BottomLoop, _BottomReverse);
	AniRenderBottom->CreateAnimation(_Name + "_Left", _FileName + "(Left).bmp", _BottomStart, _BottomEnd, _FrameTime, _BottomLoop, _BottomReverse);
}

void PivotTestPlayer::ChangeAnimation(const GJHString& _Name)
{
	switch (m_ImageDir)
	{
	case ENUM_DIRECTION::LEFT:
		AniRenderTop->ChangeAnimation(_Name + "_Left");
		AniRenderBottom->ChangeAnimation(_Name + "_Left");
		break;
	case ENUM_DIRECTION::RIGHT:
		AniRenderTop->ChangeAnimation(_Name + "_Right");
		AniRenderBottom->ChangeAnimation(_Name + "_Right");
		break;
	}
	
	if (PlayAnimation == false)
	{
		AniRenderTop->SetAnimationPlay(false);
		AniRenderBottom->SetAnimationPlay(false);
	}
	else
	{
		AniRenderTop->SetAnimationPlay(true);
		AniRenderBottom->SetAnimationPlay(true);

		AniRenderTop->AnimationReset();
		AniRenderBottom->AnimationReset();
	}

	std::set<GJHString>::iterator Find = TopBodyDrawSkip.find(_Name);
	if (Find != TopBodyDrawSkip.end())
	{
		AniRenderTop->SetDraw(false);
	}
	else
	{
		AniRenderTop->SetDraw(true);
	}
}

void PivotTestPlayer::CreateState(const GJHString& _Name, int _TopStart, int _TopEnd, int _BottomStart, int _BottomEnd, float _FrameTime, bool _TopLoop, bool _BottomLoop, bool _TopReverse, bool _BottomReverse, const GJHString& _FileName)
{
	if (FindState(_Name) != StateVec.end())
	{
		AssertMsg("if (Find != StateVec.end())");
	}

	if (_TopStart == -1 || _TopEnd == -1)
	{
		TopBodyDrawSkip.insert(_Name);

		_TopStart = 0;
		_TopEnd = 0;
	}

	State* NewState = new State();
	NewState->TopIndex.Start = _TopStart;
	NewState->TopIndex.End = _TopEnd;
	NewState->TopIndex.Cur = _TopStart;
	NewState->BottomIndex.Start = _BottomStart;
	NewState->BottomIndex.End = _BottomEnd;
	NewState->BottomIndex.Cur = _BottomStart;

	for (int i = _TopStart; i <= _TopEnd; ++i)
	{
		NewState->TopPivot.insert(std::map<int, Pivot>::value_type(i, Pivot()));
		NewState->TopFrameTime.insert(std::map<int, float>::value_type(i, _FrameTime));
	}
	for (int i = _BottomStart; i <= _BottomEnd; ++i)
	{
		NewState->BottomPivot.insert(std::map<int, Pivot>::value_type(i, Pivot()));
		NewState->BottomFrameTime.insert(std::map<int, float>::value_type(i, _FrameTime));
	}

	StateVec.push_back(std::pair<GJHString, State*>(_Name, NewState));

	CreateAnimation(_Name, _TopStart, _TopEnd, _BottomStart, _BottomEnd, _FrameTime, _TopLoop, _BottomLoop, _TopReverse, _BottomReverse, _FileName);
}

void PivotTestPlayer::ChangeState(const GJHString& _Name)
{
	std::vector<std::pair<GJHString, State*>>::iterator Find = FindState(_Name);
	if (Find == StateVec.end())
	{
		AssertMsg("if (Find == StateVec.end())");
	}

	CurStateName = Find->first;
	CurState = Find->second;
	ChangeAnimation(CurStateName);
}

std::vector<std::pair<GJHString, PivotTestPlayer::State*>>::iterator PivotTestPlayer::FindState(const GJHString& _Name)
{
	std::vector<std::pair<GJHString, State*>>::iterator iter = StateVec.begin();
	std::vector<std::pair<GJHString, State*>>::iterator iterEnd = StateVec.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == _Name)
		{
			return iter;
		}
	}

	return StateVec.end();
}

void PivotTestPlayer::PrevState()
{
	std::vector<std::pair<GJHString, State*>>::iterator Find = FindState(CurStateName);
	if (Find == StateVec.end())
	{
		return;
	}

	if (Find != StateVec.begin())
	{
		CurStateName = (--Find)->first;
		ChangeState(CurStateName);
	}
}

void PivotTestPlayer::NextState()
{
	std::vector<std::pair<GJHString, State*>>::iterator Find = FindState(CurStateName);
	if (Find == StateVec.end())
	{
		AssertMsg("if (Find == StateVec.end())");
	}

	if (Find != StateVec.end() - 1)
	{
		CurStateName = (++Find)->first;
		ChangeState(CurStateName);
	}
}

void PivotTestPlayer::DirStateCheck()
{
	if (KEYPRESS("PivotCharLMove") == true)
	{
		m_ImageDir = ENUM_DIRECTION::LEFT;
	}
	if (KEYPRESS("PivotCharRMove") == true)
	{
		m_ImageDir = ENUM_DIRECTION::RIGHT;
	}
}

void PivotTestPlayer::AnimationChangeChecker()
{
	{
		if (AniRenderTop->IsLoop() == true)
		{
			if (CurState->TopIndex.Cur < CurState->TopIndex.Start)
			{
				CurState->TopIndex.Cur = CurState->TopIndex.Start;
			}

			if (CurState->TopIndex.End < CurState->TopIndex.Cur)
			{
				CurState->TopIndex.Cur = CurState->TopIndex.End;
			}

			if (CurState->BottomIndex.Cur < CurState->BottomIndex.Start)
			{
				CurState->BottomIndex.Cur = CurState->BottomIndex.Start;
			}

			if (CurState->BottomIndex.End < CurState->BottomIndex.Cur)
			{
				CurState->BottomIndex.Cur = CurState->BottomIndex.End;
			}
		}
		else
		{
			if (AniRenderTop->AnimationEnd()
				&& AniRenderBottom->AnimationEnd()
				&& PlayAnimation == true)
			{
				PlayAnimation = false;

				ChangeState(CurStateName);
			}
		}

		if (PlayAnimation == false)
		{
			AniRenderTop->SetAnimationFrameIndex(CurState->TopIndex.Cur);
			AniRenderBottom->SetAnimationFrameIndex(CurState->BottomIndex.Cur);
		}
	}

	{
		int TopAnimationFrameIndex = AniRenderTop->GetAnimationFrameIndex();
		int BottomAnimationFrameIndex = AniRenderBottom->GetAnimationFrameIndex();

		AniRenderTop->SetAddActorPivot({ CurState->TopPivot[TopAnimationFrameIndex].X, CurState->TopPivot[TopAnimationFrameIndex].Y });
		AniRenderBottom->SetAddActorPivot({ CurState->BottomPivot[BottomAnimationFrameIndex].X, CurState->BottomPivot[BottomAnimationFrameIndex].Y });
	}
}

void PivotTestPlayer::SetActorPivot(int _FrameIndex, float _XValue, float _YValue, ENUM_BODYTYPE _ControlBody)
{
	if (_ControlBody == ENUM_BODYTYPE::TOP)
	{
		CurState->TopPivot[_FrameIndex].X = _XValue;
		CurState->TopPivot[_FrameIndex].Y = _YValue;
	}
	else
	{
		CurState->BottomPivot[_FrameIndex].X = _XValue;
		CurState->BottomPivot[_FrameIndex].Y = _YValue;
	}
}

void PivotTestPlayer::SetAllActorPivotX(float _Value, ENUM_BODYTYPE _ControlBody)
{
	if (_ControlBody == ENUM_BODYTYPE::TOP)
	{
		std::map<int, Pivot>::iterator iter = CurState->TopPivot.begin();
		std::map<int, Pivot>::iterator iterEnd = CurState->TopPivot.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.X = _Value;
		}
	}
	else if (_ControlBody == ENUM_BODYTYPE::BOTTOM)
	{
		std::map<int, Pivot>::iterator iter = CurState->BottomPivot.begin();
		std::map<int, Pivot>::iterator iterEnd = CurState->BottomPivot.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.X = _Value;
		}
	}
}

void PivotTestPlayer::SetAllActorPivotY(float _Value, ENUM_BODYTYPE _ControlBody)
{
	if (_ControlBody == ENUM_BODYTYPE::TOP)
	{
		std::map<int, Pivot>::iterator iter = CurState->TopPivot.begin();
		std::map<int, Pivot>::iterator iterEnd = CurState->TopPivot.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.Y = _Value;
		}
	}
	else if (_ControlBody == ENUM_BODYTYPE::BOTTOM)
	{
		std::map<int, Pivot>::iterator iter = CurState->BottomPivot.begin();
		std::map<int, Pivot>::iterator iterEnd = CurState->BottomPivot.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.Y = _Value;
		}
	}
}

void PivotTestPlayer::ChangeAllPivot()
{
	if (ControlBody == ENUM_BODYTYPE::TOP)
	{
		std::map<int, Pivot>::iterator iter = CurState->TopPivot.begin();
		std::map<int, Pivot>::iterator iterEnd = CurState->TopPivot.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.X = CurState->TopPivot[CurState->TopIndex.Cur].X;
			iter->second.Y = CurState->TopPivot[CurState->TopIndex.Cur].Y;
		}
	}
	else if (ControlBody == ENUM_BODYTYPE::BOTTOM)
	{
		std::map<int, Pivot>::iterator iter = CurState->BottomPivot.begin();
		std::map<int, Pivot>::iterator iterEnd = CurState->BottomPivot.end();

		for (; iter != iterEnd; ++iter)
		{
			iter->second.X = CurState->BottomPivot[CurState->BottomIndex.Cur].X;
			iter->second.Y = CurState->BottomPivot[CurState->BottomIndex.Cur].Y;
		}
	}
}

void PivotTestPlayer::Save()
{
	FILE* File;

	fopen_s(&File, "..\\Pivot.txt", "wb");

	if (File == nullptr)
	{
		return;
	}

	for (int i = CurState->TopIndex.Start; i <= CurState->TopIndex.End; i++)
	{
		char Buffer[256];
		sprintf_s(Buffer, "PushAnimationData(\"%s\", %d, %d, %d, %.2ff);\n", CurStateName.Str.c_str(), i, (int)CurState->TopPivot[i].X, (int)CurState->TopPivot[i].Y, CurState->TopFrameTime[i]);

		fwrite(&Buffer, (int)strlen(Buffer), 1, File);
	}

	for (int i = CurState->BottomIndex.Start; i <= CurState->BottomIndex.End; i++)
	{
		char Buffer[256];
		sprintf_s(Buffer, "PushAnimationData(\"%s\", %d, %d, %d, %.2ff, ENUM_BODYTYPE::BOTTOM);\n", CurStateName.Str.c_str(), i, (int)CurState->BottomPivot[i].X, (int)CurState->BottomPivot[i].Y, CurState->BottomFrameTime[i]);

		fwrite(&Buffer, (int)strlen(Buffer), 1, File);
	}

	fclose(File);
}

void PivotTestPlayer::AnimationSpeedDown(float _Value)
{
	{
		int AnimationFrameIndex = AniRenderTop->GetAnimationFrameIndex();
		float AnimationFrameTime = AniRenderTop->GetFrameTime(AnimationFrameIndex) - _Value;

		if (AnimationFrameTime <= 0)
		{
			AnimationFrameTime = 0.01f;
		}

		CurState->TopFrameTime[AnimationFrameIndex] = AnimationFrameTime;

		AniRenderTop->SetFrameTime(AnimationFrameIndex, AnimationFrameTime);
	}

	{
		int AnimationFrameIndex = AniRenderBottom->GetAnimationFrameIndex();
		float AnimationFrameTime = AniRenderBottom->GetFrameTime(AnimationFrameIndex) - _Value;

		if (AnimationFrameTime <= 0)
		{
			AnimationFrameTime = 0.01f;
		}

		CurState->BottomFrameTime[AnimationFrameIndex] = AnimationFrameTime;

		AniRenderBottom->SetFrameTime(AnimationFrameIndex, AnimationFrameTime);
	}
}

void PivotTestPlayer::AnimationSpeedUp(float _Value)
{
	{
		int AnimationFrameIndex = AniRenderTop->GetAnimationFrameIndex();
		float AnimationFrameTime = AniRenderTop->GetFrameTime(AnimationFrameIndex);

		AnimationFrameTime += _Value;

		CurState->TopFrameTime[AnimationFrameIndex] = AnimationFrameTime;

		AniRenderTop->SetFrameTime(AnimationFrameIndex, AnimationFrameTime);
	}

	{
		int AnimationFrameIndex = AniRenderBottom->GetAnimationFrameIndex();
		float AnimationFrameTime = AniRenderBottom->GetFrameTime(AnimationFrameIndex);

		AnimationFrameTime += _Value;

		CurState->BottomFrameTime[AnimationFrameIndex] = AnimationFrameTime;

		AniRenderBottom->SetFrameTime(AnimationFrameIndex, AnimationFrameTime);
	}
}

void PivotTestPlayer::AllAnimationSpeedDown(float _Value)
{
	for (int i = CurState->TopIndex.Start; i <= CurState->TopIndex.End; ++i)
	{
		float AnimationFrameTime = AniRenderTop->GetFrameTime(i) - _Value;
		if (AnimationFrameTime <= 0)
		{
			AnimationFrameTime = 0.01f;
		}

		CurState->TopFrameTime[i] = AnimationFrameTime;
		AniRenderTop->SetFrameTime(i, AnimationFrameTime);
	}

	for (int i = CurState->BottomIndex.Start; i <= CurState->BottomIndex.End; ++i)
	{
		float AnimationFrameTime = AniRenderBottom->GetFrameTime(i) - _Value;
		if (AnimationFrameTime <= 0)
		{
			AnimationFrameTime = 0.01f;
		}

		CurState->BottomFrameTime[i] = AnimationFrameTime;
		AniRenderBottom->SetFrameTime(i, AnimationFrameTime);
	}
}

void PivotTestPlayer::AllAnimationSpeedUp(float _Value)
{
	for (int i = CurState->TopIndex.Start; i <= CurState->TopIndex.End; ++i)
	{
		float AnimationFrameTime = AniRenderTop->GetFrameTime(i) + _Value;

		CurState->TopFrameTime[i] = AnimationFrameTime;
		AniRenderTop->SetFrameTime(i, AnimationFrameTime);
	}

	for (int i = CurState->BottomIndex.Start; i <= CurState->BottomIndex.End; ++i)
	{
		float AnimationFrameTime = AniRenderBottom->GetFrameTime(i) + _Value;

		CurState->BottomFrameTime[i] = AnimationFrameTime;
		AniRenderBottom->SetFrameTime(i, AnimationFrameTime);
	}
}

void PivotTestPlayer::SetFrameTime(int _FrameIndex, float _Value, ENUM_BODYTYPE _ControlBody)
{
	if (_ControlBody == ENUM_BODYTYPE::TOP)
	{
		CurState->TopFrameTime.insert(std::map<int, float>::value_type(_FrameIndex, _Value));
	}
	else
	{
		CurState->BottomFrameTime.insert(std::map<int, float>::value_type(_FrameIndex, _Value));
	}

	switch (m_ImageDir)
	{
	case ENUM_DIRECTION::LEFT:
		if (_ControlBody == ENUM_BODYTYPE::TOP)
		{
			AniRenderTop->SetFrameTime(_FrameIndex, _Value);
			AniRenderTop->ChangeAnimation(CurStateName + "_Right");
			AniRenderTop->SetFrameTime(_FrameIndex, _Value);
			AniRenderTop->ChangeAnimation(CurStateName + "_Left");
		}
		else
		{
			AniRenderBottom->SetFrameTime(_FrameIndex, _Value);
			AniRenderBottom->ChangeAnimation(CurStateName + "_Right");
			AniRenderBottom->SetFrameTime(_FrameIndex, _Value);
			AniRenderBottom->ChangeAnimation(CurStateName + "_Left");
		}
		break;
	case ENUM_DIRECTION::RIGHT:
		if (_ControlBody == ENUM_BODYTYPE::TOP)
		{
			AniRenderTop->SetFrameTime(_FrameIndex, _Value);
			AniRenderTop->ChangeAnimation(CurStateName + "_Left");
			AniRenderTop->SetFrameTime(_FrameIndex, _Value);
			AniRenderTop->ChangeAnimation(CurStateName + "_Right");
		}
		else
		{
			AniRenderBottom->SetFrameTime(_FrameIndex, _Value);
			AniRenderBottom->ChangeAnimation(CurStateName + "_Left");
			AniRenderBottom->SetFrameTime(_FrameIndex, _Value);
			AniRenderBottom->ChangeAnimation(CurStateName + "_Right");
		}
		break;
	}
}

void PivotTestPlayer::PushAnimationData(const GJHString& _StateName, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime, ENUM_BODYTYPE _ControlBody)
{
	ChangeState(_StateName);
	SetActorPivot(_FrameIndex, (float)_PivotX, (float)_PivotY, _ControlBody);
	SetFrameTime(_FrameIndex, _FrameTime, _ControlBody);
}

void PivotTestPlayer::BasicPivot()
{
	{
		PushAnimationData("Idle_Basic", 0, 11, -34, 0.1f);
		PushAnimationData("Idle_Basic", 1, 11, -34, 0.1f);
		PushAnimationData("Idle_Basic", 2, 12, -34, 0.1f);
		PushAnimationData("Idle_Basic", 3, 12, -34, 0.1f);
		PushAnimationData("Idle_Basic", 4, 0, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("MoveLoop_Basic", 9, 19, -37, 0.05f);
		PushAnimationData("MoveLoop_Basic", 10, 14, -39, 0.05f);
		PushAnimationData("MoveLoop_Basic", 11, 14, -37, 0.05f);
		PushAnimationData("MoveLoop_Basic", 12, 15, -39, 0.05f);
		PushAnimationData("MoveLoop_Basic", 13, 13, -37, 0.05f);
		PushAnimationData("MoveLoop_Basic", 14, 10, -36, 0.05f);
		PushAnimationData("MoveLoop_Basic", 15, 15, -38, 0.05f);
		PushAnimationData("MoveLoop_Basic", 16, 19, -39, 0.05f);
		PushAnimationData("MoveLoop_Basic", 17, 20, -38, 0.05f);
		PushAnimationData("MoveLoop_Basic", 18, 17, -37, 0.05f);
		PushAnimationData("MoveLoop_Basic", 19, 15, -34, 0.05f);
		PushAnimationData("MoveLoop_Basic", 20, 16, -36, 0.05f);
	}

	{
		PushAnimationData("StopMove_Basic", 37, 14, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("StopMove_Basic", 38, 14, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("StopMove_Basic", 39, 14, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("StopMove_Basic", 40, 14, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("IdleAttack_Basic", 102, 51, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 103, 50, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 104, 49, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 105, 11, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 106, 13, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 107, 22, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 108, 21, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 109, 21, -55, 0.04f);
		PushAnimationData("IdleAttack_Basic", 110, 17, -41, 0.04f);
		PushAnimationData("IdleAttack_Basic", 111, 12, -37, 0.04f);
	}

	{
		PushAnimationData("MoveAttack_Basic", 102, 56, -60, 0.04f);
		PushAnimationData("MoveAttack_Basic", 103, 53, -57, 0.04f);
		PushAnimationData("MoveAttack_Basic", 104, 52, -58, 0.04f);
		PushAnimationData("MoveAttack_Basic", 105, 14, -61, 0.04f);
		PushAnimationData("MoveAttack_Basic", 106, 16, -61, 0.04f);
		PushAnimationData("MoveAttack_Basic", 107, 20, -52, 0.04f);
		PushAnimationData("MoveAttack_Basic", 108, 26, -58, 0.04f);
		PushAnimationData("MoveAttack_Basic", 109, 30, -54, 0.04f);
		PushAnimationData("MoveAttack_Basic", 110, 24, -46, 0.04f);
		PushAnimationData("MoveAttack_Basic", 111, 16, -43, 0.04f);
	}

	{
		PushAnimationData("LookUpStart_Basic", 73, 17, -55, 0.12f);
		PushAnimationData("LookUpStart_Basic", 74, 21, -55, 0.12f);
	}

	{
		PushAnimationData("LookUpLoop_Basic", 75, 8, -55, 0.12f);
		PushAnimationData("LookUpLoop_Basic", 76, 8, -55, 0.12f);
		PushAnimationData("LookUpLoop_Basic", 77, 10, -55, 0.12f);
		PushAnimationData("LookUpLoop_Basic", 78, 10, -55, 0.12f);
	}

	{
		PushAnimationData("LookUpAttack_Basic", 112, -8, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 113, -11, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 114, -11, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 115, -11, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 116, -11, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 117, -13, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 118, -9, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 119, -4, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 120, -3, -56, 0.04f);
		PushAnimationData("LookUpAttack_Basic", 121, 1, -56, 0.04f);
	}

	{
		PushAnimationData("MoveLookUpStart_Basic", 73, 17, -55, 0.12f);
		PushAnimationData("MoveLookUpStart_Basic", 74, 21, -55, 0.12f);
	}

	{
		PushAnimationData("MoveLookUpLoop_Basic", 75, 8, -55, 0.12f);
		PushAnimationData("MoveLookUpLoop_Basic", 76, 8, -55, 0.12f);
		PushAnimationData("MoveLookUpLoop_Basic", 77, 10, -55, 0.12f);
		PushAnimationData("MoveLookUpLoop_Basic", 78, 10, -55, 0.12f);
	}

	{
		PushAnimationData("SitStart_Basic", 84, 12, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitStart_Basic", 85, 9, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitStart_Basic", 86, 24, 0, 0.1f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("SitLoop_Basic", 91, 10, 4, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitLoop_Basic", 92, 10, 4, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitLoop_Basic", 93, 10, 4, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitLoop_Basic", 94, 10, 4, 0.16f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("SitMove_Basic", 95, 10, 5, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 96, 10, 5, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 97, 10, 5, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 98, 10, 5, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 99, 10, 5, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 100, 10, 5, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitMove_Basic", 101, 10, 5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("SitAttack_Basic", 128, 51, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 129, 51, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 130, 49, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 131, 11, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 132, 12, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 133, 22, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 134, 22, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 135, 22, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 136, 18, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttack_Basic", 137, 21, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("SitAttackLoop_Basic", 138, 16, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttackLoop_Basic", 139, 13, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttackLoop_Basic", 140, 10, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitAttackLoop_Basic", 141, 13, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("Jump_Basic", 41, -5, -78, 0.06f);
		PushAnimationData("Jump_Basic", 42, -7, -78, 0.06f);
		PushAnimationData("Jump_Basic", 43, -7, -78, 0.06f);
		PushAnimationData("Jump_Basic", 44, -7, -78, 0.15f);
		PushAnimationData("Jump_Basic", 45, -7, -78, 0.06f);
		PushAnimationData("Jump_Basic", 46, -7, -78, 0.06f);
		PushAnimationData("Jump_Basic", 47, -6, -78, 0.06f);
		PushAnimationData("Jump_Basic", 48, -9, -78, 0.06f);
		PushAnimationData("Jump_Basic", 49, -9, -74, 0.15f);
		PushAnimationData("Jump_Basic", 50, -9, -77, 0.15f);
		PushAnimationData("Jump_Basic", 51, -5, -77, 0.06f);

		PushAnimationData("Jump_Basic", 58, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 59, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 60, 0, -5, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 61, 3, -7, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 62, 5, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Jump_Basic", 63, 5, -30, 0.06f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("MoveJump_Basic", 52, -25, -30, 0.03f);
		PushAnimationData("MoveJump_Basic", 53, -19, -30, 0.06f);
		PushAnimationData("MoveJump_Basic", 54, -15, -30, 0.18f);
		PushAnimationData("MoveJump_Basic", 55, -13, -30, 0.09f);
		PushAnimationData("MoveJump_Basic", 56, -20, -34, 0.06f);
		PushAnimationData("MoveJump_Basic", 57, -20, -40, 0.03f);

		PushAnimationData("MoveJump_Basic", 65, 0, -15, 0.03f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 66, 0, -15, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 67, 0, -25, 0.21f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 68, -5, -20, 0.09f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 69, -5, -15, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 70, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 71, -9, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJump_Basic", 72, -9, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("JumpAttack_Basic", 102, 51, -75, 0.04f);
		PushAnimationData("JumpAttack_Basic", 103, 50, -75, 0.04f);
		PushAnimationData("JumpAttack_Basic", 104, 49, -75, 0.04f);
		PushAnimationData("JumpAttack_Basic", 105, 11, -75, 0.04f);
		PushAnimationData("JumpAttack_Basic", 106, 13, -75, 0.04f);
		PushAnimationData("JumpAttack_Basic", 107, 22, -75, 0.04f);
		PushAnimationData("JumpAttack_Basic", 108, 21, -75, 0.04f);
		PushAnimationData("JumpAttack_Basic", 109, 21, -71, 0.04f);
		PushAnimationData("JumpAttack_Basic", 110, 17, -61, 0.04f);
		PushAnimationData("JumpAttack_Basic", 111, 12, -57, 0.04f);

		PushAnimationData("JumpAttack_Basic", 58, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 59, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 60, 0, -5, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 61, 3, -7, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 62, 5, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpAttack_Basic", 63, 5, -30, 0.06f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("MoveJumpAttack_Basic", 102, 36, -65, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 103, 35, -65, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 104, 34, -65, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 105, -4, -65, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 106, -2, -65, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 107, 7, -65, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 108, 6, -65, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 109, 6, -61, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 110, 2, -51, 0.04f);
		PushAnimationData("MoveJumpAttack_Basic", 111, -3, -47, 0.04f);

		PushAnimationData("MoveJumpAttack_Basic", 65, 0, -15, 0.03f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 66, 0, -15, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 67, 0, -25, 0.21f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 68, -5, -20, 0.09f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 69, -5, -15, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 70, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 71, -9, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpAttack_Basic", 72, -9, 0, 0.06f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("JumpLookUpStart_Basic", 73, 15, -75, 0.12f);
		PushAnimationData("JumpLookUpStart_Basic", 74, 18, -75, 0.12f);
	}

	{
		PushAnimationData("JumpLookUpLoop_Basic", 75, 8, -75, 0.12f);
		PushAnimationData("JumpLookUpLoop_Basic", 76, 8, -75, 0.12f);
		PushAnimationData("JumpLookUpLoop_Basic", 77, 10, -75, 0.12f);
		PushAnimationData("JumpLookUpLoop_Basic", 78, 10, -75, 0.12f);

		PushAnimationData("JumpLookUpLoop_Basic", 60, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 61, 3, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 62, 5, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookUpLoop_Basic", 63, 5, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("MoveJumpLookUpLoop_Basic", 65, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 66, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 67, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 68, -5, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 69, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 70, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 71, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("MoveJumpLookUpLoop_Basic", 72, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("JumpLookDownStart_Basic", 81, 0, -50, 0.1f);
		PushAnimationData("JumpLookDownStart_Basic", 82, 2, -33, 0.1f);

		PushAnimationData("JumpLookDownStart_Basic", 60, 0, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 61, 3, -7, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 62, 5, -20, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownStart_Basic", 63, 5, -30, 0.1f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("JumpLookDownLoop_Basic", 83, 2, -28, 0.1f);

		PushAnimationData("JumpLookDownLoop_Basic", 60, 0, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 61, 3, -7, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 62, 5, -20, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownLoop_Basic", 63, 5, -30, 0.1f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("JumpLookDownAttack_Basic", 122, 4, 31, 0.1f);
		PushAnimationData("JumpLookDownAttack_Basic", 123, 2, 37, 0.1f);
		PushAnimationData("JumpLookDownAttack_Basic", 124, 4, 44, 0.1f);
		PushAnimationData("JumpLookDownAttack_Basic", 125, 9, -52, 0.1f);
		PushAnimationData("JumpLookDownAttack_Basic", 126, 5, -36, 0.1f);
		PushAnimationData("JumpLookDownAttack_Basic", 127, 3, -34, 0.1f);

		PushAnimationData("JumpLookDownAttack_Basic", 60, 0, -5, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 61, 3, -7, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 62, 5, -20, 0.1f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("JumpLookDownAttack_Basic", 63, 5, -30, 0.1f, ENUM_BODYTYPE::BOTTOM);
	}

	{
		PushAnimationData("ThrowGranade_Basic", 142, 10, -34, 0.05f);
		PushAnimationData("ThrowGranade_Basic", 143, 15, -34, 0.05f);
		PushAnimationData("ThrowGranade_Basic", 144, 13, -34, 0.05f);
		PushAnimationData("ThrowGranade_Basic", 145, 13, -34, 0.05f);
		PushAnimationData("ThrowGranade_Basic", 146, 13, -34, 0.05f);
		PushAnimationData("ThrowGranade_Basic", 147, 13, -34, 0.05f);
	}

	{
		PushAnimationData("MoveThrowGranade_Basic", 142, 16, -38, 0.05f);
		PushAnimationData("MoveThrowGranade_Basic", 143, 21, -38, 0.05f);
		PushAnimationData("MoveThrowGranade_Basic", 144, 19, -38, 0.05f);
		PushAnimationData("MoveThrowGranade_Basic", 145, 19, -38, 0.05f);
		PushAnimationData("MoveThrowGranade_Basic", 146, 19, -38, 0.05f);
		PushAnimationData("MoveThrowGranade_Basic", 147, 19, -38, 0.05f);
	}

	{
		PushAnimationData("SitThrowGranade_Basic", 150, 10, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitThrowGranade_Basic", 151, 10, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitThrowGranade_Basic", 152, 10, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitThrowGranade_Basic", 153, 10, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitThrowGranade_Basic", 154, 10, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("SitThrowGranade_Basic", 155, 10, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
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
		PushAnimationData("Death_Basic", 0, 10, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 1, 5, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 2, 5, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 3, -2, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 4, -16, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 5, -20, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 6, -17, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 7, -17, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 8, -11, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 9, -15, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 10, -15, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 11, -18, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 12, -24, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 13, -20, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 14, -17, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 15, -16, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 16, -18, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 17, -18, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 18, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 19, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
		PushAnimationData("Death_Basic", 20, 0, 0, 0.25f, ENUM_BODYTYPE::BOTTOM);
	}

	//{
	//	PushAnimationData("Alive_Basic", 0, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	//	PushAnimationData("Alive_Basic", 1, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	//	PushAnimationData("Alive_Basic", 2, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	//	PushAnimationData("Alive_Basic", 3, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	//	PushAnimationData("Alive_Basic", 4, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	//	PushAnimationData("Alive_Basic", 5, 0, 0, 0.03f, ENUM_BODYTYPE::BOTTOM);
	//	PushAnimationData("Alive_Basic", 6, 0, 0, 0.15f, ENUM_BODYTYPE::BOTTOM);
	//}
}

void PivotTestPlayer::HeavyMachineGunPivot()
{
	PushAnimationData("Idle_HeavyMachineGun", 0, 29, -38, 0.15f);
	PushAnimationData("Idle_HeavyMachineGun", 1, 30, -34, 0.12f);
	PushAnimationData("Idle_HeavyMachineGun", 2, 28, -34, 0.12f);
	PushAnimationData("Idle_HeavyMachineGun", 3, 28, -34, 0.12f);
	PushAnimationData("Idle_HeavyMachineGun", 231, 0, 0, 0.20f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLoop_HeavyMachineGun", 4, 38, -44, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 5, 32, -46, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 6, 34, -44, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 7, 35, -46, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 8, 32, -44, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 9, 29, -43, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 10, 35, -45, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 11, 38, -45, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 12, 39, -44, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 13, 36, -44, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 14, 36, -44, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 15, 37, -46, 0.05f);
	PushAnimationData("MoveLoop_HeavyMachineGun", 236, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 237, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 238, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 239, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 240, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 241, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 242, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 243, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 244, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 245, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 246, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLoop_HeavyMachineGun", 247, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("StopMove_HeavyMachineGun", 0, 0, 0, 0.05f);
	PushAnimationData("StopMove_HeavyMachineGun", 16, 29, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("StopMove_HeavyMachineGun", 17, 28, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("StopMove_HeavyMachineGun", 18, 26, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("StopMove_HeavyMachineGun", 19, 22, 1, 0.05f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("IdleAttack_HeavyMachineGun", 70, 67, -37, 0.04f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 71, 69, -34, 0.04f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 72, 65, -37, 0.04f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 73, 65, -34, 0.04f);
	PushAnimationData("IdleAttack_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("IdleAttackUp_HeavyMachineGun", 77, 55, -55, 0.04f);
	PushAnimationData("IdleAttackUp_HeavyMachineGun", 78, 53, -55, 0.04f);
	PushAnimationData("IdleAttackUp_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 134, 25, -40, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 135, 23, -37, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 136, 27, -42, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 137, 25, -39, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 138, 29, -39, 0.04f);
	PushAnimationData("IdleAttackEnd_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveAttack_HeavyMachineGun", 70, 72, -42, 0.04f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 71, 72, -37, 0.04f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 72, 68, -40, 0.04f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 73, 68, -40, 0.04f);
	PushAnimationData("MoveAttack_HeavyMachineGun", 236, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 237, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 238, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 239, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 240, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 241, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 242, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 243, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 244, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 245, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 246, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttack_HeavyMachineGun", 247, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 134, 30, -44, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 135, 28, -43, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 136, 33, -51, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 137, 30, -46, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 138, 35, -47, 0.04f);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 236, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 237, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 238, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 239, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 240, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 241, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 242, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 243, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 244, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 245, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 246, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackEnd_HeavyMachineGun", 247, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveAttackUp_HeavyMachineGun", 77, 59, -60, 0.04f);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 78, 58, -60, 0.04f);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 236, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 237, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 238, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 239, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 240, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 241, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 242, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 243, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 244, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 245, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 246, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveAttackUp_HeavyMachineGun", 247, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpStart_HeavyMachineGun", 31, 17, -55, 0.12f);
	PushAnimationData("LookUpStart_HeavyMachineGun", 32, 17, -55, 0.12f);
	PushAnimationData("LookUpStart_HeavyMachineGun", 231, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpLoop_HeavyMachineGun", 36, 18, -55, 0.12f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 37, 21, -55, 0.12f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 38, 22, -55, 0.12f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 39, 22, -55, 0.12f);
	PushAnimationData("LookUpLoop_HeavyMachineGun", 231, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpEnd_HeavyMachineGun", 85, 15, -55, 0.12f);
	PushAnimationData("LookUpEnd_HeavyMachineGun", 86, 15, -55, 0.12f);
	PushAnimationData("LookUpEnd_HeavyMachineGun", 87, 17, -55, 0.12f);
	PushAnimationData("LookUpEnd_HeavyMachineGun", 231, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpAttack_HeavyMachineGun", 79, -7, -55, 0.04f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 80, -13, -55, 0.04f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 81, -11, -55, 0.04f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 82, -11, -55, 0.04f);
	PushAnimationData("LookUpAttack_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpAttackDown_HeavyMachineGun", 83, 33, -55, 0.04f);
	PushAnimationData("LookUpAttackDown_HeavyMachineGun", 84, 50, -55, 0.04f);
	PushAnimationData("LookUpAttackDown_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 109, -6, -56, 0.04f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 110, -10, -56, 0.04f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 111, -10, -56, 0.04f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 112, -10, -56, 0.04f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 113, -12, -56, 0.04f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 114, -10, -56, 0.04f);
	PushAnimationData("LookUpAttackEnd_HeavyMachineGun", 231, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 31, 17, -55, 0.12f);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 32, 18, -55, 0.12f);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 236, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 237, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 238, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 239, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 240, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 241, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 242, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 243, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 244, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 245, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 246, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpStart_HeavyMachineGun", 247, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 36, 18, -55, 0.12f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 37, 21, -55, 0.12f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 38, 23, -55, 0.12f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 39, 23, -55, 0.12f);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 236, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 237, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 238, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 239, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 240, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 241, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 242, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 243, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 244, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 245, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 246, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpLoop_HeavyMachineGun", 247, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 85, 15, -50, 0.12f);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 86, 16, -50, 0.12f);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 87, 18, -50, 0.12f);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 236, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 237, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 238, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 239, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 240, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 241, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 242, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 243, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 244, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 245, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 246, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpEnd_HeavyMachineGun", 247, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 79, 0, -60, 0.12f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 80, -6, -60, 0.12f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 81, -4, -60, 0.12f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 82, -4, -60, 0.12f);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 236, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 237, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 238, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 239, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 240, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 241, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 242, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 243, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 244, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 245, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 246, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttack_HeavyMachineGun", 247, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 109, 1, -61, 0.12f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 110, -3, -61, 0.12f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 111, -3, -61, 0.12f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 112, -3, -61, 0.12f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 113, -5, -61, 0.12f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 114, -3, -61, 0.12f);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 236, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 237, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 238, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 239, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 240, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 241, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 242, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 243, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 244, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 245, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 246, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackEnd_HeavyMachineGun", 247, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 83, 41, -60, 0.04f);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 84, 58, -60, 0.04f);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 236, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 237, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 238, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 239, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 240, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 241, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 242, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 243, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 244, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 245, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 246, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveLookUpAttackDown_HeavyMachineGun", 247, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

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

	PushAnimationData("SitAttack_HeavyMachineGun", 96, 64, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttack_HeavyMachineGun", 97, 63, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttack_HeavyMachineGun", 98, 63, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("SitAttack_HeavyMachineGun", 99, 61, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

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

	PushAnimationData("JumpAttack_HeavyMachineGun", 70, 66, -57, 0.04f);
	PushAnimationData("JumpAttack_HeavyMachineGun", 71, 69, -55, 0.04f);
	PushAnimationData("JumpAttack_HeavyMachineGun", 72, 66, -58, 0.04f);
	PushAnimationData("JumpAttack_HeavyMachineGun", 73, 66, -55, 0.04f);
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
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 248, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 249, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 250, 0, -5, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 251, 0, -7, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 252, 0, -20, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpAttackEnd_HeavyMachineGun", 253, 0, -30, 0.04f, ENUM_BODYTYPE::BOTTOM);

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

	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 70, 52, -47, 0.04f);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 71, 54, -44, 0.04f);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 72, 49, -46, 0.04f);
	PushAnimationData("MoveJumpAttack_HeavyMachineGun", 73, 50, -44, 0.04f);
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
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 254, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 255, 0, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 256, 0, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 257, 0, -25, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 258, -5, -25, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 259, -5, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 260, -9, -5, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 261, -9, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackEnd_HeavyMachineGun", 262, -9, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 77, 40, -65, 0.04f);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 78, 39, -65, 0.04f);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 254, 0, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 255, 0, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 256, 0, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 257, 0, -25, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 258, -5, -25, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 259, -5, -15, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 260, -9, -5, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 261, -9, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpAttackUp_HeavyMachineGun", 262, -9, 0, 0.04f, ENUM_BODYTYPE::BOTTOM);

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

	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 31, 15, -76, 0.12f);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 32, 15, -76, 0.12f);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpStart_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 36, 19, -76, 0.12f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 37, 22, -76, 0.12f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 38, 23, -76, 0.12f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 39, 23, -76, 0.12f);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpLoop_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 85, 16, -74, 0.12f);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 86, 16, -74, 0.12f);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 87, 18, -74, 0.12f);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpEnd_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 79, -5, -75, 0.12f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 80, -11, -75, 0.12f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 81, -9, -75, 0.12f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 82, -9, -75, 0.12f);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttack_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 109, -5, -76, 0.12f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 110, -9, -76, 0.12f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 111, -9, -76, 0.12f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 112, -9, -76, 0.12f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 113, -11, -76, 0.12f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 114, -10, -76, 0.12f);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackEnd_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 83, 35, -75, 0.12f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 84, 52, -75, 0.12f);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 248, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 249, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 250, 0, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 251, 0, -7, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 252, 0, -20, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookUpAttackDown_HeavyMachineGun", 253, 0, -30, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 31, 0, -60, 0.12f);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 32, 0, -60, 0.12f);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpStart_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 36, 0, -60, 0.12f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 37, 3, -59, 0.12f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 38, 5, -59, 0.12f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 39, 5, -59, 0.12f);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 254, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 255, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 256, 0, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 257, 0, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 258, -5, -25, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 259, -5, -15, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 260, -9, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 261, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpLoop_HeavyMachineGun", 262, -9, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 85, 5, -60, 0.12f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 86, 5, -60, 0.12f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 87, 7, -60, 0.12f);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 254, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 255, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 256, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 257, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 258, -5, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 259, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 260, -9, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 261, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpEnd_HeavyMachineGun", 262, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 79, -20, -65, 0.12f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 80, -26, -65, 0.12f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 81, -24, -65, 0.12f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 82, -24, -65, 0.12f);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 254, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 255, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 256, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 257, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 258, -5, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 259, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 260, -9, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 261, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttack_HeavyMachineGun", 262, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 109, -20, -66, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 110, -24, -66, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 111, -23, -66, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 112, -23, -66, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 113, -25, -66, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 114, -23, -66, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 254, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 255, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 256, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 257, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 258, -5, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 259, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 260, -9, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 261, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackEnd_HeavyMachineGun", 262, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 83, 23, -64, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 84, 40, -64, 0.12f);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 254, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 255, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 256, 0, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 257, 0, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 258, -5, -25, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 259, -5, -15, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 260, -9, -5, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 261, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpLookUpAttackDown_HeavyMachineGun", 262, -9, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 40, 8, -45, 0.10f);
	PushAnimationData("JumpLookDownStart_HeavyMachineGun", 41, -2, -10, 0.10f);
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

	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 90, 13, 67, 0.10f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 91, 13, 67, 0.10f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 92, 9, 73, 0.10f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 93, 8, 73, 0.10f);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttack_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 94, 25, 55, 0.10f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 95, 53, 23, 0.10f);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 248, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 249, 0, 0, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 250, 0, -5, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 251, 0, -7, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 252, 0, -20, 0.10f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("JumpLookDownAttackUp_HeavyMachineGun", 253, 0, -30, 0.10f, ENUM_BODYTYPE::BOTTOM);

	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 40, 1, -32, 0.10f);
	PushAnimationData("MoveJumpLookDownStart_HeavyMachineGun", 41, -9, 3, 0.10f);
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

	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 94, 10, 65, 0.10f);
	PushAnimationData("MoveJumpLookDownAttackUp_HeavyMachineGun", 95, 36, 33, 0.10f);
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
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 236, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 237, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 238, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 239, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 240, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 241, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 242, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 243, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 244, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 245, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 246, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveThrowGranade_HeavyMachineGun", 247, 0, 0, 0.12f, ENUM_BODYTYPE::BOTTOM);

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
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 254, 0, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 255, 0, -15, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 256, 0, -15, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 257, 0, -25, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 258, -5, -25, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 259, -5, -15, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 260, -9, -5, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 261, -9, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
	PushAnimationData("MoveJumpThrowGranade_HeavyMachineGun", 262, -9, 0, 0.05f, ENUM_BODYTYPE::BOTTOM);
}

void PivotTestPlayer::SetDefaultPivot()
{
	{
		for (int i = CurState->TopIndex.Start; i < CurState->TopIndex.End + 1; ++i)
		{
			CurState->TopPivot[i] = Pivot();
		}

		for (int i = CurState->BottomIndex.Start; i < CurState->BottomIndex.End + 1; ++i)
		{
			CurState->BottomPivot[i] = Pivot();
		}
	}

	AniRenderBottom->SetActorPivot({ 0, 0 });

	BasicPivot();
	HeavyMachineGunPivot();

	ChangeState("Idle_Basic");
}