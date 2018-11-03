// opengl_GIS.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "opengl_GIS.h"
#include "CELLWinApp.hpp"
#include "CELLShpReader.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	CELL::CELLWinApp * app = new CELL::CELLWinApp;
	if (!app->createWindow(800, 600, hInstance))
	{
		delete app;
		return 0;
	}
	app->main(0, 0);
	delete app;

	return 0;

}


