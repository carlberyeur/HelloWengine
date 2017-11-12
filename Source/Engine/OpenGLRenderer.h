#pragma once
#include "BaseRenderer.h"
#include "../CommonUtilities/Synchronizer.h"

namespace pulp
{
	class CBaseWindow;
	class CGLMesh;
	class CGLEffect;
	class CGLUniformBuffer;
	class CGLTexture;
	class CGLSurface;

	class COpenGLRenderer : public CBaseRenderer
	{
	public:
		COpenGLRenderer();
		COpenGLRenderer(const COpenGLRenderer& aCopy) = delete;
		~COpenGLRenderer();

		virtual void Start(CBaseWindow& aWindow) override;

		virtual void AddRenderCommand(IRenderCommand* aRenderCommand) override;
		virtual void SwapCommandBuffer() override;
		virtual void DoRenderQueue() override;

		virtual MeshID CreateMesh(const SMeshDesc& aMeshDesc) override;
		virtual EffectID CreateEffect(const SEffectDesc& aEffectDesc) override;
		virtual ConstantBufferID CreateConstantBuffer(const SConstantBufferDesc& aConstantBufferDesc) override;
		virtual TextureID CreateTexture(const STextureDesc& aTextureDesc) override;
		virtual SurfaceID CreateSurface(const SSurfaceDesc& aSurfaceDesc) override;

		virtual void DestroyMesh(const MeshID aMesh) override;

		CGLMesh* GetMesh(MeshID aID);
		CGLEffect* GetEffect(EffectID aID);
		CGLUniformBuffer* GetUniformBuffer(ConstantBufferID aID);
		CGLTexture* GetTexture(TextureID aID);
		CGLSurface* GetSurface(SurfaceID aID);

	private:
		cu::CSynchronizer<IRenderCommand*> mySynchronizer;

		cu::CVector<CGLMesh> myMeshes;
		cu::CVector<CGLEffect> myEffects;
		cu::CVector<CGLUniformBuffer> myUniformBuffers;
		cu::CVector<CGLTexture> myTextures;
		cu::CVector<CGLSurface> mySurfaces;

		std::uintptr_t myMeshCount;
		std::uintptr_t myEffectCount;
		std::uintptr_t myUniformCount;
		std::uintptr_t myTextureCount;
		std::uintptr_t mySurfaceCount;

		cu::CVector<cu::CFunction<void>> myAddFunctions;

		std::mutex myAddMutex;
	};
}
