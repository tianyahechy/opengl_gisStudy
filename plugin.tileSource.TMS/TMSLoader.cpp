
#include "TMSLoader.h"
#include "../opengl_GIS/lifeiTileTask.h"
#include "../opengl_GIS/lifeiImageLoader.h"

namespace CELL
{
	TMSLoader::TMSLoader()
	{
	}

	TMSLoader::~TMSLoader()
	{
	}

	void TMSLoader::setParam(const char * name, const char * value)
	{
		if (_stricmp(name,"url") == 0 )
		{
			strncpy(_path, value, sizeof(_path));
		}
		else if (_stricmp(name, "ext") == 0)
		{
			strncpy(_ext, value, sizeof(_ext));
		}
	}

	lifeiTask * TMSLoader::load(lifeiTask * task)
	{
		lifeiTileTask* pTask = dynamic_cast<lifeiTileTask*> (task);
		char    szPathName[1024];
		sprintf(szPathName, "%s/%d/%d/%d%s", _path, pTask->_tileId._lev, pTask->_tileId._col, pTask->_tileId._row, _ext);
		bool bLoadSuccess = lifeiImageLoader::loadImageToDXT1(szPathName, pTask->_image);
		if (bLoadSuccess)
		{
			return task;
		}
		return nullptr;
	}

	void TMSLoader::unload(lifeiTask * task)
	{
	}

	extern "C" EXPORTFUNC IPluginTileSource * createTileSourceDLL(IGIS3DPlatform* platform)
	{
		return new TMSLoader();
	}

}
