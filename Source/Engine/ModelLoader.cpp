#include "stdafx.h"
#include "ModelLoader.h"

#include "BaseRenderer.h"
#include "Model.h"

#include "VertexStructs.h"

#include "../CommonUtilities/ObjLoader.h"

namespace wendy
{
	CModelLoader::CModelLoader(CBaseRenderer& aRenderer)
		: myRenderer(aRenderer)
	{
	}

	CModelLoader::~CModelLoader()
	{
	}

	bool CModelLoader::LoadModel(const std::string& aModelPath, EffectID aEffect, CModel& aModelOut)
	{
		size_t extPos = aModelPath.rfind(".obj");
		if (extPos != std::string::npos)
		{
			return LoadObjModel(aModelPath, aEffect, aModelOut);
		}

		extPos = aModelPath.rfind(".fbx");
		if (extPos != std::string::npos)
		{
			return LoadFbxModel(aModelPath, aEffect, aModelOut);
		}

		return false;
	}
	
	bool CModelLoader::LoadObjModel(const std::string& aModelPath, EffectID aEffect, CModel& aModelOut)
	{
		cu::CObjLoader::SIndexedMeshData objData;
		if (!cu::CObjLoader::LoadObjFile(aModelPath, objData))
		{
			return false;
		}

		cu::CVector<SBaseVertex> vertices;
		for (const cu::CObjLoader::SVertex& vertex : objData.vertices)
		{
			SBaseVertex newVertex;
			newVertex.x = vertex.position.x;
			newVertex.y = vertex.position.y;
			newVertex.z = vertex.position.z;

			newVertex.u = vertex.uv.x;
			newVertex.v = vertex.uv.y;

			vertices.push_back(newVertex);
		}

		SMeshDesc meshDesc;
		meshDesc.indices = objData.indices;
		meshDesc.attributeInfos = SBaseVertex::AttributeInfos;
		meshDesc.vertices.AddChunk(vertices.data(), vertices.ByteSize<>());
		meshDesc.vertexSize = sizeof(SBaseVertex);
		meshDesc.vertexCount = vertices.Size<int>();

		MeshID mesh = myRenderer.CreateMesh(meshDesc);
		
		STextureDesc textureDesc;
		textureDesc.pixelData.AddChunk(nullptr, 0u);
		textureDesc.textureSize.Set(0u, 0u);
		textureDesc.textureUnit = 0u;

		TextureID texture = myRenderer.CreateTexture(textureDesc);

		SConstantBufferDesc constantBufferDesc;
		constantBufferDesc.constantBuffer = std::hash<std::string>()("transform");
		constantBufferDesc.effect = aEffect;

		ConstantBufferID constantBuffer = myRenderer.CreateConstantBuffer(constantBufferDesc);

		if (!aModelOut.Init(mesh, texture, constantBuffer))
		{
			return false;
		}

		return true;
	}

	bool CModelLoader::LoadFbxModel(const std::string& aModelPath, EffectID aEffect, CModel& aModelOut)
	{
		return false;
	}
}
