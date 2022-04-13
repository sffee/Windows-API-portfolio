#include "PivotTestMonster.h"
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

PivotTestMonster::~PivotTestMonster()
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

void PivotTestMonster::Start()
{
	DefaultImageSize = { 512, 512 };
	AniRender = CreateRender(DefaultImageSize, "ZombieMan(Right).bmp", (int)ContentsEnum::RENDERORDER::PLAYER);

	m_ImageDir = ENUM_DIRECTION::RIGHT;

	{
		CreateState("ZombieMan_Idle", "ZombieMan", 0, 6, 0.1f, true, true);
		CreateState("ZombieMan_Move", "ZombieMan", 7, 22, 0.1f, true);
		CreateState("ZombieMan_Attack", "ZombieMan", 23, 42, 0.08f, true);
		CreateState("ZombieMan_AttackEffect", "ZombieManAttack", 0, 11, 0.08f, true, false, { 256, 256 });
		CreateState("ZombieMan_ThrowVomit", "ZombieManAttack", 12, 25, 0.08f, true, false, { 256, 256 });
		CreateState("ZombieMan_GroundEffect", "ZombieManAttack", 26, 44, 0.08f, true, false, { 256, 256 });
		CreateState("ZombieMan_HitEffect", "ZombieManAttack", 45, 60, 0.08f, true, false, { 256, 256 });
		CreateState("ZombieMan_BulletDeath", "ZombieManDeath", 0, 14, 0.08f, true, false);
		CreateState("ZombieMan_GranadeDeath", "ZombieManDeath", 15, 40, 0.08f, true, false);
		CreateState("ZombieMan_Blood", "Blood", 0, 15, 0.08f, true, false);

		CreateState("ZombieGirl_Idle", "ZombieGirl", 0, 11, 0.1f, true);
		CreateState("ZombieGirl_Move", "ZombieGirl", 12, 23, 0.1f, true);
		CreateState("ZombieGirl_Attack", "ZombieGirl", 25, 44, 0.1f, true);
		CreateState("ZombieGirl_AttackEffect", "ZombieGirlAttack", 0, 9, 0.08f, true, false, { 256, 256 });
		CreateState("ZombieGirl_GranadeDeath", "ZombieGirlDeath", 15, 33, 0.08f, false);

		CreateState("ZombieDoctor_Idle", "ZombieDoctor", 0, 6, 0.1f, true, true);
		CreateState("ZombieDoctor_Move", "ZombieDoctor", 7, 18, 0.1f, true);
		CreateState("ZombieDoctor_Attack", "ZombieDoctor", 19, 46, 0.1f, true);
		CreateState("ZombieDoctor_AttackEffect", "ZombieDoctorAttack", 0, 11, 0.1f, true, false, { 256, 256 });
		CreateState("ZombieDoctor_GranadeDeath", "ZombieDoctorDeath", 15, 39, 0.08f, false);

		CreateState("MordenMinigun_Idle", "Morden_Minigun", 31, 34, 0.15f, true, true);
		CreateState("MordenMinigun_Move", "Morden_Minigun", 8, 19, 0.1f, true);
		CreateState("MordenMinigun_Attack", "Morden_Minigun", 58, 87, 0.1f, false);
		CreateState("MordenMinigun_AttackEffect", "Morden_Minigun", 88, 91, 0.1f, false);
		CreateState("MordenMinigun_Death1", "Morden_Death", 0, 10, 0.1f, false);
		CreateState("MordenMinigun_Death2", "Morden_Death", 48, 54, 0.1f, false);
		CreateState("MordenMinigun_GrandeDeathJump", "Morden_Death", 81, 85, 0.06f, true, true);

		CreateState("Helicopter_Move24", "Helicopter", 0, 5, 0.1f, false);
		CreateState("Helicopter_Move24_AttackEffect", "Helicopter", 55, 56, 0.05f, false);
		CreateState("Helicopter_Move26", "Helicopter", 6, 11, 0.1f, false);
		CreateState("Helicopter_Move26_AttackEffect", "Helicopter", 57, 58, 0.05f, false);
		CreateState("Helicopter_Move33", "Helicopter", 12, 17, 0.1f, false);
		CreateState("Helicopter_Move33_AttackEffect", "Helicopter", 59, 60, 0.05f, false);
		CreateState("Helicopter_Move41", "Helicopter", 18, 23, 0.1f, false);
		CreateState("Helicopter_Move41_AttackEffect", "Helicopter", 61, 62, 0.05f, false);
		CreateState("Helicopter_Move46", "Helicopter", 24, 29, 0.1f, false);
		CreateState("Helicopter_Move46_AttackEffect", "Helicopter", 63, 64, 0.05f, false);
		CreateState("Helicopter_Move62", "Helicopter", 30, 35, 0.1f, false);
		CreateState("Helicopter_Move62_AttackEffect", "Helicopter", 65, 66, 0.05f, false);
		CreateState("Helicopter_Move74", "Helicopter", 36, 41, 0.1f, false);
		CreateState("Helicopter_Move74_AttackEffect", "Helicopter", 67, 68, 0.05f, false);
		CreateState("Helicopter_Move90", "Helicopter", 42, 47, 0.1f, false);
		CreateState("Helicopter_Move90_AttackEffect", "Helicopter", 69, 70, 0.05f, false);

		CreateState("Explosion_SmallExplosion", "Explosion", 0, 27, 0.05f, false);
		CreateState("Explosion_LargeExplosion", "Explosion", 56, 83, 0.05f, false);

		CreateState("Bomber_Idle", "Bomber", 3, 3, 0.1f, true);
		CreateState("Bomber_Back", "Bomber", 0, 2, 0.1f, true);
		CreateState("Bomber_Front", "Bomber", 4, 6, 0.1f, true);
		CreateState("Bomber_Propeller_0", "Bomber", 17, 21, 0.05f, true);
		CreateState("Bomber_Propeller_1", "Bomber", 7, 11, 0.05f, true);
		CreateState("Bomber_Propeller_2", "Bomber", 12, 16, 0.05f, true);
		CreateState("Bomber_Propeller_3", "Bomber", 22, 26, 0.05f, true);
		CreateState("Bomber_Propeller_4", "Bomber", 27, 31, 0.05f, true);
		CreateState("Bomber_Propeller_5", "Bomber", 32, 36, 0.05f, true);
		CreateState("Bomber_Propeller_6", "Bomber", 37, 41, 0.05f, true);
		CreateState("Bomber_Bomb", "Bomber", 42, 48, 0.05f, true, true);
		CreateState("Bomber_Fog", "Bomber", 49, 56, 0.05f, false, false);

		CreateState("Granade_NormalExplosion", "GranadeExplosion", 0, 26, 0.05f, false, false, { 768, 768 });
		CreateState("Granade_BigExplosion", "GranadeExplosion", 27, 56, 0.05f, false, false, { 768, 768 });

		CreateState("MonoeyeUFO_Idle_Top", "MonoeyeUFO", 0, 4, 0.1f, true, false, { 768, 768 });
		CreateState("MonoeyeUFO_Idle_Bottom", "MonoeyeUFO", 16, 16, 0.1f, true, false, { 768, 768 });
		CreateState("MonoeyeUFO_Charge", "MonoeyeUFO", 5, 8, 0.1f, true, false, { 768, 768 });
		CreateState("MonoeyeUFO_Fire", "MonoeyeUFO", 9, 14, 0.1f, true, false, { 768, 768 });
		CreateState("MonoeyeUFO_Laser", "MonoeyeUFO_Effect", 0, 5, 0.1f, true, false, { 128, 900 });
		CreateState("MonoeyeUFO_Laser_Bottom", "MonoeyeUFO_Effect", 6, 11, 0.1f, true, false, { 128, 900 });
		CreateState("MonoeyeUFO_TombStone", "TombStone", 0, 32, 0.1f, true);

		CreateState("ZombieMorden_Idle", "ZombieMorden", 16, 20, 0.15f, true, true);
		CreateState("ZombieMorden_Move", "ZombieMorden", 0, 15, 0.08f, true);
		CreateState("ZombieMorden_Attack", "ZombieMorden", 23, 32, 0.1f, false);
		CreateState("ZombieMorden_Boom", "ZombieMorden_Attack", 0, 17, 0.1f, false, false, { 256, 256 });

		CreateState("GranadeBox_Idle", "Item", 0, 5, 0.1f, true, false);
		CreateState("Item_PickUp", "Item", 9, 14, 0.1f, false, false);
		CreateState("NPC_Bind", "NPC", 0, 4, 0.1f, true, true);
		CreateState("NPC_BindOut", "NPC", 5, 8, 0.1f, false, false);
		CreateState("NPC_Falling", "NPC", 9, 13, 0.1f, true, false);
		CreateState("NPC_Walk", "NPC", 14, 25, 0.1f, true, false);
		CreateState("NPC_DropItem", "NPC", 26, 36, 0.1f, false, false);
		CreateState("NPC_Salute", "NPC", 37, 50, 0.1f, false, false);
		CreateState("NPC_RunAway", "NPC", 51, 58, 0.1f, true, false);

		ChangeState("ZombieMan_Idle");

		SetDefaultPivot();
	}

	AniRender->SetAnimationPlay(false);

	PlayAnimation = false;
}

