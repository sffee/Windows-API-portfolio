#pragma once
#include <GJHGameEngineActor.h>
#include <GJHGameEngineImage.h>

class TitlePressStart : public GJHGameEngineActor
{
private:
	GJHGeometryInfo2D m_Geo;
	GJHVector ImagePivot;
	GJHVector ImageSize;
	GJHGameEngineImage* Image;
	unsigned int TransColor;

private:
	int Time;
	bool isDraw;

private:
	void Start() override;
	void Update() override;
	void Render() override;
};