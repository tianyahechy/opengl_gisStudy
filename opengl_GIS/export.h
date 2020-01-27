#pragma once

#ifdef ENGINE_API_EXP
#define ENGINE_API	__declspec(dllexport)
#else
#define ENGINE_API	__declspec(dllimport)
#endif

#define EXPORTFUNC	__declspec(dllexport)
#define IMPORTFUNC	__declspec(dllimport)



