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

	bool CGLTexture::Init(const std::uint32_t aTextureUnit, const cu::Vector2ui& aTextureSize, const void* aPixelData, const bool aClampToEdge)
	{
		if (aTextureSize.Length2() == 0)
		{
			DL_MESSAGE_BOX("Error loading texture, texture dimensions are 0 (zero)");
			return false;
		}

		if (aTextureUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - GL_TEXTURE0)
		{
			DL_MESSAGE_BOX("Error loading texture, invalid texture unit: %d", aTextureUnit);
			return false;
		}

		glGenTextures(1, &myTextureID);
		glActiveTexture(GL_TEXTURE0 + aTextureUnit);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, aTextureSize.x, aTextureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, aPixelData);

		if (aClampToEdge)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (aPixelData)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		
		myTextureSize = aTextureSize;

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	bool CGLTexture::InitCompressed(const std::uint32_t aTextureUnit, const cu::Vector2ui& aTextureSize, const void* aPixelData, const std::uint32_t aMipMapCount, const int aDXTFormat, const bool /*aClampToEdge*/)
	{
		if (aTextureSize.Length2() == 0)
		{
			DL_MESSAGE_BOX("Error loading texture, texture dimensions are 0 (zero)");
			return false;
		}

		if (aTextureUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - GL_TEXTURE0)
		{
			DL_MESSAGE_BOX("Error loading texture, invalid texture unit: %d", aTextureUnit);
			return false;
		}

		if (!aPixelData)
		{
			DL_MESSAGE_BOX("Error loading texture, pixeldata is NULL");
			return false;
		}

		GLenum format = 0;
		switch (aDXTFormat)
		{
		case 1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case 3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case 5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			DL_MESSAGE_BOX("Error loading texture, format DXT&d not supported", aDXTFormat);
			return false;
		}

		glGenTextures(1, &myTextureID);
		glActiveTexture(GL_TEXTURE0 + aTextureUnit);
		glBindTexture(GL_TEXTURE_2D, myTextureID);

		std::uint32_t blockSize = 8u;
		if (aDXTFormat > 1)
		{
			blockSize *= 2;
		}

		std::uint32_t width = aTextureSize.x;
		std::uint32_t height = aTextureSize.y;

		const std::uint8_t* pixelData = static_cast<const std::uint8_t*>(aPixelData);
		std::uint32_t offset = 0u;

		for (std::uint32_t mipLevel = 0; mipLevel < aMipMapCount && (width || height); ++mipLevel)
		{
			std::uint32_t size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, mipLevel, format, width, height, 0/*border*/, size, pixelData + offset);

			offset += size;
			width /= 2;
			height /= 2;
		}

		myTextureSize = aTextureSize;

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	void CGLTexture::Activate(const int aTextureSlot)
	{
		glActiveTexture(GL_TEXTURE0 + aTextureSlot);
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
			glBindTexture(GL_TEXTURE_2D, 0u);
			glDeleteTextures(1, &myTextureID);
		}

		myTextureID = 0u;
	}
}
