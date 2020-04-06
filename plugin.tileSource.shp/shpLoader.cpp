
#include "shpLoader.h"
#include "../opengl_GIS/lifeiTileTask_2.h"
#include "../opengl_GIS/lifeiImageLoader.h"
#include "../opengl_GIS/IPluginTileManager.h"
#include "../opengl_GIS/IGISPlatform.h"
#include "../opengl_GIS/lifeiShpLayer.h"
#include "../opengl_GIS/IFeaturePoint.h"
#include "../opengl_GIS/IFeatureLine.h"

namespace CELL
{
	shpLoader::shpLoader(IGISPlatform* app)
	{
		_app = app;
		_layer = 0;
		HWND hWnd = GetDesktopWindow();
		HDC hDesk = GetDC(hWnd);
		_hMemDC = CreateCompatibleDC(hDesk);

		BITMAPINFO bmpInfor;
		bmpInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfor.bmiHeader.biWidth = 256;
		bmpInfor.bmiHeader.biHeight = -256;
		bmpInfor.bmiHeader.biPlanes = 1;
		bmpInfor.bmiHeader.biBitCount = 32;
		bmpInfor.bmiHeader.biCompression = BI_RGB;
		bmpInfor.bmiHeader.biSizeImage = 0;
		bmpInfor.bmiHeader.biXPelsPerMeter = 0;
		bmpInfor.bmiHeader.biYPelsPerMeter = 0;
		bmpInfor.bmiHeader.biClrUsed = 0;
		bmpInfor.bmiHeader.biClrImportant = 0;
		_hBitMap = CreateDIBSection(_hMemDC, &bmpInfor, DIB_RGB_COLORS, &_pRGBA, 0, 0);
		SelectObject(_hMemDC, _hBitMap);
	}

	shpLoader::~shpLoader()
	{
		DeleteObject(_hBitMap);
		DeleteDC(_hMemDC);
	}

	void shpLoader::setParam(const char * name, const char * value)
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
			size_t nLen = strlen(value);
			size_t nCopy = sizeof(_arg0) > nLen ? nLen : sizeof(_arg0);
			for (size_t i = 0, j = 0; i < nLen; i++)
			{
				if (value[i] == ' ')
				{
					continue;
				}
				_arg0[j] = value[i];
				++j;
			}
		}
		else if (_stricmp(name, "arg1") == 0)
		{
			size_t nLen = strlen(value);
			size_t nCopy = sizeof(_arg1) > nLen ? nLen : sizeof(_arg1);
			for (size_t i = 0, j = 0; i < nLen; i++)
			{
				if (value[i] == ' ')
				{
					continue;
				}
				_arg1[j] = value[i];
				++j;
			}
		}
		else if (_stricmp(name, "arg2") == 0)
		{
			size_t nLen = strlen(value);
			size_t nCopy = sizeof(_arg2) > nLen ? nLen : sizeof(_arg2);
			for (size_t i = 0, j = 0; i < nLen; i++)
			{
				if (value[i] == ' ')
				{
					continue;
				}
				_arg2[j] = value[i];
				++j;
			}
		}
		else if (_stricmp(name, "dataSource") == 0)
		{
			memset(_dataSource, 0, sizeof(_dataSource));
			strncpy(_dataSource, value, sizeof(_dataSource));
			_layer = _app->loadLayer(_dataSource);
		}

	}

	lifeiTask_2 * shpLoader::load(lifeiTask_2 * task)
	{
		lifeiMutex_2::ScopeLock lk(_mutex);
		lifeiTileTask_2* pTask = dynamic_cast<lifeiTileTask_2*> (task);

		//¼ÆËãÍßÆ¬Êý¾Ý
		RECT rect = { 0, 0, 256, 256 };
		HBRUSH brush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		FillRect(_hMemDC, &rect, brush);
		SelectObject(_hMemDC, _hBitMap);

		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		SelectObject(_hMemDC, hPen);
		renderShapefile();

		lifeiImageLoader::rgbaBuffertToDXT1(_pRGBA, 256, 256, pTask->_image);
		DeleteObject(hPen);

		return task;
	}

	void shpLoader::renderShapefile()
	{
		if (0 == _layer)
		{
			return;
		}

		size_t fCount = _layer->getFeatureCount();
		for (size_t i = 0; i < fCount; i++)
		{
			IFeature* pObject = _layer->getFeature(i);
			IFeaturePoint* pPoint = dynamic_cast<IFeaturePoint*> (pObject);
			if (pPoint)
			{
				renderPoint(pPoint);
				continue;
			}
			IFeatureLine* pLine = dynamic_cast<IFeatureLine*> (pObject);
			if (pLine)
			{
				renderLine(pLine);
			}
		}
	}

	void shpLoader::unload(lifeiTask_2 * task)
	{
	}

	bool shpLoader::getImageData(const char * url, std::vector<char>& arBuf)
	{
	
		return true;
	}
	
	void shpLoader::renderLine(IFeatureLine* pFeature)
	{
		size_t nPoint = pFeature->getPointCount();
		if ( 0 == nPoint)
		{
			return;
		}
		real2 scalar(256.0 / 360, 256.0 / 180);
		real2 offset(180, 90);
		real2 pt = pFeature->getPoint(0) + offset;
		::MoveToEx(_hMemDC, (int)pt.x, (int)pt.y, 0);
		for (size_t i = 1; i < nPoint; i++)
		{
			pt = pFeature->getPoint(i) + offset;
			pt.x = pt.x* scalar.x;
			pt.y = pt.y * scalar.y;
			::LineTo(_hMemDC, (int)pt.x, (int)pt.y);
		}
	}
	
	void shpLoader::renderPoint(IFeaturePoint* pFeature)
	{

	}
	
	int shpLoader::getArg(const char* args, const lifeiTileId& id)
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
		return new shpLoader(platform);
	}

}
