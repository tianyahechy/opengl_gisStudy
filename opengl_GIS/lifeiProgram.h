#pragma once
#include "lifeiPlatform.h"
#include "lifeiTexture.h"
#include "lifeiTexture3dID.h"

namespace CELL
{
	class CELLOpenGL;
	class lifeiProgram
	{
	public:
		typedef GLint	attribute;
		typedef GLint	uniform;

	public:
		GLint			_vHandle;
		GLint			_pHandle;
		GLint			_program;
		CELLOpenGL*		_device;

	public:
		lifeiProgram();
		virtual ~lifeiProgram();
		virtual void destroy();
	};

}

