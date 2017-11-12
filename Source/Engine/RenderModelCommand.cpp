#include "stdafx.h"
#include "RenderModelCommand.h"

#include "OpenGLRenderer.h"
#include "GLMesh.h"
#include "GLEffect.h"
#include "GLUniformBuffer.h"
#include "GLTexture.h"
#include "GLSurface.h"

namespace pulp
{
	CRenderModelCommand::CRenderModelCommand(const MeshID aMesh, const ConstantBufferID aConstantBuffer, const /*TextureID*/SurfaceID aTexture, const ConstantBufferID aAlbedoBuffer, const cu::Matrix44f& aTransformation)
		: myTransformation(aTransformation)
		, myMesh(aMesh)
		, myConstantBuffer(aConstantBuffer)
		, myTexture(/*aTexture*/NullTexture)
		, mySurface(aTexture)
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

		//CGLTexture* texture = aRenderer.GetTexture(myTexture);
		//if (!texture) return;

		CGLSurface* surface = aRenderer.GetSurface(mySurface);
		if (!surface) return;

		//CGLUniformBuffer* albedoBuffer = aRenderer.GetUniformBuffer(myAlbedoBuffer);
		//if (!albedoBuffer) return;
		
		surface->Activate();

		//texture->Activate(0);
		//albedoBuffer->SetData(0);
		constantBuffer->SetData(myTransformation);
		
		mesh->Draw();
	}
}
