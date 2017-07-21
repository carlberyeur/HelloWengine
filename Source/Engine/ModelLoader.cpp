#include "stdafx.h"
#include "ModelLoader.h"

#include "BaseRenderer.h"
#include "Model.h"

#include "VertexStructs.h"

#include "../CommonUtilities/ObjLoader.h"
#include "../CommonUtilities/FBXLoader.h"

#include "../CommonUtilities/DDSLoader.h"

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
		
		//STextureDesc textureDesc;
		//textureDesc.pixelData.AddChunk(nullptr, 0u);
		//textureDesc.textureSize.Set(0u, 0u);
		//textureDesc.textureUnit = 0u;

		//TextureID texture = myRenderer.CreateTexture(textureDesc);

		SConstantBufferDesc constantBufferDesc;
		constantBufferDesc.constantBuffer = std::hash<std::string>()("transform");
		constantBufferDesc.effect = aEffect;

		ConstantBufferID constantBuffer = myRenderer.CreateConstantBuffer(constantBufferDesc);

		if (!aModelOut.Init(mesh, NullTexture, constantBuffer, NullConstantBuffer))
		{
			return false;
		}

		return true;
	}

	bool CModelLoader::LoadFbxModel(const std::string& aModelPath, EffectID aEffect, CModel& aModelOut)
	{
		cu::CFBXLoader::SModelData fbxData;
		if (!cu::CFBXLoader::LoadFbxFile(aModelPath, fbxData))
		{
			return false;
		}

		SMeshDesc meshDesc;
		meshDesc.indices = fbxData.mesh.indices;

		for (const cu::CFBXLoader::SVertexAttribute& vertexAttribute : fbxData.mesh.vertexAttributes)
		{
			SVertexAttributeInfo attributeInfo;
			attributeInfo.count = vertexAttribute.Size() / sizeof(float);
			attributeInfo.offset = vertexAttribute.myByteOffset;

			meshDesc.attributeInfos.push_back(attributeInfo);
		}

		meshDesc.vertices.AddChunk(fbxData.mesh.vertices.data(), fbxData.mesh.vertices.ByteSize<>());
		meshDesc.vertexSize = fbxData.mesh.vertexSize;
		meshDesc.vertexCount = fbxData.mesh.vertexCount;

		MeshID mesh = myRenderer.CreateMesh(meshDesc);

		cu::CDDSLoader::STextureData textureData;
		cu::CDDSLoader::LoadDDSFile("Textures/" + fbxData.textures[cu::CFBXLoader::STextureData::eTextureType::eAlbedo], textureData);

		STextureDesc textureDesc;
		textureDesc.pixelData = textureData.data;
		textureDesc.textureSize = textureData.textureSize;
		textureDesc.textureUnit = 0u;
		textureDesc.dxt.enable = true;
		textureDesc.dxt.mipMapCount = textureData.mipMapCount;
		textureDesc.dxt.format = textureData.dxtFormat;

		TextureID texture = myRenderer.CreateTexture(textureDesc);

		SConstantBufferDesc albedoBufferDesc;
		albedoBufferDesc.constantBuffer = std::hash<std::string>()("albedo");
		albedoBufferDesc.effect = aEffect;

		ConstantBufferID albedoBuffer = myRenderer.CreateConstantBuffer(albedoBufferDesc);

		SConstantBufferDesc transformBufferDesc;
		transformBufferDesc.constantBuffer = std::hash<std::string>()("transform");
		transformBufferDesc.effect = aEffect;

		ConstantBufferID constantBuffer = myRenderer.CreateConstantBuffer(transformBufferDesc);

		if (!aModelOut.Init(mesh, texture, constantBuffer, albedoBuffer))
		{
			return false;
		}

		return true;
	}
}
