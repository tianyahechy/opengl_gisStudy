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
		context._camera.setEye(real3(0, 0, 10));
		context._camera.setTarget(real3(0, 0, 0));
		context._camera.calcDir();
		context._camera.setUp(real3(0, 1, 0));
		context._camera.setRight(real3(1, 0, 0));
	}
	

	CELLFrameBigMap::~CELLFrameBigMap()
	{
	}
	//开始绘制
	void CELLFrameBigMap::onFrameStart(CELLContext& context)
	{
		context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		context._device->clearColor(0, 0, 0, 1);
		context._device->disableRenderState(GL_CULL_FACE);
		//顶点数据
		float3 vLines[6] =
		{
			float3(-0.5, 0.5, 3),
			float3(0.5, 0.5, 3),
			float3(0.5, -0.5, 3),

			float3(-0.5, 0.5, 3),
			float3(0.5, -0.5, 3),
			float3(-0.5, -0.5, 3)
		}; 
		Rgba4Byte color(255, 0, 0, 255);
		//获取shader
		Program_p3_uc& prg = context._resMgr->_program_p3_UC;
		prg.begin();
		{
			context._device->setUniformMatrix4fv(prg._MVP, 1, false, _context._vp.data());
			context._device->setUniform4f(
				prg._color,
				color._r / 255.0,
				color._g / 255.0,
				color._b / 255.0,
				color._a / 255.0
				);
			context._device->attributePointer(prg._position, 3, GL_FLOAT, GL_FALSE, sizeof(float3), vLines);
			context._device->drawArrays(GL_TRIANGLES, 0, 6);
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
		_context._camera.setViewSize(real2(_context._width, _context._height));
		_context._camera.perspective (45.0, real(_context._width) / real(_context._height), 0.1, 1000.0);
		_context._camera.update();
		_context._mvp = _context._camera._matProj * _context._camera._matView * _context._camera._matWorld;
		_context._vp = _context._camera._matProj * _context._camera._matView;
		_context._timePerFrame = _timeStamp.getElapsedSecond();
		_timeStamp.update();

		if (_context._keyState[VK_UP])
		{
			_context._camera.moveFront(_context._timePerFrame);
		} 
		if (_context._keyState[VK_DOWN])
		{
			_context._camera.moveBack(_context._timePerFrame);
		}
		if (_context._keyState[VK_LEFT])
		{
			_context._camera.moveLeft(_context._timePerFrame);
		}
		if (_context._keyState[VK_RIGHT])
		{
			_context._camera.moveRight(_context._timePerFrame);
		}
		
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
	void CELLFrameBigMap::onMouseWheel(int delta)
	{
		double percent = 1;
		if (delta > 0)
		{
			percent = 0.9;
		}
		else
		{
			percent = 1.1;
		}
		_context._camera.scaleCameraByPos(real3(0, 0, 0), percent);
	}
	//键盘事件
	void CELLFrameBigMap::onKeyDown(int key)
	{
		_context._keyState[key] = 1;
	
	}
	//键盘事件
	void CELLFrameBigMap::onKeyUp(int key)
	{
		_context._keyState[key] = 0;
	}
}

