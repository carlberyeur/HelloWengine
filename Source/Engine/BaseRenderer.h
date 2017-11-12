#pragma once

namespace pulp
{
	typedef struct MeshID_t* MeshID;
	typedef struct EffectID_t* EffectID;
	typedef struct ConstantBufferID_t* ConstantBufferID;
	typedef struct TextureID_t* TextureID;
	typedef struct SurfaceID_t* SurfaceID;

	const MeshID NullMesh(MeshID(PTRDIFF_MAX));
	const EffectID NullEffect(EffectID(PTRDIFF_MAX));
	const ConstantBufferID NullConstantBuffer(ConstantBufferID(PTRDIFF_MAX));
	const TextureID NullTexture(TextureID(PTRDIFF_MAX));
	const SurfaceID NullSurface(SurfaceID(PTRDIFF_MAX));

	struct SVertexAttributeInfo;

	struct SMeshDesc
	{
		cu::CVector<uint32_t> indices;
		cu::CVector<SVertexAttributeInfo> attributeInfos;
		cu::CVector<char> vertices;
		int vertexSize;
		int vertexCount;
	};

	struct SEffectDesc
	{
		std::string vertexPath;
		std::string vertexEntryPoint;
		std::string pixelPath;
		std::string pixelEntryPoint;

		cu::CVector<std::string> inputAttributes;
		cu::CVector<std::string> constantBuffers;
	};

	struct SConstantBufferDesc
	{
		EffectID effect;
		size_t constantBuffer;
	};

	struct STextureDesc
	{
		cu::CVector<char> pixelData;
		cu::Vector2ui textureSize;
		std::uint32_t textureUnit; //texture slot -> make enum for albedo-normalmap-etc
		struct
		{
			bool enable;
			std::uint32_t mipMapCount;
			std::uint32_t format;
		} dxt;
	};

	struct SSurfaceDesc
	{
		cu::CArray<cu::CVector<char>, 4> pixelDatas;
		cu::CArray<cu::Vector2ui, 4> textureSizes;
		struct SDXT
		{
			bool enable;
			std::uint32_t mipMapCount;
			std::uint32_t format;
		};
		cu::CArray<SDXT, 4> dxt;
	};

	class CBaseWindow;
	class IRenderCommand;

	class CBaseRenderer
	{
	public:
		CBaseRenderer() {}
		virtual ~CBaseRenderer() {}

		virtual void Start(CBaseWindow& aWindow) = 0;

		virtual void AddRenderCommand(IRenderCommand* aRenderCommand) = 0;
		virtual void SwapCommandBuffer() = 0;
		virtual void DoRenderQueue() = 0;

		virtual MeshID CreateMesh(const SMeshDesc& aMeshDesc) = 0;
		virtual EffectID CreateEffect(const SEffectDesc& aEffectDesc) = 0;
		virtual ConstantBufferID CreateConstantBuffer(const SConstantBufferDesc& aConstantBufferDesc) = 0;
		virtual TextureID CreateTexture(const STextureDesc& aTextureDesc) = 0;
		virtual SurfaceID CreateSurface(const SSurfaceDesc& aSurfaceDesc) = 0;

		virtual void DestroyMesh(const MeshID aMesh) = 0;
	};
}
