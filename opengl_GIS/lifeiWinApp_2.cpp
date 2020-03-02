#include "lifeiWinApp_2.h"

namespace CELL
{
	lifeiWinApp_2::lifeiWinApp_2()
	{
		_hParentWnd = 0;
		_frame = 0;
		_threadRun = true;
		_makeResult = false;
		_context._device = &_device;
		_context._shaderMgr = &_shaderMgr;

	}

	bool lifeiWinApp_2::createWindow(HWND hParentWnd, int width, int height, HINSTANCE hInst)
	{
		_hParentWnd = hParentWnd;
		HDC hDC = GetDC(_hParentWnd);
		bool bInitContextGL = _contextGL.init(_hParentWnd, hDC);
		return bInitContextGL;
	}

	void lifeiWinApp_2::initContext()
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

	lifeiFrame_2 * lifeiWinApp_2::createFrame()
	{
		return new lifeiFrameBigMap(_context);
	}

	void lifeiWinApp_2::main(int argc, char ** argv)
	{
		initContext();
		_frame = createFrame();
		//解除与主线程的绑定
		_contextGL.makeCurrentNone();

		if (0 == _frame)
		{
			return;
		}
		//创建opengl上下文与窗口绑定，然后一边发送event事件，让主程序继续运行，一方面多线程渲染
		//			pThis->onCreate();即在此步创建opengl上下文与窗口绑定，然后传递event事件
		//pThis->onRun();
		//pThis->onDestroy();
		lifeiThread_2::start();
		_event.wait();

		if (!_makeResult)
		{
			lifeiThread_2::join();
			delete _frame;
			_contextGL.shutdown();
			return;
		}
	}

	void lifeiWinApp_2::render()
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

	bool lifeiWinApp_2::onCreate()
	{
		_makeResult = _contextGL.makeCurrent();
		assert(_makeResult);
		_event.set();
		return _makeResult;
	}

	bool lifeiWinApp_2::onRun()
	{
		while (_threadRun)
		{
			render();
		}
		return false;
	}

	bool lifeiWinApp_2::onDestroy()
	{
		_contextGL.shutdown();
		return false;
	}

	LRESULT lifeiWinApp_2::eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch ( message)
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
			_frame->onLButtonUp(LOWORD(lParam), HIWORD(lParam));
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
			HDC hDC = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_SIZE:
		{
			if (IsWindow(_hParentWnd))
			{
				RECT rect;
				GetClientRect(_hParentWnd, &rect);
				_context._width = rect.right - rect.left;
				_context._height = rect.bottom - rect.top;
			}
		}
		break;

		case WM_DESTROY:
		{
			_threadRun = false;
			lifeiThread_2::join();
			PostQuitMessage(0);
		}
		break;

		default:
			break;
		}

		return S_OK;
	}


}
