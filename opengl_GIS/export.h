#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <tchar.h>
#include <Windows.h>

//#include "gl/glew.h"
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#ifdef ENGINE_API_EXP
#define ENGINE_API	__declspec(dllexport)
#else
#define ENGINE_API	__declspec(dllimport)
#endif

#define EXPORTFUNC	__declspec(dllexport)
#define IMPORTFUNC	__declspec(dllimport)



