#include "stdafx.h"
#include "RenderPipeline.h"

#include "BaseRenderer.h"
#include "Model.h"
#include "ModelLoader.h"
#include "ChangeEffectCommand.h"

namespace wendy
{
	CRenderPipeline::CRenderPipeline()
	{
	}

	CRenderPipeline::~CRenderPipeline()
	{
	}

	bool CRenderPipeline::Init(CBaseRenderer& aRenderer)
	{
		myModelLoader = std::make_unique<CModelLoader>(aRenderer);
		
		SEffectDesc effectDesc;
		effectDesc.vertexPath = "Shaders/shader.vert";
		effectDesc.pixelPath = "Shaders/shader.frag";
		effectDesc.inputAttributes = { "Pos" };
		effectDesc.constantBuffers = { "transform" };

		myEffect = aRenderer.CreateEffect(effectDesc);
		if (myEffect == NullEffect)
		{
			return false;
		}
		
		return true;
	}

	void CRenderPipeline::PrepareFrame()
	{
	}

	void CRenderPipeline::DoFrame(CBaseRenderer& aRenderer)
	{
		aRenderer.AddRenderCommand(new CChangeEffectCommand(myEffect));

		for (CModel& model : myModels)
		{
			model.Render(aRenderer);
		}
	}

	size_t CRenderPipeline::AddModel(const std::string& aModelPath)
	{
		CModel newModel;
		if (!myModelLoader->LoadModel(aModelPath, myEffect, newModel))
		{
			return SIZE_MAX;
		}

		size_t index = myModels.size();
		myModels.push_back(newModel);
		return index;
	}

	CModel* CRenderPipeline::GetModel(const size_t aIndex)
	{
		return myModels.TryGet(aIndex);
	}
}
