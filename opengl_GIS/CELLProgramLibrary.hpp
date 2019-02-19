#pragma once
#include "CELLOpenGL.h"

namespace CELL
{
	//位置属性
	class Program_p2_uc : public CELLProgram
	{
	public:
		attribute	_position;
		//uniform
		uniform		_MVP;
		uniform		_color;

	public:
		Program_p2_uc()
		{
			_position = -1;
			_color = -1;
			_MVP = -1;
		}
		virtual ~Program_p2_uc()
		{

		}
	public:
		//初始化函数
		virtual bool initialize(CELLOpenGL * device)
		{
			_device = device;
			const char* vs =
			{
				"#version 330\n"
				"precision highp float; \n"
				"uniform mat4x4 _MVP;\n"
				"attribute vec2 _position;\n"
				"void main() \n"
				"{"
				" vec4 pos = vec4(_position.x, _position.y, 0,1);\n"
				" gl_Position = _MVP * pos;\n"
				"}"
			};
			const char* ps =
			{
				"#version 330\n"
				"precision highp float; \n"
				"uniform vec4 _color;\n"
				"void main() \n"
				"{\n"
				"gl_FragColor = _color;\n"
				"}\n"
			};
			bool result = device->createProgram(*this, vs, ps);
			if (result)
			{
				_position = device->getAttribLocation(_program, "_position");
				_color = device->getUniformLocation(_program, "_color");
				_MVP = device->getUniformLocation(_program, "_MVP");
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
}