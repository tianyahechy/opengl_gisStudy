
#include "httpGoogleLoader.h"
#include "../opengl_GIS/lifeiTileTask.h"
#include "../opengl_GIS/lifeiImageLoader.h"

namespace CELL
{
	httpGoogleLoader::httpGoogleLoader()
	{
	}

	httpGoogleLoader::~httpGoogleLoader()
	{
	}

	void httpGoogleLoader::setParam(const char * name, const char * value)
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

	lifeiTask * httpGoogleLoader::load(lifeiTask * task)
	{
		lifeiTileTask* pTask = dynamic_cast<lifeiTileTask*> (task);
		int row = pTask->_tileId._row;
		int col = pTask->_tileId._col;
		int level = pTask->_tileId._lev;
		char    szURL[1024];
		sprintf(szURL, "http://mt2.google.cn/vt?n=404&lyrs=s&hl=zh-CN&gl=cn&v=191&x=%d&y=%d&z=%d", col, row, pTask->_tileId._lev);
		//sprintf(szURL, "http://map.geoq.cn/arcgis/rest/services/ChinaOnlineStreetPurplishBlue/MapServer", col, row, pTask->_tileId._lev);
	
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
		return nullptr;
	}

	void httpGoogleLoader::unload(lifeiTask * task)
	{
	}

	bool httpGoogleLoader::getImageData(const char * url, std::vector<char>& arBuf)
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

	extern "C" EXPORTFUNC IPluginTileSource * createTileSourceDLL(IGIS3DPlatform* platform)
	{
		return new httpGoogleLoader();
	}

}
