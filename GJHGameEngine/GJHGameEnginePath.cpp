#include "GJHGameEnginePath.h"
#include <io.h>

bool GJHGameEnginePath::IsExist(const GJHGameEnginePath& _Path)
{
	if (_access(_Path.m_PathStr, 0))
	{
		return false;
	}

	return true;
}