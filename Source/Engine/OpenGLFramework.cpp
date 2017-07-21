#include "stdafx.h"
#include "OpenGLFramework.h"
#include "BaseWindow.h"

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#endif // _WIN32

namespace wendy
{
	COpenGLFramework::COpenGLFramework()
	{
	}

	COpenGLFramework::~COpenGLFramework()
	{
	}

	bool COpenGLFramework::Init(CBaseWindow& aWindow)
	{
		if (!aWindow.AssignSwapBuffersFunction(mySwapBuffers))
		{
			return false;
		}

		if (!LoadExtensions(aWindow))
		{
			return false;
		}

		return true;
	}

	bool COpenGLFramework::BeginFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		return true;
	}

	bool COpenGLFramework::EndFrame()
	{
		mySwapBuffers();
		return true;
	}

	void COpenGLFramework::OnWindowResize(const cu::Vector2ui& /*aWindowSize*/)
	{
	}

	bool COpenGLFramework::LoadExtensions(CBaseWindow& aWindow)
	{
		cu::CFunction<void(*)(), const std::string&> getExtension;
		if (!aWindow.GetExtensionLoaderFunction(getExtension))
		{
			return false;
		}

		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)getExtension("glGenVertexArrays");
		if (!glGenVertexArrays)
		{
			return false;
		}

		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)getExtension("glBindVertexArray");
		if (!glBindVertexArray)
		{
			return false;
		}

		glGenBuffers = (PFNGLGENBUFFERSPROC)getExtension("glGenBuffers");
		if (!glGenBuffers)
		{
			return false;
		}

		glBindBuffer = (PFNGLBINDBUFFERPROC)getExtension("glBindBuffer");
		if (!glBindBuffer)
		{
			return false;
		}

		glBufferData = (PFNGLBUFFERDATAPROC)getExtension("glBufferData");
		if (!glBufferData)
		{
			return false;
		}

		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)getExtension("glEnableVertexAttribArray");
		if (!glEnableVertexAttribArray)
		{
			return false;
		}

		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)getExtension("glVertexAttribPointer");
		if (!glVertexAttribPointer)
		{
			return false;
		}

		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)getExtension("glDisableVertexAttribArray");
		if (!glDisableVertexAttribArray)
		{
			return false;
		}

		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)getExtension("glDeleteBuffers");
		if (!glDeleteBuffers)
		{
			return false;
		}

		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)getExtension("glDeleteVertexArrays");
		if (!glDeleteVertexArrays)
		{
			return false;
		}

		glCreateShader = (PFNGLCREATESHADERPROC)getExtension("glCreateShader");
		if (!glCreateShader)
		{
			return false;
		}

		glShaderSource = (PFNGLSHADERSOURCEPROC)getExtension("glShaderSource");
		if (!glShaderSource)
		{
			return false;
		}

		glCompileShader = (PFNGLCOMPILESHADERPROC)getExtension("glCompileShader");
		if (!glCompileShader)
		{
			return false;
		}

		glGetShaderiv = (PFNGLGETSHADERIVPROC)getExtension("glGetShaderiv");
		if (!glGetShaderiv)
		{
			return false;
		}

		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)getExtension("glGetShaderInfoLog");
		if (!glGetShaderInfoLog)
		{
			return false;
		}

		glLinkProgram = (PFNGLLINKPROGRAMPROC)getExtension("glLinkProgram");
		if (!glLinkProgram)
		{
			return false;
		}

		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)getExtension("glGetProgramiv");
		if (!glGetProgramiv)
		{
			return false;
		}

		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)getExtension("glGetProgramInfoLog");
		if (!glGetProgramInfoLog)
		{
			return false;
		}

		glCreateProgram = (PFNGLCREATEPROGRAMPROC)getExtension("glCreateProgram");
		if (!glCreateProgram)
		{
			return false;
		}

		glAttachShader = (PFNGLATTACHSHADERPROC)getExtension("glAttachShader");
		if (!glAttachShader)
		{
			return false;
		}

		glUseProgram = (PFNGLUSEPROGRAMPROC)getExtension("glUseProgram");
		if (!glUseProgram)
		{
			return false;
		}

		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)getExtension("glBindAttribLocation");
		if (!glBindAttribLocation)
		{
			return false;
		}

		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)getExtension("glGetUniformLocation");
		if (!glGetUniformLocation)
		{
			return false;
		}

		glUniform1i = (PFNGLUNIFORM1IPROC)getExtension("glUniform1i");
		if (!glUniform1i)
		{
			return false;
		}

		glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)getExtension("glUniformMatrix3fv");
		if (!glUniformMatrix3fv)
		{
			return false;
		}

		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)getExtension("glUniformMatrix4fv");
		if (!glUniformMatrix4fv)
		{
			return false;
		}

		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)getExtension("glDeleteProgram");
		if (!glDeleteProgram)
		{
			return false;
		}

		glDetachShader = (PFNGLDETACHSHADERPROC)getExtension("glDetachShader");
		if (!glDetachShader)
		{
			return false;
		}

		glDeleteShader = (PFNGLDELETESHADERPROC)getExtension("glDeleteShader");
		if (!glDeleteShader)
		{
			return false;
		}

		glActiveTexture = (PFNGLACTIVETEXTUREPROC)getExtension("glActiveTexture");
		if (!glActiveTexture)
		{
			return false;
		}

		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)getExtension("glGenerateMipmap");
		if (!glGenerateMipmap)
		{
			return false;
		}

		glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)getExtension("glCompressedTexImage2D");
		if (!glCompressedTexImage2D)
		{
			return false;
		}

		return true;
	}

	//global opengl function pointers
	PFNGLATTACHSHADERPROC glAttachShader;
	PFNGLBINDBUFFERPROC glBindBuffer;
	PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	PFNGLBUFFERDATAPROC glBufferData;
	PFNGLCOMPILESHADERPROC glCompileShader;
	PFNGLCREATEPROGRAMPROC glCreateProgram;
	PFNGLCREATESHADERPROC glCreateShader;
	PFNGLDELETEBUFFERSPROC glDeleteBuffers;
	PFNGLDELETEPROGRAMPROC glDeleteProgram;
	PFNGLDELETESHADERPROC glDeleteShader;
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
	PFNGLDETACHSHADERPROC glDetachShader;
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	PFNGLGENBUFFERSPROC glGenBuffers;
	PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	PFNGLGETPROGRAMIVPROC glGetProgramiv;
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	PFNGLGETSHADERIVPROC glGetShaderiv;
	PFNGLLINKPROGRAMPROC glLinkProgram;
	PFNGLSHADERSOURCEPROC glShaderSource;
	PFNGLUSEPROGRAMPROC glUseProgram;
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
	PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
	PFNGLACTIVETEXTUREPROC glActiveTexture;
	PFNGLUNIFORM1IPROC glUniform1i;
	PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
	PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
	PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
	PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
	PFNGLUNIFORM3FVPROC glUniform2fv;
	PFNGLUNIFORM3FVPROC glUniform3fv;
	PFNGLUNIFORM4FVPROC glUniform4fv;
	PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
	PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
	PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
	PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
	PFNGLDRAWBUFFERSPROC glDrawBuffers;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
}
