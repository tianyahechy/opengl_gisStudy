#pragma once

#include <assert.h>
#include "CELLOpenGL.h"

namespace CELL
{
	class PROGRAM_P3_U3_TEXARRAY : public lifeiProgram
	{
	public:
		attribute	_position;
		attribute	_uv;
		uniform		_texture;
		uniform		_mvp;
	public:
		virtual bool initialize(CELLOpenGL* device)
		{
			_device = device;
			if (NULL == _device)
			{
				return false;
			}
			const char* vs =
			{
				"#version 330 \n"
				"precision highp float;\n"
				"uniform mat4 _MVP;\n"
				"attribute vec3 _position;\n"
				"attribute vec3 _uv;	\n"
				"varying vec3 _outUV;	\n"
				"void main()\n"
				"{"
				"vec4 pos = vec4(_position, 1 );\n"
				"_outUV = _uv;\n"
				"gl_Position = _MVP * pos;\n"
				"}"
			};
			const char* ps =
			{
				"#version 330 \n"
				"precision highp float;"
				"uniform sampler2DArray	_texture;\n"
				"varying vec3		_outUV;\n"
				"void main()\n"
				"{\n"
				"gl_FragColor = texture(_texture,_outUV);\n"
				"}\n"
			};
			bool result = _device->createProgram(*this, vs, ps);
			if (result)
			{
				_position = _device->getAttribLocation(_program, "_position");
				_uv = _device->getAttribLocation(_program, "_uv");
				_texture = _device->getUniformLocation(_program, "_texture");
				_mvp = _device->getUniformLocation(_program, "_MVP");
			}
			else
			{
				assert(result == true);
			}
			return result;
		}
		//Ê¹ÓÃshader
		virtual void begin()
		{
			_device->useProgram(_program);
			_device->enableVertexAttribArray(_position);
			_device->enableVertexAttribArray(_uv);
		}
		//½áÊø
		virtual void end()
		{
			_device->disableVertexAttribArray(_position);
			_device->disableVertexAttribArray(_uv);
			_device->useProgram(0);
		}
	};
}