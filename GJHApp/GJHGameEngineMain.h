#pragma once
#include <GJHGameEngineWindow.h>

class GJHGameEngineMain : public GJHWindowDeadTimeInstance
{
public:
	static GJHGameEngineMain Inst;

private:
	void SceneCreate();
	void ResourcesLoading();
	void CutImage(GJHString _ImageName, GJHVector _ImageSize, bool _Reverse = false);

private:
	GJHGameEngineMain();

public:
	void InitProcess() override;
	void DeadTimeProcess() override;
};

