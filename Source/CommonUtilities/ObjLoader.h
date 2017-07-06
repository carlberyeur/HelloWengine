#pragma once

namespace cu
{
	class CObjLoader
	{
	public:
		struct SFaceData
		{
			uint32_t positionIndex[3];
			uint32_t uvIndex[3];
			uint32_t normalIndex[3];
		};

		struct SMeshData
		{
			CVector<SFaceData> faces;
			CVector<Vector3f> positions;
			CVector<Vector2f> uvs;
			CVector<Vector3f> normals;
		};

		struct SVertex
		{
			Vector3f position;
			//Vector3f normal;
			Vector2f uv;
			
			bool operator==(const SVertex& aRight) const
			{
				return position == aRight.position && /*normal == aRight.normal && */uv == aRight.uv;
			}
		};

		struct SIndexedMeshData
		{
			CVector<SVertex> vertices;
			CVector<std::uint32_t> indices;
		};

		static bool LoadObjFile(const std::string& aFilePath, SMeshData& aDataOut);
		static bool LoadObjFile(const std::string& aFilePath, SIndexedMeshData& aDataOut);
	};
}
