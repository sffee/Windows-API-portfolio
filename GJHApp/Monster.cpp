#include "Monster.h"
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "InstanceObject.h"

int Monster::MonsterCount = 0;

Monster::Monster()
{
	++MonsterCount;
}

void Monster::CreateBlood(const GJHVector& _ActorPivot, int _RandomXStart, int _RandomXEnd, int _RandomYStart, int _RandomYEnd)
{
	InstanceObjectData Data;
	Data.Size = GJHVector(512, 512);
	Data.Pos = GetPos();
	Data.ImageFileName = "Blood";
	Data.ImageDir = m_ImageDir;
	Data.ReverseImageDir = true;
	Data.ActorPivot = GJHMath::RandomRange(_ActorPivot, _RandomXStart, _RandomXEnd, _RandomYStart, _RandomYEnd);
	Data.StartFrame = 0;
	Data.EndFrame = 15;
	Data.FrameTime = 0.05f;
	Data.SoundFileName = "Bleeding.mp3";
	Data.SoundFrame = 0;

	AniDataMap Map;
	float Delay = 0.05f;
	Map[0] = { PivotData(0, 0), Delay };
	Map[1] = { PivotData(5, 0), Delay };
	Map[2] = { PivotData(10, -5), Delay };
	Map[3] = { PivotData(15, 0), Delay };
	Map[4] = { PivotData(10, 0), Delay };
	Map[5] = { PivotData(10, 5), Delay };
	Map[6] = { PivotData(10, 15), Delay };
	Map[7] = { PivotData(20, 20), Delay };
	Map[8] = { PivotData(20, 15), Delay };
	Map[9] = { PivotData(20, 15), Delay };
	Map[10] = { PivotData(15, 15), Delay };
	Map[11] = { PivotData(15, 15), Delay };
	Map[12] = { PivotData(10, 20), Delay };
	Map[13] = { PivotData(10, 15), Delay };
	Map[14] = { PivotData(10, 15), Delay };
	Map[15] = { PivotData(10, 10), Delay };
	Data.AniData = Map;

	InstanceObject* NewObject = GetScene()->CreateActor<InstanceObject>();
	NewObject->SetData(Data);
}
