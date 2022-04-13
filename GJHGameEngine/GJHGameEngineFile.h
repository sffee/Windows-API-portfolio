#pragma once
#include "GJHGameEnginePath.h"

class GJHGameEngineDirectory;
class GJHGameEngineFile : public GJHGameEnginePath
{
public:
	GJHGameEngineDirectory Directory() const;

public:
	GJHString Extension() const;
	
public:
	GJHGameEngineFile(const GJHString& _Path);
	~GJHGameEngineFile();
};

