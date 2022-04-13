#pragma once
#include <GJHGameEngineFile.h>
#include "GJHGameEngineImage.h"
#include <map>

class GJHResourcesManager
{
private:
	static GJHResourcesManager* pInst;

public:
	static GJHResourcesManager* Inst()
	{
		return pInst;
	}

	static void Destroy()
	{
		if (pInst != nullptr)
		{
			delete pInst;
			pInst = nullptr;
		}
	}

private:
	std::map<GJHString, GJHGameEngineImage*> m_AllImage;

public:
	void LoadBmp(const GJHGameEngineFile& _File);
	GJHGameEngineImage* FindBmp(const GJHString& _FileName);

	void CutBmp(const GJHString& _FileName, const GJHVector& _Size, bool _XReverse = false);

private:
	GJHResourcesManager();

public:
	~GJHResourcesManager();
};

