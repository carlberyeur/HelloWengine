#pragma once

namespace wendy
{
	typedef struct EffectID_t* EffectID;

	class CBaseRenderer;
	class CModel;

	class CModelLoader
	{
	public:
		CModelLoader(CBaseRenderer& aRenderer);
		~CModelLoader();

		bool LoadModel(const std::string& aModelPath, EffectID aEffect, CModel& aModelOut);

	private:
		bool LoadObjModel(const std::string& aModelPath, EffectID aEffect, CModel& aModelOut);
		bool LoadFbxModel(const std::string& aModelPath, EffectID aEffect, CModel& aModelOut);

		CBaseRenderer& myRenderer;
	};
}
