#pragma once

namespace wendy
{
	class CGLTexture
	{
	public:
		CGLTexture();
		CGLTexture(const CGLTexture& aCopy) = delete;
		CGLTexture(CGLTexture&& aTemporary);
		CGLTexture& operator=(CGLTexture&& aTemporary);
		~CGLTexture();

		bool Init(const std::uint32_t aTextureUnit, const cu::Vector2ui& aTextureSize, const void* aPixelData);
		bool InitCompressed(const std::uint32_t aTextureUnit, const cu::Vector2ui& aTextureSize, const void* aPixelData, const std::uint32_t aMipMapCount, const int aDXTFormat);
		void Activate();

		const cu::Vector2ui& GetTextureSize() const;
		cu::Vector2f GetTextureSizeF() const;

		void Destroy();

	private:
		cu::Vector2ui myTextureSize;

		std::uint32_t myTextureID;
	};
}
