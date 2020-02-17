#include "lifeiTextureMgr_2.h"

namespace CELL
{
	lifeiTextureMgr_2::lifeiTextureMgr_2(lifeiContext & context)
		: _context(context)
	{
		_textureId = _context._device->createTexture2dArray(256, 256, sizeof(_used), GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE);
		memset(_used, 0, sizeof(_used));
	}

	bool lifeiTextureMgr_2::initialize()
	{
		return true;
	}

	uint lifeiTextureMgr_2::allocTexture()
	{
		for (size_t i = 0; i < sizeof(_used); i++)
		{
			if (!_used[i])
			{
				_used[i] = true;
				return i;
			}
		}
		return -1;
	}

	void lifeiTextureMgr_2::freeTexture(uint index)
	{
		_used[index] = false;
	}

	void lifeiTextureMgr_2::updateTexture(uint index, const void * data)
	{
		_context._device->updateCompressTexture2dArray(0, 0, 0, index, 256, 256, GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE, 256 * 256 * 4 / 8, data);
	}

	uint lifeiTextureMgr_2::getUsedCount()
	{
		uint cnt = 0;
		for (size_t i = 0; i < sizeof(_used); i++)
		{
			if (_used[i])
			{
				++cnt;
			}
		}
		return cnt;
	}

	uint lifeiTextureMgr_2::getFreeCount()
	{
		return sizeof(_used) - getUsedCount();
	}
	
	

}
