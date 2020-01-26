#include "lifeiProgram.h"
#include "lifeiOpengl.h"

namespace CELL
{
	lifeiProgram::lifeiProgram()
	{
		_device	 = 0;
		_vHandle = -1;
		_pHandle = -1;
		_program = -1;

	}

	lifeiProgram::~lifeiProgram()
	{
		_device->destroyProgram(*this);
	}

	void lifeiProgram::destroy()
	{
		_device->destroyProgram(*this);
	}

}
