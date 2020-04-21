#include "lifeiFrameBigMap_2.h"
#include "lifeiShaderManager_2.h"
#include "lifeiSpatialReference_2.h"

#define FSIZE		20037508

namespace CELL
{
	lifeiFrameBigMap_2::lifeiFrameBigMap_2(lifeiContext_2 & context)
		:lifeiFrame_2(context),
		_bLbuttonDown(false),
		_terrain(_context)

	{
		_bMbuttonDown = false;
		_context._camera.setEye(real3(0, FSIZE * 2, 0));
		_context._camera.setTarget(real3(0, 0, 0));
		_context._camera.calcDir();

		_context._camera.setUp(real3(0, 0, 1));
		_context._camera.setRight(real3(1, 0, 0));
	}

	lifeiFrameBigMap_2::~lifeiFrameBigMap_2()
	{
	}

	bool lifeiFrameBigMap_2::loadScene(const char * fileName)
	{
		return _terrain.loadScene(fileName);
	}

	void lifeiFrameBigMap_2::update(lifeiContext_2 & context)
	{
		_context._device->setViewPort(0, 0, _context._width, _context._height);
		_context._screenPrj = CELL::ortho<real>(0.0f, (real)_context._width, (real)_context._height, 0, -1000.0f, 1000.0f);
		_context._camera.setViewSize(real2(_context._width, _context._height));
		_context._camera.perspective(45.0, real(_context._width) / real(_context._height), 1.0, FSIZE * 10);

		_context._camera.update();
		_context._mvp = _context._camera._matProj * _context._camera._matView * _context._camera._matWorld;
		_context._vp = _context._camera._matProj * _context._camera._matView;

		_context._timePerFrame = _timeStamp.getElapsedSecond();
		_timeStamp.update();
		matrix4r matVP = _context._vp.transpose();
		_context._frustum.loadFrustum_2(matVP);

		if (_context._keyState[VK_UP])
		{
			_context._camera.moveFront_2(_context._timePerFrame);
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

		//���µ���
		_terrain.update(_context);
	}

	void lifeiFrameBigMap_2::onFrameStart(lifeiContext_2 & context)
	{
		_context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_context._device->clearColor(0, 0, 0, 1);
		_context._device->disableRenderState(GL_CULL_FACE);
		_terrain.render(_context);
	}

	void lifeiFrameBigMap_2::onFrameEnd(lifeiContext_2 & context)
	{
	}

	void lifeiFrameBigMap_2::onLButtonUp(int x, int y)
	{
		_bLbuttonDown = false;
	}

	void lifeiFrameBigMap_2::onLButtonDown(int x, int y)
	{
		//getPointsFromScreen(x, y, _basePoint);
		_bLbuttonDown = true;
		_lbuttonDown = int2(x, y);
	}

	void lifeiFrameBigMap_2::onRButtonUp(int x, int y)
	{
	}

	void lifeiFrameBigMap_2::onRButtonDown(int x, int y)
	{
	}

	void lifeiFrameBigMap_2::onMButtonUp(int x, int y)
	{
		_bMbuttonDown = false;
	}

	void lifeiFrameBigMap_2::onMButtonDown(int x, int y)
	{
		_bMbuttonDown = true;
		_mButtonDown = int2(x, y);
	}

	void lifeiFrameBigMap_2::onMouseMove(int x, int y)
	{
		
		if (_bLbuttonDown)
		{
			int2 curPoint(x, y);
			int2 offset = curPoint - _lbuttonDown;
			_lbuttonDown = curPoint;
			_context._camera.roteteViewXByCenter(offset.x, _basePoint);
			_context._camera.roteteViewYByCenter(offset.y, _basePoint);

		}

		if (_bMbuttonDown)
		{
			//�����ƽ��
			int2 ofScreen = int2(x, y) - _mButtonDown;
			_mButtonDown = int2(x, y);
			moveScene(_basePoint, ofScreen);
			
		}
		
	}

	void lifeiFrameBigMap_2::onMouseWheel(int delta)
	{
		double percent = 1.0;
		if (delta > 0)
		{
			percent = 0.9;
		}
		else
		{
			percent = 1.1;
		}
		_context._camera.scaleCameraByPos(_basePoint, percent);
	}

	void lifeiFrameBigMap_2::onKeyDown(int key)
	{
		_context._keyState[key] = 1;
	}

	void lifeiFrameBigMap_2::onKeyUp(int key)
	{
		_context._keyState[key] = 0;
	}

	void lifeiFrameBigMap_2::moveScene(const real3 & worldPickup, const int2 & ofScreen)
	{
		lifeiCamera& camera = _context._camera;
		real3 rightDir(camera._right.x, camera._right.y, camera._right.z);
		real3 upDir(camera._up.x, camera._up.y, camera._up.z);
		real3 pos = real3(worldPickup.x, worldPickup.y, worldPickup.z);
		real3 pos1 = worldPickup + rightDir * 1000.0;
		real2 screen0 = camera.worldToScreen(pos);
		real2 screen1 = camera.worldToScreen(pos1);

		real pixelU = 1000.0 / (screen1.x - screen0.x);
		//���ȼ������һ�����غ͵�ǰ�����ı���
		real3 offset = rightDir * (-pixelU * (real)ofScreen.x);
		offset += upDir * (pixelU * (real)ofScreen.y);

		real3 newEye = camera.getEye() + offset;
		real3 newTgt = camera.getTarget() + offset;

		camera.setEye(newEye);
		camera.setTarget(newTgt);
		camera.update();
	}

	
	bool lifeiFrameBigMap_2::getPointsFromScreen(int x, int y, real3 & point)
	{
		CELL::Ray ray = _context._camera.createRayFromScreen(x, y);
		real t, u, v;
		bool res = CELL::intersectTriangle<real>(
			ray.getOrigin(),
			ray.getDirection(),
			real3(-FSIZE, -3.0f, +FSIZE),
			real3(+FSIZE, -3.0f, +FSIZE),
			real3(+FSIZE, -3.0f, -FSIZE),
			&t, &u, &v
			);

		if (!res)
		{
			res = CELL::intersectTriangle<real>(
				ray.getOrigin(),
				ray.getDirection(),
				real3(-FSIZE, -3.0f, +FSIZE),
				real3(+FSIZE, -3.0f, -FSIZE),
				real3(-FSIZE, -3.0f, -FSIZE),
				&t, &u, &v
				);
		}
		if (res)
		{
			point = ray.getPoint(t);
		}
		return res;
	}
	


}
