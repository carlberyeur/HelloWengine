#include "stdafx.h"
#include "Model.h"

#include "BaseRenderer.h"
#include "RenderModelCommand.h"

#include "../CommonUtilities/Intersection.h"

namespace wendy
{
	CModel::CModel()
		: myMesh(NullMesh)
		, myTransformationBuffer(NullConstantBuffer)
		, myTexture(/*NullTexture*/NullSurface)
		, myAlbedoBuffer(NullConstantBuffer)
		, myRadius(10.f)
	{
	}

	CModel::~CModel()
	{
	}
	
	bool CModel::Init(const MeshID aMesh, const /*TextureID*/SurfaceID aTexture, const ConstantBufferID aTransformationBuffer, const ConstantBufferID aAlbedoBuffer)
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

	cu::SSphere CModel::GetBoundingSphere() const
	{
		cu::SSphere sphere;
		sphere.position = myTransformation.myPosition;
		sphere.radius = myRadius;

		return sphere;
	}
}