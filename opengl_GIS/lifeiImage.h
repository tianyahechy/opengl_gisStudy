#pragma once

#include <stdlib.h>
#include <string>
#include <assert.h>

#include "CELLMath.hpp"
#include "lifeiObject.h"

namespace CELL
{
	class lifeiImage : public lifeiObject
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
	template<int w = 256, int h = 256>
	class lifeiImageRGB : public lifeiImage
	{
	public:
		unsigned char _data[w * h * 3];
	public:
		lifeiImageRGB()
		{
			_width = w;
			_height = h;
			_format = FORMAT_RGB8;
			_buffer = _data;
		}
		virtual ~lifeiImageRGB()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

	};

	template<int w = 256,int h = 256>
	class lifeiImageRGBA : public lifeiImage
	{
	public:
		unsigned char _data[w * h * 4];
	public:
		lifeiImageRGBA()
		{
			_width = w;
			_height = h;
			_format = FORMAT_RGBA8;
			_buffer = _data;
		}
		virtual ~lifeiImageRGBA()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

	};

	template<int w = 256, int h = 256>
	class lifeiDXT1 : public lifeiImage
	{
	public:
		unsigned char _data[w * h * 4 / 8];
	public:
		lifeiDXT1()
		{
			_width = w;
			_height = h;
			_format = FORMAT_DXT1;
			_buffer = _data;
		}
		virtual ~lifeiDXT1()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

		virtual void create(int, int, Format)
		{

		}
		virtual void create(int w, int h, Format, void*)
		{

		}

	};

	template<int w = 256, int h = 256>
	class lifeiDXT5 : public lifeiImage
	{
	public:
		unsigned char _data[w * h * 4 / 8];
	public:
		lifeiDXT5()
		{
			_width = w;
			_height = h;
			_format = FORMAT_DXT5;
			_buffer = _data;
		}
		virtual ~lifeiDXT5()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

		virtual void create(int, int, Format)
		{

		}
		virtual void create(int w, int h, Format, void*)
		{

		}

	};

	typedef lifeiImageRGBA<256, 256>		RgbaBuffer;
	typedef lifeiImageRGB<256, 256>			RgbBuffer;
	typedef lifeiDXT1<256, 256>				DXT1Buffer;
	typedef lifeiDXT5<256, 256>				DXT5Buffer;

}