#pragma once

namespace pulp
{
	class CBaseRenderer;
	class CBaseRenderPipeline;
	class CModel;

	enum eRenderPipeline : std::uint16_t
	{
		eRenderPipeline_Model,
		//eRenderPipeline_AlphaModel,
		//eRenderPipeline_GUI,
		eRenderPipeline_Length
	};

	class CScene
	{
	public:
		CScene(CBaseRenderer& aRenderer);
		~CScene();

		bool Init();
		void Render();

		size_t AddModel(const std::string& aModelPath, const eRenderPipeline aPipeline);
		CModel* GetModel(const size_t aID, const eRenderPipeline aPipeline);

	private:
		std::array<CBaseRenderPipeline*, eRenderPipeline_Length> myRenderPipelines;
		CBaseRenderer& myRenderer;
	};
}
