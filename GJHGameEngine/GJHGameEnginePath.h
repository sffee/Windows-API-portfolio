#pragma once
#include "GJHString.h"
#include "GJHGameEngineDebug.h"

enum class PATHTYPE
{
	FILE,
	DIR,
	NONE,
};

class GJHGameEnginePath
{
public:
	GJHString m_PathStr;

public:
	static bool IsExist(const GJHGameEnginePath& _Path);

	GJHString FullPath() const
	{
		return m_PathStr;
	}

public:
	PATHTYPE Type() const
	{
		if (m_PathStr.Size() == 0)
		{
			return PATHTYPE::NONE;
		}

		if (m_PathStr[m_PathStr.Size() - 1] == '\\')
		{
			return PATHTYPE::DIR;
		}

		return PATHTYPE::FILE;
	}

public:
	GJHString DirectoryName() const
	{
		if (Type() != PATHTYPE::DIR)
		{
			AssertMsg("Type() != PATHTYPE::DIR");
		}

		size_t LastCharPos = m_PathStr.LastFind('\\', m_PathStr.Size() - 2);

		if (LastCharPos == GJHString::FINDERROR)
		{
			AssertMsg("if (LastCharPos == GJHString::FINDERROR");
		}

		GJHString DirName = m_PathStr.Cut(LastCharPos + 1, m_PathStr.Size() - LastCharPos - 2);
		
		return DirName;
	}

	GJHString FileName() const
	{
		if (Type() != PATHTYPE::FILE)
		{
			AssertMsg("if (Type() != PATHTYPE::FILE)");
		}

		size_t LastCharPos = m_PathStr.LastFind('\\');

		if (LastCharPos == GJHString::FINDERROR)
		{
			AssertMsg("if (LastCharPos == GJHString::FINDERROR)");
		}

		GJHString FileName = m_PathStr.Cut(LastCharPos + 1, m_PathStr.Size() - LastCharPos);
		
		return FileName;
	}

public:
	GJHGameEnginePath(const GJHString& _Path) :
		m_PathStr(_Path)
	{

	}
	~GJHGameEnginePath()
	{

	}
};