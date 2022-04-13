#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include <map>
#include <vector>
#include <set>

class PivotTestMonster : public GJHGameEngineActor
{
	struct FrameIndex
	{
		int Start;
		int End;
		int Cur;

		FrameIndex()
			: Start(0), End(0), Cur(0)
		{

		}
	};

	struct Pivot
	{
		float X;
		float Y;

		Pivot() :
			X(0), Y(0)
		{
		}
	};

	struct State
	{
		FrameIndex FrameIndex;
		std::map<int, float> FrameTime;
		std::map<int, Pivot> Pivot;
	};

private:
	GJHRenderer* AniRender;

	std::vector<std::pair<GJHString, State*>> StateVec;
	std::map<GJHString, GJHVector> StateImageSizeMap;
	GJHString CurStateName;
	State* CurState;
	GJHVector DefaultImageSize;

	GJHString MonsterName;

	bool PlayAnimation;

	void Start() override;
	void Update() override;

	void CreateAnimation(const GJHString& _StateName, const GJHString& _FileName, int _FrameStart, int _FrameEnd, float _FrameTime, bool _Loop = true, bool _Reverse = false);
	void ChangeAnimation(const GJHString& _StateName);

	void CreateState(const GJHString& _StateName, const GJHString& _FileName, int _FrameStart, int _FrameEnd, float _FrameTime, bool _Loop = true, bool _Reverse = false, GJHVector _Size = GJHVector::ZERO);
	void ChangeState(const GJHString& _StateName);
	std::vector<std::pair<GJHString, State*>>::iterator FindState(const GJHString& _StateName);
	void PrevState();
	void NextState();

	void AnimationChangeChecker();
	void DirStateCheck();
	void Information();
	void KeyChecker();
	void ChangeAllPivot();
	void Save();

	void SetActorPivot(int _FrameIndex, float _XValue, float _YValue);
	void SetAllActorPivotX(float _Value);
	void SetAllActorPivotY(float _Value);
	void PushAnimationData(const GJHString& _StateName, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime);

	void AnimationSpeedUp(float _Value);
	void AnimationSpeedDown(float _Value);
	void AllAnimationSpeedUp(float _Value);
	void AllAnimationSpeedDown(float _Value);
	void SetFrameTime(int _FrameIndex, float _Value);

	void SetDefaultPivot();
	void ZombieManPivot();
	void ZombieGirlPivot();
	void ZombieDoctorPivot();
	void MordenMinigunPivot();
	void ExplosionPivot();
	void HelicopterPivot();
	void BomberPivot();
	void GranadeExplosionPivot();
	void MonoeyeUFOPivot();
	void ZombieMordenPivot();
	void ItemPivot();

public:
	~PivotTestMonster();
};