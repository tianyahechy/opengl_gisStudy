#pragma once

#include    "CELLApp.hpp"
#include    <windows.h>
#include    <tchar.h>
#include "CELLGLContext.h"
#include "CELLOpenGL.h"
#include "CELLShader.hpp"
#include "CELLShpReader.h"

namespace CELL
{
    class CELLWinApp :public CELLApp
    {
    public:
		//窗口句柄
        HWND    _hWnd;
		//窗口宽度
		int		_width;
		//窗口高度
		int		_height;
		CELLGLContext _context;
		CELLOpenGL _device;
		PROGRAM_P2_AC4 _shader;
		PROGRAM_P2_C4 _shaderShp;
		CELLShpReader _shpReader;

		struct vertex
		{
			CELL::float2 pos;
			CELL::Rgba4Byte color;
		};
    public:
        CELLWinApp()
        {
            _hWnd   =   0;
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
			HDC hDC = GetDC(_hWnd);
			if (!_context.Init(_hWnd, hDC))
			{
				DestroyWindow(_hWnd);
				return false;
			}
			//初始化数据
			this->InitData();
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
			_device.clearColor(0, 0, 0, 1);
			//视口
			_device.setViewPort(0, 0, _width, _height);
			
			CELL::matrix4 longLatPrj = CELL::ortho<float>(_shpReader._xMin, _shpReader._xMax, _shpReader._yMin, _shpReader._yMax,-100.0,100.0);
			_shaderShp.begin();
			glUniformMatrix4fv(_shaderShp._MVP, 1, false, longLatPrj.data());
			_shpReader.render(_shaderShp);
			_shaderShp.end();
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
			case WM_SIZE:
			{
				if (::IsWindow(hWnd))
				{
					RECT rc;
					GetClientRect(hWnd, &rc);
					_width = rc.right - rc.left;
					_height = rc.bottom - rc.top;
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
