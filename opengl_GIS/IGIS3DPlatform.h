#pragma once
#ifdef ENGINE_API_EXP
#define ENGINE_API_EXP	declspec(dllexport)
#else
#define ENGINE_API_EXP	declspec(dllimport)
#endif

#define EXPORTFUNC	_declspec(dllexport)
#define IMPORTFUNC	_declspec(dllimport)

#include <Windows.h>

namespace CELL
{
	class CELLTask;
	class IPlugin
	{
	public:
	};

#define CREATE_TILESOURCE	"createTileSource"

	class IPluginTileSource : public IPlugin
	{
	public:
		//设置参数
		virtual void setParam(const char* name, const char* value) = 0;
		//加载数据
		virtual CELLTask * load(CELLTask* task) = 0;
		//卸载数据
		virtual void unload(CELLTask * task) = 0;
	};
	class IGIS3DPlatform
	{
	public:
		//初始化平台
		virtual bool initialize() = 0;
		//反向
		virtual void unInitialize() = 0;
		//事件响应
		virtual LRESULT inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam) = 0;
	};

	struct CREATEPARAM
	{
		//父窗口句柄
		HWND _hWnd;
	};
	//实例化
	__declspec(dllexport) IGIS3DPlatform * createPlatform(const CREATEPARAM& param);
}