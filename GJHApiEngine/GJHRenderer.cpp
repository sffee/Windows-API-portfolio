#include "GJHRenderer.h"
#include <Windows.h>
#include "GJHGameEngineWindow.h"
#include "GJHGameEngineActor.h"
#include "GJHResourcesManager.h"
#include <GJHGameEngineTime.h>
#include "GJHGameEngineScene.h"
#include <GJHCameraManager.h>

void GJHRenderer::Render()
{
	if (m_pCurAnimation != nullptr && isDraw == false)
	{
		m_pCurAnimation->AnimationEnd = true;
		return;
	}

	m_Geo.Pos = m_Actor->GetPos();
	m_Geo.Pos = m_Geo.Pos + GJHVector(m_ActorPivot.x * (int)m_Actor->GetImageDir(), m_ActorPivot.y)
						  + GJHVector(m_AddActorPivot.x * (int)m_Actor->GetImageDir(), m_AddActorPivot.y);

	if (m_pCurAnimation == nullptr || m_pCurAnimation->MapCheck == true)
	{
		if (m_Geo.Pos.x < MAPSTARTX)
			m_Geo.Pos.x = MAPSTARTX;

		if (MAPENDX < m_Geo.Pos.x)
			m_Geo.Pos.x = MAPENDX;

		if (m_Geo.Pos.y < MAPSTARTY)
			m_Geo.Pos.y = MAPSTARTY;
	}

	if (m_IsCameraEffect == true)
		m_Geo.Pos -= GJHVector(GJHCameraManager::GetCamPos().x * m_CamEffectRatioX, GJHCameraManager::GetCamPos().y * m_CamEffectRatioY);

	if (m_pCurAnimation == nullptr)
	{
		if (m_Image != nullptr && isDraw == true)
		{
			if (m_Alpha != 255)
			{
				GJHGameEngineWindow::MainWindow()->GetBackBuffer().AlphaCopy(*m_Image,
					m_Geo.LeftUp(), m_Geo.Size, m_ImageRect.Pos, m_ImageRect.Size, m_Alpha);
			}
			else
			{
				GJHGameEngineWindow::MainWindow()->GetBackBuffer().TransCopy(*m_Image,
					m_Geo.LeftUp(), m_Geo.Size, m_ImageRect.Pos, m_ImageRect.Size, m_TransColor);
			}
		}
	}
	else
	{
		m_ImageRect = m_pCurAnimation->m_Image->GetCutData(m_pCurAnimation->CurFrameIndex);

		m_pCurAnimation->CurFrameTime += GJHGameEngineTime::FDeltaTime();

		if (m_Image != nullptr && isDraw == true)
		{
			if (m_Alpha != 255)
			{
				GJHGameEngineWindow::MainWindow()->GetBackBuffer().AlphaCopy(*m_pCurAnimation->m_Image,
					m_Geo.LeftUp(), m_Geo.Size, m_ImageRect.Pos, m_ImageRect.Size, m_Alpha);
			}
			else
			{
				GJHGameEngineWindow::MainWindow()->GetBackBuffer().TransCopy(*m_pCurAnimation->m_Image,
					m_Geo.LeftUp(), m_Geo.Size, m_ImageRect.Pos, m_ImageRect.Size, m_TransColor);
			}
		}

	}

	if (IsDebug() == true)
	{
		Rectangle(GJHGameEngineWindow::MainWindow()->GetBackBuffer(),
			m_Geo.LeftUp().ix(),
			m_Geo.LeftUp().iy(),
			m_Geo.RightDown().ix(),
			m_Geo.RightDown().iy());
	}
}

