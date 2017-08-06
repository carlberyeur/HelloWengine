#pragma once
#include "PlaneVolume.h"

namespace cu
{
	struct SSphere;

	class CFrustum
	{
	public:
		CFrustum();
		~CFrustum();

		void SetFrustum(float aFar, float aNear, float aFOVRadians, float aWidth, float aHeight);
		void SetFrustum(const Matrix44f& aProjectionInverse);

		bool IsInside(const SSphere& aSphere) const;

	private:
		PlaneVolume<float> myPlanes;
	};
}