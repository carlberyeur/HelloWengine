#include "stdafx.h"
#include "Frustum.h"

#include "Intersection.h"

namespace cu
{
	CFrustum::CFrustum()
	{
	}
	
	CFrustum::~CFrustum()
	{
	}

	void CFrustum::SetFrustum(float aFar, float aNear, float aFOVRadians, float aWidth, float aHeight)
	{
		myPlanes.RemovePlanes();

		float FovExtens = 0.0f;

		float AspectRatioY = aHeight / aWidth;
		float FovX = (aFOVRadians + FovExtens);
		float TanFovX = std::tan(FovX / 2.0f);
		float FovY = 2.0f * std::atan(TanFovX * AspectRatioY);


		Plane<float> farPlane = Plane<float>(Point3f(0.f, 0.f, aFar), Vector3f(0.f, 0.f, 1.0f));
		Plane<float> nearPlane = Plane<float>(Point3f(0.f, 0.f, aNear), Vector3f(0.f, 0.f, -1.0f));

		Plane<float> leftPlane;
		Plane<float> rightPlane;
		Plane<float> topPlane;
		Plane<float> bottomPlane;

		//Ortho
		if (aFOVRadians == 0.0f)
		{
			leftPlane = Plane<float>(Point3f((aWidth / 2), 0.f, 0.f), Point3f(1.f, 0.f, 0.f));
			rightPlane = Plane<float>(Point3f(-(aWidth / 2), 0.f, 0.f), Point3f(-1.f, 0.f, 0.f));
			topPlane = Plane<float>(Point3f(0.f, (aHeight / 2), 0.f), Point3f(0.f, 1.f, 0.f));
			bottomPlane = Plane<float>(Point3f(0.f, -(aHeight / 2), 0.f), Point3f(0.f, -1.f, 0.f));
		}
		else //projo
		{
			leftPlane = Plane<float>(Point3f(0.f, 0.f, 0.f),
				Point3f(1.f, 0.f, 0.f) * Matrix33f::CreateRotateAroundY(FovX));

			rightPlane = Plane<float>(Point3f(0.f, 0.f, 0.f),
				Point3f(-1.f, 0.f, 0.f) * Matrix33f::CreateRotateAroundY(-FovX));

			topPlane = Plane<float>(Point3f(0.f, 0.f, 0.f),
				Point3f(0.f, 1.f, 0.f) * Matrix33f::CreateRotateAroundX(-FovY));

			bottomPlane = Plane<float>(Point3f(0.f, 0.f, 0.f),
				Point3f(0.f, -1.f, 0.f) * Matrix33f::CreateRotateAroundX(FovY));
		}

		myPlanes.AddPlane(farPlane);
		myPlanes.AddPlane(nearPlane);
		myPlanes.AddPlane(leftPlane);
		myPlanes.AddPlane(rightPlane);
		myPlanes.AddPlane(topPlane);
		myPlanes.AddPlane(bottomPlane);
	}

	void CFrustum::SetFrustum(const Matrix44f& aProjectionInverse)
	{
		myPlanes.RemovePlanes();

		Vector3f frustumPoints[8] =
		{
			//Far Plane
			Vector3f /*topNearLeft		*/(-1.0f, 1.0f, 0.0f),
			Vector3f /*topNearRight		*/(1.0f, 1.0f, 0.0f),
			Vector3f /*bottomNearLeft	*/(-1.0f, -1.0f, 0.0f),
			Vector3f /*bottomNearRight	*/(1.0f, -1.0f, 0.0f),

			//near plane
			Vector3f /*topFarLeft		*/(-1.0f, 1.0f, 1.0f),
			Vector3f /*topFarRight		*/(1.0f, 1.0f,	1.0f),
			Vector3f /*bottomFarLeft	*/(-1.0f, -1.0f,1.0f),
			Vector3f /*bottomFarRight	*/(1.0f, -1.0f, 1.0f)
		};

		for (Vector3f& point : frustumPoints)
		{
			Vector4f pointo(point);
			pointo.w = 1.0f;
			pointo = pointo * aProjectionInverse;
			pointo /= pointo.w;
			point = pointo.xyz;
		}

		Plane<float> farPlane(frustumPoints[2], frustumPoints[3], frustumPoints[0]);
		Plane<float> nearPlane(frustumPoints[7], frustumPoints[6], frustumPoints[5]);
		Plane<float> leftPlane(frustumPoints[6], frustumPoints[2], frustumPoints[4]);
		Plane<float> rightPlane(frustumPoints[3], frustumPoints[7], frustumPoints[1]);
		Plane<float> topPlane(frustumPoints[0], frustumPoints[1], frustumPoints[4]);
		Plane<float> bottomPlane(frustumPoints[6], frustumPoints[7], frustumPoints[2]);

		myPlanes.AddPlane(farPlane);
		myPlanes.AddPlane(nearPlane);
		myPlanes.AddPlane(leftPlane);
		myPlanes.AddPlane(rightPlane);
		myPlanes.AddPlane(topPlane);
		myPlanes.AddPlane(bottomPlane);
	}

	bool CFrustum::IsInside(const SSphere& aSphere) const
	{
		return myPlanes.Inside(aSphere.position, aSphere.radius);
	}
}
