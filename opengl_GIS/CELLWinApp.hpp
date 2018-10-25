#pragma once

#include    "CELLApp.hpp"
#include    <windows.h>
#include    <tchar.h>
#include "CELLGLContext.h"

namespace CELL
{
    class CELLWinApp :public CELLApp
    {
    public:
        HWND    _hWnd;
		CELLGLContext _context;
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
                                    , nullptr);
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
            while (GetMessage(&msg, nullptr, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
			_context.shutdown();
        }
    protected:
        static  LRESULT CALLBACK  wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
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
            return 0;
        }
    };

}
