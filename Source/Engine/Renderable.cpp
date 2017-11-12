#include "stdafx.h"
#include "Renderable.h"
#include "Scene.h"
#include "BaseRenderPipeline.h"
#include "Model.h"

namespace pulp
{
	static cu::Matrix44f locNobodysMatrix;

	CRenderable::CRenderable()
		: myScene(nullptr)
		, myPipeline(eRenderPipeline::eRenderPipeline_Length)
		, myRenderableID(UINT16_MAX)
	{
	}

	CRenderable::~CRenderable()
	{
	}

	CRenderable::operator cu::Matrix44f&() const
	{
		if (myScene)
		{
			CModel* model = myScene->GetModel(myRenderableID, myPipeline);
			if (model)
			{
				return model->GetTransformation();
			}
		}

		return locNobodysMatrix;
	}

	bool pulp::CRenderable::IsValid() const
	{
		return myScene != nullptr && myPipeline != eRenderPipeline_Length && myRenderableID != UINT16_MAX;
	}
}
