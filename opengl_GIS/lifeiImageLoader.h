#pragma once
#include "lifeiImage.h"
#include "CELLDXTCompressor.h"
#include "IGIS3DPlatform.h"

namespace CELL
{
	class EXPORTFUNC lifeiImageLoader
	{
	public:
		static bool loadImage(const char* fileName, CELL::lifeiImage& image);
		//加载png/jpg格式数据并转换成dxt1
		static bool loadImageToDXT1(const char* fileName, lifeiImage& image);
	};
}
