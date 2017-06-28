#include "stdafx.h"
#include "RenderModelCommand.h"

#include "OpenGLRenderer.h"
#include "GLMesh.h"
#include "GLEffect.h"
#include "GLUniformBuffer.h"
#include "GLTexture.h"

namespace wendy
{
	CRenderModelCommand::CRenderModelCommand(const MeshID aMesh, const EffectID aEffect, const size_t aConstantBuffer, const cu::Matrix33f& aTransformation, const TextureID aTexture)
		: myTransformation(aTransformation)
		, myConstantBuffers(aConstantBuffer)
		, myMesh(aMesh)
		, myEffect(aEffect)
		, myTexture(aTexture)
	{
	}

	CRenderModelCommand::~CRenderModelCommand()
	{
	}

	void CRenderModelCommand::Execute(COpenGLRenderer& aRenderer)
	{
		CGLEffect* effect = aRenderer.GetEffect(myEffect);
		if (!effect) return;

		CGLMesh* mesh = aRenderer.GetMesh(myMesh);
		if (!mesh) return;

		//get texture
		//set texture

		effect->Activate();
		effect->GetUniformBuffer(myConstantBuffers).SetData(myTransformation);
		mesh->Draw();
	}
}
