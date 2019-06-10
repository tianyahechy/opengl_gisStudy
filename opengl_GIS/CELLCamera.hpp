#pragma once

#include    "CELLObject.hpp"
#include    "CELLMath.hpp"

namespace   CELL
{
    /// 左手坐标系
    #define COORD_LH    
    class CELLCamera :public CELLObject
    {
    public:
        enum 
        {
            FLAG_MOV_X  =   1<<0,
            FLAG_MOV_Y  =   1<<1,
            FLAG_MOV_Z  =   1<<2,
            FLAG_ROT_X  =   1<<3,
            FLAG_ROT_Y  =   1<<4,
            FLAG_ROT_Z  =   1<<5,
        };
    public:
        /// 保存操作摄像机的一些状态信息
        unsigned    _flag;
		real3_lf       _eye;
		real3_lf       _target;
		real3_lf       _up;
		real3_lf       _right;
		real3_lf       _dir;
        matrix4r    _matView;
        matrix4r    _matProj;
        matrix4r    _matWorld;
        real2_lf       _viewSize;
		real3_lf       _oldLength;
		real_lf        _speed;
		real_lf        _fovy;
    public:
		CELLCamera(const real3_lf& target = real3_lf(0, 0, 0), const real3_lf& eye = real3_lf(0, 100, 100), const real3_lf& right = real3_lf(1, 0, 0))
        {
            _viewSize   =   real2_lf(256,256);
            _matView    =   CELL::matrix4r(1);
            _matProj    =   CELL::matrix4r(1);
            _matWorld   =   CELL::matrix4r(1);
            _oldLength  =   10;
            _speed      =   10;
            _flag       =   0xFFFFFFFF;
            _target     =   target;
            _eye        =   eye;
            _dir        =   normalize(_target - _eye);
            _right      =   right;
            _up         =   normalize(cross(_right,_dir));
            _fovy       =   45.0f;

        }
        ~CELLCamera()
        {}

        void   calcDir()
        {
            _dir = normalize(_target - _eye);
        }
        void  enable(unsigned state)
        {
            _flag   |=  state;
        }
        void  disable(unsigned state)
        {
            _flag &= ~state;
        }
		real3_lf getEye() const
        { 
            return _eye;
        }
        /**
        *   设置眼睛的位置
        */
		void    setEye(CELL::real3_lf val)
        { 
            _eye    =   val; 
        }
        
		real3_lf getTarget() const
        { 
            return _target;
        }

		void    setTarget(CELL::real3_lf val)
        { 
            _target = val;
        }
		void    setRight(CELL::real3_lf val)
        {
            _right  =   val;
        }
        
		real3_lf getUp() const
        { 
            return _up;
        }
		void    setUp(CELL::real3_lf val)
        {
            _up = val;
        }
		real3_lf  getDir() const
        {
            return  _dir;
        }


		real3_lf  getRight() const
        {
            return  _right;
        }
        void    setViewSize(const real2_lf& viewSize)
        {
            _viewSize   =   viewSize;
        }
		void    setViewSize(real_lf x, real_lf y)
        {
			_viewSize = real2_lf(x, y);
        }

		real2_lf  getViewSize()
        {
            return  _viewSize;
        }
        
        void    setProject(const matrix4r& proj)
        {
            _matProj    =   proj;
        }
        const matrix4r& getProject() const
        {
            return  _matProj;
        }
        const matrix4r&  getView() const
        {
            return  _matView;
        }

        /**
        *   正交投影
        */
		void    ortho(real_lf left, real_lf right, real_lf bottom, real_lf top, real_lf zNear, real_lf zFar)
        {
            _matProj    =   CELL::ortho(left,right,bottom,top,zNear,zFar);
        }
        /**
        *   透视投影
        */
		void    perspective(real_lf fovy, real_lf aspect, real_lf zNear, real_lf zFar)
        {
            _fovy       =   fovy;
			_matProj = CELL::perspective<real_lf>(fovy, aspect, zNear, zFar);
        }

