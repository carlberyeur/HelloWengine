#include "stdafx.h"
#include "OpenGLRenderer.h"
#include "GLMesh.h"
#include "GLEffect.h"
#include "GLTexture.h"

#include "VertexStructs.h"

#include "RenderCommand.h"
#include "BaseWindow.h"

namespace wendy
{
	COpenGLRenderer::COpenGLRenderer()
	{
	}

	COpenGLRenderer::~COpenGLRenderer()
	{
	}

	void COpenGLRenderer::Start(CBaseWindow& aWindow)
	{
		aWindow.MakeContextCurrent();
	}

	MeshID COpenGLRenderer::CreateMesh(const SMeshDesc& aMeshDesc)
	{
		std::lock_guard<std::mutex> lock(myAddMutex);

		std::uintptr_t index = myMeshes.Size<std::uintptr_t>();
		myMeshes.Add();

		auto addFunction = [aMeshDesc, this, index]()
		{
			CGLMesh newMesh;
			if (newMesh.Init(aMeshDesc.vertexSize, aMeshDesc.vertexCount, aMeshDesc.vertices.data(), aMeshDesc.indices, aMeshDesc.attributeInfos))
			{
				myMeshes[index] = std::move(newMesh);
			}
		};

		myAddFunctions.push_back(addFunction);

		return reinterpret_cast<MeshID>(index);
	}

	EffectID COpenGLRenderer::CreateEffect(const SEffectDesc& aEffectDesc)
	{
		std::lock_guard<std::mutex> lock(myAddMutex);

		std::uintptr_t index = myEffects.Size<std::uintptr_t>();
		myEffects.Add();

		auto addFunction = [aEffectDesc, this, index]()
		{
			CGLEffect newEffect;
			if (newEffect.Init(aEffectDesc.vertexPath, aEffectDesc.pixelPath, aEffectDesc.inputAttributes, aEffectDesc.constantBuffers))
			{
				myEffects[index] = std::move(newEffect);
			}
		};

		myAddFunctions.push_back(addFunction);

		return reinterpret_cast<EffectID>(index);
	}

	TextureID COpenGLRenderer::CreateTexture(const STextureDesc& aTextureDesc)
	{
		std::lock_guard<std::mutex> lock(myAddMutex);

		std::uintptr_t index = myTextures.Size<std::uintptr_t>();
		myTextures.Add();

		auto addFunction = [aTextureDesc, this, index]()
		{
			CGLTexture newTexture;
			if (newTexture.Init(aTextureDesc.textureUnit, aTextureDesc.textureSize, aTextureDesc.pixelData.data()))
			{
				myTextures[index] = std::move(newTexture);
			}
		};

		myAddFunctions.push_back(addFunction);

		return reinterpret_cast<TextureID>(index);
	}

	void COpenGLRenderer::DestroyMesh(const MeshID aMesh)
	{
		size_t index = reinterpret_cast<size_t>(aMesh);
		CGLMesh* mesh = myMeshes.TryGet(index);
		if (mesh)
		{
			mesh->Destroy();
		}
	}

	CGLMesh* COpenGLRenderer::GetMesh(MeshID aID)
	{
		size_t index = reinterpret_cast<size_t>(aID);
		return myMeshes.TryGet(index);
	}

	CGLEffect* COpenGLRenderer::GetEffect(EffectID aID)
	{
		size_t index = reinterpret_cast<size_t>(aID);
		return myEffects.TryGet(index);
	}

	CGLTexture* COpenGLRenderer::GetTexture(TextureID aID)
	{
		size_t index = reinterpret_cast<size_t>(aID);
		return myTextures.TryGet(index);
	}

	void COpenGLRenderer::AddRenderCommand(IRenderCommand* aRenderCommand)
	{
		mySynchronizer << aRenderCommand;
	}

	void COpenGLRenderer::SwapCommandBuffer()
	{
		mySynchronizer.SwapWrite();
	}

	void COpenGLRenderer::DoRenderQueue()
	{
		myAddMutex.lock();
		if (!myAddFunctions.empty())
		{
			for (cu::CFunction<void>& addFunction : myAddFunctions)
			{
				addFunction();
			}
			myAddFunctions.clear();
		}
		myAddMutex.unlock();

		mySynchronizer.SwapRead();

		for (size_t i = 0; i < !mySynchronizer; ++i)
		{
			mySynchronizer[i]->Execute(*this);
		}
	}
}
