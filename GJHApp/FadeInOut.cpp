#include <GJHRenderer.h>
#include <GJHCollision.h>
#include <GJHGameEngineSound.h>
#include <GJHGameEngineScene.h>
#include "FadeInOut.h"

void FadeInOut::Start()
{
	m_AniRender = CreateRender({ 1280, 960 }, "BlackScreen.bmp", 100000);
	m_AniRender->SetAlpha(0);
	m_AniRender->CameraEffectOff();

	m_IsFadeIn = false;
	m_IsFadeOut = false;
	m_IsOver = false;
}

void FadeInOut::Update()
{
	if (m_IsFadeIn == true)
	{
		m_Alpha += m_AlphaAddValue;
		if (255 <= m_Alpha)
		{
			m_IsOver = true;
			m_Alpha = 255;
		}

		m_AniRender->SetAlpha((int)m_Alpha);
	}
	else if (m_IsFadeOut == true)
	{
		m_Alpha -= m_AlphaAddValue;
		if (m_Alpha <= 0)
		{
			m_IsOver = true;
			m_Alpha = 0;
		}

		m_AniRender->SetAlpha((int)m_Alpha);
	}
}

void FadeInOut::FadeIn(float _Time)
{
	m_Alpha = 0;
	m_AniRender->SetAlpha((int)m_Alpha);
	m_AlphaAddValue = GJHGameEngineTime::FDeltaTime(2.f) / _Time * 255.f;
	m_IsFadeIn = true;
}

void FadeInOut::FadeOut(float _Time)
{
	m_Alpha = 255;
	m_AniRender->SetAlpha((int)m_Alpha);
	m_AlphaAddValue = GJHGameEngineTime::FDeltaTime(2.f) / _Time * 255.f;
	m_IsFadeOut = true;
}