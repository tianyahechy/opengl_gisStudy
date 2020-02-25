
#include "tileSoureUserDraw.h"
#include "../opengl_GIS/lifeiTileTask_2.h"
#include "../opengl_GIS/lifeiImageLoader.h"
#include "../opengl_GIS/IPluginTileManager.h"

namespace CELL
{
	tileSoureUserDraw::tileSoureUserDraw()
	{

		HWND hWnd = GetDesktopWindow();
		HDC hDesk = GetDC(hWnd);
		_hMemDC = CreateCompatibleDC(hDesk);
		BITMAPINFO bmpInfor;
		bmpInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfor.bmiHeader.biWidth = 256;
		bmpInfor.bmiHeader.biHeight = 256;
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

	tileSoureUserDraw::~tileSoureUserDraw()
	{
	}

	void tileSoureUserDraw::setParam(const char * name, const char * value)
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

	lifeiTask_2 * tileSoureUserDraw::load(lifeiTask_2 * task)
	{
		lifeiMutex_2::ScopeLock lk(_mutex);
		lifeiTileTask_2* pTask = dynamic_cast<lifeiTileTask_2*> (task);
		int row = pTask->_tileId._row;
		int col = pTask->_tileId._col;
		int level = pTask->_tileId._lev;
		char    szURL[1024];

		int arg0 = getArg( _arg0, pTask->_tileId);
		int arg1 = getArg( _arg1, pTask->_tileId);
		int arg2 = getArg( _arg2, pTask->_tileId);
		sprintf(szURL, _path, arg0, arg1, arg2);
		
		//计算瓦片数据
		RECT rect = { 0, 0, 256, 256 };
		HBRUSH brush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		FillRect(_hMemDC, &rect, brush);

		//绘制文字
		char szBuf[128] = { 0 };
		sprintf(szBuf, ("瓦片ID:%d%06d-%06d"), (int)pTask->_tileId._lev, (int)pTask->_tileId._col, (int)pTask->_tileId._row);
		SetTextColor(_hMemDC, RGB(0, 0, 255));
		TextOutA(_hMemDC, 10, 10, szBuf, strlen(szBuf));
		SelectObject(_hMemDC, _hBitMap);
		lifeiImageLoader::rgbaBuffertToDXT1(_pRGBA, 256, 256, pTask->_image);

		return task;
	}

	void tileSoureUserDraw::unload(lifeiTask_2 * task)
	{
	}

	int tileSoureUserDraw::getArg(const char* args, const lifeiTileId& id)
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
		return new tileSoureUserDraw();
	}

}
