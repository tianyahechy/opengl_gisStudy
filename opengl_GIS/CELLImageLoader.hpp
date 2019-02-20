#pragma once
#include "CELLImage.hpp"

namespace CELL
{
	class CELLImageLoader
	{
	public:
		//根据文件加载图形信息
		static CELLImage* load(const char* fileName);
		static bool loadImage(const char* fileName, CELL::CELLImage& image);
		//加载png/jpg格式数据并转化成rgb
		static RgbBuffer* loadRgb_256x256(const char* fileName);
		//加载png/jpg格式数据并转化成rgba
		static RgbaBuffer* loadRgba_256x256(const char* fileName);
		//加载png/jpg格式数据并转化成rgb
		static bool loadImageToRgb(const char* fileName, CELLImage& image);
		//加载png/jpg格式数据并转化成rgba
		static bool loadImageToRgba(const char* fileName, CELLImage& image);
	};
}