void GJHRenderer::CalcRender()
{
	if (m_pCurAnimation == nullptr)
	{
		return;
	}

	if (m_pCurAnimation->isPlay == true)
	{
		std::map<int, float>::iterator FindFrameTime = m_pCurAnimation->FrameTime.find(m_pCurAnimation->CurFrameIndex);
		if (FindFrameTime == m_pCurAnimation->FrameTime.end())
			return;

		if (FindFrameTime->second < m_pCurAnimation->CurFrameTime)
		{
			m_pCurAnimation->CurFrameIndex += (int)m_pCurAnimation->ReverseState;
			m_pCurAnimation->CurFrameTime = 0.0f;

			if (m_pCurAnimation->ReverseState == GJHAnimation::REVERSE_STATE::FRONT)
			{
				if (m_pCurAnimation->End < m_pCurAnimation->CurFrameIndex)
				{
					if (m_pCurAnimation->isReverse == true)
					{
						m_pCurAnimation->ReverseState = GJHAnimation::REVERSE_STATE::BACK;
						m_pCurAnimation->CurFrameIndex = m_pCurAnimation->End - 1;
					}
					else
					{
						if (m_pCurAnimation->m_bLoop == true)
						{
							m_pCurAnimation->CurFrameIndex = m_pCurAnimation->Start;
						}
						else
						{
							m_pCurAnimation->AnimationEnd = true;
							--m_pCurAnimation->CurFrameIndex;
						}
					}
				}
			}
			else
			{
				if (m_pCurAnimation->CurFrameIndex < m_pCurAnimation->Start)
				{
					if (m_pCurAnimation->m_bLoop == true)
					{
						m_pCurAnimation->ReverseState = GJHAnimation::REVERSE_STATE::FRONT;
						m_pCurAnimation->CurFrameIndex = m_pCurAnimation->Start + 1;
					}
					else
					{
						m_pCurAnimation->AnimationEnd = true;
						++m_pCurAnimation->CurFrameIndex;
					}
				}
			}
		}

		if (m_pCurAnimation->Start == m_pCurAnimation->End)
		{
			m_pCurAnimation->CurFrameIndex = m_pCurAnimation->Start;
		}
	}
}

void GJHRenderer::SetAnimationFrameIndex(int _Index)
{
	if (_Index < m_pCurAnimation->Start)
	{
		return;
	}

	if (m_pCurAnimation->End < _Index)
	{
		return;
	}

	m_pCurAnimation->CurFrameIndex = _Index;
	m_pCurAnimation->AnimationEnd = false;
}

int GJHRenderer::GetAnimationFrameIndex()
{
	return m_pCurAnimation->CurFrameIndex;
}

void GJHRenderer::SetFrameTime(float _Value)
{
	if (_Value <= 0)
	{
		AssertMsg("if (_Value <= 0)");
	}

	std::map<int, float>::iterator iter = m_pCurAnimation->FrameTime.begin();
	std::map<int, float>::iterator iterEnd = m_pCurAnimation->FrameTime.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second = _Value;
	}
}

void GJHRenderer::SetFrameTime(int _Index, float _Value)
{
	if (_Value <= 0)
	{
		AssertMsg("if (_Value <= 0)");
	}

	if (_Index < m_pCurAnimation->Start)
	{
		AssertMsg("if (_Index < m_pCurAnimation->Start)");
	}

	if (m_pCurAnimation->End < _Index)
	{
		AssertMsg("if (m_pCurAnimation->End < _Index)");
	}

	std::map<int, float>::iterator iter = m_pCurAnimation->FrameTime.find(_Index);

	if (iter == m_pCurAnimation->FrameTime.end())
	{
		AssertMsg("if (iter == m_pCurAnimation->FrameTime.end())");
	}

	iter->second = _Value;
}

float GJHRenderer::GetFrameTime(int _FrameIndex)
{
	std::map<int, float>::iterator iter = m_pCurAnimation->FrameTime.find(_FrameIndex);
	if (iter == m_pCurAnimation->FrameTime.end())
	{
		AssertMsg("if (iter == m_pCurAnimation->FrameTime.end())");
	}

	return iter->second;
}


