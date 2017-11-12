#include "stdafx.h"
#include "ModelRenderPipeline.h"

#include "BaseRenderer.h"
#include "Model.h"
#include "ModelLoader.h"

#include "ChangeEffectCommand.h"
#include "SetCullModeCommand.h"
#include "SetBlendStateCommand.h"
#include "SetTextureSlotCommand.h"

#include "../CommonUtilities/Intersection.h"

namespace wendy
{
	CModelRenderPipeline::CModelRenderPipeline()
	{
	}

	CModelRenderPipeline::~CModelRenderPipeline()
	{
	}

	bool CModelRenderPipeline::Init(CBaseRenderer& aRenderer)
	{
		myModelLoader = std::make_unique<CModelLoader>(aRenderer);
		
		SEffectDesc effectDesc = {};
		effectDesc.vertexPath = "Shaders/modelshader.vert";
		effectDesc.pixelPath = "Shaders/modelshader.frag";
		effectDesc.inputAttributes = { "Pos", "Norm", "Tangent", "Bitangent", "uv" };
		effectDesc.constantBuffers = { "mvp", "albedo", "normal", "rmao", "emissive" };

		myEffect = aRenderer.CreateEffect(effectDesc);
		if (myEffect == NullEffect)
		{
			return false;
		}

		for (size_t i = 0; i < myTextureSlots.size(); ++i)
		{
			SConstantBufferDesc textureSlotDesc = {};
			textureSlotDesc.constantBuffer = std::hash<std::string>()(effectDesc.constantBuffers[i + 1]);
			textureSlotDesc.effect = myEffect;

			myTextureSlots[i] = aRenderer.CreateConstantBuffer(textureSlotDesc);
			if (myTextureSlots[i] == NullConstantBuffer)
			{
				return false;
			}
		}
		
		return true;
	}

	void CModelRenderPipeline::PrepareFrame()
	{
		myPreparedModels.clear();

		for (CModel& model : myModels)
		{
			if (myCamera.IsInside(model.GetBoundingSphere()))
			{
				myPreparedModels.push_back(&model);
			}
		}

		auto lessComparer = [this](CModel* aLeft, CModel* aRight) -> bool
		{
			cu::Vector3f leftPosition = aLeft->GetPosition() * myCamera.GetTransformationInverse();
			cu::Vector3f rightPosition = aRight->GetPosition() * myCamera.GetTransformationInverse();
			
			return leftPosition.z < rightPosition.z;
		};

		myPreparedModels.Sort(lessComparer);
	}

	void CModelRenderPipeline::DoFrame(CBaseRenderer& aRenderer)
	{
		aRenderer.AddRenderCommand(new CChangeEffectCommand(myEffect));
		//aRenderer.AddRenderCommand(new CSetCullModeCommand(eCullMode_WireFrame));
		aRenderer.AddRenderCommand(new CSetBlendStateCommand(eBlendState::eAlphaBlend));

		for (int i = 0; i < myTextureSlots.Size<int>(); ++i)
		{
			aRenderer.AddRenderCommand(new CSetTextureSlotCommand(myTextureSlots.At(i), i));
		}

		for (CModel* model : myPreparedModels)
		{
			model->Render(aRenderer);
		}
	}

	size_t CModelRenderPipeline::AddModel(const std::string& aModelPath)
	{
		CModel newModel;
		if (!myModelLoader->LoadModel(aModelPath, myEffect, newModel))
		{
			return SIZE_MAX;
		}

		size_t index = myModels.size();
		myModels.push_back(std::move(newModel));
		return index;
	}

	CModel* CModelRenderPipeline::GetModel(const size_t aIndex)
	{
		return myModels.TryGet(aIndex);
	}
}
