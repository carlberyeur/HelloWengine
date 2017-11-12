#include "stdafx.h"
#include "OpenGLRenderer.h"

#include "GLMesh.h"
#include "GLEffect.h"
#include "GLUniformBuffer.h"
#include "GLTexture.h"
#include "GLSurface.h"

#include "VertexStructs.h"

#include "RenderCommand.h"
#include "BaseWindow.h"
#include "OpenGLFramework.h"

namespace pulp
{
	COpenGLRenderer::COpenGLRenderer()
		: myMeshCount(0u)
		, myEffectCount(0u)
		, myUniformCount(0u)
		, myTextureCount(0u)
		, mySurfaceCount(0u)
	{
	}

	COpenGLRenderer::~COpenGLRenderer()
	{
	}

	void COpenGLRenderer::Start(CBaseWindow& aWindow)
	{
		aWindow.MakeContextCurrent();

		glEnable(GL_BLEND);
	}

	MeshID COpenGLRenderer::CreateMesh(const SMeshDesc& aMeshDesc)
	{
		std::lock_guard<std::mutex> lock(myAddMutex);

		std::uintptr_t index = myMeshCount++;

		auto addFunction = [aMeshDesc, this, index]()
		{
			assert(myMeshes.Size<std::uintptr_t>() == index && "this should work, the other create functions are not thread safe :(");

			CGLMesh newMesh;
			if (newMesh.Init(aMeshDesc.vertexSize, aMeshDesc.vertexCount, aMeshDesc.vertices.data(), aMeshDesc.indices, aMeshDesc.attributeInfos))
			{
				myMeshes.push_back(std::move(newMesh));
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

	ConstantBufferID COpenGLRenderer::CreateConstantBuffer(const SConstantBufferDesc& aConstantBufferDesc)
	{
		std::lock_guard<std::mutex> lock(myAddMutex);

		std::uintptr_t index = myUniformBuffers.Size<std::uintptr_t>();
		myUniformBuffers.Add();

		auto addFunction = [aConstantBufferDesc, this, index]()
		{
			CGLEffect* effect = GetEffect(aConstantBufferDesc.effect);
			if (effect)
			{
				myUniformBuffers[index] = effect->GetUniformBuffer(aConstantBufferDesc.constantBuffer);
			}
		};

		myAddFunctions.push_back(addFunction);
		return reinterpret_cast<ConstantBufferID>(index);
	}

	TextureID COpenGLRenderer::CreateTexture(const STextureDesc& aTextureDesc)
	{
		std::lock_guard<std::mutex> lock(myAddMutex);

		std::uintptr_t index = myTextures.Size<std::uintptr_t>();
		myTextures.Add();

		auto addFunction = [aTextureDesc, this, index]()
		{
			CGLTexture newTexture;
			if (aTextureDesc.dxt.enable)
			{
				if (newTexture.InitCompressed(aTextureDesc.textureUnit, aTextureDesc.textureSize, aTextureDesc.pixelData.data(), aTextureDesc.dxt.mipMapCount, aTextureDesc.dxt.format, false))
				{
					myTextures[index] = std::move(newTexture);
				}
			}
			else
			{
				if (newTexture.Init(aTextureDesc.textureUnit, aTextureDesc.textureSize, aTextureDesc.pixelData.data(), false))
				{
					myTextures[index] = std::move(newTexture);
				}
			}
		};

		myAddFunctions.push_back(addFunction);

		return reinterpret_cast<TextureID>(index);
	}

	SurfaceID COpenGLRenderer::CreateSurface(const SSurfaceDesc& aSurfaceDesc)
	{
		std::lock_guard<std::mutex> lock(myAddMutex);

		std::uintptr_t index = mySurfaces.Size<std::uintptr_t>();
		mySurfaces.Add();

		auto addFunction = [aSurfaceDesc, this, index]()
		{
			CGLSurface newSurface;
			cu::CArray<const void*, 4> pixelDatas;
			for (size_t i = 0; i < pixelDatas.size(); ++i)
			{
				pixelDatas[i] = aSurfaceDesc.pixelDatas[i].data();
			}

			if (aSurfaceDesc.dxt[0].enable)
			{
				if (newSurface.InitCompressed(aSurfaceDesc.textureSizes, pixelDatas, aSurfaceDesc.dxt[0].mipMapCount, aSurfaceDesc.dxt[0].format, false))
				{
					mySurfaces[index] = std::move(newSurface);
				}
			}
			else
			{
				if (newSurface.Init(aSurfaceDesc.textureSizes, pixelDatas, false))
				{
					mySurfaces[index] = std::move(newSurface);
				}
			}
		};

		myAddFunctions.push_back(addFunction);

		return reinterpret_cast<SurfaceID>(index);
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

	CGLUniformBuffer* COpenGLRenderer::GetUniformBuffer(ConstantBufferID aID)
	{
		size_t index = reinterpret_cast<size_t>(aID);
		return myUniformBuffers.TryGet(index);
	}

	CGLTexture* COpenGLRenderer::GetTexture(TextureID aID)
	{
		size_t index = reinterpret_cast<size_t>(aID);
		return myTextures.TryGet(index);
	}

	CGLSurface* COpenGLRenderer::GetSurface(SurfaceID aID)
	{
		size_t index = reinterpret_cast<size_t>(aID);
		return mySurfaces.TryGet(index);
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
