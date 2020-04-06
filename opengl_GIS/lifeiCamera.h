#pragma once

#include "lifeiObject_2.h"
#include "tvec2.h"
#include "tray.h"
#include "cameraMath.h"

namespace CELL
{
	//左手坐标系
#define COORD_LH
	class lifeiCamera : public lifeiObject_2
	{
	public:
		enum
		{
			FLAG_MOV_X = 1 << 0,
			FLAG_MOV_Y = 1 << 1,
			FLAG_MOV_Z = 1 << 2,
			FLAG_ROT_X = 1 << 3,
			FLAG_ROT_Y = 1 << 4,
			FLAG_ROT_Z = 1 << 5,
		};
	public:
		//保存操作摄像机的一些状态信息
		unsigned		_flag;
		real3			_eye;
		real3			_target;
		real3			_up;
		real3			_right;
		real3			_dir;
		matrix4r		_matView;
		matrix4r		_matProj;
		matrix4r		_matWorld;
		real2			_viewSize;
		real3			_oldLength;
		real			_speed;
		real			_fovY;

	public:
		lifeiCamera(const real3& target = real3(0, 0, 0), const real3& eye = real3(0, 100, 100), const real3& right = real3(1, 0, 0))
		{
			_viewSize = real2(256, 256);
			_matView = CELL::matrix4r(1);
			_matProj = CELL::matrix4r(1);
			_matWorld = CELL::matrix4r(1);
			_oldLength = 10;
			_speed = 10;
			_flag = 0xFFFFFFFF;
			_target = target;
			_eye = eye;
			_dir = normalize(_target - _eye);
			_right = right;
			_up = normalize(cross(_right, _dir));
			_fovY = 45.0f;

		}
		~lifeiCamera()
		{

		}

		void calcDir()
		{
			_dir = normalize(_target - _eye);
		}
		void enable(unsigned state)
		{
			_flag |= state;
		}
		void disble(unsigned state)
		{
			_flag &= ~state;
		}

		real3 getEye() const
		{
			return _eye;
		}
		//设置眼睛的位置
		void setEye(CELL::real3 val)
		{
			_eye = val;
		}
		real3 getTarget() const
		{
			return _target;
		}

		void setTarget(CELL::real3 val)
		{
			_target = val;
		}
		void setRight(CELL::real3 val)
		{
			_right = val;
		}

		real3 getUp() const
		{
			return _up;
		}
		void setUp(CELL::real3 val)
		{
			_up = val;
		}
		real3 getDir() const
		{
			return _dir;
		}
		real3 getRight() const
		{
			return _right;
		}

		void setViewSize(const real2& viewSize)
		{
			_viewSize = viewSize;
		}
		void setViewSize(real x, real y)
		{
			_viewSize = real2(x, y);
		}
		real2 getViewSize()
		{
			return _viewSize;
		}

		void setProject(const matrix4r& proj)
		{
			_matProj = proj;
		}
		const matrix4r& getProject() const
		{
			return _matProj;
		}

		const matrix4r& getView() const
		{
			return _matView;
		}
		
		//正交投影
		void ortho(real left, real right, real bottom, real top, real zNear, real zFar)
		{
			_matProj = CELL::ortho(left, right, bottom, top, zNear, zFar);
		}

		//透视投影
		void perspective(real fovY, real aspect, real zNear, real zFar)
		{
			_fovY = fovY;
			_matProj = CELL::perspective<real>(fovY, aspect, zNear, zFar);
		}

		/*
		//世界坐标转化为窗口坐标
		bool project(const real4& world, real4& screen)
		{
			screen = (_matProj * _matView * _matWorld) * world;
			if (screen.w == 0.0f)
			{
				return false;
			}
			screen.x /= screen.w;
			screen.y /= screen.w;
			screen.z /= screen.w;

			//map to range 0-1
			screen.x = screen.x * 0.5f + 0.5f;
			screen.y = screen.y * 0.5f + 0.5f;
			screen.z = screen.z * 0.5f + 0.5f;

			//map to viewport
			screen.x = screen.x * _viewSize.x;
			screen.y = _viewSize.y - screen.y * _viewSize.y;

			return true;
		}
		*/
		//世界坐标转为窗口坐标
		bool project_2(const real4& world, real4& screen)
		{
			screen = (_matProj * _matView * _matWorld) * world;
			if (screen.w == 0.0f)
			{
				return false;
			}
			screen.x /= screen.w;
			screen.y /= screen.w;
			screen.z /= screen.w;

			//将范围到0-1
			screen.x = screen.x * 0.5f + 0.5f;
			screen.y = screen.y  * 0.5f + 0.5f;
			screen.z = screen.z * 0.5f + 0.5f;

			//映射到视口
			screen.x = screen.x * _viewSize.x;
			screen.y = _viewSize.y - screen.y * _viewSize.y;

			return true;
		}

