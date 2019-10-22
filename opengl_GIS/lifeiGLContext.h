#pragma once
#include "lifeiPlatform.h"
#if LIFEI_PLATFORM == CELL_PLATFORM_WIN32
namespace CELL
{
	class LifeiGLContext
	{
	protected:
		int				_format;
		HWINDOW			_hWnd;
		HDISPLAY		_hDC;
		HGLRC			_hRC;

	public:
		int				_winWidth;
		int				_winHeight;

	public:
		LifeiGLContext()
		{
			_format = 0;
			_hWnd = 0;
			_hDC = 0;
			_winWidth = 64;
			_winHeight = 64;
		}
		~LifeiGLContext()
		{
			shutdown();
		}

		//初始化GL
		bool init(HWINDOW hWnd, HDISPLAY hDC)
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
			if (!wglMakeCurrent(_hDC, _hRC))
			{
				return false;
			}
			glewInit();
			return true;

		}
		bool makeCurrent()
		{
			return wglMakeCurrent(_hDC, _hRC);
		}

		bool makeCurrentNone()
		{
			return wglMakeCurrent(0, 0);
		}
		//销毁egl
		void shutdown()
		{
			if (NULL != _hRC)
			{
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(_hRC);
				_hRC = NULL;
			}
			if (NULL != _hDC)
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
	};
}
#elif LIFEI_PLATFORM == CELL_PLATFORM_LINUX
namespace CELL
{
	class lifeiGLContext
	{
	protected:
		Display* _display;
		Window	_window;
		GLXContext _context;
	public:
		lifeiGLContext()
		{
			_display = 0;
			_context = 0;
			_window = 0;
		}
		~lifeiGLContext()
		{
		}
		bool init(HWINDOW hWnd, HDISPLAY hDC)
		{
			_window = hWnd;
			_display = hDC;

			int attrib[] = 
			{
				GLX_RGBA,				GL_DOUBLEBUFFER,
				GLX_RED_SIZE,			8,
				GLX_GREEN_SIZE,			8,
				GLX_BLUE_SIZE,			8,
				GLX_ALPHA_SIZE,			8,
				GLX_DEPTH_SIZE,			24,
				GLX_STENCIL_SIZE,		8,
				None,					
			}
			int screen = DefaultScreen(_display);
			XVisualInfo *visual = glXChooseVisual(_display, screen, attrib);
			if (!_context)
			{
				context = glXCreateContex(_display, visual, NULL, TRUE);
			}
			if(!_context)
			{
				return false;
			}
			glMakeCurrent(_display, _window, _context);
			return true;
		}

		//销毁EGL
		void shutdownGL()
		{
			if (_context)
			{
				glXDestroyContext(_display, _context);
			}
		}

		//交换缓冲区
		void swapBuffer()
		{
			glXSwapBuffers(_display,_window);
		}
		
	};
}
#endif