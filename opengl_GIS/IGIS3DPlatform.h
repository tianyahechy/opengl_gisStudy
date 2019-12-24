#pragma once
#ifdef ENGINE_API_EXP
#define ENGINE_API_EXP	declspec(dllexport)
#else
#define ENGINE_API_EXP	declspec(dllimport)
#endif
#include <Windows.h>

namespace CELL
{
	class IGIS3DPlatform
	{
	public:
		//初始化平台
		virtual bool initialize(HWND hWnd) = 0;
		//反向
		virtual void unInitialize() = 0;
	};

	struct CREATEPARAM
	{
		//父窗口句柄
		HWND _hWnd;
	};
	//实例化
	__declspec(dllexport) IGIS3DPlatform * createPlatform(const CREATEPARAM& param);
}