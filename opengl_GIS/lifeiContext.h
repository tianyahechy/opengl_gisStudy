#pragma once
#include "lifeiPlatform.h"
#include "CELLMath.hpp"
#include "lifeiCamera.h"
#include "lifeiFrustum.h"

#define CELL_PATH_LENGTH 1024
namespace CELL
{
	class lifeiFrame;
	class lifeiShaderManager;
	class lifeiOpenGL;
	class CELLGIS3DPlatform;
	class lifeiContext
	{
	public:
		//全局的app
		CELLGIS3DPlatform * _app;
		lifeiOpenGL *		_device;
		//shader指针
		lifeiShaderManager *_shaderMgr;
		//鼠标的当前位置
		int					_mouseX;
		//鼠标的当前位置
		int					_mouseY;
		//窗口的大小
		int					_width;
		int					_height;
		//每一帧绘制所需要的时间
		float				_timePerFrame;
		//2d屏幕投影矩阵
		matrix4r			_screenPrj;
		//观察矩阵
		lifeiCamera			_camera;
		//mvp
		matrix4r			_mvp;
		matrix4r			_vp;
		//视锥裁剪
		Frustum				_frustum;
		byte				_keyState[256];
		lifeiContext()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
	};
}