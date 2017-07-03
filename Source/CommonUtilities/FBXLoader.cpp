#include "stdafx.h"
#include "FBXLoader.h"

#include "AssImp\cimport.h"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#ifdef _DEBUG
#pragma comment (lib, "..\\Dependencies\\assimp-vc140-mtd.lib")
#else
#pragma comment (lib, "..\\Dependencies\\assimp-vc140-mt.lib")
#endif

namespace cu
{
	struct SVertexCollection
	{
		SVertexCollection(void* aBuffer) : position(0) { data = static_cast<char*>(aBuffer); }

		void PushVec2f(const aiVector3D& aPos)
		{
			float* fdata = reinterpret_cast<float*>(data + position);

			fdata[0] = aPos.x;
			fdata[1] = aPos.y;

			position += sizeof(float) * 2;
		}
		void PushVec4f(const aiVector3D& aPos)
		{
			float* fdata = reinterpret_cast<float*>(data + position);

			fdata[0] = aPos.x;
			fdata[1] = aPos.y;
			fdata[2] = aPos.z;
			fdata[3] = 1.f;

			position += sizeof(float) * 4;
		}

		char* data;
		int position;
	};

	bool CFBXLoader::LoadFbxFile(const std::string& aFilePath, SModelData& aDataOut)
	{
		if (!std::ifstream(aFilePath).good())
		{
			return false;
		}

		const aiScene* scene = aiImportFile(aFilePath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality /*| aiProcess_ConvertToLeftHanded*/);
		if (!scene)
		{
			//aiGetErrorString();
			return false;
		}

		if (!scene->HasMeshes())
		{
			return false;
		}

		if (!LoadMeshInternal(aFilePath, *scene, aDataOut.mesh))
		{
			return false;
		}

		if (scene->HasTextures())
		{
			LoadTexturesInternal(*scene, aDataOut.textures);
		}

		return true;
	}

	bool CFBXLoader::LoadMeshInternal(const std::string& /*aFilePath*/, const aiScene& aScene, SMeshData& aDataOut)
	{
		aiMesh* fbxMesh = aScene.mMeshes[0];

		std::uint32_t vertexSize = 0;
		if (fbxMesh->HasPositions())
		{
			SVertexAttribute posAttrib;
			posAttrib.myByteOffset = vertexSize;
			posAttrib.myType = SVertexAttribute::eType::eVec4;
			aDataOut.vertexAttributes.push_back(posAttrib);

			vertexSize += posAttrib.Size();
		}
		if (fbxMesh->HasNormals())
		{
			SVertexAttribute normalAttrib;
			normalAttrib.myByteOffset = vertexSize;
			normalAttrib.myType = SVertexAttribute::eType::eVec4;
			aDataOut.vertexAttributes.push_back(normalAttrib);

			vertexSize += normalAttrib.Size();
		}
		if (fbxMesh->HasTangentsAndBitangents())
		{
			SVertexAttribute tangentAttrib;
			tangentAttrib.myByteOffset = vertexSize;
			tangentAttrib.myType = SVertexAttribute::eType::eVec4;
			aDataOut.vertexAttributes.push_back(tangentAttrib);

			vertexSize += tangentAttrib.Size();
			
			SVertexAttribute bitangentAttrib;
			bitangentAttrib.myByteOffset = vertexSize;
			bitangentAttrib.myType = SVertexAttribute::eType::eVec4;
			aDataOut.vertexAttributes.push_back(bitangentAttrib);

			vertexSize += bitangentAttrib.Size();
		}
		if (fbxMesh->HasTextureCoords(0))
		{
			SVertexAttribute uvAttrib;
			uvAttrib.myByteOffset = vertexSize;
			uvAttrib.myType = SVertexAttribute::eType::eVec2;
			aDataOut.vertexAttributes.push_back(uvAttrib);

			vertexSize += uvAttrib.Size();
		}

		aDataOut.vertexSize = vertexSize;
		aDataOut.vertexCount = fbxMesh->mNumVertices;
		aDataOut.vertices.resize(aDataOut.vertexSize * aDataOut.vertexCount);
		SVertexCollection vertexCollection(aDataOut.vertices.data());

		for (unsigned int i = 0; i < fbxMesh->mNumVertices; ++i)
		{
			if (fbxMesh->HasPositions())
			{
				vertexCollection.PushVec4f(fbxMesh->mVertices[i]);
			}
			if (fbxMesh->HasNormals())
			{
				vertexCollection.PushVec4f(fbxMesh->mNormals[i]);
			}
			if (fbxMesh->HasTangentsAndBitangents())
			{
				vertexCollection.PushVec4f(fbxMesh->mTangents[i]);
				vertexCollection.PushVec4f(fbxMesh->mBitangents[i]);
			}
			if (fbxMesh->HasTextureCoords(0))
			{
				vertexCollection.PushVec2f(fbxMesh->mTextureCoords[0][i]);
			}
		}

		for (std::uint32_t i = 0; i < fbxMesh->mNumFaces; ++i)
		{
			for (std::uint32_t j = 0; j < fbxMesh->mFaces[i].mNumIndices; ++j)
			{
				aDataOut.indices.push_back(fbxMesh->mFaces[i].mIndices[j]);
			}
		}

		return true;
	}

