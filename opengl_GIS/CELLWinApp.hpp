#pragma once

#include    "lifeiApp.h"
#include    <windows.h>
#include    <tchar.h>
#include    "lifeiGLContext.h"
#include    "CELLOpenGL.h"
#include    "CELLFrameBigMap.h"
#include    "lifeiContext.h"
#include    "lifeiThread.h"
#include    "lifeiEvent.h"
#include	"lifeiShaderManager.h"
#include	"CELLFrameBigMap.h"
#include    <assert.h>

namespace CELL
{
    class CELLWinApp 
        :public LifeiApp
        ,public lifeiThread
    {
    public:
        HWND				_hParentWnd;
		LifeiGLContext		_contextGL;
		lifeiContext		_context;
		lifeiShaderManager	_shaderMgr;
        CELLOpenGL			_device;
        lifeiFrame*			_frame;
        bool				_threadRun;
        bool				_makeReuslt;
        lifeiEvent			_event;
    public:
        CELLWinApp()
        {
			_hParentWnd			=   0;
            _frame              =   0;
            _threadRun          =   true;
            _makeReuslt         =   false;
            _context._device    =   &_device;
            _context._shaderMgr =   &_shaderMgr;
        }
    public:
        /// 创建窗口函数
        virtual bool    createWindow(HWND hParentWnd, int width, int height,INSTANCE hInst)
        {
			_hParentWnd = hParentWnd;
            HDISPLAY    hDC     =   GetDC(_hParentWnd);
            if(!_contextGL.init(_hParentWnd,hDC))
            {
                return  false;
            }
            
            return  true;
        }
		//初始化上下文
		void initContext()
		{
			_context._device->initialize();
            _context._shaderMgr->initialize(_context._device);
			if (IsWindow(_hParentWnd))
            {
                RECT    rect;
                GetClientRect(_hParentWnd, &rect);
                _context._width     =   rect.right - rect.left;
                _context._height    =   rect.bottom - rect.top;
            }
            else
            {
                _context._width     =   64;
                _context._height    =   64;
            }
		}

        /// <summary>
        /// 创建框架
        /// </summary>
        virtual lifeiFrame*  createFrame()
        {
            return  new CELLFrameBigMap(_context);
        }
        ///  入口函数
        virtual void    main(int argc, char** argv)
        {
			initContext();
            _frame  =   createFrame();

            /// 解除与主线程的绑定
            _contextGL.makeCurrentNone();

            if (_frame == 0)
            {
				return;
            }
            lifeiThread::start();

             _event.wait();
             if (!_makeReuslt)
             {
				lifeiThread::join();
                 delete  _frame;
                 _contextGL.shutdown();
                 return;
             }

        }

        /// 绘制函数
        virtual void    render()
        {
            if (_frame == 0)
            {
                return;
            }
            _frame->update(_context);
            _frame->onFrameStart(_context);
            _frame->onFrameEnd(_context);
            _contextGL.swapBuffer();
        }
        //////////////////////////////////////////////////////////////////////////

        /// <summary>
        /// 创建完成通知函数
        /// </summary>
        virtual bool    onCreate()
        {
            _makeReuslt =   _contextGL.makeCurrent();
            assert(_makeReuslt);
            _event.set();
            return  _makeReuslt;
        }
     
        /// <summary>
        /// 线程执行函数
        /// </summary>
        virtual bool    onRun()
        {
            while (_threadRun)
            {
                render();
            }
            return  false;
        }
        /// <summary>
        /// 结束函数
        /// </summary>
        virtual bool    onDestroy()
        {
            _contextGL.shutdown();
            return  false;
        }

    public:
        LRESULT         eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
            case WM_LBUTTONDOWN:
                _frame->onLButtonDown(LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_LBUTTONUP:
                _frame->onLButtonUp(LOWORD(lParam),HIWORD(lParam));
                break;
			case WM_RBUTTONDOWN:
				_frame->onRButtonDown(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_RBUTTONUP:
				_frame->onRButtonUp(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MBUTTONDOWN:
				_frame->onMButtonDown(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MBUTTONUP:
				_frame->onMButtonUp(LOWORD(lParam), HIWORD(lParam));
				break;
            case WM_MOUSEMOVE:
                _context._mouseX = LOWORD(lParam);
                _context._mouseY = HIWORD(lParam);
                _frame->onMouseMove(LOWORD(lParam), HIWORD(lParam));
                break;
            case WM_MOUSEWHEEL:

                _frame->onMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
                break;
            case WM_KEYDOWN:
                _frame->onKeyDown(wParam);
                break;
            case WM_KEYUP:
                _frame->onKeyUp(wParam);
                break;
            case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);
                    EndPaint(hWnd, &ps);
                }
                break;
            case WM_SIZE:
                {
                    if(IsWindow(_hParentWnd))
                    { 
                        RECT    rect;
                        GetClientRect(_hParentWnd,&rect);
                        _context._width     =   rect.right - rect.left;
                        _context._height    =   rect.bottom - rect.top;
                    }
                }
                break;
            case WM_DESTROY:
                _threadRun  =   false;
				lifeiThread::join();
                PostQuitMessage(0);
                break;
            default:
                return  DefWindowProc(hWnd, message, wParam, lParam);
            }
            return  S_OK;
        }

    protected:
        static  LRESULT CALLBACK  wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            if (WM_CREATE == message)
            {
                CREATESTRUCT*   pSTRUCT     =   (CREATESTRUCT* )lParam;
                CELLWinApp*     pApp        =   (CELLWinApp*)pSTRUCT->lpCreateParams;
                #ifndef GWL_USERDATA
                #define GWL_USERDATA (-21)
                #endif
                SetWindowLongPtr(hWnd,GWL_USERDATA,(LONG_PTR)pApp);
                return  pApp->eventProc(hWnd,WM_CREATE,wParam,lParam);
            }
            else
            {
                CELLWinApp*     pApp        =       (CELLWinApp*)GetWindowLongPtr(hWnd,GWL_USERDATA);
                if (pApp)
                {
                    return  pApp->eventProc(hWnd,message,wParam,lParam);
                }
                else
                {
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
        }
    };

}