		//世界坐标转化为窗口坐标
		real2 worldToScreen(const real3& world)
		{
			real4 worlds(world.x, world.y, world.z, 1);
			real4 screens;
			project_2(worlds, screens);
			return real2(screens.x, screens.y);
		}
		
		//世界坐标转化为窗口坐标
		int2 worldToScreenInt(const real3& world)
		{
			real4 worlds(world.x, world.y, world.z, 1);
			real4 screens;
			project_2(worlds, screens);
			return int2((int)screens.x, (int)screens.y);
		}
		
		//窗口坐标转化为世界坐标
		bool unProject(const real4& screen, real4& world)
		{
			real4 v;
			v.x = screen.x;
			v.y = screen.y;
			v.z = screen.z;
			v.w = 1.0;

			//map from viewport to 0 - 1
			v.x = v.x / _viewSize.x;
			v.y = (_viewSize.y - v.y) / _viewSize.y;

			//map to range -1 to 1
			v.x = v.x * 2.0 - 1.0f;
			v.y = v.y * 2.0 - 1.0f;
			v.z = v.z * 2.0 - 1.0f;

			CELL::matrix4r inverse = (_matProj * _matView * _matWorld).inverse();

			v = v * inverse;
			if (v.w == 0.0f)
			{
				return false;
			}
			world = v / v.w;
			return true;
		}

		//窗口坐标转为世界坐标
		real3 screenToWorld(const real2& screen)
		{
			real4 screens(screen.x, screen.y, 0, 1);
			real4 world;
			unProject(screens, world);
			return real3(world.x, world.y, world.z);
		}
		//窗口坐标转为世界坐标
		real3 screenToWorld(real x, real y)
		{
			real4 screens(x, y, 0, 1);
			real4 world;
			unProject(screens, world);
			return real3(world.x, world.y, world.z);
		}