	void CFBXLoader::LoadTexturesInternal(const aiScene& aScene, STextureData& aDataOut)
	{
		LoadTextureInternal(aiTextureType_DIFFUSE, *aScene.mMaterials[0], aDataOut[STextureData::eTextureType::eAlbedo]); // TEXTURE_DEFINITION_ALBEDO
		LoadTextureInternal(aiTextureType_SPECULAR, *aScene.mMaterials[0], aDataOut[STextureData::eTextureType::eRoughness]); // TEXTURE_DEFINITION_ROUGHNESS
		LoadTextureInternal(aiTextureType_AMBIENT, *aScene.mMaterials[0], aDataOut[STextureData::eTextureType::eAmbientOcclusion]); // TEXTURE_DEFINITION_AMBIENTOCCLUSION
		LoadTextureInternal(aiTextureType_EMISSIVE, *aScene.mMaterials[0], aDataOut[STextureData::eTextureType::eEmissive]); // TEXTURE_DEFINITION_EMISSIVE
		LoadTextureInternal(aiTextureType_NORMALS, *aScene.mMaterials[0], aDataOut[STextureData::eTextureType::eNormal]); // TEXTURE_DEFINITION_NORMAL
		LoadTextureInternal(aiTextureType_REFLECTION, *aScene.mMaterials[0], aDataOut[STextureData::eTextureType::eMetalness]); // TEXTURE_DEFINITION_METALNESS
	}

	void CFBXLoader::LoadTextureInternal(const aiTextureType aType, const aiMaterial& aMaterial, std::string& aTexturePathOut)
	{
		aiString path;
		aiReturn texFound = aMaterial.GetTexture(aType, 0, &path);
		if (texFound == AI_FAILURE)
		{
			return;
		}
		
		aTexturePathOut = std::string(path.C_Str());

		const size_t lastSlashIndex = aTexturePathOut.find_last_of("\\/");
		if (lastSlashIndex != std::string::npos)
		{
			aTexturePathOut.erase(0, lastSlashIndex + 1);
		}
	}
	
	std::uint32_t CFBXLoader::SVertexAttribute::Size() const
	{
		return Size(myType);
	}

	std::uint32_t CFBXLoader::SVertexAttribute::Size(const eType aType)
	{
		switch (aType)
		{
		case cu::CFBXLoader::SVertexAttribute::eType::eVec1:
			return sizeof(float);
		case cu::CFBXLoader::SVertexAttribute::eType::eVec2:
			return sizeof(float) * 2u;
		case cu::CFBXLoader::SVertexAttribute::eType::eVec3:
			return sizeof(float) * 3u;
		case cu::CFBXLoader::SVertexAttribute::eType::eVec4:
			return sizeof(float) * 4u;
		case cu::CFBXLoader::SVertexAttribute::eType::eMat3:
			return sizeof(float) * 3 * 3;
		case cu::CFBXLoader::SVertexAttribute::eType::eMat4:
			return sizeof(float) * 4 * 4;
		case cu::CFBXLoader::SVertexAttribute::eType::eUint4:
			return sizeof(std::uint32_t) * 4;
		}

		return 0u;
	}
}