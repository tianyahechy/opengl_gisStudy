#include "lifeiGIS3DPlatform.h"
#include "IGISPlatform.h"
#include "lifeiWinApp.h"

namespace CELL
{
	lifeiGIS3DPlatform::lifeiGIS3DPlatform(const CREATEPARAM& param)
	{
		_createParam = param;
	}

	lifeiGIS3DPlatform::~lifeiGIS3DPlatform()
	{

	}

	bool lifeiGIS3DPlatform::initialize()
	{
		_winApp = new lifeiWinApp();
		_winApp->_context._app = this;

		bool bCreateWinAppSuccess = _winApp->createWindow(_createParam._hWnd, 800, 600, 0);
		if (!bCreateWinAppSuccess)
		{
			delete _winApp;
			_winApp = 0;
			return false;
		}
		_winApp->main(0, 0);
		return true;
	}

	void lifeiGIS3DPlatform::unInitialize()
	{
		delete _winApp;
		_winApp = 0;
	}

	LRESULT lifeiGIS3DPlatform::inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		if (!_winApp)
		{
			return 0;
		}
		return _winApp->eventProc(hWnd, msgId, wParam, lParam);
	}

	bool lifeiGIS3DPlatform::loadScene(const char* sceneFile)
	{
		if ( 0 == _winApp || 0 == _winApp->_frame)
		{
			return false;
		}
		return _winApp->_frame->loadScene(sceneFile);
	}

	IGISPlatform * createPlatform(const CREATEPARAM& param)
	{
		return new lifeiGIS3DPlatform(param);
	}
}