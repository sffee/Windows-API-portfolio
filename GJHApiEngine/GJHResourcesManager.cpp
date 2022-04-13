#include "GJHResourcesManager.h"

GJHResourcesManager* GJHResourcesManager::pInst = new GJHResourcesManager();

void GJHResourcesManager::LoadBmp(const GJHGameEngineFile& _File)
{
	if (_File.Extension().Lower() != "bmp")
	{
		AssertMsg("if (_File.Exp().Lower() != \"bmp\")");
	}

	GJHGameEngineImage* NewImage = new GJHGameEngineImage();

	NewImage->Load(_File.FullPath());

	m_AllImage.insert(std::map<GJHString, GJHGameEngineImage*>::value_type(_File.FileName(), NewImage));
}

GJHGameEngineImage* GJHResourcesManager::FindBmp(const GJHString& _FileName)
{
	std::map<GJHString, GJHGameEngineImage*>::iterator FindIter = m_AllImage.find(_FileName);

	if (FindIter == m_AllImage.end())
	{
		AssertMsg("if (FindIter == m_AllImage.end())");
	}

	return FindIter->second;
}

void GJHResourcesManager::CutBmp(const GJHString& _FileName, const GJHVector& _Size, bool _XReverse)
{
	GJHGameEngineImage* FindImage = FindBmp(_FileName);

	if (FindImage == nullptr)
	{
		AssertMsg("if (FindImage == nullptr)");
	}

	FindImage->Cutting(_Size, _XReverse);
}

GJHResourcesManager::GJHResourcesManager()
{

}

GJHResourcesManager::~GJHResourcesManager()
{
	std::map<GJHString, GJHGameEngineImage*>::iterator Start = m_AllImage.begin();
	std::map<GJHString, GJHGameEngineImage*>::iterator End = m_AllImage.end();

	for (; Start != End; ++Start)
	{
		if (Start->second != nullptr)
		{
			delete Start->second;
			Start->second = nullptr;
		}
	}
}