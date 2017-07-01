#include "stdafx.h"
#include "ObjLoader.h"

//stolen from glm
void glm_hash_combine(size_t& seed, size_t hash)
{
	hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
	seed ^= hash;
}

namespace std
{
	template <>
	struct std::hash<cu::CObjLoader::SVertex>
	{
		//stolen from glm
		size_t operator()(cu::CObjLoader::SVertex const& aVertex) const
		{
			size_t positionHash = 0;
			hash<float> hasher;
			glm_hash_combine(positionHash, hasher(aVertex.position.x));
			glm_hash_combine(positionHash, hasher(aVertex.position.y));
			glm_hash_combine(positionHash, hasher(aVertex.position.z));

			//size_t normalHash = 0;
			//glm_hash_combine(normalHash, hasher(aVertex.normal.x));
			//glm_hash_combine(normalHash, hasher(aVertex.normal.y));
			//glm_hash_combine(normalHash, hasher(aVertex.normal.z));

			size_t uvHash = 0;
			glm_hash_combine(uvHash, hasher(aVertex.uv.x));
			glm_hash_combine(uvHash, hasher(aVertex.uv.y));
						
			return ((positionHash /*^ (normalHash << 1) >> 1*/) ^ (uvHash << 1));
		}
	};
}

namespace cu
{
	bool CObjLoader::LoadObjFile(const std::string& aFilePath, SMeshData& aDataOut)
	{
		std::ifstream file(aFilePath);
		if (!file.good())
		{
			return false;
		}

		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream stream(line);
			std::string type;
			stream >> type;
			if (type == "v")
			{
				cu::Vector3f position;
				stream >> position.x >> position.y >> position.z;
				aDataOut.positions.push_back(position);
			}
			else if (type == "vt")
			{
				cu::Vector2f uv;
				stream >> uv.x >> uv.y;
				aDataOut.uvs.push_back(uv);
			}
			else if (type == "vn")
			{
				cu::Vector3f normal;
				stream >> normal.x >> normal.y >> normal.z;
				aDataOut.normals.push_back(normal);
			}
			else if (type == "f")
			{
				SFaceData face;
				int matches = sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&face.positionIndex[0], &face.uvIndex[0], &face.normalIndex[0],
					&face.positionIndex[1], &face.uvIndex[1], &face.normalIndex[1],
					&face.positionIndex[2], &face.uvIndex[2], &face.normalIndex[2]);

				if (matches != 9) // no uv:s?
				{
					matches = sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d",
						&face.positionIndex[0], &face.normalIndex[0],
						&face.positionIndex[1], &face.normalIndex[1],
						&face.positionIndex[2], &face.normalIndex[2]);
					if (matches != 6)
					{
						DL_PRINT("cannot find matching format for f-line in obj file: %s", line.c_str());
						return false;
					}
				}

				aDataOut.faces.push_back(face);
			}
		}

		return true;
	}

	bool CObjLoader::LoadObjFile(const std::string& aFilePath, SIndexedMeshData& aDataOut)
	{
		SMeshData data = {};
		if (!LoadObjFile(aFilePath, data))
		{
			return false;
		}

		std::unordered_map<SVertex, uint32_t> uniqueVertices = {};

		for (const SFaceData& face : data.faces)
		{
			for (std::uint32_t i = 0; i < 3; i++)
			{
				SVertex vertex = {};

				vertex.position = data.positions[face.positionIndex[i] - 1];
				if (!data.uvs.empty())
				{
					vertex.uv = data.uvs[face.uvIndex[i] - 1];
				}

				if (uniqueVertices.find(vertex) == uniqueVertices.end())
				{
					uniqueVertices[vertex] = aDataOut.vertices.Size<std::uint32_t>();
					aDataOut.vertices.push_back(vertex);
				}

				aDataOut.indices.push_back(uniqueVertices[vertex]);
			}
		}

		return !aDataOut.indices.empty() && !aDataOut.vertices.empty();
	}
}