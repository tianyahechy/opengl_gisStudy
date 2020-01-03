#include "CELLGIS3DPlatform.h"
#include "rapidxml.hpp"
namespace CELL
{
	CELLGIS3DPlatform::CELLGIS3DPlatform(const CREATEPARAM& param)
	{
		_createParam = param;
		_tileSource = 0;
		_hTileSourceDll = NULL;
	}

	CELLGIS3DPlatform::~CELLGIS3DPlatform()
	{
	}

	bool CELLGIS3DPlatform::initialize()
	{
		_winApp = new CELLWinApp();
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
		rapidxml::xml_document<> doc;
		FILE* file = fopen(sceneFile, "rt");
		if (0 == file)
		{
			return false;
		}

		fseek(file, 0, SEEK_END);
		size_t nSize = ftell(file);
		fseek(file, 0, SEEK_SET);
		char * pBuf = new char[nSize + 1];
		fread(pBuf, 1, nSize, file);
		pBuf[nSize] = '\0';

		rapidxml::xml_document<> doc;
		try
		{
			do
			{
				doc.parse<0>(pBuf);
				rapidxml::xml_node<> * pRoot = doc.first_node();
				rapidxml::xml_node<> * pImageSource = pRoot->first_node();
				if ( 0 == pImageSource)
				{
					break;
				}
				rapidxml::xml_attribute<>* pDll = pImageSource->first_attribute("loader");
				if ( 0 == pDll)
				{
					break;
				}
				_tileSource = createTileSource(pDll->value());
				if ( 0 == _tileSource)
				{
					break;
				}
				rapidxml::xml_attribute<>* pAttr = pImageSource->first_attribute();
				for (; pAttr; pAttr = pAttr->next_attribute())
				{
					_tileSource->setParam(pAttr->name(), pAttr->value());
				}

			} while (false);
		}
		catch (...)
		{

		}
		delete[] pBuf;
		return false;
	}

	IPluginTileSource * CELLGIS3DPlatform::createTileSource(const char * dllFileName)
	{
		HMODULE hDll = LoadLibraryA(dllFileName);
		if ( 0 == hDll)
		{
			return NULL;
		}
		CREATETILESOURCEFUNC func = (CREATETILESOURCEFUNC)GetProcAddress(hDll, CREATE_TILESOURCE);
		if ( NULL == func )
		{
			CloseHandle(hDll);
			return NULL;
		}
		_hTileSourceDll = hDll;
		return func(this);
	}

	IGIS3DPlatform * createPlatform(const CREATEPARAM& param)
	{
		return new CELLGIS3DPlatform(param);
	}

}

