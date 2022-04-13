#include "GJHGameEngineFile.h"
#include "GJHGameEngineDirectory.h"

GJHGameEngineDirectory GJHGameEngineFile::Directory() const
{
	GJHString DirectoryPath = m_PathStr.Cut(0, m_PathStr.LastFind('\\') + 1);
	return GJHGameEngineDirectory(DirectoryPath);
}

GJHString GJHGameEngineFile::Extension() const
{
	GJHString Extension = m_PathStr.Cut(m_PathStr.LastFind('.') + 1, m_PathStr.Size() - m_PathStr.LastFind('.'));

	return Extension;
}

GJHGameEngineFile::GJHGameEngineFile(const GJHString& _Path) :
	GJHGameEnginePath(_Path)
{
}

GJHGameEngineFile::~GJHGameEngineFile()
{

}