#include "Mission.h"
#include <GJHRenderer.h>
#include <GJHGameEngineScene.h>
#include <GJHGameEngineSound.h>
#include <GJHSceneManager.h>
#include "MissionText.h"

void Mission::Start()
{
	{
		m_MissionStartActor[0] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[0]->SetText("F");
		m_MissionStartActor[0]->SetPos(GJHVector(-135.f, -410.f));
		m_MissionStartActor[0]->SetMoveSpeed(1050.f);

		m_MissionStartActor[1] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[1]->SetText("I");
		m_MissionStartActor[1]->SetPos(GJHVector(-65.f, -410.f));
		m_MissionStartActor[1]->SetMoveSpeed(1050.f);

		m_MissionStartActor[2] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[2]->SetText("N");
		m_MissionStartActor[2]->SetPos(GJHVector(15.f, -410.f));
		m_MissionStartActor[2]->SetMoveSpeed(1050.f);

		m_MissionStartActor[3] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[3]->SetText("A");
		m_MissionStartActor[3]->SetPos(GJHVector(100.f, -410.f));
		m_MissionStartActor[3]->SetMoveSpeed(1050.f);

		m_MissionStartActor[4] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[4]->SetText("L");
		m_MissionStartActor[4]->SetPos(GJHVector(185.f, -410.f));
		m_MissionStartActor[4]->SetMoveSpeed(1050.f);

		m_MissionStartActor[5] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[5]->SetText("M");
		m_MissionStartActor[5]->SetPos(GJHVector(-220.f, -270.f));
		m_MissionStartActor[5]->SetMoveSpeed(1050.f);

		m_MissionStartActor[6] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[6]->SetText("I");
		m_MissionStartActor[6]->SetPos(GJHVector(-145.f, -270.f));
		m_MissionStartActor[6]->SetMoveSpeed(1050.f);

		m_MissionStartActor[7] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[7]->SetText("S");
		m_MissionStartActor[7]->SetPos(GJHVector(-65.f, -270.f));
		m_MissionStartActor[7]->SetMoveSpeed(1050.f);

		m_MissionStartActor[8] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[8]->SetText("S");
		m_MissionStartActor[8]->SetPos(GJHVector(20.f, -270.f));
		m_MissionStartActor[8]->SetMoveSpeed(1050.f);

		m_MissionStartActor[9] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[9]->SetText("I");
		m_MissionStartActor[9]->SetPos(GJHVector(90.f, -270.f));
		m_MissionStartActor[9]->SetMoveSpeed(1050.f);

		m_MissionStartActor[10] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[10]->SetText("O");
		m_MissionStartActor[10]->SetPos(GJHVector(160.f, -270.f));
		m_MissionStartActor[10]->SetMoveSpeed(1050.f);

		m_MissionStartActor[11] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[11]->SetText("N");
		m_MissionStartActor[11]->SetPos(GJHVector(245.f, -270.f));
		m_MissionStartActor[11]->SetMoveSpeed(1050.f);

		m_MissionStartActor[12] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[12]->SetText("S");
		m_MissionStartActor[12]->SetPos(GJHVector(-165.f, -100.f));
		m_MissionStartActor[12]->SetMoveSpeed(1050.f);

		m_MissionStartActor[13] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[13]->SetText("T");
		m_MissionStartActor[13]->SetPos(GJHVector(-80.f, -100.f));
		m_MissionStartActor[13]->SetMoveSpeed(1050.f);

		m_MissionStartActor[14] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[14]->SetText("A");
		m_MissionStartActor[14]->SetPos(GJHVector(-5.f, -100.f));
		m_MissionStartActor[14]->SetMoveSpeed(1050.f);

		m_MissionStartActor[15] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[15]->SetText("R");
		m_MissionStartActor[15]->SetPos(GJHVector(85.f, -100.f));
		m_MissionStartActor[15]->SetMoveSpeed(1050.f);

		m_MissionStartActor[16] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[16]->SetText("T");
		m_MissionStartActor[16]->SetPos(GJHVector(160.f, -100.f));
		m_MissionStartActor[16]->SetMoveSpeed(1050.f);

		m_MissionStartActor[17] = GetScene()->CreateActor<MissionText>();
		m_MissionStartActor[17]->SetText("!");
		m_MissionStartActor[17]->SetPos(GJHVector(235.f, -100.f));
		m_MissionStartActor[17]->SetMoveSpeed(1050.f);

		State.CreateState("MissionStart_StartMove", &Mission::MissionStart_StartMoveInit, &Mission::MissionStart_StartMoveState, nullptr, this);
		State.CreateState("MissionStart_Blink", &Mission::MissionStart_BlinkInit, &Mission::MissionStart_BlinkState, nullptr, this);
		State.CreateState("MissionStart_End", &Mission::MissionStart_EndInit, &Mission::MissionStart_EndState, nullptr, this);
	}

	{
		m_MissionCompleteActor[0] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[0]->SetText("M");
		m_MissionCompleteActor[0]->SetPos(GJHVector(-220.f, -270.f));
		m_MissionCompleteActor[0]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[1] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[1]->SetText("I");
		m_MissionCompleteActor[1]->SetPos(GJHVector(-145.f, -270.f));
		m_MissionCompleteActor[1]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[2] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[2]->SetText("S");
		m_MissionCompleteActor[2]->SetPos(GJHVector(-65.f, -270.f));
		m_MissionCompleteActor[2]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[3] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[3]->SetText("S");
		m_MissionCompleteActor[3]->SetPos(GJHVector(20.f, -270.f));
		m_MissionCompleteActor[3]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[4] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[4]->SetText("I");
		m_MissionCompleteActor[4]->SetPos(GJHVector(90.f, -270.f));
		m_MissionCompleteActor[4]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[5] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[5]->SetText("O");
		m_MissionCompleteActor[5]->SetPos(GJHVector(160.f, -270.f));
		m_MissionCompleteActor[5]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[6] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[6]->SetText("N");
		m_MissionCompleteActor[6]->SetPos(GJHVector(245.f, -270.f));
		m_MissionCompleteActor[6]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[7] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[7]->SetText("C");
		m_MissionCompleteActor[7]->SetPos(GJHVector(-315.f, -100.f));
		m_MissionCompleteActor[7]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[8] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[8]->SetText("O");
		m_MissionCompleteActor[8]->SetPos(GJHVector(-230.f, -100.f));
		m_MissionCompleteActor[8]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[9] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[9]->SetText("M");
		m_MissionCompleteActor[9]->SetPos(GJHVector(-155.f, -100.f));
		m_MissionCompleteActor[9]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[10] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[10]->SetText("P");
		m_MissionCompleteActor[10]->SetPos(GJHVector(-65.f, -100.f));
		m_MissionCompleteActor[10]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[11] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[11]->SetText("L");
		m_MissionCompleteActor[11]->SetPos(GJHVector(10.f, -100.f));
		m_MissionCompleteActor[11]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[12] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[12]->SetText("E");
		m_MissionCompleteActor[12]->SetPos(GJHVector(85.f, -100.f));
		m_MissionCompleteActor[12]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[13] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[13]->SetText("T");
		m_MissionCompleteActor[13]->SetPos(GJHVector(160.f, -100.f));
		m_MissionCompleteActor[13]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[14] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[14]->SetText("E");
		m_MissionCompleteActor[14]->SetPos(GJHVector(235.f, -100.f));
		m_MissionCompleteActor[14]->SetMoveSpeed(800.f);

		m_MissionCompleteActor[15] = GetScene()->CreateActor<MissionText>();
		m_MissionCompleteActor[15]->SetText("!");
		m_MissionCompleteActor[15]->SetPos(GJHVector(310.f, -100.f));
		m_MissionCompleteActor[15]->SetMoveSpeed(800.f);

		State.CreateState("MissionComplete_StartMove", &Mission::MissionComplete_StartMoveInit, &Mission::MissionComplete_StartMoveState, nullptr, this);
		State.CreateState("MissionComplete_Blink", &Mission::MissionComplete_BlinkInit, &Mission::MissionComplete_BlinkState, nullptr, this);
		State.CreateState("MissionComplete_End", &Mission::MissionComplete_EndInit, &Mission::MissionComplete_EndState, nullptr, this);

		m_MissionCompleteEnd = false;
	}
}

