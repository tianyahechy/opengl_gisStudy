#pragma once
#include <vector>
#include "CELLHttpClient.h"
#include "../opengl_GIS/IPluginTileManager.h"
#include "../opengl_GIS/lifeiTileId.h"

namespace CELL
{
#define KEY_ROW				"row"
#define KEY_REVERSEROW		"rrow"
#define KEY_COL				"col"
#define KEY_REVERSECOL		"rcol"
#define KEY_LEVEL			"lev"
	class httpGoogleLoader : public IPluginTileManager
	{
	public:
		char _path[1024];
		char _ext[16];
		char _arg0[128];  //占位符
		char _arg1[128];
		char _arg2[128];
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

		int getArg( const char* arg, const lifeiTileId& id);
	};

}