void PivotTestMonster::Update()
{
	DirStateCheck();
	Information();
	KeyChecker();

	AnimationChangeChecker();
}

void PivotTestMonster::Information()
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

	int AnimationFrameIndex = AniRender->GetAnimationFrameIndex();

	char AnimationIndex[100];
	sprintf_s(AnimationIndex, "AnimationIndex : %d / %d / %d", CurState->FrameIndex.Start, AnimationFrameIndex, CurState->FrameIndex.End);
	TextOutA(hDC, 300, 300, AnimationIndex, (int)strlen(AnimationIndex));

	char AnimationPivot[100];
	sprintf_s(AnimationPivot, "AnimationPivot : x = %d / y = %d", (int)CurState->Pivot[AnimationFrameIndex].X * (int)m_ImageDir, (int)CurState->Pivot[AnimationFrameIndex].Y);
	TextOutA(hDC, 300, 320, AnimationPivot, (int)strlen(AnimationPivot));

	char AnimationFrameTime[100];
	sprintf_s(AnimationFrameTime, "AnimationFrameTime : %.2f", AniRender->GetFrameTime(AnimationFrameIndex));
	TextOutA(hDC, 300, 340, AnimationFrameTime, (int)strlen(AnimationFrameTime));

	std::string Str = AniRender->IsLoop() == true ? "true" : "false";
	char AnimationLoop[100];
	sprintf_s(AnimationLoop, "AnimationLoop : %s", Str.c_str());
	TextOutA(hDC, 300, 360, AnimationLoop, (int)(int)strlen(AnimationLoop));

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
		"A : 몬스터 방향 좌측\n"
		"D : 몬스터 방향 우측\n\n"
		"Numpad* : 현재 피봇 상태를 txt 파일로 저장";
	RECT rc = { 800, 280, 1500, 700 };
	DrawTextA(hDC, ch, -1, &rc, DT_LEFT);
}

void PivotTestMonster::KeyChecker()
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

		PivotX = &CurState->Pivot[CurState->FrameIndex.Cur].X;
		PivotY = &CurState->Pivot[CurState->FrameIndex.Cur].Y;

		if (PivotX == nullptr || PivotY == nullptr)
		{
			return;
		}

		if (KEYDOWN("PivotLMicroMove"))
		{
			*PivotX -= 1;
		}
		else if (KEYDOWN("PivotLMove"))
		{
			*PivotX -= 5;
		}

		if (KEYDOWN("PivotRMicroMove"))
		{
				*PivotX += 1;
		}
		else if (KEYDOWN("PivotRMove"))
		{
				*PivotX += 5;
		}

		if (KEYDOWN("PivotUpMicroMove"))
		{
			*PivotY -= 1;
		}
		else if (KEYDOWN("PivotUpMove"))
		{
			*PivotY -= 5;
		}

		if (KEYDOWN("PivotDownMicroMove"))
		{
			*PivotY += 1;
		}
		else if (KEYDOWN("PivotDownMove"))
		{
			*PivotY += 5;
		}
	}

	{
		if (KEYDOWN("PrevAnimation"))
		{
			if (CurState->FrameIndex.Start < CurState->FrameIndex.Cur)
			{
				CurState->FrameIndex.Cur--;
			}
		}

		if (KEYDOWN("NextAnimation"))
		{
			if (CurState->FrameIndex.Cur < CurState->FrameIndex.End)
			{
				CurState->FrameIndex.Cur++;
			}
		}
	}

	{
		if (KEYDOWN("PrevState"))
		{
			PrevState();
		}

		if (KEYDOWN("NextState"))
		{
			NextState();
		}
	}

	{
		if (KEYDOWN("PlayAnimation"))
		{
			if (PlayAnimation == false)
			{
				AniRender->SetAnimationPlay(true);
				AniRender->SetAnimationFrameIndex(CurState->FrameIndex.Start);
				AniRender->AnimationReset();
			}
			else
			{
				AniRender->SetAnimationPlay(false);
				AniRender->SetAnimationFrameIndex(CurState->FrameIndex.Cur);
			}

			PlayAnimation = !PlayAnimation;
		}
	}

	{
		if (KEYDOWN("ChangeAllPivot"))
		{
			ChangeAllPivot();
		}
	}

	{
		if (KEYDOWN("SavePivotFile"))
		{
			Save();
		}
	}

	{
		if (KEYDOWN("AllAnimationSpeedMicroDown"))
		{
			AllAnimationSpeedDown(0.01f);
		}
		else if (KEYDOWN("AllAnimationSpeedDown"))
		{
			AllAnimationSpeedDown(0.1f);
		}
		else if (KEYDOWN("AnimationSpeedMicroDown"))
		{
			AnimationSpeedDown(0.01f);
		}
		else if (KEYDOWN("AnimationSpeedDown"))
		{
			AnimationSpeedDown(0.1f);
		}
		else if (KEYDOWN("AllAnimationSpeedMicroUp"))
		{
			AllAnimationSpeedUp(0.01f);
		}
		else if (KEYDOWN("AllAnimationSpeedUp"))
		{
			AllAnimationSpeedUp(0.1f);
		}
		else if (KEYDOWN("AnimationSpeedMicroUp"))
		{
			AnimationSpeedUp(0.01f);
		}
		else if (KEYDOWN("AnimationSpeedUp"))
		{
			AnimationSpeedUp(0.1f);
		}
	}
}

void PivotTestMonster::CreateAnimation(const GJHString& _StateName, const GJHString& _FileName, int _FrameStart, int _FrameEnd, float _FrameTime, bool _Loop, bool _Reverse)
{
	AniRender->CreateAnimation(_StateName + "_Right", _FileName + "(Right).bmp", _FrameStart, _FrameEnd, _FrameTime, _Loop, _Reverse);
	AniRender->CreateAnimation(_StateName + "_Left", _FileName + "(Left).bmp", _FrameStart, _FrameEnd, _FrameTime, _Loop, _Reverse);
}

void PivotTestMonster::ChangeAnimation(const GJHString& _Name)
{
	switch (m_ImageDir)
	{
	case ENUM_DIRECTION::LEFT:
		AniRender->ChangeAnimation(_Name + "_Left");
		break;
	case ENUM_DIRECTION::RIGHT:
		AniRender->ChangeAnimation(_Name + "_Right");
		break;
	}

	if (PlayAnimation == false)
	{
		AniRender->SetAnimationPlay(false);
	}
	else
	{
		AniRender->SetAnimationPlay(true);
		AniRender->AnimationReset();
	}
}

void PivotTestMonster::CreateState(const GJHString& _StateName, const GJHString& _FileName, int _FrameStart, int _FrameEnd, float _FrameTime, bool _Loop, bool _Reverse, GJHVector _Size)
{
	if (FindState(_StateName) != StateVec.end())
	{
		AssertMsg("if (Find != StateVec.end())");
	}

	State* NewState = new State();
	NewState->FrameIndex.Start = _FrameStart;
	NewState->FrameIndex.End = _FrameEnd;
	NewState->FrameIndex.Cur = _FrameStart;

	for (int i = _FrameStart; i <= _FrameEnd; ++i)
	{
		NewState->Pivot.insert(std::map<int, Pivot>::value_type(i, Pivot()));
		NewState->FrameTime[i] = _FrameTime;
	}

	StateVec.push_back(std::pair<GJHString, State*>(_StateName, NewState));

	if (_Size != GJHVector::ZERO)
	{
		StateImageSizeMap.insert(std::map<GJHString, GJHVector>::value_type(_StateName, _Size));
	}

	CreateAnimation(_StateName, _FileName, _FrameStart, _FrameEnd, _FrameTime, _Loop, _Reverse);
}

void PivotTestMonster::ChangeState(const GJHString& _StateName)
{
	std::vector<std::pair<GJHString, State*>>::iterator Find = FindState(_StateName);
	if (Find == StateVec.end())
	{
		AssertMsg("if (Find == StateVec.end())");
	}

	std::map<GJHString, GJHVector>::iterator Find2 = StateImageSizeMap.find(_StateName);
	if (Find2 != StateImageSizeMap.end())
	{
		AniRender->SetSize(Find2->second);
	}
	else
	{
		AniRender->SetSize(DefaultImageSize);
	}

	CurStateName = Find->first;
	CurState = Find->second;
	ChangeAnimation(CurStateName);
}

std::vector<std::pair<GJHString, PivotTestMonster::State*>>::iterator PivotTestMonster::FindState(const GJHString& _StateName)
{
	std::vector<std::pair<GJHString, State*>>::iterator iter = StateVec.begin();
	std::vector<std::pair<GJHString, State*>>::iterator iterEnd = StateVec.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->first == _StateName)
		{
			return iter;
		}
	}

	return StateVec.end();
}

void PivotTestMonster::PrevState()
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

