#pragma once
#include <vector>
#include "CELLHttpClient.h"
#include "../opengl_GIS/IPluginTileManager.h"

namespace CELL
{
	class httpGoogleLoader : public IPluginTileManager
	{
	public:
		char _path[1024];
		char _ext[16];
	public:
		httpGoogleLoader();
		~httpGoogleLoader();
		//设置参数
		virtual void setParam(const char* name, const char* value);
		//加载数据
		virtual lifeiTask * load(lifeiTask* task);
		//卸载数据
		virtual void unload(lifeiTask * task);

	protected:
		//给定url(http)返回数据
		bool getImageData(const char* url, std::vector<char>& arBuf);

	};

}

