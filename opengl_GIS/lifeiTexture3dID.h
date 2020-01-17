#pragma once
#include "lifeiTexture.h"

namespace CELL
{
	class lifeiTexture3dID : public lifeiTexture
	{
	public:
		unsigned		_width;
		unsigned		_height;
		unsigned		_depth;
	public:
		lifeiTexture3dID()
			:lifeiTexture(TEXTURE_3D)
		{
			_width = 0;
			_height = 0;
			_depth = 0;
		}
		virtual ~lifeiTexture3dID()
		{
		}
	};

}

