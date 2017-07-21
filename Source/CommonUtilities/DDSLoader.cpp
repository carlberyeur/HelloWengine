#include "stdafx.h"
#include "DDSLoader.h"

#include <ddraw.h>

//#ifndef MAKEFOURCC
//#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
//                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
//                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
//#endif //defined(MAKEFOURCC)
//
///*
//* FOURCC codes for DX compressed-texture pixel formats
//*/
//#define FOURCC_DXT1  (MAKEFOURCC('D','X','T','1'))
//#define FOURCC_DXT2  (MAKEFOURCC('D','X','T','2'))
//#define FOURCC_DXT3  (MAKEFOURCC('D','X','T','3'))
//#define FOURCC_DXT4  (MAKEFOURCC('D','X','T','4'))
//#define FOURCC_DXT5  (MAKEFOURCC('D','X','T','5'))

namespace cu
{
	struct SDDSHeader
	{
		char garbage1[8];
		std::uint32_t height;
		std::uint32_t width;
		std::uint32_t linearSize;
		char garbage2[4];
		std::uint32_t mipMapCount;
		char garbage3[52];
		std::uint32_t fourCharacterCode;
		char garbage4[40];
	};

	static_assert(sizeof(SDDSHeader) == 124, "Messed up dds header");

	bool CDDSLoader::LoadDDSFile(const std::string& aTexturePath, STextureData& aDataOut)
	{
		std::string fileContent;
		if (!ReadFileBinary(aTexturePath, fileContent))
		{
			return false;
		}

		if (fileContent.size() < sizeof(SDDSHeader) + 4)
		{
			return false;
		}

		if (strncmp(fileContent.c_str(), "DDS ", 4) != 0)
		{
			return false;
		}

		SDDSHeader header = {};
		memcpy(&header, fileContent.c_str() + 4, sizeof(SDDSHeader));

		aDataOut.textureSize.Set(header.width, header.height);
		aDataOut.linearSize = header.linearSize;
		aDataOut.mipMapCount = header.mipMapCount;

		switch (header.fourCharacterCode)
		{
		case 827611204:
			aDataOut.dxtFormat = 1;
			break;
		case 844388420:
			aDataOut.dxtFormat = 2;
			break;
		case 861165636:
			aDataOut.dxtFormat = 3;
			break;
		case 877942852:
			aDataOut.dxtFormat = 4;
			break;
		case 894720068:
			aDataOut.dxtFormat = 5;
			break;
		default:
			return false;
		}

		size_t bufferSize = header.linearSize;
		if (header.mipMapCount > 1)
		{
			bufferSize *= 2;
		}

		if (fileContent.size() > bufferSize)
		{
			return false;
		}

		aDataOut.data.resize(bufferSize);

		memcpy(aDataOut.data.data(), fileContent.c_str() + 4 + sizeof(SDDSHeader), fileContent.size() - 4 - sizeof(SDDSHeader));

		return true;
	}
}
