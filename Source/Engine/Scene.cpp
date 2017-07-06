#include "stdafx.h"
#include "Scene.h"

namespace wendy
{
	CScene::CScene(CBaseRenderer& aRenderer)
		: myRenderer(aRenderer)
	{
	}

	CScene::~CScene()
	{
	}

	bool CScene::Init()
	{
		if (!myModelPipeline.Init(myRenderer))
		{
			return false;
		}

		return true;
	}

	void CScene::Render()
	{
		myModelPipeline.PrepareFrame();
		myModelPipeline.DoFrame(myRenderer);
	}

	size_t CScene::AddModel(const std::string& aModelPath)
	{
		return myModelPipeline.AddModel(aModelPath);
	}

	CModel* CScene::GetModel(const size_t aID)
	{
		return myModelPipeline.GetModel(aID);
	}
}
