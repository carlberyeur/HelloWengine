#pragma once

#include "BaseRenderPipeline.h"
#include "../CommonUtilities/Camera.h"

namespace wendy
{
	typedef struct EffectID_t* EffectID;
	typedef struct ConstantBufferID_t* ConstantBufferID;

	class CBaseRenderer;
	class CModel;
	class CModelLoader;

	class CModelRenderPipeline : public CBaseRenderPipeline
	{
	public:
		CModelRenderPipeline();
		CModelRenderPipeline(const CModelRenderPipeline& aCopy) = delete;
		CModelRenderPipeline& operator=(const CModelRenderPipeline& aCopy) = delete;
		~CModelRenderPipeline();
		
		virtual bool Init(CBaseRenderer& aRenderer) override;

		virtual void PrepareFrame() override;
		virtual void DoFrame(CBaseRenderer& aRenderer) override;

		virtual size_t AddModel(const std::string& aModelPath) override;
		virtual CModel* GetModel(const size_t aIndex) override;

	private:
		cu::Camera myCamera;

		cu::CVector<CModel> myModels;
		cu::CVector<CModel*> myPreparedModels;

		std::unique_ptr<CModelLoader> myModelLoader;
		EffectID myEffect;
		cu::CArray<ConstantBufferID, 4> myTextureSlots;
	};
}
