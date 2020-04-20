#include "lifeiOpengl.h"
#include <assert.h>

namespace CELL
{
	inline void checkError(const char* line)
	{
#ifdef _DEBUG
		int err = glGetError();
#endif
	}

	lifeiOpenGL::lifeiOpenGL()
	{
	}

	lifeiOpenGL::~lifeiOpenGL()
	{

	}
	void lifeiOpenGL::initialize()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_PROGRAM_POINT_SIZE);
		checkError(__FUNCDNAME__);

	}

	void lifeiOpenGL::clearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void lifeiOpenGL::clear(unsigned mask)
	{
		glClear(mask);
	}

	void lifeiOpenGL::setViewPort(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	lifeiTexture3dID lifeiOpenGL::createTexture2dArray(int width, int height, int depths, unsigned fmt)
	{
		lifeiTexture3dID texID;
		texID._width = width;
		texID._height = height;
		texID._depth = depths;

		glGenTextures(1, &texID._texture);
		char szBuf[110];
		sprintf(szBuf, "%d", texID._texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texID._texture);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, fmt, width, height, depths);
	
		return texID;

	}


	void lifeiOpenGL::updateCompressTexture2dArray(
		int level,
		int xOffset,
		int yOffset,
		int layer,
		int width,
		int height,
		int srcFormat,
		int size,
		const void* data)
	{
		glCompressedTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			level,
			xOffset,
			yOffset,
			layer,
			width,
			height,
			1,
			srcFormat,
			size,
			data
			);
	}

	void lifeiOpenGL::bindTextureArray(const lifeiTexture3dID * textureId, unsigned stage)
	{
		if (textureId)
		{
			glActiveTexture(GL_TEXTURE0 + stage);
			glBindTexture(GL_TEXTURE_2D_ARRAY, textureId->_texture);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0 + stage);
			glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
		}
	}

	bool lifeiOpenGL::createProgram(lifeiProgram& program, const char* vs, const char* ps)
	{
		bool result = false;
		do
		{
			//创建shader
			program._vHandle = glCreateShader(GL_VERTEX_SHADER);
			program._pHandle = glCreateShader(GL_FRAGMENT_SHADER);

			//指定shader的源代码
			glShaderSource(program._vHandle, 1, (const GLchar**)&vs, 0);
			glShaderSource(program._pHandle, 1, (const GLchar**)&ps, 0);

			//编译shader
			glCompileShader(program._vHandle);
			GLint status = 0;
			char compileLog[1024] = { 0 };
			glGetShaderiv(program._vHandle, GL_COMPILE_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetShaderInfoLog(program._vHandle, sizeof(compileLog), 0, compileLog);
				assert(false && compileLog);
				break;
			}

			glCompileShader(program._pHandle);
			glGetShaderiv(program._pHandle, GL_COMPILE_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetShaderInfoLog(program._pHandle, sizeof(compileLog), 0, compileLog);
				assert(false && compileLog);
				break;
			}
			//创建程序
			program._program = glCreateProgram();
			glAttachShader(program._program, program._vHandle);
			glAttachShader(program._program, program._pHandle);

			//链接程序
			glLinkProgram(program._program);
			glGetProgramiv(program._program, GL_LINK_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetProgramInfoLog(program._program, sizeof(compileLog), 0, compileLog);
				assert(false && compileLog);
				break;
			}
			result = true;
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
			program._vHandle = -1;
			program._pHandle = -1;
			program._program = -1;
		}
		return result;
	}
	void lifeiOpenGL::destroyProgram(lifeiProgram& program)
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
		program._vHandle = -1;
		program._pHandle = -1;
		program._program = -1;
	}

	void lifeiOpenGL::useProgram(GLint progHandle)
	{
		glUseProgram(progHandle);
	}

	void lifeiOpenGL::useProgram(lifeiProgram& progma)
	{
		glUseProgram(progma._program);
	}
	
	GLint lifeiOpenGL::getUniformLocation(GLuint program, const char* name)
	{
		return glGetUniformLocation(program, name);
	}

	GLint lifeiOpenGL::getAttribLocation(GLuint program, const char* name)
	{
		return glGetAttribLocation(program, name);
	}

	void lifeiOpenGL::enableVertexAttribArray(GLuint index)
	{
		glEnableVertexAttribArray(index);
	}
	void lifeiOpenGL::disableVertexAttribArray(GLuint index)
	{
		glDisableVertexAttribArray(index);
	}
	void lifeiOpenGL::attributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, ptr);
	}

	void lifeiOpenGL::setUniform1i(int index, int v0)
	{
		glUniform1i(index, v0);
	}

	void lifeiOpenGL::setUniformMatrix4fv(int index, int count, bool transpose, const double* value)
	{
		GLfloat vParam[16] =
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

	void lifeiOpenGL::drawArrays_lf(GLenum mode, GLint first, GLsizei count)
	{
		glDrawArrays(mode, first, count);
	}

	void lifeiOpenGL::disableRenderState(unsigned state)
	{
		glDisable(state);
	}
}