         /**
        *   世界坐标转化为窗口坐标
        */
		bool    project(const real4_lf& world, real4_lf& screen)
        {
            screen  =   (_matProj * _matView * _matWorld) * world;
            if (screen.w == 0.0f)
            {
                return false;
            }
            screen.x    /=  screen.w;
            screen.y    /=  screen.w;
            screen.z    /=  screen.w;

            // map to range 0 - 1
            screen.x    =   screen.x * 0.5f + 0.5f;
            screen.y    =   screen.y * 0.5f + 0.5f;
            screen.z    =   screen.z * 0.5f + 0.5f;

            // map to viewport
            screen.x    =   screen.x * _viewSize.x;
            screen.y    =   _viewSize.y - (screen.y * _viewSize.y);
            return  true;
        }

		bool project_lf(const real4_lf& world, real4_lf& screen)
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
			screen.y = _viewSize.y - (screen.y * _viewSize.y);
			return true;

		}

        /**
        *   世界坐标转化为窗口坐标
        */

		real2_lf WorldToScreen_lf(const real3_lf& world)
		{
			real4_lf worlds(world.x, world.y, world.z, 1);
			real4_lf screens;
			project(worlds, screens);
			return real2_lf(screens.x, screens.y);
		}

		int2_lf WorldToScreenInt_lf(const real3_lf& world)
		{
			real4_lf worlds(world.x, world.y, world.z, 1);
			real4_lf screens;
			project(worlds, screens);
			return int2_lf((int)screens.x, (int)screens.y);
		}
 
        /**
        *   窗口坐标转化为世界坐标
        */
		real3_lf  screenToWorld(const real2_lf& screen)
        {
			real4_lf  screens(screen.x, screen.y, 0, 1);
			real4_lf  world;
            unProject(screens,world);
			return  real3_lf(world.x, world.y, world.z);
        }

		real3_lf  screenToWorld(real_lf x, real_lf y)
        {
			real4_lf  screens(x, y, 0, 1);
			real4_lf  world;
            unProject(screens,world);
			return  real3_lf(world.x, world.y, world.z);
        }


        /**
        *   窗口坐标转化为世界坐标
        */
		bool    unProject(const real4_lf& screen, real4_lf& world)
        {
			real4_lf v;
            v.x =   screen.x;
            v.y =   screen.y;
            v.z =   screen.z;
            v.w =   1.0;

            // map from viewport to 0 - 1
            v.x =   (v.x) /_viewSize.x;
            v.y =   (_viewSize.y - v.y) /_viewSize.y;
            //v.y = (v.y - _viewPort.Y) / _viewPort.Height;

            // map to range -1 to 1
            v.x =   v.x * 2.0f - 1.0f;
            v.y =   v.y * 2.0f - 1.0f;
            v.z =   v.z * 2.0f - 1.0f;

            CELL::matrix4r  inverse = (_matProj * _matView * _matWorld).inverse();

            v   =   v * inverse;
            if (v.w == 0.0f)
            {
                return false;
            }
            world   =   v / v.w;
            return true;
        }

