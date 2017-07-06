#include "stdafx.h"
#include "ObjLoader.h"

#if defined _WIN32
#define SSCANF sscanf_s
#else
#define SSCANF sscanf

#endif

namespace cu
{
	CObjLoader::CObjLoader()
	{
	}

	CObjLoader::~CObjLoader()
	{
	}

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
				int matches = SSCANF(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&face.positionIndex[0], &face.uvIndex[0], &face.normalIndex[0],
					&face.positionIndex[1], &face.uvIndex[1], &face.normalIndex[1],
					&face.positionIndex[2], &face.uvIndex[2], &face.normalIndex[2]);

				if (matches != 9) // no uv:s?
				{
					matches = SSCANF(line.c_str(), "f %d//%d %d//%d %d//%d",
						&face.positionIndex[0], &face.normalIndex[0],
						&face.positionIndex[1], &face.normalIndex[1],
						&face.positionIndex[2], &face.normalIndex[2]);
					if (matches != 6)
					{
						DL_PRINT("cannot find matching format for f-line in obj file: %s", line.c_str());
						return false;
					}
				}
			}
		}

		return true;
	}
}
