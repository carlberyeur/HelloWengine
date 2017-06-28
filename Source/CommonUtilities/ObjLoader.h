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

		CObjLoader();
		~CObjLoader();

		bool LoadObjFile(const std::string& aFilePath, SMeshData& aDataOut);
	};
}
