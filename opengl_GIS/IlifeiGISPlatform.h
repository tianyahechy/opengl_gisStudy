
#pragma once
#include <Windows.h>
#include "export.h"

namespace CELL
{

	struct CREATEPARAM
	{
		//父窗口句柄
		HWND _hWnd;
	};

	class ILifeiGISPlatform
	{
	public:
		//初始化平台
		virtual bool initialize() = 0;
		//反向
		virtual void unInitialize() = 0;
		//事件响应
		virtual LRESULT inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam) = 0;
		//加载
		virtual bool loadScene(const char* sceneFile) = 0;
	};

	//实例化
	ENGINE_API ILifeiGISPlatform * createPlatform(const CREATEPARAM& param);
	
}