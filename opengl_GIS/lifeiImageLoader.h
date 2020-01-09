#pragma once
#include "lifeiImage.h"
#include "CELLDXTCompressor.h"
#include "IGIS3DPlatform.h"

namespace CELL
{
	class EXPORTFUNC lifeiImageLoader
	{
	public:
		//根据文件加载图形信息
		static lifeiImage* load(const char* fileName);
		static bool loadImage(const char* fileName, CELL::lifeiImage& image);
		//加载png/jpg格式数据并转成rgb
		static RgbBuffer* loadRgb_256X256(const char* fileName);
		//加载png/jpg格式数据并转换成rgba
		static RgbaBuffer* loadRgba_256X256(const char* fileName);
		//加载png/jpg格式数据并转换成rgb
		static bool loadImageToRGB(const char* fileName, lifeiImage& image);
		//加载png/jpg格式数据并转换成rgba
		static bool loadImageToRGBA(const char* fileName, lifeiImage& image);
		//加载png/jpg格式数据并转换成dxt1
		static bool loadImageToDXT1(const char* fileName, lifeiImage& image);
		//加载png/jpg格式数据并转换成dxt5
		static bool loadImageToDXT5(const char* fileName, lifeiImage& image);
		

	};
}
