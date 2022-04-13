#pragma once
#include "ObjectBase.h"
#include "define.h"

class FadeInOut : public ObjectBase
{
private:
	float m_Alpha;
	float m_AlphaAddValue;
	bool m_IsFadeIn;
	bool m_IsFadeOut;
	bool m_IsOver;

private:
	void Start() override;
	void Update() override;

public:
	bool IsOver()
	{
		return m_IsOver;
	}

public:
	void FadeIn(float _Time);
	void FadeOut(float _Time);
};