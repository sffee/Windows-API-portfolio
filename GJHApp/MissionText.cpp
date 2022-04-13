#include "MissionText.h"
#include <GJHRenderer.h>

void MissionText::Start()
{
	m_MoveSpeed = 800.f;
	m_ImageDir = ENUM_DIRECTION::RIGHT;

	m_IsGravity = false;
}

void MissionText::Update()
{

}

void MissionText::SetText(const GJHString& _Text)
{
	int Ascii;
	if (_Text == "!")
	{
		Ascii = 26;
	}
	else
	{
		Ascii = (int)_Text.Str[0] - (int)'A';
	}

	m_AniRender = CreateRender({ 128, 128 }, "MissionText.bmp", ContentsEnum::RENDERORDER::UI);
	m_AniRender->CreateAnimation("Text", "MissionText.bmp", Ascii, Ascii, 1.f);
	m_AniRender->ChangeAnimation("Text");
	m_AniRender->SetMapCheck(false);
	m_AniRender->CameraEffectOff();
}

int MissionText::AccelMove(const GJHVector& _TargetPos)
{
	GJHVector Pos = GetPos();
	GJHVector Distance = Pos - _TargetPos;

	if (abs(Distance.x) <= 1.f &&
		abs(Distance.y) <= 1.f)
	{
		return 1;
	}

	float MoveRatioX = min(abs(Distance.x) / 200.f, 1.f);
	float MoveRatioY = min(abs(Distance.y) / 200.f, 1.f);
	m_Angle = abs(GJHMath::VecToVecAngle(_TargetPos, Pos));
	if (90.f <= m_Angle)
	{
		m_Angle = abs(m_Angle - 180.f);
	}

	__super::Move(GJHVector(m_MoveSpeed * MoveRatioX,
		m_MoveSpeed * MoveRatioY) *
		GJHGameEngineTime::FDeltaTime());

	return 0;
}

void MissionText::Move(float _Angle)
{
	m_Angle = _Angle;

	__super::Move(m_MoveSpeed * GJHGameEngineTime::FDeltaTime());
}