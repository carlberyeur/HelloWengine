#pragma once

namespace wendy
{
	typedef struct EffectID_t* EffectID;

	class CBaseRenderer;
	class CModel;
	class CModelLoader;

	class CRenderPipeline
	{
	public:
		CRenderPipeline();
		CRenderPipeline(const CRenderPipeline& aCopy) = delete;
		CRenderPipeline& operator=(const CRenderPipeline& aCopy) = delete;
		~CRenderPipeline();
		
		bool Init(CBaseRenderer& aRenderer);

		void PrepareFrame();
		void DoFrame(CBaseRenderer& aRenderer);

		size_t AddModel(const std::string& aModelPath);
		CModel* GetModel(const size_t aIndex);

	private:
		std::unique_ptr<CModelLoader> myModelLoader;
		cu::CVector<CModel> myModels;
		EffectID myEffect;
	};
}
