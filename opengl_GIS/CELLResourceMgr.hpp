#pragma once
#include "CELLProgramLibrary.hpp"

namespace CELL
{
	class CELLResourceMgr
	{
	public:
		//针对绘制屏幕二维数据
		Program_p2_uc _program_p2_UC;
	public:
		CELLResourceMgr()
		{

		}
		~CELLResourceMgr()
		{

		}

	public:
		void initialize(CELLOpenGL * device)
		{
			_program_p2_UC.initialize(device);
		}
		void destroy()
		{
			_program_p2_UC.destroy();
		}
	};

}