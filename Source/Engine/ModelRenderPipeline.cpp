#include "stdafx.h"
#include "ModelRenderPipeline.h"

#include "BaseRenderer.h"
#include "Model.h"
#include "ModelLoader.h"

#include "ChangeEffectCommand.h"
#include "SetCullModeCommand.h"
#include "SetBlendStateCommand.h"

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
		
		SEffectDesc effectDesc;
		effectDesc.vertexPath = "Shaders/modelshader.vert";
		effectDesc.pixelPath = "Shaders/modelshader.frag";
		effectDesc.inputAttributes = { "Pos", "Norm", "Tangent", "Bitangent", "uv" };
		effectDesc.constantBuffers = { "transform", "albedo" };

		myEffect = aRenderer.CreateEffect(effectDesc);
		if (myEffect == NullEffect)
		{
			return false;
		}
		
		return true;
	}

	void CModelRenderPipeline::PrepareFrame()
	{
		myPreparedModels.clear();

		for (CModel& model : myModels)
		{
			if (/*myCamera.IsInside(model.GetBoundingBox())*/true)
			{
				myPreparedModels.push_back(&model);
			}
		}

		//auto lessComparer = [this](CModel* aLeft, CModel* aRight) -> bool
		//{
		//	cu::Vector3f leftPosition = myCamera.GetInverse() * aLeft->GetPosition();
		//	cu::Vector3f rightPosition = myCamera.GetInverse() * aRight->GetPosition();
		//	
		//	return leftPosition.z < rightPosition.z;
		//};

		//std::sort(myPreparedModels.begin(), myPreparedModels.end(), lessComparer);
	}

	void CModelRenderPipeline::DoFrame(CBaseRenderer& aRenderer)
	{
		aRenderer.AddRenderCommand(new CChangeEffectCommand(myEffect));
		//aRenderer.AddRenderCommand(new CSetCullModeCommand(eCullMode_WireFrame));
		aRenderer.AddRenderCommand(new CSetBlendStateCommand(eBlendState::eAlphaBlend));

		for (CModel& model : myModels)
		{
			model.Render(aRenderer);
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
