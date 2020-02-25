#pragma once
#include "lifeiImage.h"
#include "CELLDXTCompressor.h"

namespace CELL
{
	class EXPORTFUNC lifeiImageLoader
	{
	public:
		static bool loadImage(const char* fileName, CELL::lifeiImage& image);

		static bool loadImageBufferToDXT1(const void* data, int len, lifeiImage& image);
		//加载png/jpg格式数据并转换成dxt1
		static bool loadImageToDXT1(const char* fileName, lifeiImage& image);
		//RGBA数据转化成DXT1
		static bool rgbaBuffertToDXT1(const void* data, int w, int h, lifeiImage& image);
	};
}
