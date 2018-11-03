#pragma once

#include    "CELLApp.hpp"
#include    <windows.h>
#include    <tchar.h>
#include "CELLGLContext.h"
#include "CELLOpenGL.h"

namespace CELL
{
    class CELLWinApp :public CELLApp
    {
    public:
        HWND    _hWnd;
		CELLGLContext _context;
		CELLOpenGL _device;
    public:
        CELLWinApp()
        {
            _hWnd   =   0;
        }
    public:
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
            wcex.lpszClassName  =   _T("CELL.BigMap");
            wcex.hIconSm        =   0;
            RegisterClassExW(&wcex);
            /// 创建窗口
            _hWnd   =   CreateWindow(
                                      _T("CELL.BigMap")
                                    , _T("BigMap")
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

			HDC hDC = GetDC(_hWnd);
			if (!_context.Init(_hWnd, hDC))
			{
				DestroyWindow(_hWnd);
				return false;
			}
			return true;
        }
        ///  入口函数
        virtual void    main(int argc, char** argv)
        {
            MSG msg =   {0};
            // 主消息循环: 
#if 0
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

#endif
			_context.shutdown();
        }

		//绘制函数
		void render()
		{
			_device.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			_device.clearColor(1, 0, 0, 1);
			_context.swapBuffer();
		}
		LRESULT eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{           
			switch (message)
            {
			case WM_LBUTTONDOWN:
				break;
			case WM_LBUTTONUP:
				break;
			case WM_MOUSEMOVE:
				break;
			case WM_MOUSEWHEEL:
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
