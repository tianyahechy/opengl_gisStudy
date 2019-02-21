#pragma once
#include "CELLProgramLibrary.hpp"
#include <map>
#include "CELLImage.hpp"
#include "CELLImageLoader.hpp"

namespace CELL
{
	class CELLResourceMgr
	{
	public:
		typedef std::map<std::string, Texture* > mapTexture;
	public:
		CELLOpenGL * _device;
		//针对绘制屏幕二维数据
		Program_p2_uc _program_p2_UC;
		Program_p3_uc _program_p3_UC;
		mapTexture _mapTexture;
	public:
		CELLResourceMgr()
		{
			_device = 0;
		}
		~CELLResourceMgr()
		{

		}

	public:
		void initialize(CELLOpenGL * device)
		{
			_device = device;
			_program_p2_UC.initialize(device);
			_program_p3_UC.initialize(device);
		}
		void destroy()
		{
			_program_p2_UC.destroy();
			_program_p3_UC.destroy();
		}
		//获取纹理资源
		Texture * getTexture(const char* filePathName)
		{
			mapTexture::iterator itr = _mapTexture.find(filePathName);
			if (itr != _mapTexture.end())
			{
				//加载数据，并创建纹理
				//加入系统中
				return 0;
			}
			return itr->second;
		}
		//创建1D纹理方法
		Texture1dId *createTexture1d(const char * pName)
		{
			Texture* pTex = getTexture(pName);
			if (pTex)
			{
				return dynamic_cast<Texture1dId*> (pTex);
			}
			Texture1dId  pTex1D = this->createTexture1dFromImage(pName);
			_mapTexture[pName] = &pTex1D;
			return &pTex1D;
		}
		//创建2D纹理方法
		Texture2dId *createTexture2d(const char * pName)
		{
			Texture* pTex = getTexture(pName);
			if (pTex)
			{
				return dynamic_cast<Texture2dId*> (pTex);
			}
			Texture2dId  pTex2D = this->createTexture2dFromImage(pName);
			_mapTexture[pName] = &pTex2D;
			return &pTex2D;
		}

		//创建3D纹理方法
		Texture3dId *createTexture3d(const char * pID, int w, int h, int d, int fmt)
		{
			Texture* pTex = getTexture(pID);
			if (pTex)
			{
				return dynamic_cast<Texture3dId*> (pTex);
			}
			Texture3dId  pTex3D = _device->createTexture2dArray(w, h, d, fmt);
			_mapTexture[pID] = &pTex3D;
			return &pTex3D;
		}

	protected:
		Texture1dId createTexture1dFromImage(const char* pathName)
		{
			Texture1dId tex;			
			CELL::CELLImage image;
			if (CELLImageLoader::loadImage(pathName, image))
			{
				switch (image._format)
				{
				case CELLImage::FORMAT_RGB8:
					tex = _device->createTexture1d(0, GL_RGBA, image._width, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
					break;
				case CELLImage::FORMAT_RGBA8:
					tex = _device->createTexture1d(0, GL_RGBA, image._width, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
					break;
				default:
					break;
				}
			}
			return tex;
		}
		Texture2dId createTexture2dFromImage(const char* pathName)
		{
			Texture2dId tex;
			CELL::CELLImage image;
			if (CELLImageLoader::loadImage(pathName, image))
			{
				switch (image._format)
				{
				case CELLImage::FORMAT_RGB8:
					tex = _device->createTexure2D(0, GL_RGBA, image._width, image._height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
					break;
				case CELLImage::FORMAT_RGBA8:
					tex = _device->createTexure2D(0, GL_RGBA, image._width, image._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
					break;
				default:
					break;
				}
			}
			return tex;

		}
	};

}