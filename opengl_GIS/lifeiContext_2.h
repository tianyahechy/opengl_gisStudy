#pragma once
#include "lifeiCamera.h"
#include "lifeiFrustum.h"

#define CELL_PATH_LENGTH	1024

namespace CELL
{
	class lifeiFrame;
	class lifeiShaderManager_2;
	class lifeiOpenGL;
	class IGISPlatform;
	class lifeiContext_2
	{
	public:
		//全局app
		IGISPlatform*			_app;
		lifeiOpenGL*				_device;
		//shader管理器指针
		lifeiShaderManager_2*		_shaderMgr;
		//窗口的大小
		int							_width;
		int							_height;
		//每帧绘制所需要的时间
		float						_timePerFrame;
		//2d屏幕投影矩阵
		matrix4r					_screenPrj;
		//观察矩阵
		lifeiCamera					_camera;
		//mvp
		matrix4r					_mvp;
		matrix4r					_vp;
		//视锥裁剪
		Frustum						_frustum;
		byte						_keyState[256];

	public:
		lifeiContext_2()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
	};
}