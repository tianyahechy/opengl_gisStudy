#pragma once

#include    "CELLMath.hpp"
#include    "CELLCamera.hpp"
namespace   CELL
{
    class   CELLResourceMgr;
    class   CELLOpenGL;
    class   CELLContext
    {
    public:
        CELLContext()
        {
            memset(_keyState,0,sizeof(_keyState));
        }
        CELLOpenGL*         _device;
        /// 资源管理者指针
        CELLResourceMgr*    _resMgr;
        /// 鼠标的当前位置X
        int         _mouseX;
        /// 鼠标的当前位置Y
        int         _mouseY;

        /// 窗口的大小
        int         _width;
        int         _height;
        /// 每一帧绘制所需要的时间
        float       _timePerFrame;
        /// 2d 屏幕投影矩阵
        matrix4r    _screenPrj;
        /// 观察矩阵
        CELLCamera  _camera;
        /// mvp;
        matrix4r    _mvp;
        matrix4r    _vp;

		byte_lf        _keyState[256];

    };
}
