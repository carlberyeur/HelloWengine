#include "stdafx.h"
#include "GLUniformBuffer.h"

#include "OpenGLFramework.h"

namespace pulp
{
	CGLUniformBuffer::CGLUniformBuffer()
		: myLocation(-1)
	{
	}

	CGLUniformBuffer::CGLUniformBuffer(const int aLocation)
		: myLocation(aLocation)
	{
	}

	CGLUniformBuffer::~CGLUniformBuffer()
	{
	}

	template<>
	void CGLUniformBuffer::SetData(const int& aType)
	{
		glUniform1i(myLocation, aType);
	}

	template<>
	void CGLUniformBuffer::SetData(const cu::Matrix33f& aType)
	{
		glUniformMatrix3fv(myLocation, 1, GL_FALSE, aType.myMatrix.data());
	}

	template<>
	void CGLUniformBuffer::SetData(const cu::Matrix44f& aType)
	{
		glUniformMatrix4fv(myLocation, 1, GL_FALSE, aType.myMatrix.data());
	}
}
