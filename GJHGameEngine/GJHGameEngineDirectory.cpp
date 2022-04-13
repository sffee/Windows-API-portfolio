#include "GJHGameEngineDirectory.h"
#include "GJHGameEngineFile.h"

std::vector<GJHGameEngineFile> GJHGameEngineDirectory::AllFile(const GJHString& _FileType, bool _IsSubDirectory)
{
	if (Type() != PATHTYPE::DIR)
	{
		AssertMsg("if (Type() != PATHTYPE::DIR)");
		return std::vector<GJHGameEngineFile>();
	}

	std::vector<GJHGameEngineFile> FileList;

	FindFileInDirectory(m_PathStr, _FileType.Lower(), FileList, _IsSubDirectory);
	
	return FileList;
}

void GJHGameEngineDirectory::FindFileInDirectory(const GJHString& _DirPath, const GJHString& _FileType, std::vector<GJHGameEngineFile>& _FileList, bool _IsSubDirectory)
{
	WIN32_FIND_DATAA fd;
	HANDLE hFind = FindFirstFileA(_DirPath + "*.*", &fd);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		AssertMsg("hFind == INVALID_HANDLE_VALUE");
	}

	do
	{
		if (StrCmpA(fd.cFileName, ".") == 0
			|| StrCmpA(fd.cFileName, "..") == 0)
		{
			continue;
		}

		if (_IsSubDirectory == true && fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			FindFileInDirectory(_DirPath + fd.cFileName + "\\", _FileType, _FileList, _IsSubDirectory);
		}

		GJHGameEngineFile File = GJHGameEngineFile(_DirPath + fd.cFileName);
		if (File.Extension().Lower() == _FileType && fd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{
			_FileList.push_back(File);
		}

	} while (FindNextFileA(hFind, &fd));

	FindClose(hFind);
}

GJHGameEngineDirectory::GJHGameEngineDirectory(const GJHString& _FilePath) :
	GJHGameEnginePath(_FilePath)
{

}

GJHGameEngineDirectory::GJHGameEngineDirectory() :
	GJHGameEnginePath("")
{
	char Path[256];
	GetCurrentDirectoryA(sizeof(Path), Path);

	m_PathStr = Path;
	m_PathStr += "\\";
}

void GJHGameEngineDirectory::MoveParent()
{
	if (Type() != PATHTYPE::DIR)
	{
		AssertMsg("Type() != PATHTYPE::DIR");
	}

	size_t Test = m_PathStr.Size();

	size_t LastCharPos = m_PathStr.LastFind('\\', m_PathStr.Size() - 2);

	if (LastCharPos == GJHString::FINDERROR)
	{
		AssertMsg("LastChar == GJHString::FINDERROR");
	}

	m_PathStr = m_PathStr.Cut(0, LastCharPos + 1);
}

void GJHGameEngineDirectory::MoveParent(const GJHString& _ParentName)
{
	while (_ParentName != DirectoryName())
	{
		MoveParent();
	}
}

void GJHGameEngineDirectory::Move(const GJHString& _ParentName)
{
	if (Type() != PATHTYPE::DIR)
	{
		AssertMsg("Type() != PATHTYPE::DIR");
	}

	if (IsExist(m_PathStr + _ParentName + "\\") == false)
	{
		AssertMsg("IsExsit(m_PathStr + _ParentName + \"\\\") == false");
	}

	m_PathStr += _ParentName + "\\";
}