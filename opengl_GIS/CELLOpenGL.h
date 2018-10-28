#pragma once

#include    "CELLPlatform.hpp"

namespace   CELL
{ 
    class   CELLOpenGL;

    
    class   Texture
    {
    public:
        enum
        {
            TEXTURE_NONE,
            TEXTURE_1D,
            TEXTURE_2D,
            TEXTURE_3D,
        };
    public:
        unsigned        _texture;
        unsigned        _texType;
    public:
        Texture(unsigned type = TEXTURE_NONE )
            :_texture(0xFFFFFFFF)
            ,_texType(type)
        {}
        virtual ~Texture()
        {}

    };
    class   Texture1d :public Texture
    {
    public:
        unsigned        _width;
    public:
        Texture1d()
            :Texture(TEXTURE_1D)
        {
            _width  =   0;
        }
        virtual~Texture1d()
        {}
    };
    
    class   Texture2dId :public Texture
    {
    public:
        unsigned        _width;
        unsigned        _height;
    public:
        Texture2dId()
            :Texture(TEXTURE_2D)
        {
            _width      =   0;
            _height     =   0;
        }
        virtual ~Texture2dId()
        {}
    };

    class   Texture3dId :public Texture
    {
    public:
        unsigned        _width;
        unsigned        _height;
        unsigned        _depth;
    public:
        Texture3dId()
            :Texture(TEXTURE_3D)
        {
            _width      =   0;
            _height     =   0;
            _depth      =   1;
        }
        virtual~Texture3dId()
        {}
        
    };


    class   CELLProgram
    {
    public:
        typedef GLint   attribute;
        typedef GLint   uniform;
    public:
        enum    ShaderType
        {
            SHADER_NONE         =   0,
            SHADER_VERTEX       =   1,
            SHADER_FRAGMENT     =   2,
            SHADER_TES          =   3,
            SHADER_TCS          =   4,
            SHADER_GEM          =   5,
            SHADER_COMPUTE      =   6,
        };
    public:
        friend  CELLOpenGL;
    public:
        GLint       _vHandle;
        GLint       _pHandle;
        GLint       _program;
        CELLOpenGL* _device;
    public:
        CELLProgram();
        virtual ~CELLProgram();
        /**
        *   初始化
        */
        virtual bool    initialize(CELLOpenGL* device);
        virtual void    destroy();
        /**
        *   使用shader
        */
        virtual void    begin();
        /**
        *   结束
        */
        virtual void    end();
        /**
         *	创建shader函数
         */
        virtual GLuint  createShader(const char* source,int type);
        /**
         *	将shader关联到program
         */
        virtual bool    attachShader(GLuint shader);
        /**
         *	link
         */
        virtual bool    linkProgram();
        /// <summary>
        /// 根据名称获取uniform
        /// </summary>
        virtual GLuint  getUniform(const char* name);
        /// <summary>
        /// 根据名称获取attribute
        /// </summary>
        virtual GLuint  getAttribute(const char* name);
    };

    class   CELLContext;

    class   VertexBufferId
    {
    public:
        VertexBufferId()
        {
            _bufferId   =   unsigned(-1);
            _buffserSize=   0;
            _accessType =   0;
            _user       =   0;
        }
        unsigned    _bufferId;
        unsigned    _buffserSize;
        unsigned    _accessType;
        void*       _user;
    };


    class   IndexBufferId
    {
    public:
        enum    DataType
        {
            DT_UINT8     =   0,
            DT_UINT16    =   1,
            DT_UINT32    =   2,
        };
    public:
        IndexBufferId()
        {
            _bufferId   =   unsigned(-1);
            _buffserSize=   0;
            _accessType =   0;
            _elementType=   0;
            _primitive  =   0;
            _elementCnt =   0;
        }
        unsigned    _bufferId;
        unsigned    _buffserSize;
        unsigned    _accessType;
        unsigned    _elementCnt;
        short       _elementType;
        short       _primitive;
    };

