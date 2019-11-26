#pragma once

#include "lifeiPlatform.h"
#include "lifeiFrame.h"

namespace CELL
{
    class   CELLApp
    {
    public:

        /// 创建窗口函数
        virtual bool        createWindow(int width,int height,INSTANCE hInst)  =   0;
        /// <summary>
        /// 创建框架
        /// </summary>
        virtual lifeiFrame*  createFrame()   =   0;
        ///  入口函数
        virtual void        main(int argc,char** argv)  =   0;
    };
}
