#include "stdafx.h"
#include "Model.h"

#include "BaseRenderer.h"
#include "RenderModelCommand.h"

namespace wendy
{
	CModel::CModel()
		: myMesh(NullMesh)
		, myTransformationBuffer(NullConstantBuffer)
		, myTexture(NullTexture)
		, myAlbedoBuffer(NullConstantBuffer)
	{
	}

	CModel::~CModel()
	{
	}
	
	bool CModel::Init(const MeshID aMesh, const TextureID aTexture, const ConstantBufferID aTransformationBuffer, const ConstantBufferID aAlbedoBuffer)
	{
		myMesh = aMesh;
		myTexture = aTexture;
		myTransformationBuffer = aTransformationBuffer;
		myAlbedoBuffer = aAlbedoBuffer;

		return true;
	}

	void CModel::Render(CBaseRenderer& aRenderer)
	{
		CRenderModelCommand* renderCommand = new CRenderModelCommand(myMesh, myTransformationBuffer, myTexture, myAlbedoBuffer, myTransformation);
		aRenderer.AddRenderCommand(renderCommand);
	}
}