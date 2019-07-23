
#include "CELLImageLoader.hpp"
#include "image/stb_image.h"

namespace   CELL
{
    CELL::CELLImage* CELLImageLoader::load( const char* fileName )
    {
        int         width   =   0;
        int         height  =   0;
        int         chanel  =   0;
        stbi_uc*    pixels  =   stbi_load(fileName, &width, &height, &chanel, 0);

        if (pixels == 0)
        {
            return  0;
        }

        CELLImage*  pImage  =   new CELLImage;

        if (chanel == 3)
        {
            pImage->create(width,height,CELLImage::FORMAT_RGB8,pixels);
        }
        else if(chanel == 4)
        {
            pImage->create(width,height,CELLImage::FORMAT_RGBA8,pixels);
        }
        else
        {
            delete  pImage;
            pImage  =   0;
        }

        stbi_image_free(pixels);
        return  pImage;
    }

    bool CELLImageLoader::loadImage( const char* fileName,CELL::CELLImage& image )
    {
        int         width   =   0;
        int         height  =   0;
        int         chanel  =   0;
        stbi_uc*    pixels  =   stbi_load(fileName, &width, &height, &chanel, 0);

        if (pixels == 0)
        {
            return  false;
        }

        if (chanel == 3)
        {
            image.create(width,height,CELLImage::FORMAT_RGB8,pixels);
        }
        else if(chanel == 4)
        {
            image.create(width,height,CELLImage::FORMAT_RGBA8,pixels);
        }
        else
        {
            stbi_image_free(pixels);
            return  false;
        }

        stbi_image_free(pixels);

        return  true;
    }


    CELL::RgbBuffer* CELLImageLoader::loadRgb_256X256( const char* fileName )
    {
        int         width   =   0;
        int         height  =   0;
        int         chanel  =   0;
        stbi_uc*    pixels  =   stbi_load(fileName, &width, &height, &chanel, 0);

        if (pixels == 0)
        {
            return  0;
        }

        assert(width == 256 && height == 256);
        if (width != 256 || height != 256)
        {
            stbi_image_free(pixels);
            return  0;
        }
        RgbBuffer* pImage  =   new RgbBuffer;
        if (chanel == 3)
        {
            memcpy(pImage->data(),pixels,width * height * 3);
        }
        else if(chanel == 4)
        {
            for (int i = 0 ;i < width * height ; ++ i)
            {
                pImage->_data[i * 4 + 1] =   pixels[i * 4 + 0];
                pImage->_data[i * 4 + 2] =   pixels[i * 4 + 1];
                pImage->_data[i * 4 + 3] =   pixels[i * 4 + 2];
            }
        }
        else
        {
            delete  pImage;
            pImage  =   0;
        }
        stbi_image_free(pixels);
        return  pImage;
    }

    CELL::RgbaBuffer* CELLImageLoader::loadRgba_256X256( const char* fileName )
    {
        int         width   =   0;
        int         height  =   0;
        int         chanel  =   0;
        stbi_uc*    pixels  =   stbi_load(fileName, &width, &height, &chanel, 0);

        if (pixels == 0)
        {
            return  0;
        }

        assert(width == 256 && height == 256);
        if (width != 256 || height != 256)
        {
            stbi_image_free(pixels);
            return  0;
        }
        RgbaBuffer* pImage  =   new RgbaBuffer;
        if (chanel == 3)
        {
            for (int i = 0 ;i < width * height ; ++ i)
            {
                pImage->_data[i * 4 + 1] =   pixels[i * 3 + 0];
                pImage->_data[i * 4 + 2] =   pixels[i * 3 + 1];
                pImage->_data[i * 4 + 3] =   pixels[i * 3 + 2];
                pImage->_data[i * 4 + 3] =   0xFF;
            }
        }
        else if(chanel == 4)
        {
            memcpy(pImage->data(),pixels,width * height * 4);
        }
        else
        {
            delete  pImage;
            pImage  =   0;
        }
        stbi_image_free(pixels);
        return  pImage;
    }


    bool CELLImageLoader::loadImageToRgb(const char* fileName, CELLImage& image)
    {
        int         width   =   0;
        int         height  =   0;
        int         chanel  =   0;
        stbi_uc*    pixels  =   stbi_load(fileName, &width, &height, &chanel, 0);

        if (pixels == 0)
        {
            return  false;
        }

        if (chanel == 3)
        {
            image.create(width, height, CELLImage::FORMAT_RGB8, pixels);
        }
        else if (chanel == 4)
        {
            image.create(width, height, CELLImage::FORMAT_RGB8, 0);
			byte*   data = (byte*)image.data();
            for (int i = 0 ;i < width * height; ++ i)
            {
                data[i*3 + 0]   =   pixels[i * 4 + 0];
                data[i*3 + 1]   =   pixels[i * 4 + 1];
                data[i*3 + 2]   =   pixels[i * 4 + 2];
            }
        }
        else
        {
            stbi_image_free(pixels);
            return  false;
        }

        stbi_image_free(pixels);
        return  false;
    }

    bool CELLImageLoader::loadImageToRgba(const char* fileName, CELLImage& image)
    {
        int         width   =   0;
        int         height  =   0;
        int         chanel  =   0;
        stbi_uc*    pixels  =   stbi_load(fileName, &width, &height, &chanel, 0);

        if (pixels == 0)
        {
            return  false;
        }

        if (chanel == 3)
        {
            image.create(width, height, CELLImage::FORMAT_RGBA8, pixels);
			byte*   data = (byte*)image.data();
            for (int i = 0; i < width * height; ++i)
            {
                data[i * 3 + 0] =   pixels[i * 3 + 0];
                data[i * 3 + 1] =   pixels[i * 3 + 1];
                data[i * 3 + 2] =   pixels[i * 3 + 2];
                data[i * 3 + 3] =   255;
            }
        }
        else if (chanel == 4)
        {
            image.create(width, height, CELLImage::FORMAT_RGBA8, pixels);
            
        }
        else
        {
            stbi_image_free(pixels);
            return  false;
        }
        stbi_image_free(pixels);
        return  false;
    }

}