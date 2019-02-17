#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	class CELLResouceMgr;
	class CELLOpenGL;
	class CELLContext
	{
	public:
		CELLOpenGL * _device;
		//资源管理者指针
		CELLResouceMgr* _resMgr;
		//鼠标当前位置
		int _mouseX;
		int _mouseY;
		//窗口的大小
		int _width;
		int _height;
		//2d屏幕投影矩阵
		matrix4r _screenPrj;

	};

}