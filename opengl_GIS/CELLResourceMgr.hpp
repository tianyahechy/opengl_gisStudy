#pragma once

#include    "CELLProgramLibary.hpp"
#include    "CELLImage.hpp"
#include    "CELLImageLoader.hpp"
#include    <map>
namespace   CELL
{
    class   CELLResourceMgr
    {
    public:
        typedef     std::map<std::string,Texture*>  MapTexture;
    public:
        CELLOpenGL*     _device;
        /// 针对绘制屏幕二维数据
        PROGRAM_P2_UC   _PROGRAM_P2_UC;
        /// PROGRAM_P3_UC
        PROGRAM_P3_UC   _PROGRAM_P3_UC;
        /// 
        MapTexture      _mapTexture;

    public:
        CELLResourceMgr()
            :_device(0)
        {}
        ~CELLResourceMgr()
        {}
    public:
        void    initialize(CELLOpenGL* device)
        {
            _device =   device;
            _PROGRAM_P2_UC.initialize(device);
            _PROGRAM_P3_UC.initialize(device);
        }

        void    destroy()
        {
            _PROGRAM_P2_UC.destroy();
            _PROGRAM_P3_UC.destroy();
        }

        /// 获取纹理资源
        Texture*    getTexture(const char* filePathName)
        {
            MapTexture::iterator itr = _mapTexture.find(filePathName);
            if (itr != _mapTexture.end())
            {
                return  0;
            }
            else
            {
                return  itr->second;
            }
        }
        /// 创建2d纹理方法
        Texture1d*    createTextue1d(const char* pName)
        {
            Texture*    pTex    =   getTexture(pName);
            if (pTex)
            {
                return  dynamic_cast<Texture1d*>(pTex);
            }
            else
            {
                Texture1d*  pTex1d    =   new Texture1d();
                *pTex1d =   createTexture1dFromImage(pName);
                _mapTexture[pName]  =   pTex1d;
                return  pTex1d;
            }
        }
        /// 创建2d纹理方法
        Texture2dId*    createTextue2d(const char* pName)
        {
            Texture*    pTex = getTexture(pName);
            if (pTex)
            {
                return  dynamic_cast<Texture2dId*>(pTex);
            }
            else
            {
                Texture2dId*  pTex1d = new Texture2dId();
                *pTex1d = createTexture2dFromImage(pName);
                _mapTexture[pName] = pTex1d;
                return  pTex1d;
            }
        }
        /// 创建纹理方法
        Texture3dId*    createTextue3d(const char* pId,int w,int h,int d,int fmt)
        {
            Texture*    pTex = getTexture(pId);
            if (pTex)
            {
                return  dynamic_cast<Texture3dId*>(pTex);
            }
            else
            {
                Texture3dId*  pTex1d = new Texture3dId();
                *pTex1d = _device->createTexture2dArray(w,h,d,fmt);
                _mapTexture[pId] = pTex1d;
                return  pTex1d;
            }
        }
    protected:
        Texture1d   createTexture1dFromImage(const char* pathName)
        {
            Texture1d   tex;
            CELLImage   image;

            if(CELLImageLoader::loadImage(pathName,image))
            {
                switch (image._format)
                {
                case CELLImage::FORMAT_RGB8:
                    tex =   _device->createTexture1d(0,GL_RGBA,image._width,0,GL_RGB,GL_UNSIGNED_BYTE,image.data());
                    break;
                case CELLImage::FORMAT_RGBA8:
                    tex =   _device->createTexture1d(0,GL_RGBA,image._width,0,GL_RGBA,GL_UNSIGNED_BYTE,image.data());
                    break;
                default:
                    assert(0!=0);
                }
            }
            return  tex;
        }
        Texture2dId createTexture2dFromImage(const char* pathName)
        {
            Texture2dId tex;
            CELLImage   image;

            if (CELLImageLoader::loadImage(pathName, image))
            {
                switch (image._format)
                {
                case CELLImage::FORMAT_RGB8:
                    tex = _device->createTexure2D(0, GL_RGBA, image._width,image._height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
                    break;
                case CELLImage::FORMAT_RGBA8:
                    tex = _device->createTexure2D(0, GL_RGBA, image._width, image._height,0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
                    break;
                default:
                    assert(0 != 0);
                }
            }
            return  tex;
        }
    };
}
