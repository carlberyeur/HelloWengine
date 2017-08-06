#pragma once
#include "Plane.h"

namespace cu
{
	template<typename TYPE>
	class PlaneVolume
	{
	public:
		PlaneVolume();
		PlaneVolume(const cu::CVector<Plane<TYPE>>& aPlanes);
		~PlaneVolume();

		void AddPlane(const Plane<TYPE>& aPlane);
		void RemovePlanes();

		bool Inside(const Point3<TYPE>& aPoint) const;
		bool Inside(const Point3<TYPE>& aPoint, const float aRadius) const;

	private:
		cu::CVector<Plane<TYPE>> myPlanes;
	};

	template<typename TYPE>
	PlaneVolume<TYPE>::PlaneVolume()
	{
		myPlanes.reserve(6);
	}

	template<typename TYPE>
	PlaneVolume<TYPE>::PlaneVolume(const cu::CVector<Plane<TYPE>>& aPlanes)
	{
		myPlanes = aPlanes;
	}

	template<typename TYPE>
	PlaneVolume<TYPE>::~PlaneVolume()
	{
	}

	template<typename TYPE>
	void PlaneVolume<TYPE>::AddPlane(const Plane<TYPE>& aPlane)
	{
		myPlanes.push_back(aPlane);
	}

	template<typename TYPE>
	void PlaneVolume<TYPE>::RemovePlanes()
	{
		myPlanes.clear();
	}

	template<typename TYPE>
	bool PlaneVolume<TYPE>::Inside(const Point3<TYPE> &aPoint) const
	{
		for (Plane<TYPE>& plane : myPlanes)
		{
			if (plane.IsInside(aPoint) == false)
			{
				return false;
			}
		}

		return true;
	}
	
	template<typename TYPE>
	bool PlaneVolume<TYPE>::Inside(const Point3<TYPE>& aPoint, const float aRadius) const
	{
		for (const Plane<TYPE>& plane : myPlanes)
		{
			if (plane.IsInside(aPoint, aRadius) == false)
			{
				return false;
			}
		}

		return true;
	}
}