#pragma once

namespace CELL
{
    class   CELLApp
    {
    public:

        /// 创建窗口函数
        virtual bool    createWindow(int width,int height,HINSTANCE hInst)  =   0;
        ///  入口函数
        virtual void    main(int argc,char** argv)  =   0;
    };
}