        Ray createRayFromScreen(int x,int y)
        {
			real4_lf  minWorld;
			real4_lf  maxWorld;

			real4_lf  screen(real_lf(x), real_lf(y), 0, 1);
			real4_lf  screen1(real_lf(x), real_lf(y), 1, 1);

            unProject(screen,minWorld);
            unProject(screen1,maxWorld);
            Ray     ray;
			ray.setOrigin(real3_lf(minWorld.x, minWorld.y, minWorld.z));

			real3_lf  dir(maxWorld.x - minWorld.x, maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
            ray.setDirection(normalize(dir));
            return  ray;
        }

        /**
        *  下面的函数的功能是将摄像机的观察方向绕某个方向轴旋转一定的角度
        *  改变目标的位置，观察者的位置不变化
        */
		virtual void    rotateEyeZ(real_lf angle)
        {
            if (!(_flag & FLAG_ROT_Z))
            {
                return;
            }
			real_lf        len(0);
            matrix4r    mat(1);
			mat.rotate(angle, real3_lf(0, 0, 1));
            _dir    =   _dir * mat;
            _up     =   _up * mat;
            _right  =   CELL::normalize(cross(_dir, _up));
            len     =   CELL::length(_eye - _target);
            _target =   _eye + _dir * len;
            update();
        }

        /**
        *   下面的函数的功能是将摄像机的观察方向绕某个方向轴旋转一定的角度 
        *   改变观察者的位置，目标的位置不变化
        */
		virtual void    rotateViewY(real_lf angle)
        { 
            if (!(_flag & FLAG_ROT_Y))
            {
                return;
            }
			real_lf        len(0);
            matrix4r    mat(1);
			mat.rotate(angle, real3_lf(0, 1, 0));
            _dir        =   _dir * mat;
            _up         =   _up * mat;
            _right      =   CELL::normalize(cross(_dir, _up));
            len         =   CELL::length(_eye - _target);
            _eye        =   _target - _dir * len;
            update();
        }
		virtual void    rotateViewX(real_lf angle)
        { 
            if (!(_flag & FLAG_ROT_X))
            {
                return;
            }
			real_lf        len(0);
            matrix4r    mat(1);
            mat.rotate(angle,_right);
            _dir        =   _dir * mat;
            _up         =   _up * mat;
            _right      =   CELL::normalize(cross(_dir,_up));
            len         =   CELL::length(_eye - _target);
            _eye        =   _target - _dir * len;
            update();
        }

		virtual void    rotateViewXByCenter(real_lf angle, real3_lf  pos)
        {
            if (!(_flag & FLAG_ROT_X))
            {
                return;
            }
            //! 计算眼睛到鼠标点的方向
			real3_lf   vDir = pos - _eye;
			real_lf    len1 = length(vDir);
			real_lf    len = 0;
            vDir    =   normalize(vDir);
            matrix4r mat(1);
            mat.rotate(angle, _right);

            vDir    =   vDir * mat;
            _eye    =   pos - vDir * len1;

            _dir    =   _dir * mat;
            _up     =   _up * mat;
#ifndef COORD_LH
            _right  =   CELL::normalize(cross(_dir,_up));
            _up     =   CELL::normalize(cross(_right,_dir));
#else
            _right  =   CELL::normalize(cross(_up,_dir));
            _up     =   CELL::normalize(cross(_dir,_right));
#endif
            len     =   CELL::length(_eye - _target);

            _target     =   _eye + _dir * len;
            update();

        }

		virtual void    rotateViewYByCenter(real_lf angle, real3_lf  pos)
        {
            if (!(_flag & FLAG_ROT_Y))
            {
                return;
            }
			real_lf        len(0);
			real_lf        len1(0);
            matrix4r    mat(1);
			mat.rotate(angle, real3_lf(0, 1, 0));

			real3_lf   vDir = pos - _eye;

            len1    =   CELL::length(vDir);
            vDir    =   CELL::normalize(vDir);
            vDir    =   vDir * mat;
            _eye    =   pos - vDir * len1;

            _dir    =   _dir * mat;
            _up     =   _up * mat;
#ifndef COORD_LH
            _right  =   CELL::normalize(cross(_dir,_up));
            _up     =   CELL::normalize(cross(_right,_dir));
#else
            _right  =   CELL::normalize(cross(_up,_dir));
            _up     =   CELL::normalize(cross(_dir,_right));
#endif
            len     =   CELL::length(_eye - _target);
            _target =   _eye + _dir * len;
            update();
        }


		virtual void    rotateViewZByCenter(real_lf angle, real3_lf  pos)
        {
            if (!(_flag & FLAG_ROT_Z))
            {
                return;
            }
			real_lf        len(0);
			real_lf        len1(0);
            matrix4r    mat(1);
			mat.rotate(angle, real3_lf(0, 0, 1));

			real3_lf   vDir = pos - _eye;

            len1    =   CELL::length(vDir);
            vDir    =   CELL::normalize(vDir);
            vDir    =   vDir * mat;
            _eye    =   pos - vDir * len1;

            _dir    =   _dir * mat;
            _up     =   _up * mat;
#ifndef COORD_LH
            _right  =   CELL::normalize(cross(_dir,_up));
            _up     =   CELL::normalize(cross(_right,_dir));
#else
            _right  =   CELL::normalize(cross(_up,_dir));
            _up     =   CELL::normalize(cross(_dir,_right));
#endif
            len     =   CELL::length(_eye - _target);
            _target =   _eye + _dir * len;
            update();
        }

		virtual void rotateViewByAxis(real_lf angle, const real3_lf& axis)
        {
			real_lf        len(0);
			real_lf        len1(0);
            matrix4r    mat(1);
            mat.rotate(angle, axis);

			real3_lf   vDir = _target - _eye;

            len1 = CELL::length(vDir);
            vDir = CELL::normalize(vDir);
            vDir = vDir * mat;
            _eye = _target - vDir * len1;

            _dir    =   _dir * mat;
            _up     =   _up * mat;
#ifndef COORD_LH
            _right  =   CELL::normalize(cross(_dir,_up));
            _up     =   CELL::normalize(cross(_right,_dir));
#else
            _right  =   CELL::normalize(cross(_up,_dir));
            _up     =   CELL::normalize(cross(_dir,_right));
#endif
            len     =   CELL::length(_eye - _target);
            _target =   _eye + _dir * len;
            update();
        }

        /**
         *	指定点推进摄像机
         */
		virtual void    scaleCameraByPos(const real3_lf& pos, real_lf persent)
        {

			real3_lf   dir = CELL::normalize(pos - _eye);

			real_lf    dis = CELL::length(pos - _eye) * persent;

			real_lf    disCam = CELL::length(_target - _eye) * persent;

			real3_lf   dirCam = CELL::normalize(_target - _eye);

            _eye    =   pos - dir * dis;
            _target =   _eye + dirCam * disCam;

            update();
        }

        virtual void    update()
        {
#if 0
            _matView    =   CELL::lookAt(_eye,_target,_up);
#else
            _matView    =   CELL::lookAt(_eye,_target,_up);
#endif
        }

		virtual void    moveLeft(real_lf fElapsed)
        {
            _eye     -=  normalize(_right) * _speed * fElapsed;
            _target  -=  normalize(_right) * _speed * fElapsed;
        }

		virtual void    moveRight(real_lf fElapsed)
        {
            _eye     +=  normalize(_right) * _speed * fElapsed;
            _target  +=  normalize(_right) * _speed * fElapsed;
        }


		virtual void    moveFront(real_lf fElapsed)
        {
            _eye    +=  _dir * _speed * fElapsed;
            _target +=  _dir * _speed * fElapsed;
        }

		virtual void    moveBack(real_lf fElapsed)
        {
            _eye    -=  _dir * _speed * fElapsed;
            _target -=  _dir * _speed * fElapsed;
        }
        /**
         *	往上看，则向下移动摄像机
         */
		virtual void   moveUp(real_lf fElapsed)
         {
             _eye       +=  _up * _speed * fElapsed;
             _target    +=  _up * _speed * fElapsed;
         }
         /**
          *	向下看，则摄像机向上移动
          */
		 virtual void   moveDown(real_lf fElapsed)
         {
             _eye       -=  _up * _speed * fElapsed;
             _target    -=  _up * _speed * fElapsed;
         }
         /**
          *	根据给定的方向移动摄像机
          */
		 virtual   void    moveDir(real3_lf dir, real_lf fElapsed)
          {
            _eye    += dir * _speed * fElapsed;
            _target += dir * _speed * fElapsed;
              
          }
    };
}