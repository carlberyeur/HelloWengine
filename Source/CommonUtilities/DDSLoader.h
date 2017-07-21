#pragma once

namespace cu
{
	class CDDSLoader
	{
	public:
		struct STextureData
		{
			CVector<char> data;
			Vector2ui textureSize;
			std::uint32_t linearSize;
			std::uint32_t mipMapCount;
			int dxtFormat;
		};

		static bool LoadDDSFile(const std::string& aTexturePath, STextureData& aDataOut);
	};
}
