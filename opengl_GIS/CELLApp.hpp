#pragma once
#include "CELLPlatform.hpp"
#include "CELLFrame.h"
namespace CELL
{
    class CELLApp
    {
    public:

        /// 创建窗口函数
        virtual bool    createWindow(int width,int height,HINSTANCE hInst)  =   0;
		//创建框架
		virtual CELLFrame * createFrame() = 0;
        ///  入口函数
        virtual void    main(int argc,char** argv)  =   0;
    };
}
