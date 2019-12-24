
#include "lifeiImageLoader.h"
#include "image\stb_image.h"

namespace CELL
{
	lifeiImage * lifeiImageLoader::load(const char * fileName)
	{
		int width = 0;
		int height = 0;
		int chanel = 0;
		stbi_uc* pixels = stbi_load(fileName, &width, &height, &chanel, 0);
		if ( 0 == pixels)
		{
			return 0;
		}
		lifeiImage* pImage = new lifeiImage;
		if ( 3 == chanel)
		{
			pImage->create(width, height, lifeiImage::FORMAT_RGB8, pixels);
		}
		else if ( 4== chanel)
		{
			pImage->create(width, height, lifeiImage::FORMAT_RGBA8, pixels);
		}
		else
		{
			delete pImage;
			pImage = 0;
		}
		stbi_image_free(pixels);
		return pImage;
	
	}

	bool lifeiImageLoader::loadImage(const char* fileName, CELL::lifeiImage& image)
	{
		int width = 0;
		int height = 0;
		int chanel = 0;
		stbi_uc* pixels = stbi_load(fileName, &width, &height, &chanel, 0);
		if (0 == pixels)
		{
			return false;
		}
		if (3 == chanel)
		{
			for (int j = 0, k = width * 3; j < height / 2; j++)
			{
				for (int i = 0; i < width * 3; i++)
				{
					byte a = pixels[j*k + i];
					pixels[j*k + i] = pixels[(height - j - 1) * k + i];
					pixels[(height - j - 1) * k + i] = a;
				}
			}
			image.create(width, height, lifeiImage::FORMAT_RGB8, pixels);
		}
		else if (4 == chanel)
		{
			for (int j = 0, k = width * 4; j < height / 2; j++)
			{
				for (int i = 0; i < width * 4; i++)
				{
					byte a = pixels[j*k + i];
					pixels[j*k + i] = pixels[(height - j - 1) * k + i];
					pixels[(height - j - 1) * k + i] = a;
				}
			}
			image.create(width, height, lifeiImage::FORMAT_RGBA8, pixels);
		}
		else
		{
			stbi_image_free(pixels);
			return false;
		}
		stbi_image_free(pixels);
		return true;

	}

	RgbBuffer* lifeiImageLoader::loadRgb_256X256(const char* fileName)
	{
		int width = 0;
		int height = 0;
		int chanel = 0;
		stbi_uc* pixels = stbi_load(fileName, &width, &height, &chanel, 0);
		if ( 0 == pixels)
		{
			return 0;
		}
		assert(256 == width && 256 == height);
		if (width != 256 || height != 256)
		{
			stbi_image_free(pixels);
			return 0;
		}
		RgbBuffer* pImage = new RgbBuffer;
		if ( 3 == chanel)
		{
			memcpy(pImage->data(), pixels, width * height * 3);
		}
		else if ( 4 == chanel)
		{
			for (int i = 0; i < width * height; i++)
			{
				pImage->_data[i * 4 + 1] = pixels[i * 4 + 0];
				pImage->_data[i * 4 + 2] = pixels[i * 4 + 1];
				pImage->_data[i * 4 + 3] = pixels[i * 4 + 2];
			}
		}
		else
		{
			delete pImage;
			pImage = 0;
		}
		stbi_image_free(pixels);
		return pImage;
	}

	RgbaBuffer* lifeiImageLoader::loadRgba_256X256(const char* fileName)
	{
		int width = 0;
		int height = 0;
		int chanel = 0;
		stbi_uc* pixels = stbi_load(fileName, &width, &height, &chanel, 0);
		if (0 == pixels)
		{
			return 0;
		}
		assert(256 == width && 256 == height);
		if (width != 256 || height != 256)
		{
			stbi_image_free(pixels);
			return 0;
		}
		RgbaBuffer* pImage = new RgbaBuffer;
		if (4 == chanel)
		{
			memcpy(pImage->data(), pixels, width * height * 4);
		}
		else if (3 == chanel)
		{
			for (int i = 0; i < width * height; i++)
			{
				pImage->_data[i * 4 + 1] = pixels[i * 4 + 0];
				pImage->_data[i * 4 + 2] = pixels[i * 4 + 1];
				pImage->_data[i * 4 + 3] = pixels[i * 4 + 2];
				pImage->_data[i * 4 + 3] = 0xFF;
			}
		}
		else
		{
			delete pImage;
			pImage = 0;
		}
		stbi_image_free(pixels);
		return pImage;
	}

