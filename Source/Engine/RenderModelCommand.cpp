#include "stdafx.h"
#include "RenderModelCommand.h"

#include "OpenGLRenderer.h"
#include "GLMesh.h"
#include "GLEffect.h"
#include "GLUniformBuffer.h"
#include "GLTexture.h"

namespace wendy
{
	CRenderModelCommand::CRenderModelCommand(const MeshID aMesh, const ConstantBufferID aConstantBuffer, const TextureID aTexture, const ConstantBufferID aAlbedoBuffer, const cu::Matrix44f& aTransformation)
		: myTransformation(aTransformation)
		, myMesh(aMesh)
		, myConstantBuffer(aConstantBuffer)
		, myTexture(aTexture)
		, myAlbedoBuffer(aAlbedoBuffer)
	{
	}

	CRenderModelCommand::~CRenderModelCommand()
	{
	}

	void CRenderModelCommand::Execute(COpenGLRenderer& aRenderer)
	{
		CGLMesh* mesh = aRenderer.GetMesh(myMesh);
		if (!mesh) return;

		CGLUniformBuffer* constantBuffer = aRenderer.GetUniformBuffer(myConstantBuffer);
		if (!constantBuffer) return;

		CGLTexture* texture = aRenderer.GetTexture(myTexture);
		if (!texture) return;

		CGLUniformBuffer* albedoBuffer = aRenderer.GetUniformBuffer(myAlbedoBuffer);
		if (!albedoBuffer) return;
		
		texture->Activate();
		albedoBuffer->SetData(0);
		constantBuffer->SetData(myTransformation);
		
		mesh->Draw();
	}
}
