

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

    void CELLOpenGL::attributePointer( GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr )
    {
        glVertexAttribPointer(indx,size,type,normalized,stride,ptr);
    }

    void CELLOpenGL::setUniform1i( int index,int v0 )
    {
        glUniform1i(index, v0);
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
 
    void CELLOpenGL::drawArrays( GLenum mode, GLint first, GLsizei count )
    {
        glDrawArrays(mode,first,count);
    }

    void CELLOpenGL::disableRenderState( unsigned state )
    {
        glDisable(state);
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

    void CELLProgram::destroy()
    {
        _device->destroyProgram(*this);
    }

}