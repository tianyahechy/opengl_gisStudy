#pragma once
#include "lifeiPlatform.h"
#include "lifeiCamera.h"
#include "lifeiFrustum.h"

#define CELL_PATH_LENGTH 1024
namespace CELL
{
	class lifeiFrame;
	class lifeiShaderManager;
	class lifeiOpenGL;
	class lifeiGIS3DPlatform;
	class lifeiContext
	{
	public:
		//全局的app
		lifeiGIS3DPlatform * _app;
		lifeiOpenGL *		_device;
		//shader指针
		lifeiShaderManager *_shaderMgr;
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

	public:
		lifeiContext()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
	};
}