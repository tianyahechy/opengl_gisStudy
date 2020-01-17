#pragma once

#include "lifeiPlatform.h"
#include "lifeiTexture.h"
#include "lifeiTexture3dID.h"

namespace   CELL
{ 
    class   CELLOpenGL;
    
    class   CELLProgram
    {
		
    public:
        typedef GLint   attribute;
        typedef GLint   uniform;

    public:
        GLint       _vHandle;
        GLint       _pHandle;
        GLint       _program;
        CELLOpenGL* _device;
    public:
        CELLProgram();
        virtual ~CELLProgram();
   
        virtual void    destroy();
 
    };

    class   CELLContext;

    class   CELLOpenGL
    {
    public:
        CELLOpenGL();
        virtual ~CELLOpenGL();

        static  void        initialize();
        /**
        *   清空函数
        */
        static  void        clearColor(float r,float g,float b,float a);
        /**
        *   mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
        */
        static  void        clear(unsigned mask);

        static  void        setViewPort(int x,int y,int width,int height);

        static  lifeiTexture3dID createTexture2dArray(int width,int height,int layers,unsigned fmt);

        static  void    updateCompressTexture2dArray(   int level,
                                                        int xoffset,
                                                        int yoffset,
                                                        int layer,
                                                        int width,
                                                        int height,
                                                        int srcFormat,
                                                        int size,
                                                        const void* data
                                                        );

        static  void    bindTextureArray(const lifeiTexture3dID* textureId,unsigned stage = 0);

        static  bool    createProgram(CELLProgram& program,const char* vs,const char* ps);

        /**
        *   销毁
        */
        static  void    destroyProgram(CELLProgram& program);
        /**
        *   使用程序
        */
        static  void    useProgram(GLint progHandle);

        static  void    useProgram(CELLProgram& progam);

        static  GLint   getUniformLocation(GLuint program,const char* name);
        static  GLint   getAttribLocation(GLuint program,const char* name);

        static  void    enableVertexAttribArray(GLuint index);
        static  void    disableVertexAttribArray(GLuint index);
        
        static  void    attributePointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
        static void     setUniform1i(int index,int v0);

        // Arrays
        static void     setUniformMatrix4fv(int index, int count, bool transpose, const double *value);
        static  void    drawArrays(GLenum mode, GLint first, GLsizei count);
        static void     disableRenderState(unsigned state);

    };
}