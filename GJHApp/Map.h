#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineTime.h>

class Map : public GJHGameEngineActor
{
public:
	GJHRenderer* AniRender;
	GJHRenderer* MapPixelRender;

private:
	bool DrawMapPixel;

private:
	void Start() override;
	void Update() override;

public:
	void TogglePixelRender();

public:
	Map() :
		AniRender(nullptr),
		MapPixelRender(nullptr),
		DrawMapPixel(false)
	{
	}
};