void GJHRenderer::SetImage(const GJHString& _ImageName)
{
	m_Image = GJHResourcesManager::Inst()->FindBmp(_ImageName);

	SetImage(m_Image);
}

void GJHRenderer::SetImage(const GJHGameEngineImage* _ImageName)
{
	if (m_Image == nullptr)
	{
		AssertMsg("if (m_Image == nullptr)");
	}

	m_ImageRect.Size = m_Image->Size();
	m_ImageRect.Pos = GJHVector::ZERO;
}

void GJHRenderer::SetImageIndex(unsigned int _Index)
{
	if (m_Image == nullptr)
	{
		AssertMsg("if (m_Image == nullptr)");
	}

	if (m_Image->IsCut() == false)
	{
		AssertMsg("if (m_Image->IsCut() == false)");
	}

	m_ImageRect = m_Image->GetCutData(_Index);
}

void GJHRenderer::CreateAnimation(
	const GJHString& _AniName,
	const GJHString& _ImageName,
	int _Start, int _End,
	float _FrameTime,
	bool _Loop,
	bool _Reverse)
{
	std::map<GJHString, GJHAnimation>::iterator FindAni = m_AnimationMap.find(_AniName);
	if (FindAni != m_AnimationMap.end())
	{
		AssertMsg("if (FindAni != m_AnimationMap.end())");
	}

	GJHGameEngineImage* Image = GJHResourcesManager::Inst()->FindBmp(_ImageName);
	if (Image == nullptr)
	{
		AssertMsg("if (Image == nullptr)");
	}

	if (Image->IsCut() == false)
	{
		AssertMsg("if (Image->IsCut() == false)");
	}

	if (Image->CutSize() < _End)
	{
		AssertMsg("if (Image->CutSize() < _End)");
	}

	if (_End < _Start)
	{
		AssertMsg("if (_End < _Start)");
	}

	GJHAnimation NewAnimation;
	NewAnimation.Name = _AniName.Cut(0, _AniName.LastFind('_'));
	NewAnimation.m_Image = Image;
	NewAnimation.m_bLoop = _Loop;
	NewAnimation.Start = _Start;
	NewAnimation.End = _End;
	NewAnimation.AnimationEnd = false;
	NewAnimation.isReverse = _Reverse;
	NewAnimation.ReverseState = GJHAnimation::REVERSE_STATE::FRONT;
	NewAnimation.isPlay = true;

	for (int i = _Start; i < _End + 1; ++i)
	{
		NewAnimation.FrameTime[i] = _FrameTime;
	}

	m_AnimationMap.insert(std::map<GJHString, GJHAnimation>::value_type(_AniName, NewAnimation));
}

void GJHRenderer::ChangeAnimation(const GJHString& _AniName, bool _Correction, const GJHVector& _Size)
{
	std::map<GJHString, GJHAnimation>::iterator FindAni = m_AnimationMap.find(_AniName);

	if (FindAni == m_AnimationMap.end())
	{
		AssertMsg("if (FindAni == m_AnimationMap.end())");
	}

	if (_Size != GJHVector::ZERO)
	{
		SetSize(_Size);
	}

	if (_Correction == false)
	{
		m_pCurAnimation = &FindAni->second;
		m_pCurAnimation->Reset();
	}
	else
	{
		GJHAnimation PrevAnimation = *m_pCurAnimation;
		m_pCurAnimation = &FindAni->second;

		m_pCurAnimation->SetData(PrevAnimation);
	}
}

bool GJHRenderer::AnimationEnd()
{
	return m_pCurAnimation->AnimationEnd;
}

void GJHRenderer::SetDraw(bool _Draw)
{
	isDraw = _Draw;
}

GJHRenderer::GJHRenderer() :
	m_Image(nullptr),
	m_TransColor(RGB(255, 0, 255)),
	m_pCurAnimation(nullptr),
	isDraw(true),
	m_Alpha(255)
{

}

GJHRenderer::~GJHRenderer()
{

}