
#include "lifeiImageLoader.h"
#include "image\stb_image.h"

namespace CELL
{
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
	bool lifeiImageLoader::loadImageBufferToDXT1(const void * imageData, int len, lifeiImage & image)
	{
		int width;
		int height;
		int fmt;
		BYTE * srcData = stbi_load_from_memory((stbi_uc*)imageData, len, &width, &height, &fmt, 0);
		if (4 == fmt)
		{
			BYTE * pixels = (BYTE*)srcData;
			BYTE * data = pixels;

			for (int j = 0, k = width * 4; j < height / 2; j++)
			{
				for (int i = 0; i < width * 4; i++)
				{
					BYTE a = data[j*k + i];
					data[j*k + i] = data[(height - j - 1) * k + i];
					data[(height - j - 1) * k + i] = a;
				}
			}
			image.create(width, height, lifeiImage::FORMAT_DXT1, 0);
			void * pDst = image.data();
			DXTC::CompressImageDXT1(data, (BYTE*)pDst, width, height);
			delete data;
			return true;
		}
		else if (3 == fmt)
		{
			BYTE* pixels = (BYTE*)srcData;
			BYTE* data = new BYTE[width * height * 4];
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
			image.create(width, height, lifeiImage::FORMAT_DXT1, 0);
			void * pDst = image.data();
			DXTC::CompressImageDXT1(data, (BYTE*)pDst, width, height);
			stbi_image_free(srcData);
			delete data;
			return true;
		}

		return false;
	}
}