		Ray createRayFromScreen(int x, int y)
		{
			real4 minWorld;
			real4 maxWorld;

			real4 screen(real(x), real(y), 0, 1);
			real4 screen1(real(x), real(y), 1, 1);

			unProject(screen, minWorld);
			unProject(screen1, maxWorld);

			Ray ray;
			ray.setOrigin(real3(minWorld.x, minWorld.y, minWorld.z));

			real3 dir(maxWorld.x - minWorld.x, maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
			ray.setDirection(normalize(dir));
			return ray;
		}

		virtual void update()
		{
#if 0
			_matView = CELL::lookAt(_eye, _target, _up);
#else
			_matView = CELL::lookAtL(_eye, _target, _up);
#endif
		}

		//下面的函数的功能是将摄像机的观察方向绕某个方向轴旋转一定的角度，
		//改变目标的位置，观察者的位置
		virtual void roteteEyeZ(real angle)
		{
			if (!(_flag & FLAG_ROT_Z))
			{
				return;
			}
			real		len(0);
			matrix4r	mat(1);
			mat.rotate(angle, real3(0, 0, 1));
			_dir = _dir * mat;
			_up = _up * mat;
			_right = CELL::normalize(cross(_dir, _up));
			len = CELL::length(_eye - _target);
			_target = _eye + _dir * len;
			update();
		}
		virtual void roteteViewY(real angle)
		{
			if (!(_flag & FLAG_ROT_Y))
			{
				return;
			}
			real		len(0);
			matrix4r	mat(1);
			mat.rotate(angle, real3(0, 1, 0));
			_dir = _dir * mat;
			_up = _up * mat;
			_right = CELL::normalize(cross(_dir, _up));
			len = CELL::length(_eye - _target);
			_eye = _target - _dir * len;
			update();
		}
		virtual void roteteViewX(real angle)
		{
			if (!(_flag & FLAG_ROT_X))
			{
				return;
			}
			real		len(0);
			matrix4r	mat(1);
			mat.rotate(angle, _right);
			_dir = _dir * mat;
			_up = _up * mat;
			_right = CELL::normalize(cross(_dir, _up));
			len = CELL::length(_eye - _target);
			_eye = _target - _dir * len;
			update();
		}

		virtual void roteteViewXByCenter(real angle, real3 pos)
		{
			if (!(_flag & FLAG_ROT_X))
			{
				return;
			}
			real3 vDir = pos - _eye;
			real len1 = length(vDir);
			real len = 0;
			vDir = normalize(vDir);
			matrix4r	mat(1);
			mat.rotate(angle, _right);
			vDir = vDir * mat;
			_eye = pos - vDir * len1;
			_dir = _dir * mat;
			_up = _up * mat;
#ifndef COORD_LH
			_right = CELL::normalize(cross(_dir, _up));
			_up = CELL::normalize(cross(_right, _dir));
#else
			_right = CELL::normalize(cross(_up, _dir));
			_up = CELL::normalize(cross(_dir, _right));
#endif
			len = CELL::length(_eye - _target);
			_target = _eye + _dir * len;

			update();
		}

		virtual void roteteViewYByCenter(real angle, real3 pos)
		{
			if (!(_flag & FLAG_ROT_Y))
			{
				return;
			}

			real len(0);
			real len1(0);
			matrix4r	mat(1);
			mat.rotate(angle, real3(0, 1, 0));
			real3 vDir = pos - _eye;
			len1 = CELL::length(vDir);

			vDir = normalize(vDir);
			vDir = vDir * mat;
			_eye = pos - vDir * len1;
			_dir = _dir * mat;
			_up = _up * mat;
#ifndef COORD_LH
			_right = CELL::normalize(cross(_dir, _up));
			_up = CELL::normalize(cross(_right, _dir));
#else
			_right = CELL::normalize(cross(_up, _dir));
			_up = CELL::normalize(cross(_dir, _right));
#endif
			len = CELL::length(_eye - _target);
			_target = _eye + _dir * len;

			update();
		}

		virtual void roteteViewZByCenter(real angle, real3 pos)
		{
			if (!(_flag & FLAG_ROT_Z))
			{
				return;
			}

			real len(0);
			real len1(0);
			matrix4r	mat(1);
			mat.rotate(angle, real3(0, 0, 1));
			real3 vDir = pos - _eye;
			len1 = CELL::length(vDir);
			vDir = normalize(vDir);
			vDir = vDir * mat;
			_eye = pos - vDir * len1;
			_dir = _dir * mat;
			_up = _up * mat;
#ifndef COORD_LH
			_right = CELL::normalize(cross(_dir, _up));
			_up = CELL::normalize(cross(_right, _dir));
#else
			_right = CELL::normalize(cross(_up, _dir));
			_up = CELL::normalize(cross(_dir, _right));
#endif
			len = CELL::length(_eye - _target);
			_target = _eye + _dir * len;

			update();
		}

		virtual void roteteViewByAxis(real angle, const real3& axis)
		{
			real len(0);
			real len1(0);
			matrix4r	mat(1);
			mat.rotate(angle, axis);
			real3 vDir = _target - _eye;
			len1 = CELL::length(vDir);
			vDir = CELL::normalize(vDir);
			vDir = vDir * mat;
			_eye = _target - vDir * len1;
			_dir = _dir * mat;
			_up = _up * mat;
#ifndef COORD_LH
			_right = CELL::normalize(cross(_dir, _up));
			_up = CELL::normalize(cross(_right, _dir));
#else
			_right = CELL::normalize(cross(_up, _dir));
			_up = CELL::normalize(cross(_dir, _right));
#endif
			len = CELL::length(_eye - _target);
			_target = _eye + _dir * len;

			update();
		}
		//指定点推进摄像机
		virtual void scaleCameraByPos(const real3& pos, real percent)
		{
			real3 dir = CELL::normalize(pos - _eye);
			real dis = CELL::length(pos - _eye) * percent;
			real disCam = CELL::length(_target - _eye) * percent;
			real3 dirCam = CELL::normalize(_target - _eye);
			_eye = pos - dir * dis;
			_target = _eye + dirCam * disCam;
			update();
		}
		virtual void moveLeft(real fElapsed)
		{
			_eye -= normalize(_right) * _speed * fElapsed;
			_target -= normalize(_right) * _speed * fElapsed;
		}
		virtual void moveRight(real fElapsed)
		{
			_eye += normalize(_right) * _speed * fElapsed;
			_target += normalize(_right) * _speed * fElapsed;
		}
		/*
		virtual void moveFront(real fElapsed)
		{
			_eye += _dir * _speed * fElapsed;
			_target += _dir * _speed * fElapsed;
		}
		*/
		virtual void moveFront_2(real fElapsed)
		{
			_eye += _dir * _speed * fElapsed;
			_target += _dir * _speed * fElapsed;
		}

		virtual void moveBack(real fElapsed)
		{
			_eye -= _dir * _speed * fElapsed;
			_target -= _dir * _speed * fElapsed;
		}
		//往上看，则向下移动摄像机
		virtual void moveUp(real fElapsed)
		{
			_eye += _dir * _speed * fElapsed;
			_target += _dir * _speed * fElapsed;
		}
		//往下看，则向上移动摄像机
		virtual void moveDown(real fElapsed)
		{
			_eye -= _dir * _speed * fElapsed;
			_target -= _dir * _speed * fElapsed;
		}
		//根据给定的方向移动摄像机
		virtual void moveDir(real3 dir, real fElapsed)
		{
			_eye += dir * _speed * fElapsed;
			_target += dir * _speed * fElapsed;
		}
	};

}