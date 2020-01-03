#pragma once
#include "IGIS3DPlatform.h"
#include "CELLWinApp.hpp"

namespace CELL
{
	class CELLGIS3DPlatform : public IGIS3DPlatform
	{
	protected:
		CREATEPARAM _createParam;
		CELLWinApp* _winApp;
		IPluginTileSource * _tileSource;
		HMODULE _hTileSourceDll;
	public:
		CELLGIS3DPlatform(const CREATEPARAM& param);
		~CELLGIS3DPlatform();
	public:
		//初始化平台
		virtual bool initialize();
		//反向
		virtual void unInitialize();
		//事件响应
		virtual LRESULT inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);
		//加载
		virtual bool loadScene(const char* sceneFile);
	protected:
		IPluginTileSource * createTileSource(const char* dllFileName);
	};
	IGIS3DPlatform* createPlatform(const CREATEPARAM& param);
}

