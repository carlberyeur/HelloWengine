#pragma once

namespace wendy
{
	struct SVertexAttributeInfo
	{
		//type: float
		int count;
		union
		{
			std::uintptr_t offset;
			void* offsetptr;
		};
	};

	struct SBaseVertex
	{
		float x, y, z;
		float u, v;

		static const cu::CVector<SVertexAttributeInfo> AttributeInfos;
	};

	struct SPosVertex
	{
		float x, y, z;

		static const cu::CVector<SVertexAttributeInfo> AttributeInfos;
	};

	struct SPosNormVertex
	{
		float x, y, z;
		float nx, ny, nz;

		bool operator==(const SPosNormVertex& aRight) const;

		static const cu::CVector<SVertexAttributeInfo> AttributeInfos;
	};
}