	bool lifeiImageLoader::loadImageToRGB(const char* fileName, lifeiImage& image)
	{
		int width = 0;
		int height = 0;
		int chanel = 0;
		stbi_uc* pixels = stbi_load(fileName, &width, &height, &chanel, 0);
		if ( 0 == pixels)
		{
			return false;
		}
		if ( 3 == chanel)
		{
			image.create(width, height, lifeiImage::FORMAT_RGB8, pixels);
		}
		else if (4 == chanel)
		{
			image.create(width, height, lifeiImage::FORMAT_RGB8, 0);
			byte* data = (byte*)image.data();
			for (int i = 0; i < width * height; i++)
			{
				data[i * 3 + 0] = pixels[i * 4 + 0];
				data[i * 3 + 1] = pixels[i * 4 + 1];
				data[i * 3 + 2] = pixels[i * 4 + 2];
			}
		}
		else
		{
			stbi_image_free(pixels);
			return false;
		}
		stbi_image_free(pixels);
		return false;
	}

	bool lifeiImageLoader::loadImageToRGBA(const char* fileName, lifeiImage& image)
	{
		int width = 0;
		int height = 0;
		int chanel = 0;
		stbi_uc* pixels = stbi_load(fileName, &width, &height, &chanel, 0);
		if (0 == pixels)
		{
			return false;
		}
		if (4 == chanel)
		{
			image.create(width, height, lifeiImage::FORMAT_RGBA8, pixels);
		}
		else if (3 == chanel)
		{
			image.create(width, height, lifeiImage::FORMAT_RGBA8, pixels);
			byte* data = (byte*)image.data();
			for (int i = 0; i < width * height; i++)
			{
				data[i * 3 + 0] = pixels[i * 3 + 0];
				data[i * 3 + 1] = pixels[i * 3 + 1];
				data[i * 3 + 2] = pixels[i * 3 + 2];
				data[i * 3 + 3] = 255;
			}
		}
		else
		{
			stbi_image_free(pixels);
			return false;
		}
		stbi_image_free(pixels);
		return false;
	}
	bool lifeiImageLoader::loadImageToDXT1(const char * fileName, lifeiImage & image)
	{
		int width = 0;
		int height = 0;
		int chanel = 0;
		stbi_uc* pixels = stbi_load(fileName, &width, &height, &chanel, 0);
		if (0 == pixels)
		{
			return false;
		}
		stbi_uc data[256 * 256 * 4];
		stbi_uc * pData = data;
		if (4 == chanel)
		{
			pData = pixels;
		}	
		else if (3 == chanel)
		{
		
			for (int i = 0; i < width * height; i++)
			{
				data[i * 4 + 0] = pixels[i * 3 + 0];
				data[i * 4 + 1] = pixels[i * 3 + 1];
				data[i * 4 + 2] = pixels[i * 3 + 2];
				data[i * 4 + 3] = 255;
			}

			for (int j = 0, k = width * 4; j < height / 2; j++)
			{
				for (int i = 0; i < width * 4; i++)
				{
					BYTE a = data[j*k + i];
					data[j*k + i] = data[(height - j - 1) * k + i];
					data[(height - j - 1) * k + i] = a;
				}
			}
		}

		image.create(width, height, lifeiImage::FORMAT_DXT1, 0);
		void * pDst = image.data();
		DXTC::CompressImageDXT1(pData, (BYTE*)pDst, width, height);
	
		stbi_image_free(pixels);
		return true;
	}
}