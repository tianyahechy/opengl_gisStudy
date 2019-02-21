#pragma once
#include "CELLMath.hpp"
#include "CELLResourceMgr.hpp"
#include "CELLCamera.hpp"
namespace CELL
{
	class CELLResourceMgr;
	class CELLOpenGL;
	class CELLContext
	{
	public:
		CELLContext()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
		CELLOpenGL * _device;
		//资源管理者指针
		CELLResourceMgr* _resMgr;
		//鼠标当前位置
		int _mouseX;
		int _mouseY;
		//窗口的大小
		int _width;
		int _height;
		//每一帧绘制所需要的时间
		float _timePerFrame;
		//2d屏幕投影矩阵
		matrix4r _screenPrj;
		//观察矩阵
		CELLCamera _camera;
		//mvp
		matrix4r _mvp;
		matrix4r _vp;

		byte _keyState[256];
	};

}