    class   FrameBufferId
    {
    public:
        FrameBufferId()
        {
            _width  =   0;
            _height =   0;
            _FBOID  =   0;
            _RBOID  =   0;
        }
        unsigned    _width;
        unsigned    _height;
        unsigned    _FBOID;
        unsigned    _RBOID;
    };

    class   CELLOpenGL
    {
    public:
        /// 顶点缓冲区
        char        _vertexBuf[1024 * 1024 * 8];
        /// 索引缓冲区
        char        _indexBuf[1024*1024];
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
        /**
        *   创建纹理函数
        */
        /**
        *   创建2D纹理
        */
        static  Texture2dId createTexure2D(
                                            int level,
                                            int intFmt,
                                            int width,
                                            int height,
                                            int border,
                                            int srcFmt,
                                            int type,
                                            const void* data
                                            );

        static  Texture2dId createCompressTexure2D(
                                            int level,
                                            int intFmt,
                                            int width,
                                            int height,
                                            int border,
                                            int size,
                                            const void* data
                                            );

        static  void updateCompressedTexSubImage2D(
              GLint level
            , GLint xoffset
            , GLint yoffset
            , GLsizei width
            , GLsizei height
            , GLenum format
            , GLsizei imageSize
            , const GLvoid* data
            );

        static  Texture2dId createTextureFromMemory(int level, int fmt, int width, int height, int format, const void *pixels);


        static  void        updateTexture2D(
                            int level,
                            int xoffset,
                            int yoffset,
                            int width,
                            int height,
                            int srcFormat,
                            int srcType,
                            const void* data
                            );
        /**
        *   邦定纹理函数
        */
        static  void    bindTexture2D(const Texture2dId* textureId,unsigned stage = 0);
        /**
        *   销毁纹理函数
        */
        static  void    destroyTexture2D(Texture2dId& id);

        static  Texture3dId createTexture2dArray(int width,int height,int layers,unsigned fmt);
        static  void    destroyTexture2dArray(Texture3dId& id);
        static  void    updateTexture2dArray(   int level,
                                                int xoffset,
                                                int yoffset,
                                                int layer,
                                                int width,
                                                int height,
                                                int srcFormat,
                                                int srcType,
                                                const void* data
                                                );

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

        static  void    bindTextureArray(const Texture3dId* textureId,unsigned stage = 0);
        static  void    bindTexture3D(const Texture3dId* textureId,unsigned stage = 0);


        /**
        *   创建顶点缓冲区
        */
        static  VertexBufferId  createVertexBuffer(unsigned size,unsigned acc,const void* data);
        /**
        *   设置数据函数
        */
        static  void            setVertexBuffer(unsigned size,unsigned acc,const void* data);
        /**
        *   跟新数据函数
        */
        static  void            updateVertexBuffer(unsigned offset,unsigned size,const void* data);
        /**
        *   使用缓冲区函数
        */
        static  void            bindVertexBuffer(const VertexBufferId* id);
        /**
        *   销毁缓冲区函数
        */
        static  void            destroyVertexBuffer(VertexBufferId& id);
        /**
        *   创建顶点缓冲区
        */
        static  IndexBufferId   createIndexBuffer(unsigned size,unsigned acc,short type,const void* data);

        static  void            setIndexBuffer(unsigned size,unsigned acc,const void* data);
        static  void            updateIndexBuffer(unsigned offset,unsigned size,const void* data);

        static  void            bindIndexBuffer(const IndexBufferId* id);
        static  void            destroyIndexBuffer(IndexBufferId& id);

        static  void            bindIndirectBuffer(unsigned bufId);
        
        /**
        *   创建一个渲染对象，离屏对象
        */
        static  FrameBufferId   createFrameBuffer(int width,int height);

