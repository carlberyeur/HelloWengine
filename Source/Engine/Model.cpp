#include "stdafx.h"
#include "Model.h"

#include "BaseRenderer.h"
#include "RenderModelCommand.h"

namespace wendy
{
	CModel::CModel()
		: myMesh(NullMesh)
		, myTexture(NullTexture)
		, myTransformationBuffer(NullConstantBuffer)
	{
	}

	CModel::~CModel()
	{
	}
	
	bool CModel::Init(const MeshID aMesh, const TextureID aTexture, const ConstantBufferID aTransformationBuffer)
	{
		myMesh = aMesh;
		myTexture = aTexture;
		myTransformationBuffer = aTransformationBuffer;

		return true;
	}

	void CModel::Render(CBaseRenderer& aRenderer)
	{
		CRenderModelCommand* renderCommand = new CRenderModelCommand(myMesh, myTransformationBuffer, myTexture, myTransformation);
		aRenderer.AddRenderCommand(renderCommand);
	}
}