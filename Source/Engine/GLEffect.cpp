#include "stdafx.h"
#include "GLEffect.h"

#include "OpenGLFramework.h"
#include "GLUniformBuffer.h"

namespace pulp
{
	CGLEffect::CGLEffect()
		: myVertexShader(0u)
		, myFragmentShader(0u)
		, myShaderProgram(0u)
	{
		myConstantBufferNames.fill(SIZE_MAX);
		myConstantBufferLocations.fill(-1);
	}

	CGLEffect::CGLEffect(CGLEffect&& aTemporary)
		: myConstantBufferNames(std::move(aTemporary.myConstantBufferNames))
		, myConstantBufferLocations(std::move(aTemporary.myConstantBufferLocations))
		, myVertexShader(aTemporary.myVertexShader)
		, myFragmentShader(aTemporary.myFragmentShader)
		, myShaderProgram(aTemporary.myShaderProgram)
	{
		aTemporary.myConstantBufferNames.fill(SIZE_MAX);
		aTemporary.myConstantBufferLocations.fill(-1);
		aTemporary.myVertexShader = 0u;
		aTemporary.myFragmentShader = 0u;
		aTemporary.myShaderProgram = 0u;
	}

	CGLEffect::~CGLEffect()
	{
		Destroy();
	}

	CGLEffect& CGLEffect::operator=(CGLEffect&& aTemporary)
	{
		Destroy();

		myConstantBufferNames = aTemporary.myConstantBufferNames;
		myConstantBufferLocations = aTemporary.myConstantBufferLocations;
		myVertexShader = aTemporary.myVertexShader;
		myFragmentShader = aTemporary.myFragmentShader;
		myShaderProgram = aTemporary.myShaderProgram;

		aTemporary.myConstantBufferNames.fill(SIZE_MAX);
		aTemporary.myConstantBufferLocations.fill(-1);
		aTemporary.myVertexShader = 0u;
		aTemporary.myFragmentShader = 0u;
		aTemporary.myShaderProgram = 0u;

		return *this;
	}

	bool CGLEffect::Init(const std::string& aVertexPath, const std::string& aPixelPath, const cu::CVector<std::string>& aInputAttributes, const cu::CVector<std::string>& aConstantBuffers)
	{
		std::string vertexShaderString;
		if (!cu::ReadFile(aVertexPath, vertexShaderString))
		{
			//must have vertex shader, return false
			return false;
		}

		std::string fragmentShaderString;
		if (!aPixelPath.empty() && !cu::ReadFile(aPixelPath, fragmentShaderString))
		{
			return false;
		}

		if (!CompileShader(vertexShaderString, GL_VERTEX_SHADER, myVertexShader))
		{
			return false;
		}

		if (!fragmentShaderString.empty() && !CompileShader(fragmentShaderString, GL_FRAGMENT_SHADER, myFragmentShader))
		{
			return false;
		}

		myShaderProgram = glCreateProgram();

		glAttachShader(myShaderProgram, myVertexShader);

		if (myFragmentShader)
		{
			glAttachShader(myShaderProgram, myFragmentShader);
		}

		for (size_t i = 0; i < aInputAttributes.size(); ++i)
		{
			glBindAttribLocation(myShaderProgram, static_cast<GLuint>(i), aInputAttributes[i].c_str());//kolla att de stämmer överens
		}

		if (!LinkShader(myShaderProgram))
		{
			return false;
		}

		for (size_t i = 0; i < aConstantBuffers.size(); ++i)
		{
			int location = glGetUniformLocation(myShaderProgram, aConstantBuffers[i].c_str());
			if (location != -1)
			{
				myConstantBufferLocations[i] = location;
				myConstantBufferNames[i] = std::hash<std::string>()(aConstantBuffers[i]);
			}
		}

		return true;
	}

	void CGLEffect::Activate()
	{
		glUseProgram(myShaderProgram);
	}

	CGLUniformBuffer CGLEffect::GetUniformBuffer(const std::string& aUniformName) const
	{
		int location = glGetUniformLocation(myShaderProgram, aUniformName.c_str());
		return CGLUniformBuffer(location);
	}

	CGLUniformBuffer CGLEffect::GetUniformBuffer(const size_t aHashedUniformName) const
	{
		int location = -1;
		for (size_t i = 0; i < myConstantBufferNames.size(); i++)
		{
			if (myConstantBufferNames[i] == aHashedUniformName)
			{
				location = myConstantBufferLocations[i];
				break;
			}
		}

		return CGLUniformBuffer(location);
	}

	void CGLEffect::Destroy()
	{
		myConstantBufferNames.fill(SIZE_MAX);
		myConstantBufferLocations.fill(-1);

		if (myVertexShader)
		{
			glDetachShader(myShaderProgram, myVertexShader);
			glDeleteShader(myVertexShader);
			myVertexShader = 0u;
		}
		if (myFragmentShader)
		{
			glDetachShader(myShaderProgram, myFragmentShader);
			glDeleteShader(myFragmentShader);
			myFragmentShader = 0u;
		}
		if (myShaderProgram)
		{
			glDeleteProgram(myShaderProgram);
			myShaderProgram = 0u;
		}
	}

	bool CGLEffect::CompileShader(const std::string& aFileContent, const unsigned int aShaderStage, unsigned int& aShaderIDOut)
	{
		aShaderIDOut = glCreateShader(aShaderStage);
		const char* shaderString = aFileContent.c_str();
		glShaderSource(aShaderIDOut, 1, &shaderString, nullptr);

		glCompileShader(aShaderIDOut);

		int compileStatus = 0;
		glGetShaderiv(aShaderIDOut, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus != 1)
		{
			int logSize = 0;
			std::string infoLog;
			glGetShaderiv(aShaderIDOut, GL_INFO_LOG_LENGTH, &logSize);
			infoLog.resize(logSize + 1);
			glGetShaderInfoLog(aShaderIDOut, logSize, nullptr, &infoLog[0]);
			DL_MESSAGE_BOX("Failed to compile shader: %s", infoLog.c_str());
			return false;
		}

		return true;
	}

	bool CGLEffect::LinkShader(const unsigned int aShaderProgram)
	{
		glLinkProgram(aShaderProgram);

		int linkStatus = 0;
		glGetProgramiv(aShaderProgram, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != 1)
		{
			int logSize = 0;
			std::string infoLog;
			glGetProgramiv(aShaderProgram, GL_INFO_LOG_LENGTH, &logSize);
			infoLog.resize(logSize + 1);
			glGetProgramInfoLog(aShaderProgram, logSize, nullptr, &infoLog[0]);
			DL_MESSAGE_BOX("Failed to link shader: %s", infoLog.c_str());
			return false;
		}

		return true;
	}
}
