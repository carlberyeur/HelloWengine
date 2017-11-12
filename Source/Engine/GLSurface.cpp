#include "stdafx.h"
#include "GLSurface.h"
#include "OpenGLFramework.h"

namespace pulp
{
	CGLSurface::CGLSurface()
	{
		myTextures.fill(0u);
	}

	CGLSurface::CGLSurface(CGLSurface&& aTemporary)
		: myTextures(std::move(aTemporary.myTextures))
	{
		aTemporary.myTextures.fill(0u);
	}

	CGLSurface& CGLSurface::operator=(CGLSurface&& aTemporary)
	{
		myTextures = std::move(aTemporary.myTextures);
		aTemporary.myTextures.fill(0u);

		return *this;
	}

	CGLSurface::~CGLSurface()
	{
		Destroy();
	}

	bool CGLSurface::Init(const cu::CArray<cu::Vector2ui, eTexture_Length>& aTextureSizes, const cu::CArray<const void*, eTexture_Length>& aPixelDatas, const bool aClampToEdge)
	{
		glGenTextures(myTextures.Size<GLsizei>(), myTextures.data());
		for (size_t i = 0; i < myTextures.size(); ++i)
		{
			if (aTextureSizes[i].Length2() == 0)
			{
				DL_MESSAGE_BOX("Error loading texture, texture dimensions are 0 (zero)");
				return false;
			}

			glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
			glBindTexture(GL_TEXTURE_2D, myTextures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, aTextureSizes[i].x, aTextureSizes[i].y, 0, GL_RGBA, GL_UNSIGNED_BYTE, aPixelDatas[i]);

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

			if (aPixelDatas[i])
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		return true;
	}

	bool CGLSurface::InitCompressed(const cu::CArray<cu::Vector2ui, eTexture_Length>& aTextureSizes, const cu::CArray<const void*, eTexture_Length>& aPixelDatas, const std::uint32_t aMipMapCount, const int aDXTFormat, const bool /*aClampToEdge*/)
	{
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

		glGenTextures(myTextures.Size<GLsizei>(), myTextures.data());

		for (size_t i = 0; i < myTextures.size(); i++)
		{
			if (aTextureSizes[i].Length2() == 0)
			{
				DL_MESSAGE_BOX("Error loading texture, texture dimensions are 0 (zero)");
				return false;
			}

			glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
			glBindTexture(GL_TEXTURE_2D, myTextures[i]);

			if (!aPixelDatas[i])
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				continue;
			}

			std::uint32_t blockSize = 8u;
			if (aDXTFormat > 1)
			{
				blockSize *= 2;
			}

			std::uint32_t width = aTextureSizes[i].x;
			std::uint32_t height = aTextureSizes[i].y;

			const std::uint8_t* pixelData = static_cast<const std::uint8_t*>(aPixelDatas[i]);
			std::uint32_t offset = 0u;

			for (std::uint32_t mipLevel = 0; mipLevel < aMipMapCount && (width || height); ++mipLevel)
			{
				std::uint32_t size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
				glCompressedTexImage2D(GL_TEXTURE_2D, mipLevel, format, width, height, 0/*border*/, size, pixelData + offset);

				offset += size;
				width /= 2;
				height /= 2;
			}
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	void CGLSurface::Activate()
	{
		for (std::uint32_t i = 0; i < myTextures.Size<std::uint32_t>(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, myTextures.At(i));
		}
	}

	void CGLSurface::Destroy()
	{
		if (myTextures[eTexture_Albedo] == 0u)
		{
			return;
		}

		for (std::uint32_t i = 0; i < myTextures.Size<std::uint32_t>(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0u);
		}

		glDeleteTextures(myTextures.Size<GLsizei>(), myTextures.data());
		myTextures.fill(0u);
	}
}
