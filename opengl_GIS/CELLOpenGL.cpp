

#include "CELLOpenGL.h"
#include <assert.h>

namespace   CELL
{
    inline void checkError(const char* line )
    {
#ifdef _DEBUG   
        int     err =   glGetError();
        //assert(err == 0);
#endif
    }

    CELLOpenGL::CELLOpenGL()
    {
    }

    CELLOpenGL::~CELLOpenGL()
    {
    }


    void CELLOpenGL::initialize()
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_PROGRAM_POINT_SIZE);
        checkError(__FUNCDNAME__);
    }


    void CELLOpenGL::clearColor( float r,float g,float b,float a )
    {
        glClearColor(r,g,b,a);
        checkError(__FUNCDNAME__);
    }

    void CELLOpenGL::clear( unsigned mask )
    {
        glClear(mask);
        checkError(__FUNCDNAME__);
    }

    void CELLOpenGL::setViewPort( int x,int y,int width,int height )
    {
        glViewport(x,y,width,height);
        checkError(__FUNCDNAME__);
    }


    CELL::Texture1d CELLOpenGL::createTexture1d(
          int level
        , int fmt
        , int width
        , int border
        , int format
        , int type
        , const void* data)
    {
        Texture1d   textureId;
        textureId._width = width;

        glGenTextures(1, &textureId._texture);
        glBindTexture(GL_TEXTURE_1D, textureId._texture);

        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

        if (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
        {
            glCompressedTexImage1D(GL_TEXTURE_1D, level, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, width, 0, width / 4, data);
        }
        else if (format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT)
        {
            glCompressedTexImage1D(GL_TEXTURE_1D, level, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, width, 0, width, data);
        }
        else if (format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT)
        {
            glCompressedTexImage1D(GL_TEXTURE_1D, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width, 0, width , data);
        }
        else
        {
            glTexImage1D(GL_TEXTURE_1D, level, fmt, width, 0, format, GL_UNSIGNED_BYTE, data);
        }
        return  textureId;
    }

    Texture2dId CELLOpenGL::createTextureFromMemory(int level, int fmt, int width, int height, int format, const void *pixels)
    {
        Texture2dId textureId;

        textureId._width    =   width;
        textureId._height   =   height;

        glGenTextures(1,&textureId._texture);
        glBindTexture(GL_TEXTURE_2D,textureId._texture);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

        if (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT)
        {
            glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, width, height, 0, width * height / 4, pixels);
        }
        else if (format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT)
        {
            glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, width, height, 0, width * height , pixels);
        }
        else if (format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT)
        {
            glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width, height, 0, width * height , pixels);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D,level,fmt,width,height,0,format,GL_UNSIGNED_BYTE,pixels);
        }
       
        checkError(__FUNCDNAME__);
        return  textureId;
    }


    void CELLOpenGL::updateTexture2D( int level, int xoffset, int yoffset, int width, int height, int srcFormat, int srcType, const void* data )
    {
        glTexSubImage2D(
            GL_TEXTURE_2D, 
            level,          //! lod级别
            xoffset,        //! x偏移量
            yoffset,        //! y偏移量
            width, 
            height, 
            srcFormat,      
            //! GL_ALPHA
            //! GL_LUMINANCE,
            //! GL_LUMINANCE_ALPHA,
            //! GL_RGB,GL_RGBA,GL_BGR,GL_BGRA,
            //! GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
            //! GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
            //! GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
            srcType,    
            //! GL_UNSIGNED_BYTE
            //! GL_SHORT
            //! GL_UNSIGNED_SHORT
            data
            );
        checkError(__FUNCDNAME__);
    }




    void CELLOpenGL::bindTexture2D( const Texture2dId* textureId,unsigned stage /*= 0*/ )
    {
        if (textureId)
        {
            glActiveTexture(GL_TEXTURE0 + stage);
            glBindTexture(GL_TEXTURE_2D,textureId->_texture);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0 + stage);
            glBindTexture(GL_TEXTURE_2D,0);
        }
        checkError(__FUNCDNAME__);
    }

    void CELLOpenGL::destroyTexture2D( Texture2dId& id )
    {
        glDeleteTextures(1,&id._texture);
        id._texture =   -1;
    }

    Texture3dId CELLOpenGL::createTexture2dArray(int width,int height,int depths,unsigned fmt)
    {
        Texture3dId texId;
        texId._width    =   width;
        texId._height   =   height;
        texId._depth    =   depths;

        glGenTextures(1, &texId._texture);

        char    szBuf[110];
        sprintf(szBuf,"%d",texId._texture);
        //sprintf_s(szBuf,sizeof(szBuf),"%d",texId._texture);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texId._texture);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexStorage3D(
            GL_TEXTURE_2D_ARRAY,
            1,
            fmt, 
            width,
            height, 
            depths); 
        checkError(__FUNCDNAME__);
        return  texId;
    }

    void CELLOpenGL::destroyTexture2dArray( Texture3dId& id )
    {
        glDeleteTextures(1,&id._texture);
        checkError(__FUNCDNAME__);
        id._texture =   -1;
    }

    void CELLOpenGL::updateTexture2dArray( 
                                            int level, 
                                            int xoffset, 
                                            int yoffset, 
                                            int layer,
                                            int width, 
                                            int height, 
                                            int srcFormat, 
                                            int srcType, 
                                            const void* data 
                                            )
    {
        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            level,
            xoffset,
            yoffset,
            layer,
            width,
            height,
            1,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);
        checkError(__FUNCDNAME__);
    }

    void CELLOpenGL::updateCompressTexture2dArray( 
        int level
        , int xoffset
        , int yoffset
        , int layer
        , int width
        , int height
        , int srcFormat
        , int size
        , const void* data 
        )
    {
        glCompressedTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            level,
            xoffset,
            yoffset,
            layer,
            width,
            height,
            1,
            srcFormat,
            size,
            data);
        checkError(__FUNCDNAME__);
    }

    void CELLOpenGL::bindTextureArray( const Texture3dId* textureId,unsigned stage /*= 0*/ )
    {
        if (textureId)
        {
            glActiveTexture(GL_TEXTURE0 + stage);
            glBindTexture(GL_TEXTURE_2D_ARRAY,textureId->_texture);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0 + stage);
            glBindTexture(GL_TEXTURE_2D_ARRAY,0);
        }
        checkError(__FUNCDNAME__);
    }

    void CELLOpenGL::bindTexture3D( const Texture3dId* textureId,unsigned stage /*= 0*/ )
    {
        if (textureId)
        {
            glActiveTexture(GL_TEXTURE0 + stage);
            glBindTexture(GL_TEXTURE_3D,textureId->_texture);
        }
        else
        {
            glActiveTexture(GL_TEXTURE0 + stage);
            glBindTexture(GL_TEXTURE_3D,0);
        }
        checkError(__FUNCDNAME__);
    }

    VertexBufferId CELLOpenGL::createVertexBuffer( unsigned size,unsigned acc,const void* data )
    {
        int     err =   glGetError();
        VertexBufferId  bufferId;
        bufferId._buffserSize   =   size;
        bufferId._accessType    =   acc;
        glGenBuffers(1, &bufferId._bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId._bufferId);
        switch(acc)
        {
        case GL_STREAM_DRAW:
        case GL_STATIC_DRAW: 
        case GL_DYNAMIC_DRAW:
            glBufferData(GL_ARRAY_BUFFER, size, data, acc);
            break;
        default:
            assert("createVertexBuffer error access type" && 0);
            break;
        }
        checkError(__FUNCDNAME__);
        if (err != 0)
        {
            bufferId._bufferId  =   unsigned(-1);
        }
        return  bufferId;
    }
    void CELLOpenGL::setVertexBuffer(unsigned size,unsigned acc,const void* data)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, acc);
    }

    void CELLOpenGL::updateVertexBuffer(unsigned offset,unsigned size,const void* data )
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void CELLOpenGL::bindVertexBuffer( const VertexBufferId* id )
    {
        if (id)
        {
            glBindBuffer(GL_ARRAY_BUFFER, id->_bufferId);
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    void CELLOpenGL::destroyVertexBuffer( VertexBufferId& id )
    {
        if (id._bufferId != unsigned(-1))
        {
            glDeleteBuffers(1,&id._bufferId);
            id._bufferId    =   unsigned(-1);
        }
    }

    IndexBufferId CELLOpenGL::createIndexBuffer( unsigned size,unsigned acc,short type,const void* data )
    {  
        IndexBufferId  bufferId;
        bufferId._buffserSize   =   size;
        bufferId._accessType    =   acc;
        bufferId._elementType   =   type;
        switch(type)
        {
        case GL_UNSIGNED_BYTE:
            bufferId._elementCnt    =   bufferId._buffserSize;
            break;
        case GL_UNSIGNED_SHORT:
            bufferId._elementCnt    =   bufferId._buffserSize/2;
            break;
        case GL_UNSIGNED_INT:
            bufferId._elementCnt    =   bufferId._buffserSize/4;
            break;
        }
        glGenBuffers(1, &bufferId._bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId._bufferId);
        switch(acc)
        {
        case GL_STREAM_DRAW:
        case GL_STATIC_DRAW: 
        case GL_DYNAMIC_DRAW:
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, acc);
            break;
        default:
            assert("createIndexBuffer error access type" && 0);
            break;
        }
        return  bufferId;
    }

    void CELLOpenGL::setIndexBuffer( unsigned size,unsigned acc,const void* data )
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, acc);
    }


    void CELLOpenGL::updateIndexBuffer(unsigned offset,unsigned size,const void* data )
    {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }


    void CELLOpenGL::bindIndexBuffer( const IndexBufferId* id )
    {
        if (id)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id->_bufferId);
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    void CELLOpenGL::destroyIndexBuffer( IndexBufferId& id )
    {
        if (id._bufferId != unsigned(-1))
        {
            glDeleteBuffers(1,&id._bufferId);
            id._bufferId    =   unsigned(-1);
        }
    }

    void CELLOpenGL::bindIndirectBuffer(unsigned bufId)
    {
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, bufId);
    }

    FrameBufferId CELLOpenGL::createFrameBuffer(int width, int height)
    {
        FrameBufferId    targetId;
        targetId._width  =   width;
        targetId._height =   height;

        glGenFramebuffers(1, &targetId._FBOID);
        glBindFramebuffer(GL_FRAMEBUFFER, targetId._FBOID);

        glGenRenderbuffers(1, &targetId._RBOID);
        glBindRenderbuffer(GL_RENDERBUFFER, targetId._RBOID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, targetId._width, targetId._height);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, targetId._RBOID);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return  targetId;
    }


    void CELLOpenGL::destroyFrameBuffer( FrameBufferId& frameBuffer )
    {

        glDeleteFramebuffers(1, &frameBuffer._FBOID);
        glDeleteRenderbuffers(1,&frameBuffer._RBOID);
        frameBuffer._RBOID  =   0;
        frameBuffer._FBOID  =   0;
    }


    void CELLOpenGL::beginFrameBuffer( const FrameBufferId& targetId,const Texture2dId& textureId )
    {
        glBindFramebuffer(GL_FRAMEBUFFER, targetId._FBOID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId._texture, 0);
        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, targetId._RBOID );
    }

    void CELLOpenGL::bindFrameBuffer( const FrameBufferId*targetId )
    {
        if (targetId)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, targetId->_FBOID);
        }
        else
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }

    void CELLOpenGL::endFrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void CELLOpenGL::resizeFrameBuffer( FrameBufferId bufferId,int width,int height )
    {
        glBindRenderbuffer(GL_RENDERBUFFER, bufferId._RBOID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    }

    bool    CELLOpenGL::createProgram( CELLProgram& program,const char* vs,const char* ps )
    {
        bool    result  =   false;

        do 
        {
            //! 创建shader
            program._vHandle    =   glCreateShader(GL_VERTEX_SHADER);
            program._pHandle    =   glCreateShader(GL_FRAGMENT_SHADER);

            //! 指定shader的源代码
            glShaderSource(program._vHandle,1,(const GLchar**)&vs,0);
            glShaderSource(program._pHandle,1,(const GLchar**)&ps,0);

            //! 编译shader
            glCompileShader(program._vHandle);
            GLint   status              =   0;
            char    compileLog[1024]    =   {0};
            glGetShaderiv(program._vHandle,GL_COMPILE_STATUS,&status);
            if (status == GL_FALSE)
            {
                glGetShaderInfoLog(program._vHandle,sizeof(compileLog),0,compileLog);
                assert(false && compileLog);
                break;
            }

            glCompileShader(program._pHandle);

            glGetShaderiv(program._pHandle,GL_COMPILE_STATUS,&status);
            if (status == GL_FALSE)
            {
                glGetShaderInfoLog(program._pHandle,sizeof(compileLog),0,compileLog);
                assert(false && compileLog);
                break;
            }

            //! 4创建程序
            program._program    =   glCreateProgram();
            glAttachShader(program._program,program._vHandle);
            glAttachShader(program._program,program._pHandle);

            //! 5链接程序
            glLinkProgram(program._program);

            glGetProgramiv(program._program,GL_LINK_STATUS,&status);
            if (status == GL_FALSE)
            {
                glGetProgramInfoLog(program._program,sizeof(compileLog),0,compileLog);
                break;
            }
            result  =   true;

        } while (false);

        if (!result)
        {
            if (program._vHandle != -1)
            {
                glDeleteShader(program._vHandle);
            }
            if (program._pHandle != -1)
            {
                glDeleteShader(program._pHandle);
            }
            if (program._program != -1)
            {
                glDeleteProgram(program._program);
            }
            program._vHandle    =   -1;
            program._pHandle    =   -1;
            program._program    =   -1;
        }
        return  result;
    }


    bool CELLOpenGL::createProgram(CELLProgram& program)
    {
        program._program = glCreateProgram();
        return  program._program != 0;
    }

    void CELLOpenGL::destroyProgram(CELLProgram& program)
    {
        if (program._vHandle != -1)
        {
            glDeleteShader(program._vHandle);
        }
        if (program._pHandle != -1)
        {
            glDeleteShader(program._pHandle);
        }
        if (program._program != -1)
        {
            glDeleteProgram(program._program);
        }
        program._vHandle    =   -1;
        program._pHandle    =   -1;
        program._program    =   -1;
    }

    void CELLOpenGL::useProgram( GLint progHandle )
    {
        glUseProgram(progHandle);
    }

    void CELLOpenGL::useProgram( CELLProgram& progam )
    {
        glUseProgram(progam._program);
    }

    GLint CELLOpenGL::getUniformLocation( GLuint program,const char* name )
    {
        return  glGetUniformLocation(program,name);
    }

    GLint CELLOpenGL::getAttribLocation( GLuint program,const char* name )
    {
        return  glGetAttribLocation(program,name);
    }

    void CELLOpenGL::enableVertexAttribArray( GLuint index )
    {
        glEnableVertexAttribArray(index);
    }

    void CELLOpenGL::disableVertexAttribArray( GLuint index )
    {
        glDisableVertexAttribArray(index);
    }


    void CELLOpenGL::vertexAttribDivisor( GLuint index,GLuint divisor )
    {
        glVertexAttribDivisor(index,divisor);
    }

    void CELLOpenGL::attributePointer( GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr )
    {
        glVertexAttribPointer(indx,size,type,normalized,stride,ptr);
    }

    
   
    void CELLOpenGL::setUniform1f( int index,float v0 )
    {
        glUniform1f(index, v0);
    }

    void CELLOpenGL::setUniform2f( int index,float v0, float v1 )
    {
        glUniform2f(index, v0,v1);
    }

    void CELLOpenGL::setUniform2d( int index,double v0, double v1 )
    {
        glUniform2d(index, v0,v1);
    }

    void CELLOpenGL::setUniform3f( int index,float v0, float v1, float v2 )
    {
        glUniform3f(index, v0,v1,v2);
    }

    void CELLOpenGL::setUniform3d( int index,double v0, double v1,double v2  )
    {
        glUniform3d(index, v0,v1,v2);
    }

    void CELLOpenGL::setUniform4f( int index,float v0, float v1, float v2, float v3 )
    {
        glUniform4f(index, v0,v1,v2,v3);
    }
    void CELLOpenGL::setUniform4d(int index, double v0, double v1, double v2, double v3)
    {
        glUniform4d(index, v0, v1, v2, v3);
    }
    
    void CELLOpenGL::setUniform1i( int index,int v0 )
    {
        glUniform1i(index, v0);
    }

    void CELLOpenGL::setUniform2i( int index,int v0, int v1 )
    {
        glUniform2i(index, v0,v1);
    }

    void CELLOpenGL::setUniform3i( int index,int v0, int v1, int v2 )
    {
        glUniform3i(index, v0,v1,v2);
    }

    void CELLOpenGL::setUniform4i( int index,int v0, int v1, int v2, int v3 )
    {
        glUniform4i(index, v0,v1,v2,v3);
    }

    void CELLOpenGL::setUniform1fv( int index,int count, const float *value )
    {
        glUniform1fv(index, count, value);
    }

    void CELLOpenGL::setUniform2fv( int index,int count, const float *value )
    {
        glUniform2fv(index, count, value);
    }

    void CELLOpenGL::setUniform2fv(int index, int count, const double *value)
    {
        glUniform2dv(index, count, value);
    }

    void CELLOpenGL::setUniform3fv(int index, int count, const float *value)
    {
        glUniform3fv(index, count, value);
    }
    void CELLOpenGL::setUniform3fv(int index, int count, const double *value)
    {
        GLfloat     vParam[3]   =  
        {
            (GLfloat)value[0],
            (GLfloat)value[1],
            (GLfloat)value[2]
        };
        glUniform3fv(index, count, vParam);
    }

    void CELLOpenGL::setUniform4fv( int index,int count, const float *value )
    {
        glUniform4fv(index, count, value);
    }

    void CELLOpenGL::setUniform4fv(int index, int count, const double *value)
    {
        glUniform4dv(index, count, value);
    }

    void CELLOpenGL::setUniform1iv(int index, int count, const int *value)
    {
        glUniform1iv(index, count, value);
    }

    void CELLOpenGL::setUniform2iv( int index,int count, const int *value )
    {
        glUniform2iv(index, count, value);
    }

    void CELLOpenGL::setUniform3iv( int index,int count, const int *value )
    {
        glUniform3iv(index, count, value);
    }

    void CELLOpenGL::setUniform4iv( int index,int count, const int *value )
    {
        glUniform4iv(index, count, value);
    }

    void CELLOpenGL::setUniformMatrix2fv( int index,int count, bool transpose, const float *value )
    {
        glUniformMatrix2fv(index, count, (GLboolean) transpose, value);
    }

    void CELLOpenGL::setUniformMatrix2fv(int index, int count, bool transpose, const double *value)
    {
        glUniformMatrix2dv(index, count, (GLboolean) transpose, value);
    }

    void CELLOpenGL::setUniformMatrix3fv(int index, int count, bool transpose, const float *value)
    {
        glUniformMatrix3fv(index, count, (GLboolean) transpose, value);
    }
    void CELLOpenGL::setUniformMatrix3fv(int index, int count, bool transpose, const double *value)
    {
        GLfloat     vParam[9]   =  
        {
            (GLfloat)value[0],
            (GLfloat)value[1],
            (GLfloat)value[2],
            (GLfloat)value[3],
            (GLfloat)value[4],
            (GLfloat)value[5],
            (GLfloat)value[6],
            (GLfloat)value[7],
            (GLfloat)value[8],
        };
        glUniformMatrix3fv(index, count, (GLboolean)transpose, vParam);
    }
    void CELLOpenGL::setUniformMatrix4fv( int index,int count, bool transpose, const float *value )
    {
        glUniformMatrix4fv(index, count, (GLboolean) transpose, value);
    }
    void CELLOpenGL::setUniformMatrix4fv(int index, int count, bool transpose, const double *value)
    {
        GLfloat     vParam[16]   =  
        {
            (GLfloat)value[0],
            (GLfloat)value[1],
            (GLfloat)value[2],
            (GLfloat)value[3],
            (GLfloat)value[4],
            (GLfloat)value[5],
            (GLfloat)value[6],
            (GLfloat)value[7],
            (GLfloat)value[8],
            (GLfloat)value[9],
            (GLfloat)value[10],
            (GLfloat)value[11],
            (GLfloat)value[12],
            (GLfloat)value[13],
            (GLfloat)value[14],
            (GLfloat)value[15],
        };

        glUniformMatrix4fv(index, count, (GLboolean)transpose, vParam);
    }
    void CELLOpenGL::setUniformMatrix4dv(int index, int count, bool transpose, const double *value)
    {
        glUniformMatrix4dv(index, count, (GLboolean)transpose, value);
    }
    void CELLOpenGL::drawArrays( GLenum mode, GLint first, GLsizei count )
    {
        glDrawArrays(mode,first,count);
    }
    void CELLOpenGL::drawElements( unsigned mode, int count,int type,const void* data )
    {
        glDrawElements(mode,count,type,data);
    }

    void CELLOpenGL::drawArraysInstanced( GLenum mode, GLint first, GLsizei count,GLsizei primcount )
    {
        glDrawArraysInstanced( mode, first, count,primcount);
    }

    void CELLOpenGL::drawArraysInstancedBaseInstance( GLenum mode, GLint first, GLsizei count,GLsizei primcount,GLuint baseinstance )
    {
        glDrawArraysInstancedBaseInstance(mode,first,count,primcount,baseinstance);
    }

    void CELLOpenGL::drawElementsInstanced( unsigned mode, int count,int type,const void* data,GLsizei primcount )
    {
        glDrawElementsInstanced(mode,count,type,data,primcount);
    }

    void CELLOpenGL::drawElementsInstancedBaseInstance( unsigned mode, int count,int type,const void* data,GLsizei primcount,GLuint baseinstance )
    {
        glDrawElementsInstancedBaseInstance(mode,count,type,data,primcount,baseinstance);
    }

    void CELLOpenGL::drawlMultiElementsIndirect( GLenum mode, GLenum type, const void *indirect, GLsizei primcount, GLsizei stride )
    {
        glMultiDrawElementsIndirect(mode,type,indirect,primcount,stride);
    }

    void CELLOpenGL::drawMultiArraysIndirect( GLenum mode, const void *indirect, GLsizei primcount, GLsizei stride )
    {
        glMultiDrawArraysIndirect(mode,indirect,primcount,stride);
    }

    void CELLOpenGL::enableRenderState( unsigned state )
    {
        switch (state)
        {
        case GL_TEXTURE1:
        case GL_TEXTURE2:
        case GL_TEXTURE3:
        case GL_TEXTURE4:
        case GL_TEXTURE5:
        case GL_TEXTURE6:
        case GL_TEXTURE7:
            glActiveTexture(state);
            break;
        default:
            glEnable(state);
            break;
        }
    }

    void CELLOpenGL::disableRenderState( unsigned state )
    {
        glDisable(state);
    }

    void CELLOpenGL::blendFunction( unsigned sfactor, unsigned dfactor )
    {
        glBlendFunc(sfactor,dfactor);
    }

    void CELLOpenGL::cullFace( unsigned face )
    {
        glCullFace(face);
    }

    Texture2dId CELLOpenGL::createTexure2D(
        int level,
        int intFmt,
        int width,
        int height,
        int border,
        int srcFmt,
        int type,
        const void* data
        )
    {
        Texture2dId textureId;
        textureId._width    =   width;
        textureId._height   =   height;
        glGenTextures(1,&textureId._texture);
        glBindTexture( GL_TEXTURE_2D, textureId._texture );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

        glTexImage2D(
            GL_TEXTURE_2D, 
            level, 
            intFmt,
            width, 
            height,
            border, 
            srcFmt , 
            type,
            data
            );
        return  textureId;
    }

    CELL::Texture2dId CELLOpenGL::createCompressTexure2D( 
                  int level
                , int intFmt
                , int width
                , int height
                , int border
                , int size
                , const void* data 
                )
    {
        Texture2dId textureId;
        textureId._width    =   width;
        textureId._height   =   height;
        glGenTextures(1,&textureId._texture);
        glBindTexture( GL_TEXTURE_2D, textureId._texture );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);


        //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
        //GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        //GL_COMPRESSED_RGBA_S3TC_DXT5_EXT

        glCompressedTexImage2D(
            GL_TEXTURE_2D
            ,level
            ,intFmt 
            ,width
            ,height
            ,border
            ,size
            ,data
            );
        return  textureId;
    }

    void CELLOpenGL::updateCompressedTexSubImage2D( 
                                      GLint level 
                                    , GLint xoffset 
                                    , GLint yoffset 
                                    , GLsizei width 
                                    , GLsizei height 
                                    , GLenum format 
                                    , GLsizei imageSize 
                                    , const GLvoid* data 
                                    )
    {
        glCompressedTexSubImage2D(GL_TEXTURE_2D,level,xoffset,yoffset,width,height,format,imageSize,data);
    }


    CELLProgram::CELLProgram()
    {
        _device     =   0;
        _vHandle    =   -1;
        _pHandle    =   -1;
        _program    =   -1;
    }

    CELLProgram::~CELLProgram()
    {
        _device->destroyProgram(*this);
    }

    bool CELLProgram::initialize( CELLOpenGL* device )
    {
        _device     =   device;
      
        return  false;
    }

    void CELLProgram::destroy()
    {
        _device->destroyProgram(*this);
    }

    void CELLProgram::begin()
    {
        _device->useProgram(_program);
    }

    void CELLProgram::end()
    {
        _device->useProgram(0);
    }



    GLuint  CELLProgram::createShader( const char* source,int type )
    {
        /// 创建shader
        GLuint  shader  =   0;
        switch(type)
        {
        case CELLProgram::SHADER_VERTEX:
            shader  =   glCreateShader(GL_VERTEX_SHADER);
            break;
        case CELLProgram::SHADER_FRAGMENT:
            shader  =   glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case CELLProgram::SHADER_TES:
            shader  =   glCreateShader(GL_TESS_EVALUATION_SHADER);
            break;
        case CELLProgram::SHADER_TCS:
            shader  =   glCreateShader(GL_TESS_CONTROL_SHADER);
            break;
        case CELLProgram::SHADER_GEM:
            shader  =   glCreateShader(GL_GEOMETRY_SHADER);
            break;
        case CELLProgram::SHADER_COMPUTE:
            shader  =   glCreateShader(GL_COMPUTE_SHADER);
            break;
        default:
            shader  =   0;
            break;
        }
        if (shader == 0)
        {
            return  0;
        }
        /// shader source
        glShaderSource(shader,1,(const GLchar**)&source,0);
        /// compile shader
        glCompileShader(shader);
        GLint   status              =   0;
        char    compileLog[4096]    =   {0};
        glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
        if (status == GL_FALSE)
        {
            glGetShaderInfoLog(shader,sizeof(compileLog),0,compileLog);
            assert(false && compileLog);
            glDeleteShader(shader);
            return  0;
        }
        return  shader;
    }

    bool CELLProgram::attachShader( GLuint shader )
    {
        glAttachShader(_program,shader);
        return  true;
    }

    bool CELLProgram::linkProgram()
    {
        GLint   status              =   0;
        char    compileLog[4096]    =   {0};
        glLinkProgram(_program);
        glGetProgramiv(_program,GL_LINK_STATUS,&status);
        if (status == GL_FALSE)
        {
            glGetProgramInfoLog(_program,sizeof(compileLog),0,compileLog);
            return  false;
        }
        return  true;
    }

    /// <summary>
    /// 根据名称获取uniform
    /// </summary>
    GLuint     CELLProgram::getUniform(const char* name)
    {
        return  CELLOpenGL::getUniformLocation(_program,name);
    }
    /// <summary>
    /// 根据名称获取uniform
    /// </summary>
    GLuint     CELLProgram::getAttribute(const char* name)
    {
        return  CELLOpenGL::getAttribLocation(_program,name);
    }
}