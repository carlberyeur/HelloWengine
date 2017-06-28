#pragma once
#include "RenderCommand.h"

namespace wendy
{
	typedef struct MeshID_t* MeshID;
	typedef struct EffectID_t* EffectID;
	typedef struct TextureID_t* TextureID;

	class CRenderModelCommand : public IRenderCommand
	{
	public:
		CRenderModelCommand(const MeshID aMesh, const EffectID aEffect, const size_t aConstantBuffer, const cu::Matrix33f& aTransformation, const TextureID aTexture);
		~CRenderModelCommand();

		virtual void Execute(COpenGLRenderer& aRenderer) override;

	private:
		const cu::Matrix33f myTransformation;
		const size_t myConstantBuffers;
		const MeshID myMesh;
		const EffectID myEffect;
		const TextureID myTexture;
	};
}
