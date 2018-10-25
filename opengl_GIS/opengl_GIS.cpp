// opengl_GIS.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "opengl_GIS.h"
#include "CELLWinApp.hpp"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	CELL::CELLWinApp app;
	if (!app.createWindow(800, 600, hInstance))
	{
		return 0;
	}
	app.main(0, 0);
	return 0;

}


