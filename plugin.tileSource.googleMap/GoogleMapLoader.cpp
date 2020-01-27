
#include "GoogleMapLoader.h"
#include "../opengl_GIS/lifeiTileTask.h"
#include "../opengl_GIS/lifeiImageLoader.h"
#include "../opengl_GIS/IPluginTileManager.h"

namespace CELL
{
	GoogleMapLoader::GoogleMapLoader()
	{
	}

	GoogleMapLoader::~GoogleMapLoader()
	{
	}

	void GoogleMapLoader::setParam(const char * name, const char * value)
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

	lifeiTask * GoogleMapLoader::load(lifeiTask * task)
	{
		lifeiTileTask* pTask = dynamic_cast<lifeiTileTask*> (task);
		char    szPathName[1024];
		sprintf(szPathName, "%s/L%02d/%06d-%06d%s", _path, pTask->_tileId._lev + 1, pTask->_tileId._row, pTask->_tileId._col, _ext);
		bool bLoadSuccess = lifeiImageLoader::loadImageToDXT1(szPathName, pTask->_image);
		if (bLoadSuccess)
		{
			return task;
		}
		return nullptr;
	}

	void GoogleMapLoader::unload(lifeiTask * task)
	{
	}

	extern "C" EXPORTFUNC IPluginTileManager * createTileSourceDLL(ILifeiGISPlatform* platform)
	{
		return new GoogleMapLoader();
	}

}
