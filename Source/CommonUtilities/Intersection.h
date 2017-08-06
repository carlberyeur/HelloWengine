#pragma once

namespace cu
{
	struct SSphere
	{
		Vector3f position;
		float radius;
	};

	struct SAABB
	{
		Vector3f min, max;
	};
}
