
#pragma once

#include "lifeiWinApp_2.h"
#include "IGISPlatform.h"

namespace CELL
{
	class lifeiGIS3DPlatform : public IGISPlatform
	{
	protected:
		CREATEPARAM		_createParam;
		lifeiWinApp_2	*_winApp;

	public:
		lifeiGIS3DPlatform(const CREATEPARAM& param);
		~lifeiGIS3DPlatform();

	public:
		//初始化平台
		virtual bool initialize();
		//反向
		virtual void unInitialize();
		//事件响应
		virtual LRESULT inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);
		//加载
		virtual bool loadScene_2(const char* sceneFile);
		//加载shp文件,并返回对象
		virtual ILayer * loadLayer(const char* shp);
	};

	IGISPlatform * createPlatform(const CREATEPARAM& param);
}