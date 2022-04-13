#pragma once

#include <vector>
#include "GJHGameEngineFile.h"

class GJHGameEngineDirectory : public GJHGameEnginePath
{
public:
	std::vector<GJHGameEngineFile> AllFile(const GJHString& _FileType = "bmp", bool _IsSubDirectory = true);

private:
	void FindFileInDirectory(const GJHString& _DirPath, const GJHString& _FileType, std::vector<GJHGameEngineFile>& _FileList, bool _IsSubDirectory = true);

public:
	void MoveParent();
	void MoveParent(const GJHString& _ParentName);
	void Move(const GJHString& _ParentName);

public:
	GJHGameEngineDirectory(const GJHString& _FilePath);
	GJHGameEngineDirectory();
};

