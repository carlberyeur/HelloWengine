#include "stdafx.h"
#include "RenderModelCommand.h"

#include "OpenGLRenderer.h"
#include "GLMesh.h"
#include "GLEffect.h"
#include "GLUniformBuffer.h"
#include "GLTexture.h"

namespace wendy
{
	CRenderModelCommand::CRenderModelCommand(const MeshID aMesh, const ConstantBufferID aConstantBuffer, const TextureID aTexture, const cu::Matrix44f& aTransformation)
		: myTransformation(aTransformation)
		, myConstantBuffer(aConstantBuffer)
		, myMesh(aMesh)
		, myTexture(aTexture)
	{
	}

	CRenderModelCommand::~CRenderModelCommand()
	{
	}

	void CRenderModelCommand::Execute(COpenGLRenderer& aRenderer)
	{
		CGLUniformBuffer* constantBuffer = aRenderer.GetUniformBuffer(myConstantBuffer);
		if (!constantBuffer) return;

		CGLMesh* mesh = aRenderer.GetMesh(myMesh);
		if (!mesh) return;

		//CGLTexture* texture = aRenderer.GetTexture(myTexture);
		//if (!texture) return;

		//texture->Activate();
		constantBuffer->SetData(myTransformation);
		mesh->Draw();
	}
}
