#pragma once
#include "../opengl_GIS/IPluginTileManager.h"
#include "../opengl_GIS/lifeiTask_2.h"
namespace CELL
{
	class GoogleMapLoader : public IPluginTileManager
	{
	public:
		char _path[1024];
		char _ext[16];
	public:
		GoogleMapLoader();
		~GoogleMapLoader();
		//设置参数
		virtual void setParam(const char* name, const char* value);
		//加载数据
		virtual lifeiTask_2 * load(lifeiTask_2* task);
		//卸载数据
		virtual void unload(lifeiTask_2 * task);
	};

}

