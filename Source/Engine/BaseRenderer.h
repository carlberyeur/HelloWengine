#pragma once

namespace wendy
{
	typedef struct MeshID_t* MeshID;
	typedef struct EffectID_t* EffectID;
	typedef struct TextureID_t* TextureID;

	const MeshID NullMesh(MeshID(PTRDIFF_MAX));
	const EffectID NullEffect(EffectID(PTRDIFF_MAX));
	const TextureID NullTexture(TextureID(PTRDIFF_MAX));

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

	struct STextureDesc
	{
		cu::CVector<char> pixelData;
		cu::Vector2ui textureSize;
		std::uint32_t textureUnit; //texture slot -> make enum for albedo-normalmap-etc
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
		virtual TextureID CreateTexture(const STextureDesc& aTextureDesc) = 0;

		virtual void DestroyMesh(const MeshID aMesh) = 0;
	};
}
