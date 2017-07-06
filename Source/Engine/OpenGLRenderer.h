#pragma once
#include "BaseRenderer.h"
#include "../CommonUtilities/Synchronizer.h"

namespace wendy
{
	class CBaseWindow;
	class CGLMesh;
	class CGLEffect;
	class CGLTexture;

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
		virtual TextureID CreateTexture(const STextureDesc& aTextureDesc) override;

		virtual void DestroyMesh(const MeshID aMesh) override;

		CGLMesh* GetMesh(MeshID aID);
		CGLEffect* GetEffect(EffectID aID);
		CGLTexture* GetTexture(TextureID aID);

	private:
		cu::CSynchronizer<IRenderCommand*> mySynchronizer;
		cu::CVector<CGLMesh> myMeshes;
		cu::CVector<CGLEffect> myEffects;
		cu::CVector<CGLTexture> myTextures;

		cu::CVector<cu::CFunction<void>> myAddFunctions;

		std::mutex myAddMutex;

		//std::mutex myMeshMutex;
		//std::mutex myEffectMutex;
		//std::mutex myTextureMutex;
	};
}
