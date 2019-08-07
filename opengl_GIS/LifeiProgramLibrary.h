#pragma once

#include <assert.h>
#include "CELLOpenGL.h"

namespace CELL
{
	class PROGRAM_P2_UC : public CELLProgram
	{
	public:
		attribute	_position;
		uniform		_color;
		uniform		_mvp;
	public:
		virtual bool initialize(CELLOpenGL* device)
		{
			const char* vs =
			{
				"#version 330 \n"
				"precision highp float;\n"
				"uniform mat4 _MVP;\n"
				"attribute vec2 _position;\n"
				"void main()\n"
				"{"
				"vec4 pos = vec4(_position.x, _position.y, 0, 1 );\n"
				"gl_Position = _MVP * pos;\n"
				"}"
			};
			const char* ps =
			{
				"#version 330 \n"
				"precision highp float;"
				"uniform vec4 _color;\n"
				"void main()\n"
				"{\n"
				"gl_FragColor = _color;\n"
				"}\n"
			};
			bool result = device->createProgram(*this, vs, ps);
			if (result)
			{
				_position = device->getAttribLocation(_program, "_position");
				_color = device->getUniformLocation(_program, "_color");
				_mvp = device->getUniformLocation(_program, "_MVP");
			}
			else
			{
				assert(result == true);
			}
			return result;
		}
		//使用shader
		virtual void begin()
		{
			_device->useProgram(_program);
			_device->enableVertexAttribArray(_position);
		}
		//结束
		virtual void end()
		{
			_device->disableVertexAttribArray(_position);
			_device->useProgram(0);
		}
	};


	class PROGRAM_P3_UC : public CELLProgram
	{
	public:
		attribute	_position;
		uniform		_color;
		uniform		_mvp;
	public:
		virtual bool initialize(CELLOpenGL* device)
		{
			const char* vs =
			{
				"#version 330 \n"
				"precision highp float;\n"
				"uniform mat4 _MVP;\n"
				"attribute vec3 _position;\n"
				"void main()\n"
				"{"
				"vec4 pos = vec4(_position, 1 );\n"
				"gl_Position = _MVP * pos;\n"
				"}"
			};
			const char* ps =
			{
				"#version 330 \n"
				"precision highp float;"
				"uniform vec4 _color;\n"
				"void main()\n"
				"{\n"
				"gl_FragColor = _color;\n"
				"}\n"
			};
			bool result = device->createProgram(*this, vs, ps);
			if (result)
			{
				_position = device->getAttribLocation(_program, "_position");
				_color = device->getUniformLocation(_program, "_color");
				_mvp = device->getUniformLocation(_program, "_MVP");
			}
			else
			{
				assert(result == true);
			}
			return result;
		}
		//使用shader
		virtual void begin()
		{
			_device->useProgram(_program);
			_device->enableVertexAttribArray(_position);
		}
		//结束
		virtual void end()
		{
			_device->disableVertexAttribArray(_position);
			_device->useProgram(0);
		}
	};

	class PROGRAM_P3_U2 : public CELLProgram
	{
	public:
		attribute	_position;
		attribute	_uv;
		uniform		_texture;
		uniform		_mvp;
	public:
		virtual bool initialize(CELLOpenGL* device)
		{
			const char* vs =
			{
				"#version 330 \n"
				"precision highp float;\n"
				"uniform mat4 _MVP;\n"
				"attribute vec3 _position;\n"
				"attribute vec2 _uv;	\n"
				"varying vec2 _outUV;	\n"
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
				"uniform sampler2D	_texture;\n"
				"varying vec2		_outUV;\n"
				"void main()\n"
				"{\n"
				"gl_FragColor = texture2D(_texture,_outUV);\n"
				"}\n"
			};
			bool result = device->createProgram(*this, vs, ps);
			if (result)
			{
				_position = device->getAttribLocation(_program, "_position");
				_uv = device->getAttribLocation(_program, "_uv");
				_texture = device->getUniformLocation(_program, "_texture");
				_mvp = device->getUniformLocation(_program, "_MVP");
			}
			else
			{
				assert(result == true);
			}
			return result;
		}
		//使用shader
		virtual void begin()
		{
			_device->useProgram(_program);
			_device->enableVertexAttribArray(_position);
			_device->enableVertexAttribArray(_uv);
		}
		//结束
		virtual void end()
		{
			_device->disableVertexAttribArray(_position);
			_device->disableVertexAttribArray(_uv);
			_device->useProgram(0);
		}
	};

	class PROGRAM_P3_U3_TEXARRAY : public CELLProgram
	{
	public:
		attribute	_position;
		attribute	_uv;
		uniform		_texture;
		uniform		_mvp;
	public:
		virtual bool initialize(CELLOpenGL* device)
		{
			const char* vs =
			{
				"#version 330 \n"
				"precision highp float;\n"
				"uniform mat4 _MVP;\n"
				"attribute vec3 _position;\n"
				"attribute vec2 _uv;	\n"
				"attribute vec2 _outUV;	\n"
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
			bool result = device->createProgram(*this, vs, ps);
			if (result)
			{
				_position = device->getAttribLocation(_program, "_position");
				_uv = device->getAttribLocation(_program, "_uv");
				_texture = device->getUniformLocation(_program, "_texture");
				_mvp = device->getUniformLocation(_program, "_MVP");
			}
			else
			{
				assert(result == true);
			}
			return result;
		}
		//使用shader
		virtual void begin()
		{
			_device->useProgram(_program);
			_device->enableVertexAttribArray(_position);
			_device->enableVertexAttribArray(_uv);
		}
		//结束
		virtual void end()
		{
			_device->disableVertexAttribArray(_position);
			_device->disableVertexAttribArray(_uv);
			_device->useProgram(0);
		}
	};

}