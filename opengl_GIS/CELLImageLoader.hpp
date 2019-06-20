#pragma once

#include "CELLImage.hpp"


namespace CELL
{
    class   CELLImageLoader
    {
    public:
        /// <summary>
        /// 根据文件加载图形信息
        /// </summary>
        static  CELLImage*  load(const char* fileName);
        static  bool        loadImage( const char* fileName,CELL::CELLImage& image );
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgb
        /// </summary>
        static  RgbBuffer*  loadRgb_256X256(const char* fileName);
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgba
        /// </summary>
        static  RgbaBuffer* loadRgba_256X256(const char* fileName);
 
        /// <summary>
        /// 加载png/jpg格式数据并转化成Rgb
        /// </summary>
        static  bool        loadImageToRgb( const char* fileName,CELLImage& image );
        // <summary>
        /// 加载png/jpg格式数据并转化成Rgba
        /// </summary>
        static  bool        loadImageToRgba( const char* fileName,CELLImage& image );
       

    };
}