        static  void        resizeFrameBuffer(FrameBufferId bufferId,int width,int height);
        /**
        *   删除一个渲染对象
        */
        static  void        destroyFrameBuffer(FrameBufferId& frameBuffer);
        /**
        *   将一个纹理与渲染目标绑定，并使用
        */
        static  void        beginFrameBuffer(const FrameBufferId& targetId,const Texture2dId& textureId);
        /**
        *   完成渲染到目标
        *   在beginRenderToTarget 与endRenderToTarget之间添加绘制代码
        */
        static  void        endFrameBuffer();
        /**
        *   使用渲染对象
        */
        static  void        bindFrameBuffer(const FrameBufferId*targetId);

        static  bool    createProgram(CELLProgram& program,const char* vs,const char* ps);

        static  bool    createProgram(CELLProgram& program);
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
        static  void    vertexAttribDivisor(GLuint index,GLuint divisor);
        

        static  void    attributePointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);

        
        static void     setUniform1f(int index,float v0);
        static void     setUniform2f(int index,float v0, float v1);
        static void     setUniform2d(int index,double v0, double v1);
        static void     setUniform3f(int index,float v0, float v1, float v2);
        static void     setUniform3d(int index,double v0, double v1,double v2);
        static void     setUniform4f(int index,float v0, float v1, float v2, float v3);
        static void     setUniform4d(int index, double v0, double v1, double v2, double v3);

        static void     setUniform1i(int index,int v0);
        static void     setUniform2i(int index,int v0, int v1);
        static void     setUniform3i(int index,int v0, int v1, int v2);
        static void     setUniform4i(int index,int v0, int v1, int v2, int v3);

        // Arrays
        static void     setUniform1fv(int index,int count, const float *value);

        static void     setUniform2fv(int index,int count, const float *value);
        static void     setUniform2fv(int index,int count, const double *value);

        static void     setUniform3fv(int index,int count, const float *value);
        static void     setUniform3fv(int index, int count, const double *value);

        static void     setUniform4fv(int index,int count, const float *value);
        static void     setUniform4fv(int index,int count, const double *value);

        static void     setUniform1iv(int index,int count, const int *value);
        static void     setUniform2iv(int index,int count, const int *value);
        static void     setUniform3iv(int index,int count, const int *value);
        static void     setUniform4iv(int index,int count, const int *value);

        static void     setUniformMatrix2fv(int index,int count, bool transpose, const float *value);
        static void     setUniformMatrix2fv(int index,int count, bool transpose, const double *value);
        static void     setUniformMatrix3fv(int index,int count, bool transpose, const float *value);
        static void     setUniformMatrix3fv(int index, int count, bool transpose, const double *value);
        static void     setUniformMatrix4fv(int index,int count, bool transpose, const float *value);
        static void     setUniformMatrix4fv(int index, int count, bool transpose, const double *value);
        static void     setUniformMatrix4dv(int index, int count, bool transpose, const double *value);
     

        static  void    drawArrays(GLenum mode, GLint first, GLsizei count);
        static  void    drawElements(unsigned mode, int count,int type,const void* data);

        static  void    drawArraysInstanced(GLenum mode, GLint first, GLsizei count,GLsizei primcount);
        static  void    drawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count,GLsizei primcount,GLuint baseinstance);
        static  void    drawElementsInstanced(unsigned mode, int count,int type,const void* data,GLsizei primcount);
        static  void    drawElementsInstancedBaseInstance(unsigned mode, int count,int type,const void* data,GLsizei primcount,GLuint baseinstance);

        static  void    drawlMultiElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei primcount, GLsizei stride);

        static  void    drawMultiArraysIndirect(GLenum mode, const void *indirect, GLsizei primcount, GLsizei stride);



        static void     enableRenderState(unsigned state);
        static void     disableRenderState(unsigned state);
        static  void    blendFunction(unsigned sfactor, unsigned dfactor);
        static  void    cullFace(unsigned face);

    };
}