void Mission::Update()
{
	State.Update();
}

void Mission::MissionStart()
{
	GJHGameEngineSound::PlayOneShot("MissionStart.mp3", 1.f);

	State.ChangeState("MissionStart_StartMove");
}

void Mission::MissionComplete()
{
	GJHGameEngineSound::PlayOneShot("MissionComplete.mp3", 1.f);

	State.ChangeState("MissionComplete_StartMove");
}

void Mission::MissionStart_On()
{
	for (int i = 0; i < 18; ++i)
	{
		m_MissionStartActor[i]->On();
	}
}

void Mission::MissionStart_Off()
{
	for (int i = 0; i < 18; ++i)
	{
		m_MissionStartActor[i]->Off();
	}
}

void Mission::MissionComplete_On()
{
	for (int i = 0; i < 16; ++i)
	{
		m_MissionCompleteActor[i]->On();
	}
}

void Mission::MissionComplete_Off()
{
	for (int i = 0; i < 16; ++i)
	{
		m_MissionCompleteActor[i]->Off();
	}
}

void Mission::MissionStart_StartMoveInit()
{
	m_MissionCount = 0;
	Timer.SetEventTime(0.05f, true);

	m_MissionArrivalPos[0] = GJHVector(500.f, 270.f);
	m_MissionArrivalPos[1] = GJHVector(570.f, 270.f);
	m_MissionArrivalPos[2] = GJHVector(640.f, 270.f);
	m_MissionArrivalPos[3] = GJHVector(725.f, 270.f);
	m_MissionArrivalPos[4] = GJHVector(810.f, 270.f);
	m_MissionArrivalPos[5] = GJHVector(415.f, 410.f);
	m_MissionArrivalPos[6] = GJHVector(490.f, 410.f);
	m_MissionArrivalPos[7] = GJHVector(560.f, 410.f);
	m_MissionArrivalPos[8] = GJHVector(645.f, 410.f);
	m_MissionArrivalPos[9] = GJHVector(715.f, 410.f);
	m_MissionArrivalPos[10] = GJHVector(785.f, 410.f);
	m_MissionArrivalPos[11] = GJHVector(870.f, 410.f);
	m_MissionArrivalPos[12] = GJHVector(470.f, 570.f);
	m_MissionArrivalPos[13] = GJHVector(555.f, 570.f);
	m_MissionArrivalPos[14] = GJHVector(630.f, 570.f);
	m_MissionArrivalPos[15] = GJHVector(720.f, 570.f);
	m_MissionArrivalPos[16] = GJHVector(795.f, 570.f);
	m_MissionArrivalPos[17] = GJHVector(870.f, 570.f);
}

