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

	bool CELLGIS3DPlatform::initialize(HWND hWnd)
	{
		_winApp = new CELLWinApp();
		
		bool bCreateWinAppSuccess = _winApp->createWindow(800, 600, 0);
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

	IGIS3DPlatform * createPlatform(const CREATEPARAM& param)
	{
		return new CELLGIS3DPlatform(param);
	}

}

