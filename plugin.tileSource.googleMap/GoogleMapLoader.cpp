
#include "GoogleMapLoader.h"

namespace CELL
{
	GoogleMapLoader::GoogleMapLoader()
	{
	}

	GoogleMapLoader::~GoogleMapLoader()
	{
	}

	void GoogleMapLoader::setParam(const char * name, const char * value)
	{
	}

	CELLTask * GoogleMapLoader::load(CELLTask * task)
	{
		return nullptr;
	}

	void GoogleMapLoader::unload(CELLTask * task)
	{
	}

	extern "C" EXPORTFUNC IPluginTileSource * createTileSource(IGIS3DPlatform* platform)
	{
		return new GoogleMapLoader();
	}

}
