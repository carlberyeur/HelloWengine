#pragma once
#include "BaseFramework.h"

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif // !__APPLE__
//#include <GLFW/glfw3.h>

namespace pulp
{
	class COpenGLFramework : public CBaseFramework
	{
	public:
		COpenGLFramework();
		~COpenGLFramework();

		virtual bool Init(CBaseWindow& aWindow) override;
		virtual bool BeginFrame() override;
		virtual bool EndFrame() override;
		virtual void OnWindowResize(const cu::Vector2ui& aWindowSize) override;

	private:
		bool LoadExtensions(CBaseWindow& aWindow);

		cu::CFunction<void> mySwapBuffers;
	};
	
	extern PFNGLATTACHSHADERPROC glAttachShader;
	extern PFNGLDETACHSHADERPROC glDetachShader;
	extern PFNGLCOMPILESHADERPROC glCompileShader;
	extern PFNGLCREATEPROGRAMPROC glCreateProgram;
	extern PFNGLCREATESHADERPROC glCreateShader;
	extern PFNGLDELETESHADERPROC glDeleteShader;
	extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
	extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	extern PFNGLGETSHADERIVPROC glGetShaderiv;
	extern PFNGLLINKPROGRAMPROC glLinkProgram;
	extern PFNGLSHADERSOURCEPROC glShaderSource;
	extern PFNGLUSEPROGRAMPROC glUseProgram;

	extern PFNGLBINDBUFFERPROC glBindBuffer;
	extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	extern PFNGLBUFFERDATAPROC glBufferData;
	extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
	extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
	extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
	extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	extern PFNGLGENBUFFERSPROC glGenBuffers;
	extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
	extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
	extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
	extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
	extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
	extern PFNGLACTIVETEXTUREPROC glActiveTexture;
	extern PFNGLUNIFORM1IPROC glUniform1i;
	extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
	extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
	extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
	extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
	extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
	extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
	extern PFNGLUNIFORM3FVPROC glUniform2fv;
	extern PFNGLUNIFORM3FVPROC glUniform3fv;
	extern PFNGLUNIFORM4FVPROC glUniform4fv;
	extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
	extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
	extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
	extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
	extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
	extern PFNGLDRAWBUFFERSPROC glDrawBuffers;
	extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
}
