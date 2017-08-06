#pragma once

struct aiScene;
struct aiMaterial;

// Sorry for this

#ifdef _WIN32
enum aiTextureType; // ISO C++ forbids forward reference to 'enum' types
#else
#include "AssImp/material.h"
#endif


namespace cu
{
	enum class eTextureType
	{
		eAlbedo,
		eRoughness,
		eAmbientOcclusion,
		eEmissive,
		eNormal,
		eMetalness,
		eLength
	};

	class CFBXLoader
	{
	public:
		struct SVertexAttribute
		{
			enum class eType : std::uint32_t
			{
				eVec1,
				eVec2,
				eVec3,
				eVec4,
				eMat3,
				eMat4,
				eUint4,
				eLength
			};

			std::uint32_t Size() const;
			static std::uint32_t Size(const eType aType);

			eType myType;
			std::uint32_t myByteOffset;
		};

		struct SMeshData
		{
			CVector<std::uint32_t> indices;
			CVector<char> vertices;
			CVector<SVertexAttribute> vertexAttributes;
			std::uint32_t vertexSize;
			std::uint32_t vertexCount;
		};

		struct STextureData
		{
			std::array<std::string, static_cast<size_t>(eTextureType::eLength)> texturePaths;

			std::string& operator[](const eTextureType aType) { return texturePaths[static_cast<size_t>(aType)]; }
		};

		struct SModelData
		{
			SMeshData mesh;
			STextureData textures;
		};

		static bool LoadFbxFile(const std::string& aFilePath, SModelData& aDataOut);

	private:
		static bool LoadMeshInternal(const std::string& aFilePath, const aiScene& aScene, SMeshData& aDataOut);
		static void LoadTexturesInternal(const aiScene& aScene, STextureData& aDataOut);
		static void LoadTextureInternal(const aiTextureType aType, const aiMaterial& aMaterial, std::string& aTexturePathOut);
	};
}
