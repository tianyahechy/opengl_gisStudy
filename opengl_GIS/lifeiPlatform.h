#pragma once

#define CELL_PATH_LENGTH			1024
#define CELL_CALL					__stdcall

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <tchar.h>
#include <Windows.h>

//#include "gl/glew.h"
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#ifdef CELLBIGMAP3D_EXPORTS
#define lifei3D_API	__declspec(dllexport)
#else
#define lifei3D_API __declspec(dllimport)
#endif

#define HDISPLAY	HDC
#define HWINDOW		HWND
#define HLIBRARY	HMODULE
#define INSTANCE	HINSTANCE

typedef const char* STRING;
