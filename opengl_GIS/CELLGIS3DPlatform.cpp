#include "CELLGIS3DPlatform.h"
namespace CELL
{
	CELLGIS3DPlatform::CELLGIS3DPlatform(const CREATEPARAM& param)
	{
		_createParam = param;
	}

	CELLGIS3DPlatform::~CELLGIS3DPlatform()
	{
	}

	bool CELLGIS3DPlatform::initialize()
	{
		_winApp = new CELLWinApp();
		_winApp->_context._app = this;
		bool bCreateWinAppSuccess = _winApp->createWindow(_createParam._hWnd,800, 600, 0);
		if (!bCreateWinAppSuccess)
		{
			delete _winApp;
			_winApp = 0;
			return false;
		}
		_winApp->main(0, 0);
		return true;
	}

	void CELLGIS3DPlatform::unInitialize()
	{
		delete _winApp;
		_winApp = 0;
	}

	LRESULT CELLGIS3DPlatform::inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		if (!_winApp)
		{
			return 0;
		}
		return _winApp->eventProc(hWnd, msgId, wParam, lParam);
		
	}

	bool CELLGIS3DPlatform::loadScene(const char * sceneFile)
	{
		if ( 0 == _winApp || 0 == _winApp->_frame )
		{
			return false;
		}
		return _winApp->_frame->loadScene(sceneFile);
	}

	IGIS3DPlatform * createPlatform(const CREATEPARAM& param)
	{
		return new CELLGIS3DPlatform(param);
	}



}