void Mission::MissionStart_StartMoveState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true &&
		m_MissionCount < 18)
	{
		m_MissionCount++;
	}

	int Check = 0;
	for (int i = 0; i < m_MissionCount; ++i)
	{
		Check += m_MissionStartActor[i]->AccelMove(m_MissionArrivalPos[i]);
	}

	if (Check == 18)
	{
		State.ChangeState("MissionStart_Blink");
	}
}

void Mission::MissionStart_BlinkInit()
{
	m_MissionCount = 0;
	BlinkUpdater.PushOneShotFunc(&Mission::MissionStart_Off, this);
	BlinkUpdater.PushDelay(0.2f);
	BlinkUpdater.PushOneShotFunc(&Mission::MissionStart_On, this);
	BlinkUpdater.PushDelay(0.4f);
	BlinkUpdater.PushOneShotFunc(&Mission::MissionStart_Off, this);
	BlinkUpdater.PushDelay(0.2f);
	BlinkUpdater.PushOneShotFunc(&Mission::MissionStart_On, this);
	BlinkUpdater.PushDelay(0.4f);
	BlinkUpdater.m_bLoop = false;
}

void Mission::MissionStart_BlinkState()
{
	BlinkUpdater.Update();

	if (BlinkUpdater.GetIsEnd() == true)
	{
		State.ChangeState("MissionStart_End");
	}
}

void Mission::MissionStart_EndInit()
{
	Timer.SetEventTime(30.f, true);

	m_MissionArrivalAngle[0] = -155.f;
	m_MissionArrivalAngle[1] = -130.f;
	m_MissionArrivalAngle[2] = -117.f;
	m_MissionArrivalAngle[3] = -106.f;
	m_MissionArrivalAngle[4] = -60.f;
	m_MissionArrivalAngle[5] = 160.f;
	m_MissionArrivalAngle[6] = 142.f;
	m_MissionArrivalAngle[7] = 125.f;
	m_MissionArrivalAngle[8] = 107.f;
	m_MissionArrivalAngle[9] = 59.f;
	m_MissionArrivalAngle[10] = 45.f;
	m_MissionArrivalAngle[11] = 13.f;
	m_MissionArrivalAngle[12] = 150.f;
	m_MissionArrivalAngle[13] = 133.f;
	m_MissionArrivalAngle[14] = 116.f;
	m_MissionArrivalAngle[15] = 55.f;
	m_MissionArrivalAngle[16] = 39.f;
	m_MissionArrivalAngle[17] = 21.f;

	for (int i = 0; i < 18; ++i)
	{
		m_MissionStartActor[i]->SetMoveSpeed(2000.f);
	}
}

void Mission::MissionStart_EndState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true)
	{
		State.SetPause(true);

		for (int i = 0; i < 18; ++i)
		{
			m_MissionStartActor[i]->Death();
		}
		return;
	}

	for (int i = 0; i < 18; ++i)
	{
		m_MissionStartActor[i]->Move(m_MissionArrivalAngle[i]);
	}
}

