#pragma once
#include "RenderCommand.h"

namespace wendy
{
	typedef struct MeshID_t* MeshID;
	typedef struct EffectID_t* EffectID;
	typedef struct ConstantBufferID_t* ConstantBufferID;
	typedef struct TextureID_t* TextureID;

	class CRenderModelCommand : public IRenderCommand
	{
	public:
		CRenderModelCommand(const MeshID aMesh, const ConstantBufferID aConstantBuffer, const TextureID aTexture, const cu::Matrix44f& aTransformation);
		~CRenderModelCommand();

		virtual void Execute(COpenGLRenderer& aRenderer) override;

	private:
		const cu::Matrix44f myTransformation;
		const ConstantBufferID myConstantBuffer;
		const MeshID myMesh;
		const TextureID myTexture;
	};
}
