#include "stdafx.h"
#include "VertexStructs.h"

namespace pulp
{
	const cu::CVector<SVertexAttributeInfo> SBaseVertex::AttributeInfos =
	{
		{ 3, offsetof(SBaseVertex, x) },
		{ 2, offsetof(SBaseVertex, u) }
	};

	const cu::CVector<SVertexAttributeInfo> SPosVertex::AttributeInfos =
	{
		{ 3, offsetof(SBaseVertex, x) }
	};

	const cu::CVector<SVertexAttributeInfo> SPosNormVertex::AttributeInfos =
	{
		{ 3, offsetof(SPosNormVertex, x) },
		{ 3, offsetof(SPosNormVertex, nx) }
	};

	bool SPosNormVertex::operator==(const SPosNormVertex& aRight) const
	{
		return x == aRight.x && y == aRight.y && z == aRight.z && nx == aRight.nx && ny == aRight.ny && nz == aRight.nz;
	}
}