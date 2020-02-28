#pragma once
#include "LifeiProgramLibrary.h"

namespace CELL
{
	class lifeiShaderManager_2
	{
	public:
		//处理2d纹理数组
		PROGRAM_P3_U3_TEXARRAY _program_P3_U3_TEXTARRAY;

	public:
		lifeiShaderManager_2()
		{
			
		}
		~lifeiShaderManager_2()
		{

		}

	public:
		void initialize(lifeiOpenGL* device)
		{
			_program_P3_U3_TEXTARRAY.initialize(device);
		}
		void destroy()
		{
			_program_P3_U3_TEXTARRAY.destroy();
		}
	};
}
