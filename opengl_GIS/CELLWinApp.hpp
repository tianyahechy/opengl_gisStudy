#pragma once

#include "CELLApp.hpp"
#include <windows.h>
#include <tchar.h>
#include "CELLGLContext.h"
#include "CELLOpenGL.h"
#include "CELLShader.hpp"
#include "CELLShpReader.h"
#include "CELLFrameBigMap.h"
#include "CELLContext.h"
#include "CELLThread.hpp"
#include "CELLEvent.hpp"
#include "CELLResourceMgr.hpp"
#include "CELLProgramLibrary.hpp"
namespace CELL
{
    class CELLWinApp :public CELLApp, public CELLThread
    {
    public:
		//窗口句柄
        HWND    _hWnd;
		//窗口宽度
		int		_width;
		//窗口高度
		int		_height;
		CELLGLContext _contextGL;
		CELLContext _context;
		CELLOpenGL _device;
		CELLResourceMgr _res;
		PROGRAM_P2_AC4 _shader;
		PROGRAM_P2_C4 _shaderShp;
		CELLShpReader _shpReader;
		CELLFrame* _frame;
		bool _threadRun;
		bool _makeResult;
		CELLEvent _event;

		struct vertex
		{
			CELL::float2 pos;
			CELL::Rgba4Byte color;
		};
    public:
        CELLWinApp()
        {
            _hWnd   =   0;
			_frame = 0;
			_threadRun = true;
			_makeResult = false;
			_context._device = &_device;
			_context._resMgr = &_res;
        }
    public:
		//初始化数据
		void InitData()
		{
			_shader.initialize();
			_shaderShp.initialize();
			std::string strShpName = "data/china_province.shp";
			_shpReader.read(strShpName.c_str());
		}

        /// 创建窗口函数
        virtual bool    createWindow(int width, int height,HINSTANCE hInst)
        {
            /// 1.注册窗口类
            /// 2.创建窗口
            /// 3.更新显示

            WNDCLASSEXW wcex;

            wcex.cbSize         =   sizeof(WNDCLASSEX);

            wcex.style          =   CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc    =   wndProc;
            wcex.cbClsExtra     =   0;
            wcex.cbWndExtra     =   0;
            wcex.hInstance      =   hInst;
            wcex.hIcon          =   0;
            wcex.hCursor        =   LoadCursor(nullptr, IDC_ARROW);
            wcex.hbrBackground  =   (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName   =   0;
            wcex.lpszClassName  =   _T("gis_bim");
            wcex.hIconSm        =   0;
            RegisterClassExW(&wcex);
            /// 创建窗口
            _hWnd   =   CreateWindow(
                                      _T("gis_bim")
                                    , _T("gis_bim")
                                    , WS_OVERLAPPEDWINDOW
                                    , CW_USEDEFAULT
                                    , 0
                                    , CW_USEDEFAULT
                                    , 0
                                    , nullptr
                                    , nullptr
                                    , hInst
                                    , this);
            if (_hWnd == 0 )
            {
                return  false;
            }

            ShowWindow(_hWnd,SW_SHOW);
            UpdateWindow(_hWnd);
			
			HDISPLAY hDC = GetDC(_hWnd);
			if (!_contextGL.Init(_hWnd, hDC))
			{
				DestroyWindow(_hWnd);
				return false;
			}
			//初始化数据
			_device.initialize();
			_context._resMgr->initialize(_context._device);
			_contextGL.makeCurrentNone();
			
			return true;
        }
		//创建框架
		virtual CELLFrame * createFrame()
		{
			if (IsWindow(_hWnd))
			{
				RECT rc;
				GetClientRect(_hWnd, &rc);
				_context._width = rc.right - rc.left;
				_context._height = rc.bottom - rc.top;
			}
			else
			{
				_context._width = 64;
				_context._height = 64;
			}
			return  new CELLFrameBigMap(_context);			
		}
        ///  入口函数
        virtual void main(int argc, char** argv)
        {
			_frame = createFrame();
			if (_frame == 0)
			{
				_contextGL.shutdown();
				return;
			}

			CELLThread::start();
			_event.wait();
			if (!_makeResult)
			{
				CELLThread::join();
				delete _frame;			
				_contextGL.shutdown();
				return;
			}
            MSG msg = {0};
            // 主消息循环: 
#if 1
            while (GetMessage(&msg, nullptr, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
#else
			while (msg.message != WM_QUIT)
			{			
				if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				this->render();
			}
		_contextGL.shutdown();
#endif
			
        }

		//绘制函数
		virtual void render()
		{
			if (_frame == NULL)
			{
				return;
			}
			_frame->update(_context);
			_frame->onFrameStart(_context);
			_frame->onFrameEnd(_context);
			_contextGL.swapBuffer();
	
		}
	
		DWORD threadId() const
		{
			return _threadId;
		}
		bool isRun() const
		{
			return _thread != 0;
		}
		//创建完成通知函数
		virtual bool onCreate()
		{
			_makeResult = _contextGL.makeCurrent();
			assert(_makeResult);
			_event.set();
			return _makeResult;
		}
		//线程执行函数
		virtual bool onRun()
		{
			while (_threadRun)
			{
				render();
			}
			return false;
		}
		//结束函数
		virtual bool onDestroy()
		{
			_contextGL.shutdown();
			return false;
		}
		//启动线程函数
		virtual bool start()
		{
			if (_thread != 0)
			{
				return false;
			}
		}
		//等待退出函数
		virtual void join()
		{
			if (_thread)
			{
				WaitForSingleObject(_thread, 0xFFFFFFFF);
				CloseHandle(_thread);
				_thread = 0;
			}
		}
		//关闭
		virtual void close()
		{
			CloseHandle(_thread);
			_thread = 0;
		}
		
		
		LRESULT eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{           
			switch (message)
            {
			case WM_LBUTTONDOWN:
				_frame->onLButtonDown(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_LBUTTONUP:
				_frame->onLButtonUp(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MOUSEMOVE:
				{
					int x = LOWORD(lParam);
					int y = HIWORD(lParam);
					_context._mouseX = x;
					_context._mouseY = y;
					_frame->onMouseMove(x, y);
				}
				break;
			case WM_MOUSEWHEEL:
				break;
			case WM_SIZE:
			{
				if (::IsWindow(_hWnd))
				{
					RECT rc;
					GetClientRect(_hWnd, &rc);
					_context._width = rc.right - rc.left;
					_context._height = rc.bottom - rc.top;
				}
				
			}
			break;
            case WM_COMMAND:
                break;
            case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);
                    // TODO: 在此处添加使用 hdc 的任何绘图代码...
                    EndPaint(hWnd, &ps);
                }
                break;

            case WM_DESTROY:
				_threadRun = false;
				CELLThread::join();
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			return S_OK;
		}
    protected:
        static  LRESULT CALLBACK  wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
			if (WM_CREATE == message )
			{
				CREATESTRUCT * pSTRUCT = (CREATESTRUCT*)lParam;
				CELLWinApp * pApp = (CELLWinApp *)pSTRUCT->lpCreateParams;
#ifndef GWL_USERDATA
#define GWL_USERDATA -21
#endif
				SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pApp);
				return pApp->eventProc(hWnd, WM_CREATE, wParam, lParam);
			}
			else
			{
				CELLWinApp * pApp = (CELLWinApp*)GetWindowLongPtr(hWnd, GWL_USERDATA);
				if (pApp)
				{
					return pApp->eventProc(hWnd, message, wParam, lParam);
				}
				else
				{
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}

            return 0;
        }
    };

}
