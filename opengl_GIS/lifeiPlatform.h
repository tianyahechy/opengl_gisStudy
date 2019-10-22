#pragma once

#define CELL_PLATFORM_WIN32			1
#define CELL_PLATFORM_LINUX			2
#define CELL_PLATFORM_APPLE			3
#define CELL_PLATFORM_ANDROID		4

#define CELL_PATH_LENGTH			1024
#define CELL_CALL					__stdcall

#define LIFEI_PLATFORM				CELL_PLATFORM_WIN32

#if LIFEI_PLATFORM	== CELL_PLATFORM_WIN32
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

#elif LIFEI_PLATFORM == CELL_PLATFORM_LINUX || CELL_PLATFORM_ANDROID
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include < X11/X.h>
#include <X11/Xlib.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glx.h>
#include <dlfcn.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>


#ifdef CELLBIGMAP3D_EXPORTS
#define lifei3D_API	
#else
#define lifei3D_API 
#endif

#define HDISPLAY	void*
#define HWINDOW		void*
#define HLIBRARY	void*
#endif