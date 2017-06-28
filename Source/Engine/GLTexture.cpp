#include "stdafx.h"
#include "GLTexture.h"
#include "OpenGLFramework.h"

namespace wendy
{
	CGLTexture::CGLTexture()
		: myTextureID(0u)
	{
	}

	CGLTexture::CGLTexture(CGLTexture&& aTemporary)
		: myTextureID(aTemporary.myTextureID)
	{
		aTemporary.myTextureID = 0u;
	}

	CGLTexture& CGLTexture::operator=(CGLTexture&& aTemporary)
	{
		myTextureID = aTemporary.myTextureID;
		aTemporary.myTextureID = 0u;

		return *this;
	}

	CGLTexture::~CGLTexture()
	{
		Destroy();
	}

	bool CGLTexture::Init(const std::uint32_t aTextureUnit, const cu::Vector2ui aTextureSize, const void* aPixelData)
	{
		if (aTextureSize.Length2() == 0)
		{
			return false;
		}

		if (aTextureUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - GL_TEXTURE0)
		{
			return false;
		}

		glActiveTexture(GL_TEXTURE0 + aTextureUnit);
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, aTextureSize.x, aTextureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, aPixelData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (aPixelData)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		myTextureSize = aTextureSize;

		return true;
	}

	void CGLTexture::Activate()
	{
		glBindTexture(GL_TEXTURE_2D, myTextureID);
	}

	const cu::Vector2ui& CGLTexture::GetTextureSize() const
	{
		return myTextureSize;
	}

	cu::Vector2f CGLTexture::GetTextureSizeF() const
	{
		return cu::Vector2f(myTextureSize);
	}

	void CGLTexture::Destroy()
	{
		if (myTextureID)
		{
			glDeleteTextures(1, &myTextureID);
		}

		myTextureID = 0u;
	}
}
