#include "stdafx.h"
#include "Scene.h"

#include "BaseRenderPipeline.h"
#include "ModelRenderPipeline.h"

namespace wendy
{
	CScene::CScene(CBaseRenderer& aRenderer)
		: myRenderer(aRenderer)
	{
		myRenderPipelines.fill(nullptr);
	}

	CScene::~CScene()
	{
		for (CBaseRenderPipeline* renderPipeline : myRenderPipelines)
		{
			delete renderPipeline;
		}
	}

	bool CScene::Init()
	{
		myRenderPipelines[eRenderPipeline_Model] = new CModelRenderPipeline();
		for (CBaseRenderPipeline* renderPipeline : myRenderPipelines)
		{
			if (!renderPipeline->Init(myRenderer))
			{
				return false;
			}
		}

		return true;
	}

	void CScene::Render()
	{
		for (CBaseRenderPipeline* renderPipeline : myRenderPipelines)
		{
			renderPipeline->PrepareFrame();
			renderPipeline->DoFrame(myRenderer);
		}
	}

	size_t CScene::AddModel(const std::string& aModelPath, const eRenderPipeline aPipeline)
	{
		return myRenderPipelines[aPipeline]->AddModel(aModelPath);
	}

	CModel* CScene::GetModel(const size_t aID, const eRenderPipeline aPipeline)
	{
		return myRenderPipelines[aPipeline]->GetModel(aID);
	}
}
