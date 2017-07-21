#pragma once

namespace wendy
{
	class CBaseRenderer;
	class CModel;

	class CBaseRenderPipeline
	{
	public:
		CBaseRenderPipeline() {}
		virtual ~CBaseRenderPipeline() {}

		virtual bool Init(CBaseRenderer& aRenderer) = 0;

		virtual void PrepareFrame() = 0;
		virtual void DoFrame(CBaseRenderer& aRenderer) = 0;

		virtual size_t AddModel(const std::string& /*aFilePath*/) { return SIZE_MAX; }
		virtual CModel* GetModel(const size_t /*aID*/) { return nullptr; }
	};
}
