#pragma once

#include "RenderPipeline.h"

namespace wendy
{
	class CBaseRenderer;
	class CModel;

	class CScene
	{
	public:
		CScene(CBaseRenderer& aRenderer);
		~CScene();

		bool Init();
		void Render();

		size_t AddModel(const std::string& aModelPath);
		CModel* GetModel(const size_t aID);

	private:
		CRenderPipeline myModelPipeline;
		CBaseRenderer& myRenderer;
	};
}
