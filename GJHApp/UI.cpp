#include "UI.h"
#include <GJHRenderer.h>
#include <GJHGameEngineScene.h>
#include "Mission.h"
#include "Player.h"

int UI::m_GameTime = 60;

void UI::Start()
{
	GJHRenderer* AniRender = nullptr;
	m_ImageDir = ENUM_DIRECTION::RIGHT;

	for (int i = 0; i < 6; ++i)
	{
		CreateHUDRender(m_ScoreRender[i], "Score", 16, { (float)(100 + (i * 32)), 35.f });
	}

	for (int i = 0; i < 3; ++i)
	{
		CreateHUDRender(m_AmmoRender[i], "Ammo", 26, { (float)(328 + (i * 32)), 69 });
	}

	for (int i = 0; i < 2; ++i)
	{
		CreateHUDRender(m_GranadeRender[i], "Granade", 26, { (float)(455 + (i * 32)), 69 });
	}

	for (int i = 0; i < 2; ++i)
	{
		CreateHUDRender(m_GameTimeRender[i], "Time", 6, { (float)(570 + (i * 65)), 52 });
	}

	CreateHUDRender(AniRender, "HPBar", 0, { 150, 70 });
	CreateHUDRender(AniRender, "LifeString", 1, { 120, 105 });
	CreateHUDRender(m_LifeRender, "Life", 38, { 200, 105 });
	CreateHUDRender(AniRender, "ArmsBomb", 2, { 410, 54 });
	CreateHUDRender(m_PressStartRender, "PressStart", 4, { 1050, 50 });
	CreateHUDRender(AniRender, "Creadit", 5, { 980, 940 });
	CreateHUDRender(AniRender, "CreaditNum1", 16, { 1165, 940 });
	CreateHUDRender(AniRender, "CreaditNum2", 18, { 1197, 940 });

	PressStartUpdater.PushFunc(1.2f, &UI::PressStartOn, this);
	PressStartUpdater.PushFunc(0.5f, &UI::PressStartOff, this);

	GameTimeUpdater.PushDelay(4.f);
	GameTimeUpdater.PushOneShotFunc(&UI::SubGameTime, this);
}

void UI::Update()
{
	PressStartUpdater.Update();
	GameTimeUpdater.Update();

	ScoreUpdate();
	AmmoUpdate();
	GranadeUpdate();
	LifeUpdate();
	GameTimeUpdate();
}

void UI::CreateHUDRender(GJHRenderer*& _Render, const GJHString& _AniName, int _Frame, const GJHVector& _ActorPivot)
{
	_Render = GJHGameEngineActor::CreateRender({ 348, 68 }, "HUD.bmp", ContentsEnum::RENDERORDER::UI);
	_Render->CreateAnimation(_AniName, "HUD.bmp", 0, 45, 9999999.f);
	_Render->ChangeAnimation(_AniName);
	_Render->SetAnimationFrameIndex(_Frame);
	_Render->SetActorPivot(_ActorPivot);
	_Render->CameraEffectOff();
}

void UI::ScoreUpdate()
{
	int Score = Player::GetScore();
	int Number[6];

	int Digits = 100000;
	int i = 0;
	while (0 < Digits)
	{
		Number[i++] = Score / Digits;
		Score %= Digits;
		Digits /= 10;
	}

	for (i = 0; i < 6; ++i)
	{
		m_ScoreRender[i]->SetAnimationFrameIndex(Number[i] + 16);
	}
}

void UI::AmmoUpdate()
{
	int Ammo = Player::GetWeapon()->GetAmmo();

	if (Ammo == 0)
	{
		m_AmmoRender[0]->SetDraw(false);
		m_AmmoRender[1]->SetAnimationFrameIndex(3);
		m_AmmoRender[2]->SetDraw(false);
		return;
	}
	else
	{
		m_AmmoRender[0]->SetDraw(true);
		m_AmmoRender[2]->SetDraw(true);
	}

	int Digits = 100;
	int i = 0;
	int Number[3];
	while (0 < Digits)
	{
		Number[i++] = Ammo / Digits;
		Ammo %= Digits;
		Digits /= 10;
	}

	for (i = 0; i < 3; ++i)
	{
		m_AmmoRender[i]->SetAnimationFrameIndex(Number[i] + 26);
	}
}

void UI::GranadeUpdate()
{
	int GranadeCount = Player::GetGranadeCount();
	int Number[2];
	
	Number[0] = GranadeCount / 10;
	GranadeCount %= 10;
	Number[1] = GranadeCount;

	for (int i = 0; i < 2; ++i)
	{
		m_GranadeRender[i]->SetAnimationFrameIndex(Number[i] + 26);
	}

	if (Number[0] == 0)
	{
		m_GranadeRender[0]->SetDraw(false);
	}
	else
	{
		m_GranadeRender[0]->SetDraw(true);
	}
}

void UI::LifeUpdate()
{
	int Life = Player::GetLife();
	m_LifeRender->SetAnimationFrameIndex(Life + 36);
}

void UI::PressStartOn()
{
	m_PressStartRender->SetDraw(true);
}

void UI::PressStartOff()
{
	m_PressStartRender->SetDraw(false);
}

void UI::MissionStart()
{
	Mission* NewActor = GetScene()->CreateActor<Mission>();
	NewActor->SetPos({ 0,0 });
	NewActor->MissionStart();
}

void UI::MissionComplete()
{
	Mission* NewActor = GetScene()->CreateActor<Mission>();
	NewActor->SetPos({ 0,0 });
	NewActor->MissionComplete();
}

void UI::GameTimeUpdate()
{
	int Number[2];
	int GameTIme = m_GameTime;

	Number[0] = GameTIme / 10;
	GameTIme %= 10;
	Number[1] = GameTIme;

	for (int i = 0; i < 2; ++i)
	{
		m_GameTimeRender[i]->SetAnimationFrameIndex(Number[i] + 6);
	}
}

void UI::SubGameTime()
{
	if (0 < m_GameTime)
	{
		--m_GameTime;
	}
}