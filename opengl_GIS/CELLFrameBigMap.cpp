#include "stdafx.h"
#include "CELLPlatform.hpp"
#include "CELLFrameBigMap.h"
#include "CELLOpenGL.h"
#include "CELLProgramLibrary.hpp"
#include "CELLResourceMgr.hpp"
#include "CELLContext.h"
#include <string>

namespace CELL
{
	CELLFrameBigMap::CELLFrameBigMap(CELLContext& context)
		:CELLFrame(context)
	{
		Vertex * pData = new Vertex[1000];
		aabb3d aabb3df = calcAabb(&pData->_pos, 1000, sizeof(Vertex));
		delete[] pData;

		context._camera.setEye(real3_lf(0, 0, 10));
		context._camera.setTarget(real3_lf(0, 0, 0));
		context._camera.calcDir();
		context._camera.setUp(real3_lf(0, 1, 0));
		context._camera.setRight(real3_lf(1, 0, 0));
		_rot = 0;
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
		float3 vPlane[6] =
		{
			float3(-0.5f, 0.5f, 3.0f),
			float3(0.5f, 0.5f, 3.0f),
			float3(0.5f, -0.5f, 3.0f),
			float3(-0.5f, 0.5f, 3.0f),
			float3(0.5f, -0.5f, 3.0f),
			float3(-0.5f, -0.5f, 3.0f),
		};
		Rgba4Byte color(255, 0, 0, 255);
		//获取shader
		Program_p2_uc& prg = context._resMgr->_program_p2_UC;
		prg.begin();
		{
			context._device->setUniformMatrix4fv(prg._MVP, 1, false, _context._screenPrj.data());
	
			context._device->setUniform4f(
				prg._color,
				color._r / 255.0,
				color._g / 255.0,
				color._b / 255.0,
				color._a / 255.0
				);
			context._device->attributePointer(prg._position, 3, GL_FLOAT, GL_FALSE, sizeof(float3), vPlane);
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
		_context._screenPrj = CELL::ortho<real_lf>(0.0f, (real_lf)_context._width, (real_lf)_context._height, 0, -1000.0f, 1000.0f);
		_context._camera.setViewSize(real2_lf(_context._width, _context._height));
		_context._camera.perspective(45.0, real_lf(_context._width) / real_lf(_context._height), 0.1, 1000.0);
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

		int2_lf screen = _context._camera.WorldToScreenInt_lf(real3_lf(-0.5, 0.5, 3.0));
		real3_lf world = _context._camera.screenToWorld(screen.x, screen.y);
		std::string strWorldX = std::to_string(world.x);
		std::string strWorldY = std::to_string(world.y);
		std::string strWorldZ = std::to_string(world.z);
		std::string strWorld = strWorldX + "," + strWorldY + "," + strWorldZ + "\n";
		//OutputDebugStringA(strWorld.c_str());
		
	}
	//鼠标左键按下
	void CELLFrameBigMap::onLButtonDown(int x, int y)
	{
		CELL::Ray_lf ray = _context._camera.createRayFromScreen_lf(x, y);
		//顶点数据
		float3 vPlane[6] =
		{
			float3(-0.5f, 0.5f, 3.0f),
			float3(0.5f, 0.5f, 3.0f),
			float3(0.5f, -0.5f, 3.0f),
			float3(-0.5f, 0.5f, 3.0f),
			float3(0.5f, -0.5f, 3.0f),
			float3(-0.5f, -0.5f, 3.0f),
		};

		real_lf t = 0;
		real_lf u = 0;
		real_lf v = 0;
		bool bFlag = CELL::intersectTriangle<real_lf>(
			ray.getOrigin(),
			ray.getDirection(),
			real3_lf(-0.5, 0.5, 3.0f),
			real3_lf(-0.5f, 0.5f, 3.0f),
			real3_lf(-0.5f, 0.5f, 3.0f),
			&t,
			&u,
			&v);
		if (bFlag)
		{
			real3_lf point = ray.getDirection();
			char szBuf[128];
			sprintf(szBuf, "%lf, %lf, %lf\n", point.x, point.y, point.z);
			OutputDebugStringA(szBuf);
		}
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
		//_context._camera.scaleCameraByPos(real3_lf(0, 0, 0), percent);
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

