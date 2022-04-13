#pragma once
#include <GJHGameEngineActor.h>

class TitleBackGround : public GJHGameEngineActor
{
private:
	GJHRenderer* PressStartRender;
	GJHTimeUpdater<TitleBackGround> PressStartUpdate;

private:
	void Start() override;
	void Update() override;

private:
	void PressStartOn();
	void PressStartOff();

public:
	TitleBackGround() :
		PressStartRender(nullptr)
	{
	}
};