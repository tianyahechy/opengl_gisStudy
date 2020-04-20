#pragma once
#include "lifeiTexture.h"
#include "lifeiTexture3dID.h"
#include "lifeiProgram.h"

namespace CELL
{
	class lifeiOpenGL
	{
	public:
		lifeiOpenGL();
		virtual ~lifeiOpenGL();
		static void initialize();
		//Çå¿Õº¯Êý
		static void clearColor(float r, float g, float b, float a);
		static void clear(unsigned mask);
		static void setViewPort(int x, int y, int width, int height);
		static lifeiTexture3dID createTexture2dArray(int width, int height, int layers, unsigned fmt);
		static void updateCompressTexture2dArray(
			int level,
			int xOffset,
			int yOffset,
			int layer,
			int width,
			int heigth,
			int srcFormat,
			int size,
			const void * data);

		static void bindTextureArray(const lifeiTexture3dID* textureId, unsigned stage = 0);
		static bool createProgram(lifeiProgram& program, const char* vs, const char* ps);
		//Ïú»Ù
		static void destroyProgram(lifeiProgram& program);
		static void useProgram(GLint progHandle);
		static void useProgram(lifeiProgram& program);
		static GLint getUniformLocation(GLuint program, const char* name);
		static GLint getAttribLocation(GLuint program, const char* name);

		static void enableVertexAttribArray(GLuint index);
		static void disableVertexAttribArray(GLuint index);

		static void attributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
		static void setUniform1i(int index, int v0);

		static void setUniformMatrix4fv(int index, int count, bool transpose, const double* value);
		static void drawArrays_lf(GLenum mode, GLint first, GLsizei countst);
		static void disableRenderState(unsigned state);
		
	};
}