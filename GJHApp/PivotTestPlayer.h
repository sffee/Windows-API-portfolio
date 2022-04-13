#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>
#include <GJHStateUpdater.h>
#include <map>
#include <vector>
#include <set>

class PivotTestPlayer : public GJHGameEngineActor
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
		FrameIndex TopIndex;
		FrameIndex BottomIndex;
		std::map<int, float> TopFrameTime;
		std::map<int, float> BottomFrameTime;
		std::map<int, Pivot> TopPivot;
		std::map<int, Pivot> BottomPivot;
	};

	enum class ENUM_BODYTYPE
	{
		TOP,
		BOTTOM
	};

private:
	GJHRenderer* AniRenderTop;
	GJHRenderer* AniRenderBottom;

	std::vector<std::pair<GJHString, State*>> StateVec;
	GJHString CurStateName;
	State* CurState;

	std::set<GJHString> TopBodyDrawSkip;

	ENUM_BODYTYPE ControlBody;

	bool PlayAnimation;

	void Start() override;
	void Update() override;

	void CreateAnimation(const GJHString& _Name, int _TopStart, int _TopEnd, int _BottomStart, int _BottomEnd, float _FrameTime, bool _TopLoop = true, bool _BottomLoop = true, bool _TopReverse = false, bool _BottomReverse = false, const GJHString& _FileName = "Eri_Kasamoto");
	void ChangeAnimation(const GJHString& _Name);

	void CreateState(const GJHString& _Name, int _TopStart, int _TopEnd, int _BottomStart, int _BottomEnd, float _FrameTime, bool _TopLoop = true, bool _BottomLoop = true, bool _TopReverse = false, bool _BottomReverse = false, const GJHString& _FileName = "Eri_Kasamoto");
	void ChangeState(const GJHString& _Name);
	std::vector<std::pair<GJHString, State*>>::iterator FindState(const GJHString& _Name);
	void PrevState();
	void NextState();

	void AnimationChangeChecker();
	void DirStateCheck();
	void Information();
	void KeyChecker();
	void ChangeAllPivot();
	void Save();

	void SetActorPivot(int _FrameIndex, float _XValue, float _YValue, ENUM_BODYTYPE _ControlBody = ENUM_BODYTYPE::TOP);
	void SetAllActorPivotX(float _Value, ENUM_BODYTYPE _ControlBody = ENUM_BODYTYPE::TOP);
	void SetAllActorPivotY(float _Value, ENUM_BODYTYPE _ControlBody = ENUM_BODYTYPE::TOP);
	void PushAnimationData(const GJHString& _StateName, int _FrameIndex, int _PivotX, int _PivotY, float _FrameTime, ENUM_BODYTYPE _ControlBody = ENUM_BODYTYPE::TOP);

	void AnimationSpeedUp(float _Value);
	void AnimationSpeedDown(float _Value);
	void AllAnimationSpeedUp(float _Value);
	void AllAnimationSpeedDown(float _Value);
	void SetFrameTime(int _FrameIndex, float _Value, ENUM_BODYTYPE _ControlBody = ENUM_BODYTYPE::TOP);

	void SetDefaultPivot();
	void BasicPivot();
	void HeavyMachineGunPivot();

public:
	~PivotTestPlayer();
};