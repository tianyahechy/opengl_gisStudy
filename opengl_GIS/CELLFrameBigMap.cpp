#include "stdafx.h"
#include "CELLPlatform.hpp"
#include "CELLFrameBigMap.h"
#include "CELLOpenGL.h"
#include "CELLProgramLibrary.hpp"
#include "CELLResourceMgr.hpp"
#include "CELLContext.h"

namespace CELL
{
	CELLFrameBigMap::CELLFrameBigMap(CELLContext& context)
		:CELLFrame(context)
	{
	}

	CELLFrameBigMap::~CELLFrameBigMap()
	{
	}
	//开始绘制
	void CELLFrameBigMap::onFrameStart(CELLContext& context)
	{
		context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		context._device->clearColor(0, 0, 0, 1);
		//顶点数据
		float2 vLines[2] =
		{
			float2(0, 0),
			float2(100, 100)
		}; 
		Rgba4Byte color(255, 0, 0, 255);
		//获取shader
		Program_p2_uc& prg = context._resMgr->_program_p2_UC;
		prg.begin();
		{
			context._device->setUniformMatrix4fv(prg._MVP, 1, false, context._screenPrj.data());
			context._device->setUniform4f(
				prg._color,
				color._r / 255.0,
				color._g / 255.0,
				color._b / 255.0,
				color._a / 255.0
				);
			context._device->attributePointer(prg._position, 2, GL_FLOAT, GL_FALSE, sizeof(float2), vLines);
			context._device->drawArrays(GL_LINES, 0, 2);
		}
		prg.end();
		
	}
	//结束绘制
	void CELLFrameBigMap::onFrameEnd(CELLContext& context)
	{

	}
	//更新数据
	void CELLFrameBigMap::update(CELLContext& context)
	{
		_context._device->setViewPort(0, 0, _context._width, _context._height);
		_context._screenPrj = CELL::ortho<real>(0.0f, (real)_context._width, (real)_context._height, 0, -1000.0f, 1000.0f);
	}
	//鼠标左键按下
	void CELLFrameBigMap::onLButtonDown(int x, int y)
	{

	}
	//鼠标左键提起
	void CELLFrameBigMap::onLButtonUp(int x, int y)
	{

	}

	//鼠标移动
	void CELLFrameBigMap::onMouseMove(int x, int y)
	{

	}
}

