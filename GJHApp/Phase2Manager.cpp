#include "Phase2Manager.h"
#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include <GJHSceneManager.h>
#include "MapChange.h"
#include "MonoeyeUFO.h"
#include "Mission.h"
#include "GrandFather.h"

bool Phase2Manager::m_MissionComplete = false;
bool Phase2Manager::m_BossAppear = false;
bool Phase2Manager::m_BossDie = false;

void Phase2Manager::Start()
{
	m_AniCollision = CreateCollision(COLGEOTYPE::CGT_RECT, { 0, 0 }, { 100, 800 }, ContentsEnum::COLTYPE::NONE);
	
	m_IsCol = false;

	m_MissionComplete = false;
}

void Phase2Manager::Update()
{
	Timer.EventUpdate();
	if (m_IsCol == true &&
		Timer.CheckEventTime() == true)
	{
		m_IsCol = false;

		CreateMapChanger();
	}

	if (m_BossAppear == true)
	{
		m_BossAppear = false;

		ItemTimer.PushDelay(15.f);
		ItemTimer.PushOneShotFunc(&Phase2Manager::CreateGrandFather, this);
		ItemTimer.m_bLoop = true;
	}

	ItemTimer.Update();
	if (m_BossDie == true)
	{
		ItemTimer.SetPause(true);
	}

	if (m_MissionComplete == true)
	{
		m_MissionComplete = false;

		MissionActor = GetScene()->CreateActor<Mission>();
		MissionActor->SetPos({ 0,0 });
		MissionActor->MissionComplete();
	}

	if (MissionActor != nullptr &&
		MissionActor->IsMissionCompleteEnd() == true)
	{
		FadeIn(2.5f);
	}

	if (m_FadeInStart == true && IsFadeInOutOver() == true)
	{
		GJHSceneManager::Inst.ChangeScene("Ending");
	}
}

void Phase2Manager::ColEnter(GJHCollision* _This, GJHCollision* _Other)
{
	if (_Other->GetOrder() == (int)ContentsEnum::COLTYPE::PLAYER)
	{
		GJHGameEngineSound::FadeOut("StageBGM", 2.5f);

		m_AniCollision->SetHitable(false);
		m_IsCol = true;
		Timer.SetEventTime(1.5f, true);
	}
}

void Phase2Manager::CreateMapChanger()
{
	MapChange* NewActor = GetScene()->CreateActor<MapChange>();
	NewActor->SetPos({ 22807, 2702 });
}

void Phase2Manager::CreateGrandFather()
{
	int Random = GJHMath::Random(2);

	GrandFather* NewGrandFather = GetScene()->CreateActor<GrandFather>();
	NewGrandFather->SetPos({ 22770, 2150 });
	NewGrandFather->SetFallingState();

	switch (Random)
	{
	case 1:
		NewGrandFather->SetDropItemType(ENUM_ITEMTYPE::HEAVYMACHINEGUN);
		break;
	case 2:
		NewGrandFather->SetDropItemType(ENUM_ITEMTYPE::GRANADE);
		break;
	}
}