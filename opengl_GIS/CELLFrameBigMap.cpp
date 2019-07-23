#include    "stdafx.h"

#include    "lifeiPlatform.h"
#include    "CELLFrameBigMap.h"
#include    "CELLOpenGL.h"
#include    "CELLContext.hpp"
#include    "CELLResourceMgr.hpp"
#include    "CELLProgramLibary.hpp"


namespace CELL
{

    CELLFrameBigMap::CELLFrameBigMap(CELLContext& context)
        :CELLFrame(context)
        ,_bLbuttonDown(false)
    {
        context._camera.setEye(real3(0,0,-10));
        context._camera.setTarget(real3(0,0,0));
        context._camera.calcDir();

        context._camera.setUp(real3(0,1,0));
        context._camera.setRight(real3(1,0,0));

    }

    CELLFrameBigMap::~CELLFrameBigMap()
    {
    }

    void CELLFrameBigMap::update(CELLContext& )
    {
        _context._device->setViewPort(0,0,_context._width,_context._height);
        _context._screenPrj =   CELL::ortho<real>(0.0f,(real)_context._width,(real)_context._height,0,-1000.0f,1000.0f);

        _context._camera.setViewSize(real2(_context._width,_context._height));

        _context._camera.perspective(45.0,real(_context._width)/real(_context._height),0.1,1000.0);

        _context._camera.update();
        _context._mvp   =   _context._camera._matProj * _context._camera._matView * _context._camera._matWorld ;
        _context._vp    =   _context._camera._matProj * _context._camera._matView;
        
        _context._timePerFrame  =   _timeStamp.getElapsedSecond();
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

    void CELLFrameBigMap::onFrameStart(CELLContext& context)
    {
        context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        context._device->clearColor(0, 0, 0, 1);
        context._device->disableRenderState(GL_CULL_FACE);

        /// 顶点数据
        float3  vPlane[6]   =   
        {
			float3(-10.0f, 3.0f, + 10.0f),
			float3(+10.0f, 3.0f, + 10.0f),
			float3(+10.0f, 3.0f, - 10.0f),

			float3(-10.0f, 3.0f, + 10.0f),
			float3(+10.0f, 3.0f, - 10.0f),
			float3(-10.0f, 3.0f, - 10.0f),
        };

        _aabb.setExtents(real3(-10,-10,2.9),real3(10,10,3.0));

        Rgba    color(255,0,0,255);

        /// 获取shader
        PROGRAM_P3_UC&  prg =   context._resMgr->_PROGRAM_P3_UC;
        prg.begin();
        {
            context._device->setUniformMatrix4fv(prg._mvp,1,false,context._vp.dataPtr());
            context._device->setUniform4f(
                prg._color
                ,color._r/255.0f
                ,color._g/255.0f
                ,color._b/255.0f
                ,color._a/255.0f
                );
            context._device->attributePointer(prg._position,3,GL_FLOAT,GL_FALSE,sizeof(float3),vPlane);

            context._device->drawArrays(GL_TRIANGLES,0,6);
        }
        prg.end();

    }

    void CELLFrameBigMap::onFrameEnd(CELLContext& context)
    {
    }

    void CELLFrameBigMap::onLButtonDown(int x, int y)
    {
        getPointsFromScreen(x,y,_basePoint);
        _bLbuttonDown   =   true;
        _lbuttonDown    =   int2(x,y);
    }

    void CELLFrameBigMap::onLButtonUp(int x, int y)
    {
        _bLbuttonDown   =   false;
    }

    void CELLFrameBigMap::onMouseMove(int x, int y)
    {
        if (!_bLbuttonDown)
        {
            return;
        }
        int2    curPoint(x,y);
        int2    offset  =   curPoint - _lbuttonDown;
        _lbuttonDown    =   curPoint;
        _context._camera.roteteViewYByCenter(offset.x,_basePoint);
		_context._camera.roteteViewXByCenter(offset.y, _basePoint);
    }

    void CELLFrameBigMap::onMouseWheel(int delta)
    {
        double  persent =   1;
        if (delta > 0)
        {
            persent =   0.9;
        }
        else
        {
            persent =   1.1;
        }
        _context._camera.scaleCameraByPos(_basePoint,persent);
    }

    void CELLFrameBigMap::onKeyDown(int key)
    {
        _context._keyState[key] =  1; 
    }

    void CELLFrameBigMap::onKeyUp(int key)
    {
        _context._keyState[key] =   0;
    }

    bool CELLFrameBigMap::getPointsFromScreen(int x, int y, real3& point)
    {
        CELL::Ray   ray     =   _context._camera.createRayFromScreen(x, y);
        real3       vC      =   _aabb.getCenter();
        real        rRadius =   CELL::length(_aabb.getSize()) * 0.5;
        std::pair<bool, real>  res = ray.intersectSphere(vC, rRadius);

        if (res.first)
        {
            point = ray.getPoint(res.second);
            return  true;
        }
        return  false;
    }

}

