#pragma once
#include "IGIS3DPlatform.h"
#include "CELLWinApp.hpp"

namespace CELL
{
	class CELLGIS3DPlatform : public IGIS3DPlatform
	{
	protected:
		CREATEPARAM _createParam;
		CELLWinApp* _winApp;
	public:
		CELLGIS3DPlatform(const CREATEPARAM& param);
		~CELLGIS3DPlatform();
	public:
		//初始化平台
		virtual bool initialize(HWND hWnd);
		//反向
		virtual void unInitialize();
	};
	IGIS3DPlatform* createPlatform(const CREATEPARAM& param);
}

