#pragma once
#include "CELLPlatform.hpp"

#if CELL_PLATFORM == CELL_PLATFORM_WIN32
namespace CELL
{
	class  CELLGLContext
	{
	protected:
		int					_format;
		HWINDOW				_hWnd;
		HDISPLAY			_hDC;
		HGLRC				_hRC;
	public:
		int					_winWidth;
		int					_winHeight;
	public:
		 CELLGLContext();
		~ CELLGLContext();

		//初始化GL
		bool Init(HWINDOW hWnd, HDISPLAY hDC)
		{
			_hWnd = hWnd;
			_hDC = hDC;
			unsigned PixelFormat;
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				32,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				32,
				8,
				0,
				PFD_MAIN_PLANE,
				0,
				0,
				0,
				0
			};
			RECT rt = { 0, 0, 0, 0 };
			GetClientRect(hWnd, &rt);
			_winWidth = rt.right - rt.left;
			_winHeight = rt.bottom - rt.top;
			_hDC = GetDC(_hWnd);
			if (_format == 0)
			{
				PixelFormat = ChoosePixelFormat(_hDC, &pfd);
			}
			else
			{
				PixelFormat = _format;
			}
			if (!SetPixelFormat(_hDC, PixelFormat, &pfd))
			{
				return false;
			}
			_hRC = wglCreateContext(_hDC);
			if ( !wglMakeCurrent(_hDC,_hRC))
			{
				return false;
			}
			//glewInit();
			return true;
		}

		void shutdown()
		{
			if (_hRC != NULL)
			{
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(_hRC);
				_hRC = NULL;
			}
			if (_hDC != NULL)
			{
				ReleaseDC(_hWnd, _hDC);
				_hDC = NULL;

			}
		}
		//交换缓冲区
		void swapBuffer()
		{
			SwapBuffers(_hDC);
		}
	private:

	};

	 CELLGLContext:: CELLGLContext()
	{
		 _format = 0;
		 _hWnd = 0;
		 _hDC = 0;
		 _hRC = 0;
		 _winWidth = 64;
		 _winHeight = 64;

	}

	 CELLGLContext::~ CELLGLContext()
	{
		 shutdown();
	}
}
#elif CELL_PLATFORM == CELL_PLATFORM_LINUX
namespace CELL
{

}
#else
{

}
#endif