void Mission::MissionComplete_StartMoveInit()
{
	m_MissionCount = 0;
	Timer.SetEventTime(0.05f, true);

	m_MissionArrivalPos[0] = GJHVector(415.f, 380.f);
	m_MissionArrivalPos[1] = GJHVector(490.f, 380.f);
	m_MissionArrivalPos[2] = GJHVector(560.f, 380.f);
	m_MissionArrivalPos[3] = GJHVector(645.f, 380.f);
	m_MissionArrivalPos[4] = GJHVector(715.f, 380.f);
	m_MissionArrivalPos[5] = GJHVector(785.f, 380.f);
	m_MissionArrivalPos[6] = GJHVector(870.f, 380.f);
	m_MissionArrivalPos[7] = GJHVector(320.f, 550.f);
	m_MissionArrivalPos[8] = GJHVector(405.f, 550.f);
	m_MissionArrivalPos[9] = GJHVector(490.f, 550.f);
	m_MissionArrivalPos[10] = GJHVector(575.f, 550.f);
	m_MissionArrivalPos[11] = GJHVector(660.f, 550.f);
	m_MissionArrivalPos[12] = GJHVector(745.f, 550.f);
	m_MissionArrivalPos[13] = GJHVector(830.f, 550.f);
	m_MissionArrivalPos[14] = GJHVector(915.f, 550.f);
	m_MissionArrivalPos[15] = GJHVector(1000.f, 550.f);
}

void Mission::MissionComplete_StartMoveState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true &&
		m_MissionCount < 16)
	{
		m_MissionCount++;
	}

	int Check = 0;
	for (int i = 0; i < m_MissionCount; ++i)
	{
		Check += m_MissionCompleteActor[i]->AccelMove(m_MissionArrivalPos[i]);
	}

	if (Check == 16)
	{
		State.ChangeState("MissionComplete_Blink");
	}
}

void Mission::MissionComplete_BlinkInit()
{
	m_MissionCount = 0;
	BlinkUpdater.PushOneShotFunc(&Mission::MissionComplete_Off, this);
	BlinkUpdater.PushDelay(0.2f);
	BlinkUpdater.PushOneShotFunc(&Mission::MissionComplete_On, this);
	BlinkUpdater.PushDelay(0.4f);
	BlinkUpdater.PushOneShotFunc(&Mission::MissionComplete_Off, this);
	BlinkUpdater.PushDelay(0.2f);
	BlinkUpdater.PushOneShotFunc(&Mission::MissionComplete_On, this);
	BlinkUpdater.PushDelay(0.4f);
	BlinkUpdater.m_bLoop = false;
}

void Mission::MissionComplete_BlinkState()
{
	BlinkUpdater.Update();

	if (BlinkUpdater.GetIsEnd() == true)
	{
		State.ChangeState("MissionComplete_End");
	}
}

void Mission::MissionComplete_EndInit()
{
	Timer.SetEventTime(2.f, true);

	m_MissionArrivalAngle[0] = -155.f;
	m_MissionArrivalAngle[1] = -130.f;
	m_MissionArrivalAngle[2] = -117.f;
	m_MissionArrivalAngle[3] = -106.f;
	m_MissionArrivalAngle[4] = -60.f;
	m_MissionArrivalAngle[5] = -37.f;
	m_MissionArrivalAngle[6] = -20.f;
	m_MissionArrivalAngle[7] = 150.f;
	m_MissionArrivalAngle[8] = 133.f;
	m_MissionArrivalAngle[9] = 116.f;
	m_MissionArrivalAngle[10] = 96.f;
	m_MissionArrivalAngle[11] = 88.f;
	m_MissionArrivalAngle[12] = 70.f;
	m_MissionArrivalAngle[13] = 49.f;
	m_MissionArrivalAngle[14] = 32.f;
	m_MissionArrivalAngle[15] = 15.f;

	for (int i = 0; i < 16; ++i)
	{
		m_MissionCompleteActor[i]->SetMoveSpeed(2000.f);
	}
}

void Mission::MissionComplete_EndState()
{
	Timer.EventUpdate();
	if (Timer.CheckEventTime() == true)
	{
		State.SetPause(true);

		for (int i = 0; i < 16; ++i)
		{
			m_MissionCompleteActor[i]->Death();
		}

		m_MissionCompleteEnd = true;
		return;
	}

	for (int i = 0; i < 16; ++i)
	{
		m_MissionCompleteActor[i]->Move(m_MissionArrivalAngle[i]);
	}
}