#pragma once
#include "lifeiApp_2.h"
#include <Windows.h>
#include <tchar.h>
#include "lifeiGLContext.h"
#include "lifeiOpengl.h"
#include "lifeiFrameBigMap_2.h"
#include "lifeiContext_2.h"
#include "lifeiThread_2.h"
#include "lifeiEvent_2.h"
#include "lifeiShaderManager_2.h"
#include <assert.h>

namespace CELL
{
	class lifeiWinApp_2 : public lifeiApp_2, public lifeiThread_2
	{
	public:
		HWND					_hParentWnd;
		LifeiGLContext			_contextGL;
		lifeiContext_2			_context;
		lifeiShaderManager_2	_shaderMgr;
		lifeiOpenGL				_device;
		lifeiFrame_2	*		_frame;
		bool					_threadRun;
		bool					_makeResult;
		lifeiEvent_2			_event;

	public:
		lifeiWinApp_2();
		//创建窗口函数
		virtual bool createWindow(HWND hParentWnd, int width, int height, HINSTANCE hInst);
		//初始化上下文
		void initContext();
		//创建框架
		virtual lifeiFrame_2* createFrame();		
		//入口函数
		virtual void main(int argc, char** argv);
		//绘制函数
		virtual void render();
		//创建完成通知函数
		virtual bool onCreate();
		//线程执行函数
		virtual bool onRun();
		//结束函数
		virtual bool onDestroy();
		//事件
		LRESULT eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	};
}