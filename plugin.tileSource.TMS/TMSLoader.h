#pragma once
#include "../opengl_GIS/IGIS3DPlatform.h"
namespace CELL
{
	class TMSLoader : public IPluginTileSource
	{
	public:
		char _path[1024];
		char _ext[16];
	public:
		TMSLoader();
		~TMSLoader();
		//设置参数
		virtual void setParam(const char* name, const char* value);
		//加载数据
		virtual CELLTask * load(CELLTask* task);
		//卸载数据
		virtual void unload(CELLTask * task);
	};

}