void PivotTestMonster::NextState()
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

void PivotTestMonster::DirStateCheck()
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

void PivotTestMonster::AnimationChangeChecker()
{
	{
		if (AniRender->IsLoop() == true)
		{
			if (CurState->FrameIndex.Cur < CurState->FrameIndex.Start)
			{
				CurState->FrameIndex.Cur = CurState->FrameIndex.Start;
			}

			if (CurState->FrameIndex.End < CurState->FrameIndex.Cur)
			{
				CurState->FrameIndex.Cur = CurState->FrameIndex.End;
			}
		}
		else
		{
			if (AniRender->AnimationEnd()
				&& PlayAnimation == true)
			{
				PlayAnimation = false;

				ChangeState(CurStateName);
			}
		}

		if (PlayAnimation == false)
		{
			AniRender->SetAnimationFrameIndex(CurState->FrameIndex.Cur);
		}
	}

	{
		int AnimationFrameIndex = AniRender->GetAnimationFrameIndex();

		AniRender->SetAddActorPivot({ CurState->Pivot[AnimationFrameIndex].X, CurState->Pivot[AnimationFrameIndex].Y });
	}
}

void PivotTestMonster::SetActorPivot(int _FrameIndex, float _XValue, float _YValue)
{
	CurState->Pivot[_FrameIndex].X = _XValue;
	CurState->Pivot[_FrameIndex].Y = _YValue;
}

void PivotTestMonster::SetAllActorPivotX(float _Value)
{
	std::map<int, Pivot>::iterator iter = CurState->Pivot.begin();
	std::map<int, Pivot>::iterator iterEnd = CurState->Pivot.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second.X = _Value;
	}
}

void PivotTestMonster::SetAllActorPivotY(float _Value)
{
	std::map<int, Pivot>::iterator iter = CurState->Pivot.begin();
	std::map<int, Pivot>::iterator iterEnd = CurState->Pivot.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second.Y = _Value;
	}
}

void PivotTestMonster::ChangeAllPivot()
{
	std::map<int, Pivot>::iterator iter = CurState->Pivot.begin();
	std::map<int, Pivot>::iterator iterEnd = CurState->Pivot.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second.X = CurState->Pivot[CurState->FrameIndex.Cur].X;
		iter->second.Y = CurState->Pivot[CurState->FrameIndex.Cur].Y;
	}
}

void PivotTestMonster::Save()
{
	FILE* File;

	fopen_s(&File, "..\\Pivot.txt", "wb");

	if (File == nullptr)
	{
		return;
	}

	for (int i = CurState->FrameIndex.Start; i <= CurState->FrameIndex.End; i++)
	{
		char Buffer[256];
		GJHString StateName = CurStateName.Cut(CurStateName.FirstFind('_') + 1, (int)(CurStateName.Size() - CurStateName.FirstFind('_') + 1));
		sprintf_s(Buffer, "PushAnimationData(\"%s\", %d, %d, %d, %.2ff);\n", StateName.Str.c_str(), i, (int)CurState->Pivot[i].X, (int)CurState->Pivot[i].Y, CurState->FrameTime[i]);

		fwrite(&Buffer, (int)strlen(Buffer), 1, File);
	}

	for (int i = CurState->FrameIndex.Start; i <= CurState->FrameIndex.End; i++)
	{
		char Buffer[256];
		sprintf_s(Buffer, "Map[%d] = { PivotData(%d, %d), %.2ff };\n", i, (int)CurState->Pivot[i].X, (int)CurState->Pivot[i].Y, CurState->FrameTime[i]);

		fwrite(&Buffer, (int)strlen(Buffer), 1, File);
	}

	fclose(File);
}

void PivotTestMonster::AnimationSpeedDown(float _Value)
{
	int AnimationFrameIndex = AniRender->GetAnimationFrameIndex();
	float AnimationFrameTime = AniRender->GetFrameTime(AnimationFrameIndex) - _Value;

	if (AnimationFrameTime <= 0)
	{
		AnimationFrameTime = 0.01f;
	}

	CurState->FrameTime[AnimationFrameIndex] = AnimationFrameTime;

	AniRender->SetFrameTime(AnimationFrameIndex, AnimationFrameTime);
}

void PivotTestMonster::AnimationSpeedUp(float _Value)
{
	int AnimationFrameIndex = AniRender->GetAnimationFrameIndex();
	float AnimationFrameTime = AniRender->GetFrameTime(AnimationFrameIndex);

	AnimationFrameTime += _Value;

	CurState->FrameTime[AnimationFrameIndex] = AnimationFrameTime;

	AniRender->SetFrameTime(AnimationFrameIndex, AnimationFrameTime);
}

void PivotTestMonster::AllAnimationSpeedDown(float _Value)
{
	for (int i = CurState->FrameIndex.Start; i <= CurState->FrameIndex.End; ++i)
	{
		float AnimationFrameTime = AniRender->GetFrameTime(i) - _Value;
		if (AnimationFrameTime <= 0)
		{
			AnimationFrameTime = 0.01f;
		}

		CurState->FrameTime[i] = AnimationFrameTime;
		AniRender->SetFrameTime(i, AnimationFrameTime);
	}
}

void PivotTestMonster::AllAnimationSpeedUp(float _Value)
{
	for (int i = CurState->FrameIndex.Start; i <= CurState->FrameIndex.End; ++i)
	{
		float AnimationFrameTime = AniRender->GetFrameTime(i) + _Value;

		CurState->FrameTime[i] = AnimationFrameTime;
		AniRender->SetFrameTime(i, AnimationFrameTime);
	}
}

void PivotTestMonster::SetFrameTime(int _FrameIndex, float _Value)
{
	CurState->FrameTime.insert(std::map<int, float>::value_type(_FrameIndex, _Value));

	switch (m_ImageDir)
	{
	case ENUM_DIRECTION::LEFT:
		AniRender->SetFrameTime(_FrameIndex, _Value);
		AniRender->ChangeAnimation(CurStateName + "_Right");
		AniRender->SetFrameTime(_FrameIndex, _Value);
		AniRender->ChangeAnimation(CurStateName + "_Left");
		break;
	case ENUM_DIRECTION::RIGHT:
		AniRender->SetFrameTime(_FrameIndex, _Value);
		AniRender->ChangeAnimation(CurStateName + "_Left");
		AniRender->SetFrameTime(_FrameIndex, _Value);
		AniRender->ChangeAnimation(CurStateName + "_Right");
		break;
	}
}

void PivotTestMonster::PushAnimationData(const GJHString& _StateName, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime)
{
	ChangeState(MonsterName + "_" + _StateName);
	SetActorPivot(_FrameIndex, (float)_PivotX, (float)_PivotY);
	SetFrameTime(_FrameIndex, _FrameTime);
}

