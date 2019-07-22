#pragma once

#include "lifeiPlatform.h"

#if LIFEI_PLATFORM == CELL_PLATFORM_WIN32

namespace   CELL
{
    class   CELLGLContext
    {
    protected:
        int                 _format;
        HWINDOW             _hWnd;
        HDISPLAY            _hDC;
        HGLRC               _hRC;
    public:
        int                 _winWidth;
        int                 _winHeight;
    public:
        CELLGLContext()
        {
            _format     =   0;
            _hWnd       =   0;
            _hDC        =   0;
            _hRC        =   0;
            _winWidth   =   64;
            _winHeight  =   64;
        }

        ~CELLGLContext()
        {
            shutdown();
        }
        /**
        *   初始化GL
        */
        bool    init( HWINDOW hWnd,HDISPLAY hDC )
        {
            _hWnd   =   hWnd;
            _hDC    =   hDC;
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
            RECT    rt = { 0, 0, 0, 0 };
            GetClientRect(hWnd, &rt);
            _winWidth   =   rt.right - rt.left;
            _winHeight  =   rt.bottom - rt.top;
            _hDC        =   GetDC( _hWnd );

            
            if(_format == 0)
            {
                PixelFormat =   ChoosePixelFormat( _hDC, &pfd );
            }
            else
            {
                PixelFormat	=	_format;
            }
            if(!SetPixelFormat( _hDC, PixelFormat, &pfd ))
            {
                return  false;
            }
            _hRC        =   wglCreateContext( _hDC );
            if(!wglMakeCurrent( _hDC, _hRC ))
            {
                return  false;
            }
            /// glew init
            glewInit();
            return  true;
        }

        bool    makeCurrent()
        {
            return  wglMakeCurrent( _hDC, _hRC );
        }

        bool    makeCurrentNone()
        {
            return  wglMakeCurrent( 0, 0 );
        }

        /**
        *   销毁EGL
        */
        void    shutdown()
        {
            if( _hRC != NULL )
            {
                wglMakeCurrent( NULL, NULL );
                wglDeleteContext( _hRC );
                _hRC = NULL;							
            }
            if( _hDC != NULL )
            {
                ReleaseDC( _hWnd, _hDC );
                _hDC = NULL;
            }
        }

        /**
        *   交换缓冲区
        */
        void    swapBuffer()
        {
            SwapBuffers(_hDC);
        }

    };
}

#elif LIFEI_PLATFORM == CELL_PLATFORM_LINUX

namespace   CELL
{
    class   CELLGLContext
    {
    protected:
        Display*    _display;
        Window      _window;
        GLXContext  _context;
    public:
        CELLGLContext()
        {
            _display    =   0;
            _context    =   0;
            _window     =   0;
        }
        ~CELLGLContext()
        {
        }
        bool    init(HWINDOW hWnd,HDISPLAY hDC)
        {
            _window =   hWnd;
            _display=   hDC;

            int attrib[]    =
            {
                GLX_RGBA,               GLX_DOUBLEBUFFER,
                GLX_RED_SIZE,           8,
                GLX_GREEN_SIZE,         8,
                GLX_BLUE_SIZE,          8,
                GLX_ALPHA_SIZE,         8,
                GLX_DEPTH_SIZE,         24,
                GLX_STENCIL_SIZE,       8,
                //GLX_SAMPLE_BUFFERS_ARB, true,
                //GLX_SAMPLES_ARB,        2,
                None,
            };

            int         screen  =   DefaultScreen(_display);
            XVisualInfo*visual  =   glXChooseVisual(_display,screen,attrib);

            if(!_context)
                _context = glXCreateContext(_display,visual,NULL,True);
            if(!_context)
                return  false;

            glXMakeCurrent(_display,_window,_context);
            return  true;
        }
        /**
        *   销毁EGL
        */
        void    shutdown()
        {
            if(_context)
            {
                glXDestroyContext(_display,_context);
            }
        }
        /**
        *   交换缓冲区
        */
        void    swapBuffer()
        {
            glXSwapBuffers(_display,_window);
        }
    };
}
#else


#endif