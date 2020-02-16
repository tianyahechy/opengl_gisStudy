
#pragma once
#include "lifeiApp.h"
#include <Windows.h>
#include <tchar.h>
#include "lifeiGLContext.h"
#include "lifeiOpengl.h"
#include "lifeiFrameBigMap.h"
#include "lifeiContext.h"
#include "lifeiThread.h"
#include "lifeiEvent.h"
#include "lifeiShaderManager.h"
#include <assert.h>

namespace CELL
{
	class lifeiWinApp : public LifeiApp, public lifeiThread
	{
	public:
		HWND					_hParentWnd;
		LifeiGLContext			_contextGL;
		lifeiContext			_context;
		lifeiShaderManager		_shaderMgr;
		lifeiOpenGL				_device;
		lifeiFrame	*			_frame;
		bool					_threadRun;
		bool					_makeResult;
		lifeiEvent				_event;

	public:
		lifeiWinApp()
		{
			_hParentWnd	= 0;
			_frame = 0;
			_threadRun = true;
			_makeResult = false;
			_context._device = &_device;
			_context._shaderMgr = &_shaderMgr;

		}

	public:
		//�������ں���
		virtual bool createWindow(HWND hParentWnd, int width, int height, HINSTANCE hInst)
		{
			_hParentWnd = hParentWnd;
			HDC hDC = GetDC(_hParentWnd);
			bool bInitContextGL = _contextGL.init(_hParentWnd, hDC);
			return bInitContextGL;
		}

		//��ʼ��������
		void initContext()
		{
			_context._device->initialize();
			_context._shaderMgr->initialize(_context._device);

			if (IsWindow(_hParentWnd))
			{
				RECT rect;
				GetClientRect(_hParentWnd, &rect);
				_context._width = rect.right - rect.left;
				_context._height = rect.bottom - rect.top;
			}
			else
			{
				_context._width = 64;
				_context._height = 64;
			}
		}
	
		//�������
		virtual lifeiFrame* createFrame()
		{
			return new lifeiFrameBigMap(_context);
		}

		//��ں���
		virtual void main(int argc, char** argv)
		{
			initContext();
			_frame = createFrame();

			//��������̵߳İ�
			_contextGL.makeCurrentNone();

			if ( 0 == _frame)
			{
				return;
			}

			lifeiThread::start();
			_event.wait();

			if (!_makeResult)
			{
				lifeiThread::join();
				delete _frame;
				_contextGL.shutdown();
				return;
			}
		}
	
		//���ƺ���
		virtual void render()
		{
			if ( 0 == _frame)
			{
				return;
			}
			_frame->update(_context);
			_frame->onFrameStart(_context);
			_frame->onFrameEnd(_context);
			_contextGL.swapBuffer();
		}

		//�������֪ͨ����
		virtual bool onCreate()
		{
			_makeResult = _contextGL.makeCurrent();
			assert(_makeResult);
			_event.set();
			return _makeResult;
		}

		//�߳�ִ�к���
		virtual bool onRun()
		{
			while (_threadRun)
			{
				render();
			}
			return false;
		}

		//��������
		virtual bool onDestroy()
		{
			_contextGL.shutdown();
			return false;
		}

	public:
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
							if (IsWindow(_hParentWnd))
							{
								RECT    rect;
								GetClientRect(_hParentWnd, &rect);
								_context._width = rect.right - rect.left;
								_context._height = rect.bottom - rect.top;
							}
			}
				break;
			case WM_DESTROY:
				_threadRun = false;
				lifeiThread::join();
				PostQuitMessage(0);
				break;
			default:
				return  DefWindowProc(hWnd, message, wParam, lParam);
			}
			return  S_OK;

		}

	protected:
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (WM_CREATE == message)
			{
				CREATESTRUCT *	pSTRUCT = (CREATESTRUCT *)lParam;
				lifeiWinApp*	pApp = (lifeiWinApp*)pSTRUCT->lpCreateParams;
				#ifndef GWL_USERDATA
				#define GWL_USERDATA	(-21)
				#endif

				SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pApp);
				return pApp->eventProc(hWnd, WM_CREATE, wParam, lParam);
			}
			else
			{
				lifeiWinApp* pApp = (lifeiWinApp*)GetWindowLongPtr(hWnd, GWL_USERDATA);
				if (pApp)
				{
					return pApp->eventProc(hWnd, message, wParam, lParam);
				}
				else
				{
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
		}

	};
}
