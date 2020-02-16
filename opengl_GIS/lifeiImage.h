#pragma once

#include "export.h"
#include <stdlib.h>
#include <string>
#include <assert.h>

#include "lifeiObject_2.h"
#include "lifeiMathUtil.h"

namespace CELL
{
	class EXPORTFUNC lifeiImage : public lifeiObject_2
	{
	public:
		enum Format
		{
			FORMAT_NONE,
			FORMAT_RGB8,
			FORMAT_RGBA8,
			FORMAT_DXT1,
			FORMAT_DXT5,
		};
	public:
		uint	_width;
		uint	_height;
		Format	_format;
		byte*	_buffer;
		
	public:
		lifeiImage()
		{
			_width = 0;
			_height = 0;
			_format = FORMAT_NONE;
			_buffer = 0;
		}
		virtual ~lifeiImage()
		{
			destroy();
		}
		virtual bool isEmpty()
		{
			return _buffer == 0;
		}
		virtual int size()
		{
			return calcSize(_width, _height, _format);
		}
		//释放图形数据
		virtual void destroy()
		{
			if (_buffer)
			{
				delete[] _buffer;
				_buffer = 0;
				_width = 0;
				_height = 0;
				_format = FORMAT_NONE;
			}
		}
		//创建一个图像
		virtual void create(uint w, uint h, Format fmt)
		{
			if (_width != w || _height != h || _format != fmt)
			{
				destroy();
				_width = w;
				_height = h;
				_format = fmt;
				_buffer = new byte[calcSize(w, h, fmt)];
			}
		}
		//创建一个图像
		virtual void create(uint w, uint h, Format fmt, const void* data)
		{
			size_t length = calcSize(w, h, fmt);
			if (_width != w || _height != h || _format != fmt)
			{
				destroy();
				_width = w;
				_height = h;
				_format = fmt;
				_buffer = new byte[calcSize(w, h, fmt)];
			}
			if (_buffer == 0)
			{
				_buffer = new byte[length];
			}
			if (data)
			{
				memcpy(_buffer, data, length);
			}
		}
		//图像数据信息
		virtual void * data()
		{
			return _buffer;
		}

		virtual void detach()
		{
			_buffer = 0;
			_width = 0;
			_height = 0;
		}
	protected:
		//图像数据信息
		static int calcSize(int w, int h, Format fmt)
		{
			switch (fmt)
			{
			case CELL::lifeiImage::FORMAT_RGB8:
				return w * h * 3;
			case CELL::lifeiImage::FORMAT_RGBA8:
				return w * h * 4;
			case CELL::lifeiImage::FORMAT_DXT1:
				return w * h * 4 / 8;
			case CELL::lifeiImage::FORMAT_DXT5:
				return w * h * 4 / 4;
			}
			assert(0 != 0);
			return 0;
		}
	};
	
}