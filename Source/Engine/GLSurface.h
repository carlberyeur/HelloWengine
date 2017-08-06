#pragma once

namespace wendy
{
	class CGLSurface
	{
	public:
		enum eTexture : unsigned int //GLenum
		{
			eTexture_Albedo,
			eTexture_Normal,
			eTexture_RMAO,
			eTexture_Emissive,
			eTexture_Length
		};

		CGLSurface();
		CGLSurface(const CGLSurface& aCopy) = delete;
		CGLSurface(CGLSurface&& aTemporary);
		CGLSurface& operator=(CGLSurface&& aTemporary);
		~CGLSurface();

		bool Init(const cu::CArray<cu::Vector2ui, eTexture_Length>& aTextureSizes, const cu::CArray<const void*, eTexture_Length>& aPixelDatas, const bool aClampToEdge);
		//bool Init(const cu::CArray<cu::Vector2ui, eTexture_Length>& aTextureSizes, const cu::CArray<cu::CVector<std::int8_t>, eTexture_Length>& aPixelDatas, const bool aClampToEdge);
		bool InitCompressed(const cu::CArray<cu::Vector2ui, eTexture_Length>& aTextureSizes, const cu::CArray<const void*, eTexture_Length>& aPixelDatas, const std::uint32_t aMipMapCount, const int aDXTFormat, const bool aClampToEdge);
		//bool InitCompressed(const cu::CArray<cu::Vector2ui, eTexture_Length>& aTextureSizes, const cu::CArray<cu::CVector<std::int8_t>, eTexture_Length>& aPixelDatas, const std::uint32_t aMipMapCount, const int aDXTFormat, const bool aClampToEdge);

		void Activate();

		void Destroy();

	private:
		cu::CArray<std::uint32_t, eTexture_Length> myTextures;
	};
}