void PivotTestMonster::ZombieManPivot()
{
	MonsterName = "ZombieMan";

	float Delay = 0.1f;
	int XGap = 0;
	int YGap = 0;
	PushAnimationData("Idle", 0, 0, 0, 0.10f);
	PushAnimationData("Idle", 1, 0, 0, 0.10f);
	PushAnimationData("Idle", 2, 4, 0, 0.10f);
	PushAnimationData("Idle", 3, 1, 0, 0.10f);
	PushAnimationData("Idle", 4, 1, 0, 0.10f);
	PushAnimationData("Idle", 5, -3, 0, 0.10f);
	PushAnimationData("Idle", 6, -3, 0, 0.10f);

	PushAnimationData("Move", 7, 3, 0, Delay);
	PushAnimationData("Move", 8, 3, 0, Delay);
	PushAnimationData("Move", 10, -4, 0, Delay);
	PushAnimationData("Move", 12, -4, 0, Delay);
	PushAnimationData("Move", 13, 6, 0, Delay);
	PushAnimationData("Move", 14, 4, 0, Delay);
	PushAnimationData("Move", 15, 4, 0, Delay);
	PushAnimationData("Move", 16, 8, 0, Delay);
	PushAnimationData("Move", 17, -18, 0, Delay);
	PushAnimationData("Move", 18, -26, 0, Delay);
	PushAnimationData("Move", 19, -20, 0, Delay);
	PushAnimationData("Move", 20, -12, 0, Delay);
	PushAnimationData("Move", 21, -10, 0, Delay);
	PushAnimationData("Move", 22, -10, 0, Delay);

	Delay = 0.08f;
	PushAnimationData("AttackEffect", 0, 5, -10, Delay);
	PushAnimationData("AttackEffect", 1, 0, -15, Delay);
	PushAnimationData("AttackEffect", 2, 5, -15, Delay);
	PushAnimationData("AttackEffect", 3, 5, -20, Delay);
	PushAnimationData("AttackEffect", 4, 0, -20, Delay);
	PushAnimationData("AttackEffect", 5, 0, -5, Delay);
	PushAnimationData("AttackEffect", 6, 5, -10, Delay);
	PushAnimationData("AttackEffect", 7, 0, -10, Delay);
	PushAnimationData("AttackEffect", 8, 0, -10, Delay);
	PushAnimationData("AttackEffect", 9, 5, -15, Delay);
	PushAnimationData("AttackEffect", 10, 5, -5, Delay);
	PushAnimationData("AttackEffect", 11, 10, -10, Delay);

	Delay = 0.08f;
	PushAnimationData("Attack", 24, -5, 0, Delay);
	PushAnimationData("Attack", 25, -10, 0, Delay);
	PushAnimationData("Attack", 26, 2, 0, Delay);
	PushAnimationData("Attack", 27, -1, 0, Delay);
	PushAnimationData("Attack", 28, -8, 0, Delay);
	PushAnimationData("Attack", 29, 6, 0, Delay);
	PushAnimationData("Attack", 30, 5, 0, Delay);
	PushAnimationData("Attack", 31, 12, 0, Delay);
	PushAnimationData("Attack", 32, -2, 0, Delay);
	PushAnimationData("Attack", 33, -5, 0, Delay * 5.f);
	PushAnimationData("Attack", 34, -5, 0, Delay);
	PushAnimationData("Attack", 35, -12, 0, Delay);
	PushAnimationData("Attack", 36, -22, 0, Delay);
	PushAnimationData("Attack", 37, -22, 0, Delay);
	PushAnimationData("Attack", 38, -22, 0, Delay);
	PushAnimationData("Attack", 39, -15, 0, Delay);
	PushAnimationData("Attack", 40, -12, 0, Delay);
	PushAnimationData("Attack", 41, -2, 0, Delay);
	PushAnimationData("Attack", 42, -3, 0, Delay);

	Delay = 0.06f;
	PushAnimationData("ThrowVomit", 12, -10, 0, Delay);
	PushAnimationData("ThrowVomit", 13, -10, 5, Delay);
	PushAnimationData("ThrowVomit", 14, -2, 5, Delay);
	PushAnimationData("ThrowVomit", 15, -4, 5, Delay);
	PushAnimationData("ThrowVomit", 16, -5, 5, Delay);
	PushAnimationData("ThrowVomit", 17, 5, 5, Delay);
	PushAnimationData("ThrowVomit", 18, -6, 4, Delay);
	PushAnimationData("ThrowVomit", 19, -5, 2, Delay);
	PushAnimationData("ThrowVomit", 20, 0, 5, Delay);
	PushAnimationData("ThrowVomit", 21, 5, -10, Delay);
	PushAnimationData("ThrowVomit", 22, 5, -5, Delay);
	PushAnimationData("ThrowVomit", 23, 10, -10, Delay);
	PushAnimationData("ThrowVomit", 24, 10, 0, Delay);
	PushAnimationData("ThrowVomit", 25, 10, -10, Delay);

	Delay = 0.06f;
	PushAnimationData("HitEffect", 45, 5, 0, Delay);
	PushAnimationData("HitEffect", 46, 2, -3, Delay);
	PushAnimationData("HitEffect", 47, -2, 0, Delay);
	PushAnimationData("HitEffect", 48, -2, 1, Delay);
	PushAnimationData("HitEffect", 49, 6, 2, Delay);
	PushAnimationData("HitEffect", 51, 12, 0, Delay);
	PushAnimationData("HitEffect", 52, -10, 0, Delay);
	PushAnimationData("HitEffect", 53, -10, 5, Delay);
	PushAnimationData("HitEffect", 54, -5, 0, Delay);
	PushAnimationData("HitEffect", 55, -5, 0, Delay);

	Delay = 0.05f;
	PushAnimationData("BulletDeath", 1, 2, -1, Delay);
	PushAnimationData("BulletDeath", 2, -9, -6, Delay);
	PushAnimationData("BulletDeath", 3, -21, -17, Delay);
	PushAnimationData("BulletDeath", 4, -31, -23, Delay);
	PushAnimationData("BulletDeath", 5, -40, -35, Delay);
	PushAnimationData("BulletDeath", 6, -16, -47, Delay);
	PushAnimationData("BulletDeath", 7, -15, -45, Delay);
	PushAnimationData("BulletDeath", 8, -15, -54, Delay);
	PushAnimationData("BulletDeath", 9, 11, -35, Delay);
	PushAnimationData("BulletDeath", 10, 12, -43, Delay);
	PushAnimationData("BulletDeath", 11, 15, -58, Delay);
	PushAnimationData("BulletDeath", 12, 23, -46, Delay);
	PushAnimationData("BulletDeath", 13, 25, -20, Delay);
	PushAnimationData("BulletDeath", 14, 11, -9, Delay);

	Delay = 0.05f;
	PushAnimationData("Blood", 0, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Blood", 1, 5 + XGap, 0 + YGap, Delay);
	PushAnimationData("Blood", 2, 10 + XGap, -5 + YGap, Delay);
	PushAnimationData("Blood", 3, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Blood", 4, 10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Blood", 5, 10 + XGap, 5 + YGap, Delay);
	PushAnimationData("Blood", 6, 10 + XGap, 15 + YGap, Delay);
	PushAnimationData("Blood", 7, 20 + XGap, 20 + YGap, Delay);
	PushAnimationData("Blood", 8, 20 + XGap, 15 + YGap, Delay);
	PushAnimationData("Blood", 9, 20 + XGap, 15 + YGap, Delay);
	PushAnimationData("Blood", 10, 15 + XGap, 15 + YGap, Delay);
	PushAnimationData("Blood", 11, 15 + XGap, 15 + YGap, Delay);
	PushAnimationData("Blood", 12, 10 + XGap, 20 + YGap, Delay);
	PushAnimationData("Blood", 13, 10 + XGap, 15 + YGap, Delay);
	PushAnimationData("Blood", 14, 10 + XGap, 15 + YGap, Delay);
	PushAnimationData("Blood", 15, 10 + XGap, 10 + YGap, Delay);

	Delay = 0.08f;
	PushAnimationData("GranadeDeath", 15, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 16, 8 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 17, 1 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 18, 1 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 19, -14 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 20, -11 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 21, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 22, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 23, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 24, 5 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 25, 7 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 26, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 27, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 28, 7 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 29, 3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 30, -21 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 31, -22 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 32, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 33, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 34, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 35, -15 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 36, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 37, -35 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 38, -10 + XGap, -55 + YGap, Delay);
	PushAnimationData("GranadeDeath", 39, -6 + XGap, -27 + YGap, Delay);
	PushAnimationData("GranadeDeath", 40, 0 + XGap, -30 + YGap, Delay);
}

void PivotTestMonster::ZombieGirlPivot()
{
	MonsterName = "ZombieGirl";

	float Delay = 0.1f;
	int XGap = 0;
	int YGap = 0;
	PushAnimationData("Idle", 0, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 1, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 2, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 3, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 4, 11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 5, 4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 6, 11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 7, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 8, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 9, 1 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 10, -2 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 11, -2 + XGap, 0 + YGap, Delay);

	PushAnimationData("Move", 12, -17 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 13, -17 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 14, -7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 15, 10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 16, 10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 17, 10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 18, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 19, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 20, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 21, -12 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 22, -17 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 23, -22 + XGap, 0 + YGap, Delay);

	PushAnimationData("Attack", 25, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 26, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 27, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 28, -3 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 29, -7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 30, -10 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 31, -24 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 32, -32 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 33, -11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 34, -11 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 35, -8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 36, -5 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 37, -22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 38, -22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 39, 13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 40, 2 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 41, 2 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 42, 27 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 43, 13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 44, 3 + XGap, 0 + YGap, Delay);

	PushAnimationData("AttackEffect", 0, -17 + XGap, -119 + YGap, Delay);
	PushAnimationData("AttackEffect", 1, -11 + XGap, -111 + YGap, Delay);
	PushAnimationData("AttackEffect", 2, 23 + XGap, -99 + YGap, Delay);
	PushAnimationData("AttackEffect", 3, 38 + XGap, -94 + YGap, Delay);
	PushAnimationData("AttackEffect", 4, 43 + XGap, -84 + YGap, Delay);
	PushAnimationData("AttackEffect", 5, 53 + XGap, -74 + YGap, Delay);
	PushAnimationData("AttackEffect", 6, 23 + XGap, -84 + YGap, Delay);
	PushAnimationData("AttackEffect", 7, 23 + XGap, -64 + YGap, Delay);
	PushAnimationData("AttackEffect", 8, 38 + XGap, -59 + YGap, Delay);
	PushAnimationData("AttackEffect", 9, 43 + XGap, -59 + YGap, Delay);

	PushAnimationData("GranadeDeath", 15, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 16, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 17, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 18, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 19, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 20, -10 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 21, -3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 22, -3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 23, -2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 24, 7 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 25, 3 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 26, -14 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 27, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 28, -12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 29, -5 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 30, -20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 31, -6 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 32, -32 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 33, -25 + XGap, -110 + YGap, Delay);
}

void PivotTestMonster::ZombieDoctorPivot()
{
	MonsterName = "ZombieDoctor";

	float Delay = 0.1f;
	int XGap = 0;
	int YGap = 0;
	PushAnimationData("Idle", 0, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 1, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 2, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 3, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 4, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 5, 12 + XGap, 0 + YGap, Delay);
	PushAnimationData("Idle", 6, 15 + XGap, 0 + YGap, Delay);

	PushAnimationData("Move", 7, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 8, 24 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 9, 27 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 10, 5 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 11, 21 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 12, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 13, 13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 14, 15 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 15, 30 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 16, 33 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 17, 33 + XGap, 0 + YGap, Delay);
	PushAnimationData("Move", 18, 25 + XGap, 0 + YGap, Delay);

	PushAnimationData("Attack", 19, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 20, 7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 21, 4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 22, 7 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 23, -3 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 24, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 25, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 26, 22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 27, 26 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 28, 26 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 29, -9 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 30, -9 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 31, -13 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 32, -6 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 33, -6 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 34, 8 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 35, 22 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 36, 24 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 37, 27 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 38, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 39, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 40, 25 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 41, 0 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 42, -3 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 43, -4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 44, -4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 45, 4 + XGap, 0 + YGap, Delay);
	PushAnimationData("Attack", 46, 11 + XGap, 0 + YGap, Delay);

	PushAnimationData("AttackEffect", 0, 40 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 1, 60 + XGap, -60 + YGap, Delay);
	PushAnimationData("AttackEffect", 2, 90 + XGap, -70 + YGap, Delay);
	PushAnimationData("AttackEffect", 3, 95 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 4, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 5, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 6, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 7, 75 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 8, 65 + XGap, -55 + YGap, Delay);
	PushAnimationData("AttackEffect", 9, 65 + XGap, -40 + YGap, Delay);
	PushAnimationData("AttackEffect", 10, 50 + XGap, -10 + YGap, Delay);
	PushAnimationData("AttackEffect", 11, 75 + XGap, -10 + YGap, Delay);

	Delay = 0.08f;
	PushAnimationData("GranadeDeath", 15, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 16, 8 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 17, 12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 18, 12 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 19, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 20, -1 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 21, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 22, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 23, 23 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 24, 22 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 25, 23 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 26, 19 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 27, 16 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 28, 20 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 29, 18 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 30, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 31, 0 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 32, -10 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 33, -13 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 34, 2 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 35, -8 + XGap, -110 + YGap, Delay);
	PushAnimationData("GranadeDeath", 36, -10 + XGap, -95 + YGap, Delay);
	PushAnimationData("GranadeDeath", 37, -10 + XGap, -95 + YGap, Delay);
	PushAnimationData("GranadeDeath", 38, 1 + XGap, -53 + YGap, Delay);
	PushAnimationData("GranadeDeath", 39, 4 + XGap, -53 + YGap, Delay);
}

void PivotTestMonster::MordenMinigunPivot()
{
	MonsterName = "MordenMinigun";

	PushAnimationData("Idle", 31, 0, 0, 0.13f);
	PushAnimationData("Idle", 32, 0, 0, 0.13f);
	PushAnimationData("Idle", 33, -4, 0, 0.13f);
	PushAnimationData("Idle", 34, -5, 0, 0.13f);

	PushAnimationData("Attack", 58, 0, 0, 0.15f);
	PushAnimationData("Attack", 59, -5, 0, 0.15f);
	PushAnimationData("Attack", 60, -6, 0, 0.15f);
	PushAnimationData("Attack", 61, -6, 0, 0.15f);
	PushAnimationData("Attack", 62, -6, 0, 0.06f);
	PushAnimationData("Attack", 63, -12, 0, 0.06f);
	PushAnimationData("Attack", 64, -14, 0, 0.06f);
	PushAnimationData("Attack", 65, -15, 0, 0.06f);
	PushAnimationData("Attack", 66, -8, 0, 0.06f);
	PushAnimationData("Attack", 67, -9, 0, 0.06f);
	PushAnimationData("Attack", 68, -3, 0, 0.12f);
	PushAnimationData("Attack", 69, -2, 0, 0.12f);
	PushAnimationData("Attack", 70, -2, 0, 0.12f);
	PushAnimationData("Attack", 71, 5, 0, 0.12f);
	PushAnimationData("Attack", 72, 3, 0, 0.12f);
	PushAnimationData("Attack", 73, 7, 0, 0.12f);
	PushAnimationData("Attack", 74, 12, 0, 0.12f);
	PushAnimationData("Attack", 75, 22, 0, 0.12f);
	PushAnimationData("Attack", 76, 23, 0, 0.12f);
	PushAnimationData("Attack", 77, 24, 0, 0.12f);
	PushAnimationData("Attack", 78, 18, 0, 0.05f);
	PushAnimationData("Attack", 79, 24, 0, 0.05f);
	PushAnimationData("Attack", 80, 20, 0, 0.05f);
	PushAnimationData("Attack", 81, 23, 0, 0.05f);
	PushAnimationData("Attack", 82, 22, 0, 0.20f);
	PushAnimationData("Attack", 83, 12, 0, 0.12f);
	PushAnimationData("Attack", 84, -4, 0, 0.12f);
	PushAnimationData("Attack", 85, -7, 0, 0.12f);
	PushAnimationData("Attack", 86, 1, 0, 0.12f);
	PushAnimationData("Attack", 87, 1, 0, 0.12f);

	PushAnimationData("AttackEffect", 88, 175, -35, 0.05f);
	PushAnimationData("AttackEffect", 89, 175, -35, 0.05f);
	PushAnimationData("AttackEffect", 90, 145, -30, 0.05f);
	PushAnimationData("AttackEffect", 91, 137, -58, 0.05f);

	PushAnimationData("Death1", 0, 0, 0, 0.05f);
	PushAnimationData("Death1", 1, 0, 0, 0.05f);
	PushAnimationData("Death1", 2, 0, 0, 0.05f);
	PushAnimationData("Death1", 3, 0, 0, 0.05f);
	PushAnimationData("Death1", 4, 0, 0, 0.05f);
	PushAnimationData("Death1", 5, 0, 0, 0.05f);
	PushAnimationData("Death1", 6, 0, 0, 0.05f);
	PushAnimationData("Death1", 7, 0, 0, 0.05f);
	PushAnimationData("Death1", 8, 0, 0, 0.05f);
	PushAnimationData("Death1", 9, 0, 0, 0.05f);
	PushAnimationData("Death1", 10, 0, 0, 0.25f);

	PushAnimationData("Death2", 48, 0, 0, 0.08f);
	PushAnimationData("Death2", 49, 0, 0, 0.08f);
	PushAnimationData("Death2", 50, 0, 0, 0.08f);
	PushAnimationData("Death2", 51, 0, 0, 0.08f);
	PushAnimationData("Death2", 52, 0, 0, 0.08f);
	PushAnimationData("Death2", 53, 0, 0, 0.08f);
	PushAnimationData("Death2", 54, 0, 0, 0.25f);

	PushAnimationData("GrandeDeathJump", 81, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 82, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 83, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 84, 0, 0, 0.07f);
	PushAnimationData("GrandeDeathJump", 85, 0, 0, 0.07f);
}

void PivotTestMonster::ExplosionPivot()
{
	MonsterName = "Explosion";

	PushAnimationData("SmallExplosion", 0, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 1, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 2, 0, -45, 0.04f);
	PushAnimationData("SmallExplosion", 3, 2, -43, 0.04f);
	PushAnimationData("SmallExplosion", 4, -2, -43, 0.04f);
	PushAnimationData("SmallExplosion", 5, 0, -45, 0.04f);
	PushAnimationData("SmallExplosion", 6, 0, -50, 0.04f);
	PushAnimationData("SmallExplosion", 7, 0, -50, 0.04f);
	PushAnimationData("SmallExplosion", 8, 0, -51, 0.04f);
	PushAnimationData("SmallExplosion", 9, 0, -51, 0.04f);
	PushAnimationData("SmallExplosion", 10, 0, -51, 0.04f);
	PushAnimationData("SmallExplosion", 11, 0, -50, 0.04f);
	PushAnimationData("SmallExplosion", 12, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 13, 2, -55, 0.04f);
	PushAnimationData("SmallExplosion", 14, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 15, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 16, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 17, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 18, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 19, 0, -55, 0.04f);
	PushAnimationData("SmallExplosion", 20, -3, -57, 0.04f);
	PushAnimationData("SmallExplosion", 21, -5, -57, 0.04f);
	PushAnimationData("SmallExplosion", 22, -4, -62, 0.04f);
	PushAnimationData("SmallExplosion", 23, -3, -65, 0.04f);
	PushAnimationData("SmallExplosion", 24, -5, -62, 0.04f);
	PushAnimationData("SmallExplosion", 25, -5, -64, 0.04f);
	PushAnimationData("SmallExplosion", 26, -4, -50, 0.04f);
	PushAnimationData("SmallExplosion", 27, -3, -51, 0.04f);

	PushAnimationData("LargeExplosion", 56, 0, -140, 0.05f);
	PushAnimationData("LargeExplosion", 57, 0, -140, 0.05f);
	PushAnimationData("LargeExplosion", 58, 0, -105, 0.05f);
	PushAnimationData("LargeExplosion", 59, 0, -105, 0.05f);
	PushAnimationData("LargeExplosion", 60, 0, -105, 0.05f);
	PushAnimationData("LargeExplosion", 61, 1, -111, 0.05f);
	PushAnimationData("LargeExplosion", 62, 0, -115, 0.05f);
	PushAnimationData("LargeExplosion", 63, -2, -117, 0.05f);
	PushAnimationData("LargeExplosion", 64, -2, -118, 0.05f);
	PushAnimationData("LargeExplosion", 65, -2, -120, 0.05f);
	PushAnimationData("LargeExplosion", 66, -2, -124, 0.05f);
	PushAnimationData("LargeExplosion", 67, 0, -125, 0.05f);
	PushAnimationData("LargeExplosion", 68, 0, -130, 0.05f);
	PushAnimationData("LargeExplosion", 69, 0, -130, 0.05f);
	PushAnimationData("LargeExplosion", 70, 0, -125, 0.05f);
	PushAnimationData("LargeExplosion", 71, 0, -125, 0.05f);
	PushAnimationData("LargeExplosion", 72, -5, -130, 0.05f);
	PushAnimationData("LargeExplosion", 73, 0, -130, 0.05f);
	PushAnimationData("LargeExplosion", 74, 0, -135, 0.05f);
	PushAnimationData("LargeExplosion", 75, -5, -135, 0.05f);
	PushAnimationData("LargeExplosion", 76, -15, -140, 0.05f);
	PushAnimationData("LargeExplosion", 77, -17, -140, 0.05f);
	PushAnimationData("LargeExplosion", 78, -18, -155, 0.05f);
	PushAnimationData("LargeExplosion", 79, -20, -155, 0.05f);
	PushAnimationData("LargeExplosion", 80, -20, -170, 0.05f);
	PushAnimationData("LargeExplosion", 81, -19, -169, 0.05f);
	PushAnimationData("LargeExplosion", 82, -22, -132, 0.05f);
	PushAnimationData("LargeExplosion", 83, -24, -127, 0.05f);
}

void PivotTestMonster::HelicopterPivot()
{
	MonsterName = "Helicopter";

	PushAnimationData("Move24", 0, -30, -105, 0.10f);
	PushAnimationData("Move24", 1, -38, -105, 0.10f);
	PushAnimationData("Move24", 2, -39, -105, 0.10f);
	PushAnimationData("Move24", 3, -38, -105, 0.10f);
	PushAnimationData("Move24", 4, -38, -105, 0.10f);
	PushAnimationData("Move24", 5, -30, -106, 0.10f);

	PushAnimationData("Move26", 6, -39, -113, 0.10f);
	PushAnimationData("Move26", 7, -39, -113, 0.10f);
	PushAnimationData("Move26", 8, -39, -113, 0.10f);
	PushAnimationData("Move26", 9, -39, -113, 0.10f);
	PushAnimationData("Move26", 10, -29, -113, 0.10f);
	PushAnimationData("Move26", 11, -29, -113, 0.10f);

	PushAnimationData("Move33", 12, -40, -120, 0.10f);
	PushAnimationData("Move33", 13, -40, -120, 0.10f);
	PushAnimationData("Move33", 14, -40, -120, 0.10f);
	PushAnimationData("Move33", 15, -40, -120, 0.10f);
	PushAnimationData("Move33", 16, -23, -120, 0.10f);
	PushAnimationData("Move33", 17, -24, -120, 0.10f);

	PushAnimationData("Move41", 18, -38, -125, 0.10f);
	PushAnimationData("Move41", 19, -38, -125, 0.10f);
	PushAnimationData("Move41", 20, -38, -125, 0.10f);
	PushAnimationData("Move41", 21, -38, -125, 0.10f);
	PushAnimationData("Move41", 22, -21, -125, 0.10f);
	PushAnimationData("Move41", 23, -12, -125, 0.10f);

	PushAnimationData("Move46", 24, -23, -125, 0.10f);
	PushAnimationData("Move46", 25, -27, -125, 0.10f);
	PushAnimationData("Move46", 26, -27, -125, 0.10f);
	PushAnimationData("Move46", 27, -27, -125, 0.10f);
	PushAnimationData("Move46", 28, -9, -125, 0.10f);
	PushAnimationData("Move46", 29, -6, -125, 0.10f);

	PushAnimationData("Move62", 30, 3, -125, 0.10f);
	PushAnimationData("Move62", 31, -8, -125, 0.10f);
	PushAnimationData("Move62", 32, -15, -125, 0.10f);
	PushAnimationData("Move62", 33, -15, -125, 0.10f);
	PushAnimationData("Move62", 34, 6, -125, 0.10f);
	PushAnimationData("Move62", 35, 6, -125, 0.10f);

	PushAnimationData("Move74", 36, 4, -125, 0.10f);
	PushAnimationData("Move74", 37, 7, -125, 0.10f);
	PushAnimationData("Move74", 38, 1, -125, 0.10f);
	PushAnimationData("Move74", 39, 1, -125, 0.10f);
	PushAnimationData("Move74", 40, 10, -125, 0.10f);
	PushAnimationData("Move74", 41, 4, -125, 0.10f);

	PushAnimationData("Move90", 42, 0, -125, 0.10f);
	PushAnimationData("Move90", 43, 6, -125, 0.10f);
	PushAnimationData("Move90", 44, 0, -125, 0.10f);
	PushAnimationData("Move90", 45, 1, -125, 0.10f);
	PushAnimationData("Move90", 46, 3, -125, 0.10f);
	PushAnimationData("Move90", 47, 0, -125, 0.10f);
}

void PivotTestMonster::BomberPivot()
{
	MonsterName = "Bomber";

	PushAnimationData("Propeller_0", 17, 29, -92, 0.05f);
	PushAnimationData("Propeller_0", 18, 29, -92, 0.05f);
	PushAnimationData("Propeller_0", 19, 29, -92, 0.05f);
	PushAnimationData("Propeller_0", 20, 29, -92, 0.05f);
	PushAnimationData("Propeller_0", 21, 29, -92, 0.05f);

	PushAnimationData("Propeller_1", 7, 31, -89, 0.05f);
	PushAnimationData("Propeller_1", 8, 31, -89, 0.05f);
	PushAnimationData("Propeller_1", 9, 31, -89, 0.05f);
	PushAnimationData("Propeller_1", 10, 31, -89, 0.05f);
	PushAnimationData("Propeller_1", 11, 31, -89, 0.05f);

	PushAnimationData("Propeller_2", 12, 31, -94, 0.05f);
	PushAnimationData("Propeller_2", 13, 31, -94, 0.05f);
	PushAnimationData("Propeller_2", 14, 31, -94, 0.05f);
	PushAnimationData("Propeller_2", 15, 31, -94, 0.05f);
	PushAnimationData("Propeller_2", 16, 31, -94, 0.05f);

	PushAnimationData("Propeller_3", 22, 29, -91, 0.05f);
	PushAnimationData("Propeller_3", 23, 29, -91, 0.05f);
	PushAnimationData("Propeller_3", 24, 29, -91, 0.05f);
	PushAnimationData("Propeller_3", 25, 29, -91, 0.05f);
	PushAnimationData("Propeller_3", 26, 29, -91, 0.05f);

	PushAnimationData("Propeller_4", 27, 30, -92, 0.05f);
	PushAnimationData("Propeller_4", 28, 30, -92, 0.05f);
	PushAnimationData("Propeller_4", 29, 30, -92, 0.05f);
	PushAnimationData("Propeller_4", 30, 30, -92, 0.05f);
	PushAnimationData("Propeller_4", 31, 30, -92, 0.05f);

	PushAnimationData("Propeller_5", 32, 29, -95, 0.05f);
	PushAnimationData("Propeller_5", 33, 29, -95, 0.05f);
	PushAnimationData("Propeller_5", 34, 29, -95, 0.05f);
	PushAnimationData("Propeller_5", 35, 29, -95, 0.05f);
	PushAnimationData("Propeller_5", 36, 29, -95, 0.05f);

	PushAnimationData("Propeller_6", 37, 30, -93, 0.05f);
	PushAnimationData("Propeller_6", 38, 30, -93, 0.05f);
	PushAnimationData("Propeller_6", 39, 30, -93, 0.05f);
	PushAnimationData("Propeller_6", 40, 30, -93, 0.05f);
	PushAnimationData("Propeller_6", 41, 30, -93, 0.05f);

	PushAnimationData("Fog", 49, 0, 0, 0.05f);
	PushAnimationData("Fog", 50, 0, 10, 0.05f);
	PushAnimationData("Fog", 51, 0, 17, 0.05f);
	PushAnimationData("Fog", 52, 0, 23, 0.05f);
	PushAnimationData("Fog", 53, 3, 28, 0.05f);
	PushAnimationData("Fog", 54, 3, 30, 0.05f);
	PushAnimationData("Fog", 55, 3, 34, 0.05f);
	PushAnimationData("Fog", 56, 2, 34, 0.05f);
}

void PivotTestMonster::GranadeExplosionPivot()
{
	MonsterName = "Granade";

	PushAnimationData("NormalExplosion", 0, 0, -5, 0.03f);
	PushAnimationData("NormalExplosion", 1, 0, -5, 0.03f);
	PushAnimationData("NormalExplosion", 2, 0, -6, 0.03f);
	PushAnimationData("NormalExplosion", 3, 0, -7, 0.03f);
	PushAnimationData("NormalExplosion", 4, 0, -39, 0.03f);
	PushAnimationData("NormalExplosion", 5, 0, -69, 0.03f);
	PushAnimationData("NormalExplosion", 6, 0, -112, 0.03f);
	PushAnimationData("NormalExplosion", 7, 0, -160, 0.03f);
	PushAnimationData("NormalExplosion", 8, 5, -155, 0.03f);
	PushAnimationData("NormalExplosion", 9, 5, -155, 0.03f);
	PushAnimationData("NormalExplosion", 10, 5, -155, 0.03f);
	PushAnimationData("NormalExplosion", 11, 5, -155, 0.03f);
	PushAnimationData("NormalExplosion", 12, 3, -157, 0.03f);
	PushAnimationData("NormalExplosion", 13, 5, -155, 0.03f);
	PushAnimationData("NormalExplosion", 14, 5, -153, 0.03f);
	PushAnimationData("NormalExplosion", 15, 5, -157, 0.03f);
	PushAnimationData("NormalExplosion", 16, 5, -169, 0.03f);
	PushAnimationData("NormalExplosion", 17, 5, -180, 0.03f);
	PushAnimationData("NormalExplosion", 18, 4, -188, 0.03f);
	PushAnimationData("NormalExplosion", 19, 4, -186, 0.03f);
	PushAnimationData("NormalExplosion", 20, 4, -190, 0.03f);
	PushAnimationData("NormalExplosion", 21, 4, -199, 0.03f);
	PushAnimationData("NormalExplosion", 22, 3, -207, 0.03f);
	PushAnimationData("NormalExplosion", 23, 3, -215, 0.03f);
	PushAnimationData("NormalExplosion", 24, 3, -216, 0.03f);
	PushAnimationData("NormalExplosion", 25, 3, -215, 0.03f);
	PushAnimationData("NormalExplosion", 26, 3, -230, 0.03f);

	PushAnimationData("BigExplosion", 27, 0, 15, 0.03f);
	PushAnimationData("BigExplosion", 28, 0, 15, 0.03f);
	PushAnimationData("BigExplosion", 29, 0, 14, 0.03f);
	PushAnimationData("BigExplosion", 30, 0, 15, 0.03f);
	PushAnimationData("BigExplosion", 31, 0, -33, 0.03f);
	PushAnimationData("BigExplosion", 32, 0, -81, 0.03f);
	PushAnimationData("BigExplosion", 33, 0, -145, 0.03f);
	PushAnimationData("BigExplosion", 34, 0, -205, 0.03f);
	PushAnimationData("BigExplosion", 35, -5, -220, 0.03f);
	PushAnimationData("BigExplosion", 36, 5, -215, 0.03f);
	PushAnimationData("BigExplosion", 37, 0, -211, 0.03f);
	PushAnimationData("BigExplosion", 38, 0, -206, 0.03f);
	PushAnimationData("BigExplosion", 39, 0, -187, 0.03f);
	PushAnimationData("BigExplosion", 40, -5, -185, 0.03f);
	PushAnimationData("BigExplosion", 41, -5, -180, 0.03f);
	PushAnimationData("BigExplosion", 42, -5, -180, 0.03f);
	PushAnimationData("BigExplosion", 43, -5, -188, 0.03f);
	PushAnimationData("BigExplosion", 44, -5, -204, 0.03f);
	PushAnimationData("BigExplosion", 45, -5, -212, 0.03f);
	PushAnimationData("BigExplosion", 46, -5, -225, 0.03f);
	PushAnimationData("BigExplosion", 47, -5, -228, 0.03f);
	PushAnimationData("BigExplosion", 48, -5, -240, 0.03f);
	PushAnimationData("BigExplosion", 49, 0, -245, 0.03f);
	PushAnimationData("BigExplosion", 50, 0, -255, 0.03f);
	PushAnimationData("BigExplosion", 51, 0, -275, 0.03f);
	PushAnimationData("BigExplosion", 52, 0, -275, 0.03f);
	PushAnimationData("BigExplosion", 53, 0, -285, 0.03f);
	PushAnimationData("BigExplosion", 54, 0, -290, 0.03f);
	PushAnimationData("BigExplosion", 55, 0, -303, 0.03f);
	PushAnimationData("BigExplosion", 56, 0, -310, 0.03f);
}

void PivotTestMonster::MonoeyeUFOPivot()
{
	MonsterName = "MonoeyeUFO";

	PushAnimationData("Idle_Top", 0, 0, -248, 0.13f);
	PushAnimationData("Idle_Top", 1, 0, -248, 0.13f);
	PushAnimationData("Idle_Top", 2, -1, -248, 0.13f);
	PushAnimationData("Idle_Top", 3, 0, -248, 0.13f);
	PushAnimationData("Idle_Top", 4, 0, -248, 0.13f);

	PushAnimationData("Charge", 5, -1, -309, 0.10f);
	PushAnimationData("Charge", 6, -1, -309, 0.10f);
	PushAnimationData("Charge", 7, -1, -309, 0.10f);
	PushAnimationData("Charge", 8, -1, -309, 0.10f);

	PushAnimationData("Fire", 9, -1, -385, 0.10f);
	PushAnimationData("Fire", 10, -2, -392, 0.10f);
	PushAnimationData("Fire", 11, -1, -391, 0.10f);
	PushAnimationData("Fire", 12, -2, -389, 0.10f);
	PushAnimationData("Fire", 13, -1, -387, 0.10f);
	PushAnimationData("Fire", 14, -1, -384, 0.10f);

	PushAnimationData("Laser", 0, 0, -417, 0.04f);
	PushAnimationData("Laser", 1, 0, -417, 0.04f);
	PushAnimationData("Laser", 2, 0, -417, 0.04f);
	PushAnimationData("Laser", 3, 0, -417, 0.04f);
	PushAnimationData("Laser", 4, 0, -417, 0.04f);
	PushAnimationData("Laser", 5, 0, -417, 0.04f);

	PushAnimationData("Laser_Bottom", 6, 0, 0, 0.04f);
	PushAnimationData("Laser_Bottom", 7, 0, 0, 0.04f);
	PushAnimationData("Laser_Bottom", 8, 0, 0, 0.04f);
	PushAnimationData("Laser_Bottom", 9, 0, 0, 0.04f);
	PushAnimationData("Laser_Bottom", 10, 0, 0, 0.04f);
	PushAnimationData("Laser_Bottom", 11, 0, 0, 0.04f);

	PushAnimationData("TombStone", 0, 0, -250, 0.10f);
	PushAnimationData("TombStone", 1, 0, -245, 0.10f);
	PushAnimationData("TombStone", 2, 0, -238, 0.10f);
	PushAnimationData("TombStone", 3, 0, -229, 0.10f);
	PushAnimationData("TombStone", 4, 0, -220, 0.10f);
	PushAnimationData("TombStone", 5, 0, -210, 0.10f);
	PushAnimationData("TombStone", 6, 0, -204, 0.10f);
	PushAnimationData("TombStone", 7, 0, -201, 0.10f);
	PushAnimationData("TombStone", 8, 0, -197, 0.10f);
	PushAnimationData("TombStone", 9, -2, -187, 0.10f);
	PushAnimationData("TombStone", 10, -6, -180, 0.10f);
	PushAnimationData("TombStone", 11, -9, -173, 0.10f);
	PushAnimationData("TombStone", 12, -7, -167, 0.10f);
	PushAnimationData("TombStone", 13, -8, -160, 0.10f);
	PushAnimationData("TombStone", 14, -8, -153, 0.10f);
	PushAnimationData("TombStone", 15, -8, -147, 0.10f);
	PushAnimationData("TombStone", 16, -7, -138, 0.10f);
	PushAnimationData("TombStone", 17, -7, -131, 0.10f);
	PushAnimationData("TombStone", 18, -7, -124, 0.10f);
	PushAnimationData("TombStone", 19, -9, -117, 0.10f);
	PushAnimationData("TombStone", 20, -9, -110, 0.10f);
	PushAnimationData("TombStone", 21, -9, -103, 0.10f);
	PushAnimationData("TombStone", 22, -9, -96, 0.10f);
	PushAnimationData("TombStone", 23, -9, -89, 0.10f);
	PushAnimationData("TombStone", 24, -9, -82, 0.10f);
	PushAnimationData("TombStone", 25, -9, -75, 0.10f);
	PushAnimationData("TombStone", 26, -7, -68, 0.10f);
	PushAnimationData("TombStone", 27, -7, -61, 0.10f);
	PushAnimationData("TombStone", 28, -7, -54, 0.10f);
	PushAnimationData("TombStone", 29, -7, -47, 0.10f);
	PushAnimationData("TombStone", 30, -7, -40, 0.10f);
	PushAnimationData("TombStone", 31, -7, -33, 0.10f);
	PushAnimationData("TombStone", 32, -7, -26, 0.10f);
}

void PivotTestMonster::ZombieMordenPivot()
{
	MonsterName = "ZombieMorden";

	PushAnimationData("Idle", 16, 0, 0, 0.18f);
	PushAnimationData("Idle", 17, 2, 0, 0.15f);
	PushAnimationData("Idle", 18, 4, 0, 0.15f);
	PushAnimationData("Idle", 19, 4, 0, 0.15f);
	PushAnimationData("Idle", 20, 4, 0, 0.15f);

	PushAnimationData("Move", 0, 0, 0, 0.08f);
	PushAnimationData("Move", 1, 0, 0, 0.08f);
	PushAnimationData("Move", 2, 0, 0, 0.08f);
	PushAnimationData("Move", 3, 0, 0, 0.08f);
	PushAnimationData("Move", 4, 0, 0, 0.08f);
	PushAnimationData("Move", 5, 0, 0, 0.08f);
	PushAnimationData("Move", 6, 0, 0, 0.08f);
	PushAnimationData("Move", 7, 0, 0, 0.08f);
	PushAnimationData("Move", 8, 0, 0, 0.08f);
	PushAnimationData("Move", 9, 0, 0, 0.08f);
	PushAnimationData("Move", 10, 0, 0, 0.08f);
	PushAnimationData("Move", 11, 0, 0, 0.08f);
	PushAnimationData("Move", 12, 0, 0, 0.08f);
	PushAnimationData("Move", 13, 0, 0, 0.08f);
	PushAnimationData("Move", 14, 0, 0, 0.08f);
	PushAnimationData("Move", 15, 0, 0, 0.08f);

	PushAnimationData("Attack", 23, 0, 0, 0.10f);
	PushAnimationData("Attack", 24, 0, 0, 0.10f);
	PushAnimationData("Attack", 25, 0, 0, 0.20f);
	PushAnimationData("Attack", 26, 0, 0, 0.10f);
	PushAnimationData("Attack", 27, 0, -20, 0.10f);
	PushAnimationData("Attack", 28, 0, -20, 0.10f);
	PushAnimationData("Attack", 29, 0, -20, 0.10f);
	PushAnimationData("Attack", 30, 0, -20, 0.10f);
	PushAnimationData("Attack", 31, 0, -20, 0.10f);
	PushAnimationData("Attack", 32, 0, -20, 0.10f);

	PushAnimationData("Boom", 0, 0, -50, 0.05f);
	PushAnimationData("Boom", 1, 0, -50, 0.05f);
	PushAnimationData("Boom", 2, 0, -20, 0.05f);
	PushAnimationData("Boom", 3, 0, -55, 0.05f);
	PushAnimationData("Boom", 4, 0, -70, 0.05f);
	PushAnimationData("Boom", 5, 0, -80, 0.05f);
	PushAnimationData("Boom", 6, 5, -90, 0.05f);
	PushAnimationData("Boom", 7, 5, -90, 0.05f);
	PushAnimationData("Boom", 8, 0, -90, 0.05f);
	PushAnimationData("Boom", 9, 0, -90, 0.05f);
	PushAnimationData("Boom", 10, 0, -85, 0.05f);
	PushAnimationData("Boom", 11, 0, -80, 0.05f);
	PushAnimationData("Boom", 12, 0, -85, 0.05f);
	PushAnimationData("Boom", 13, -5, -90, 0.05f);
	PushAnimationData("Boom", 14, -5, -95, 0.05f);
	PushAnimationData("Boom", 15, -5, -95, 0.05f);
	PushAnimationData("Boom", 16, -5, -95, 0.05f);
	PushAnimationData("Boom", 17, 0, -87, 0.05f);
}

void PivotTestMonster::ItemPivot()
{
	MonsterName = "NPC";

	PushAnimationData("Bind", 0, -5, 0, 0.13f);
	PushAnimationData("Bind", 1, -7, 0, 0.13f);
	PushAnimationData("Bind", 2, -2, 0, 0.13f);
	PushAnimationData("Bind", 3, 0, 0, 0.13f);
	PushAnimationData("Bind", 4, 0, 0, 0.13f);

	PushAnimationData("BindOut", 5, -5, 0, 0.10f);
	PushAnimationData("BindOut", 6, -5, 0, 0.10f);
	PushAnimationData("BindOut", 7, -5, 0, 0.10f);
	PushAnimationData("BindOut", 8, -5, 0, 0.10f);

	PushAnimationData("Falling", 9, 10, 0, 0.05f);
	PushAnimationData("Falling", 10, 11, 0, 0.05f);
	PushAnimationData("Falling", 11, 0, 0, 0.05f);
	PushAnimationData("Falling", 12, -6, 0, 0.05f);
	PushAnimationData("Falling", 13, -6, 0, 0.05f);

	PushAnimationData("Walk", 14, -15, 0, 0.10f);
	PushAnimationData("Walk", 15, -15, 0, 0.10f);
	PushAnimationData("Walk", 16, -15, 0, 0.10f);
	PushAnimationData("Walk", 17, 0, 0, 0.10f);
	PushAnimationData("Walk", 18, 0, 0, 0.10f);
	PushAnimationData("Walk", 19, -5, 0, 0.10f);
	PushAnimationData("Walk", 20, -10, 0, 0.10f);
	PushAnimationData("Walk", 21, 0, 0, 0.10f);
	PushAnimationData("Walk", 22, 5, 0, 0.10f);
	PushAnimationData("Walk", 23, 0, 0, 0.10f);
	PushAnimationData("Walk", 24, -10, 0, 0.10f);
	PushAnimationData("Walk", 25, -20, 0, 0.10f);

	PushAnimationData("DropItem", 26, 0, 0, 0.10f);
	PushAnimationData("DropItem", 27, 0, 0, 0.10f);
	PushAnimationData("DropItem", 28, -5, 0, 0.10f);
	PushAnimationData("DropItem", 29, -5, 0, 0.10f);
	PushAnimationData("DropItem", 30, 2, 0, 0.10f);
	PushAnimationData("DropItem", 31, 2, 0, 0.10f);
	PushAnimationData("DropItem", 32, 23, 0, 0.10f);
	PushAnimationData("DropItem", 33, 35, 0, 0.10f);
	PushAnimationData("DropItem", 34, 42, 0, 0.10f);
	PushAnimationData("DropItem", 35, 39, 0, 0.10f);
	PushAnimationData("DropItem", 36, 39, 0, 0.20f);

	PushAnimationData("Salute", 37, 0, 0, 0.07f);
	PushAnimationData("Salute", 38, 0, 0, 0.07f);
	PushAnimationData("Salute", 39, 0, 0, 0.07f);
	PushAnimationData("Salute", 40, -8, 0, 0.07f);
	PushAnimationData("Salute", 41, -10, 0, 0.07f);
	PushAnimationData("Salute", 42, -6, 0, 0.07f);
	PushAnimationData("Salute", 43, -6, 0, 0.07f);
	PushAnimationData("Salute", 44, -6, 0, 0.07f);
	PushAnimationData("Salute", 45, 2, 0, 0.07f);
	PushAnimationData("Salute", 46, 7, 0, 0.07f);
	PushAnimationData("Salute", 47, 7, 0, 0.22f);
	PushAnimationData("Salute", 48, 15, 0, 0.07f);
	PushAnimationData("Salute", 49, 24, 0, 0.07f);
	PushAnimationData("Salute", 50, 16, 0, 0.07f);

	PushAnimationData("RunAway", 51, 0, 0, 0.07f);
	PushAnimationData("RunAway", 52, 0, 0, 0.07f);
	PushAnimationData("RunAway", 53, 0, 0, 0.07f);
	PushAnimationData("RunAway", 54, 0, 0, 0.07f);
	PushAnimationData("RunAway", 55, 0, 0, 0.07f);
	PushAnimationData("RunAway", 56, 0, 0, 0.07f);
	PushAnimationData("RunAway", 57, -5, 0, 0.07f);
	PushAnimationData("RunAway", 58, -10, 0, 0.07f);
}

void PivotTestMonster::SetDefaultPivot()
{
	{
		for (int i = CurState->FrameIndex.Start; i < CurState->FrameIndex.End + 1; ++i)
		{
			CurState->Pivot[i] = Pivot();
		}
	}

	ZombieManPivot();
	ZombieGirlPivot();
	ZombieDoctorPivot();
	MordenMinigunPivot();
	ExplosionPivot();
	HelicopterPivot();
	BomberPivot();
	GranadeExplosionPivot();
	MonoeyeUFOPivot();
	ZombieMordenPivot();
	ItemPivot();

	ChangeState("ZombieMan_Idle");
}