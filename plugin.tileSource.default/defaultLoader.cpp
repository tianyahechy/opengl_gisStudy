
#include "defaultLoader.h"
#include "../opengl_GIS/lifeiTileTask_2.h"
#include "../opengl_GIS/lifeiImageLoader.h"
#include "../opengl_GIS/IPluginTileManager.h"

namespace CELL
{
	defaultLoader::defaultLoader()
	{
	}

	defaultLoader::~defaultLoader()
	{
	}

	void defaultLoader::setParam(const char * name, const char * value)
	{
		if (_stricmp(name,"url") == 0 )
		{
			strncpy(_path, value, sizeof(_path));
		}
		else if (_stricmp(name, "ext") == 0)
		{
			strncpy(_ext, value, sizeof(_ext));
		}
		else if (_stricmp(name, "arg0") == 0)
		{
			strncpy(_arg0, value, sizeof(_arg0));
		}
		else if (_stricmp(name, "arg1") == 0)
		{
			strncpy(_arg1, value, sizeof(_arg1));
		}
		else if (_stricmp(name, "arg2") == 0)
		{
			strncpy(_arg2, value, sizeof(_arg2));
		}
	}

	lifeiTask_2 * defaultLoader::load(lifeiTask_2 * task)
	{
		lifeiTileTask_2* pTask = dynamic_cast<lifeiTileTask_2*> (task);
		int row = pTask->_tileId._row;
		int col = pTask->_tileId._col;
		int level = pTask->_tileId._lev;
		char    szURL[1024];

		int arg0 = getArg( _arg0, pTask->_tileId);
		int arg1 = getArg( _arg1, pTask->_tileId);
		int arg2 = getArg( _arg2, pTask->_tileId);
		sprintf(szURL, _path, arg0, arg1, arg2);
		
		if (isHttp(szURL))
		{
			std::vector<char> imageData;
			bool result = getImageData(szURL, imageData);
			if (!result)
			{
				return 0;
			}
			bool bLoadSuccess = lifeiImageLoader::loadImageBufferToDXT1(&imageData.front(), imageData.size(), pTask->_image);
			if (bLoadSuccess)
			{
				return task;
			}
		}
		else
		{
			bool bLoadSuccess = lifeiImageLoader::loadImageToDXT1(szURL, pTask->_image);
			if (bLoadSuccess)
			{
				return task;
			}
		}

		return nullptr;
	}

	void defaultLoader::unload(lifeiTask_2 * task)
	{
	}

	bool defaultLoader::getImageData(const char * url, std::vector<char>& arBuf)
	{
		CELLHttpClient client;
		arBuf.clear();

		if (client.get(url, arBuf) != 0)
		{
			return false;
		}

		if (arBuf.size() < 100)
		{
			return false;
		}

		char* data = &arBuf.front();
		char    jpgHeader[] = "JFIF";
		char arcgisHeader[] = "html";
		
		if (memcmp(data+6, jpgHeader, 4) != 0)
		{
			return false;
		}
		/*
		if (memcmp(data + 19, arcgisHeader, 4) != 0)
		{
			return false;
		}
		*/
		return true;
	}
	
	int defaultLoader::getArg(const char* args, const lifeiTileId& id)
	{
		if (strncmp(args, "row", 3) == 0)
		{
			if (isalnum(args[4]))
			{
				int num = 0;
				sscanf(args, "row(%d)", &num);
				return id._row + num;
			}
			else
			{
				return id._row;
			}
		}
		else if (strncmp(args, "rrow", 4) == 0)
		{
			if (isalnum(args[5]))
			{
				int num = 0;
				sscanf(args, "rrow(%d)", &num);
				int all = pow(2, id._lev);
				return all - id._row -1 + num;
			}
			else
			{
				int all = pow(2, id._lev);
				return all - id._row - 1 ;
			}
		}	
		else if (strncmp(args, "col", 3) == 0)
		{
			if (isalnum(args[4]))
			{
				int num = 0;
				sscanf(args, "col(%d)", &num);
				return id._col + num;
			}
			else
			{
				return id._col;
			}
		}
		else if (strncmp(args, "rcol", 4) == 0)
		{
			if (isalnum(args[5]))
			{
				int num = 0;
				sscanf(args, "rcol(%d)", &num);
				int all = pow(2, id._lev);
				return all - id._col - 1 + num;
			}
			else
			{
				int all = pow(2, id._lev);
				return all - id._col - 1;
			}
		}
		else if (strncmp(args, "lev", 3) == 0)
		{
			if (isalnum(args[4]))
			{
				int num = 0;
				sscanf(args, "lev(%d)", &num);
				return id._lev + 1;
			}
			else
			{
				return id._lev;
			}
		}

		 return 0;
	}
	
	extern "C" EXPORTFUNC IPluginTileManager * createTileSourceDLL(IGISPlatform* platform)
	{
		return new defaultLoader();
	}

}
