#pragma once
#include <stdlib.h>
#include <string.h>
#include "CELLMath.hpp"
#include "CELLObject.h"

namespace CELL
{
	class CELLImage : public CELLObject
	{
	public:
		enum Format
		{
			FORMAT_NONE,
			FORMAT_RGB8,
			FORMAT_RGBA8,
			FORMAT_DXT1,
			FORMAT_DXT5
		};
	public:
		uint _width;
		uint _height;
		Format _format;
		byte * _buffer;
	public:
		CELLImage()
		{
			_width = 0;
			_height = 0;
			_format = FORMAT_NONE;
			_buffer = 0;
		}
		virtual ~CELLImage()
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
			if (_width != w || _height !=h || _format != fmt)
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
		static int calcSize(int w, int h, Format fmt)
		{
			switch (fmt)
			{
			case CELL::CELLImage::FORMAT_NONE:
				break;
			case CELL::CELLImage::FORMAT_RGB8:
				return w * h * 3;
			case CELL::CELLImage::FORMAT_RGBA8:
				return w * h * 4;
			case CELL::CELLImage::FORMAT_DXT1:
				return w * h * 4 / 8;
			case CELL::CELLImage::FORMAT_DXT5:
				return w * h * 4 / 4;
				
			default:
				return 0;
			}
		}
	};
	
	template<int w = 256, int h = 256>
	class CELLImageRgb : public CELLImage
	{
	public:
		unsigned char _data[w*h * 3];
	public:
		CELLImageRgb()
		{
			_width = w;
			_height = h;
			_format = FORMAT_RGB8;
			_buffer = _data;
		}
		virtual ~CELLImageRgb()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

	};
	
	template<int w = 256, int h = 256>
	class CELLImageRgba : public CELLImage
	{
	public:
		unsigned char _data[w*h * 4];
	public:
		CELLImageRgba()
		{
			_width = w;
			_height = h;
			_format = FORMAT_RGBA8;
			_buffer = _data;
		}
		virtual ~CELLImageRgba()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

	};

	template<int w = 256, int h = 256>
	class CELLDXT1 : public CELLImage
	{
	public:
		unsigned char _data[w*h * 4/8];
	public:
		CELLDXT1()
		{
			_width = w;
			_height = h;
			_format = FORMAT_DXT1;
			_buffer = _data;
		}
		virtual ~CELLDXT1()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

	};

	template<int w = 256, int h = 256>
	class CELLDXT5 : public CELLImage
	{
	public:
		unsigned char _data[w*h * 4 / 8];
	public:
		CELLDXT5()
		{
			_width = w;
			_height = h;
			_format = FORMAT_DXT5;
			_buffer = _data;
		}
		virtual ~CELLDXT5()
		{
			_buffer = 0;
		}
		virtual void destroy()
		{

		}

	};

	typedef CELLImageRgba<256, 256>		RgbaBuffer;
	typedef CELLImageRgb<256, 256>		RgbBuffer;
	typedef CELLDXT1<256, 256>			DXT1Buffer;
	typedef CELLDXT5<256, 256>			DXT5Buffer;
}