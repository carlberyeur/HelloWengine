#pragma once
namespace cu
{
	template<typename TYPE>
	class Plane
	{
	public:
		Plane();
		Plane(const Point3<TYPE>& aFirstPoint, const Point3<TYPE>& aSecondPoint, const Point3<TYPE>& aThirdPoint);
		Plane(const Point3<TYPE>& aPoint, const Vector3<TYPE>& aNormal);

		void SetWith3Points(const Point3<TYPE>& aFirstPoint, const Point3<TYPE>& aSecondPoint, const Point3<TYPE>& aThirdPoint);
		void SetWithPointAndNormal(const Point3<TYPE>& aPoint, const Vector3<TYPE>& aNormal);
		void SetWithCoefficients(const TYPE aA, const TYPE aB, const TYPE aC, const TYPE aW);

		bool IsInside(const Point3<TYPE>& aPoint) const;
		bool IsInside(const Point3<TYPE>& aPoint, const float aRadius) const;

		bool operator==(const Plane<TYPE>& aRight) const;
		bool operator!=(const Plane<TYPE>& aRight) const;

	private:
		Point3<TYPE> myPoint;
		Vector3<TYPE> myNormal;
	};

	template <typename TYPE>
	Plane<TYPE>::Plane()
	{
	}

	template <typename TYPE>
	Plane<TYPE>::Plane(const Point3<TYPE> &aFirstPoint, const Point3<TYPE> &aSecondPoint, const Point3<TYPE> &aThirdPoint)
	{
		SetWith3Points(aFirstPoint, aSecondPoint, aThirdPoint);
	}

	template <typename TYPE>
	Plane<TYPE>::Plane(const Point3<TYPE> &aPoint, const Vector3<TYPE> &aNormal)
	{
		SetWithPointAndNormal(aPoint, aNormal);
	}

	template <typename TYPE>
	void Plane<TYPE>::SetWith3Points(const Point3<TYPE> &aFirstPoint, const Point3<TYPE> &aSecondPoint, const Point3<TYPE> &aThirdPoint)
	{
		myPoint = aFirstPoint;
		myNormal = (aThirdPoint - aFirstPoint).Cross(aSecondPoint - aFirstPoint).Normalize();
	}

	template <typename TYPE>
	void Plane<TYPE>::SetWithPointAndNormal(const Point3<TYPE> &aPoint, const Vector3<TYPE> &aNormal)
	{
		myPoint = aPoint;
		myNormal = aNormal;
	}

	template<typename TYPE>
	void Plane<TYPE>::SetWithCoefficients(const TYPE aA, const TYPE aB, const TYPE aC, const TYPE aW)
	{
		myNormal = Vector3f(aA, aB, aC);
		float length = myNormal.Length();
		myNormal.Normalize();
		myPoint = { 0.0f, 0.0f,0.0f };
	}

	template <typename TYPE>
	bool Plane<TYPE>::IsInside(const Point3<TYPE> &aPoint) const
	{
		Vector3<TYPE> temp = aPoint - myPoint;

		if (temp.Dot(myNormal) < 0)
		{
			return true;
		}

		return false;

	}

	template<typename TYPE>
	bool Plane<TYPE>::IsInside(const Point3<TYPE>& aPoint, const float aRadius) const
	{
		Vector3<TYPE> temp = aPoint - (myPoint + (myNormal * aRadius));

		if (temp.Dot(myNormal) < 0)
		{
			return true;
		}

		return false;
	}

	template<typename TYPE>
	inline bool Plane<TYPE>::operator==(const Plane<TYPE>& aRight) const
	{
		return (myPoint == aRight.myPoint && myNormal == aRight.myNormal);
	}

	template<typename TYPE>
	inline bool Plane<TYPE>::operator!=(const Plane<TYPE>& aRight) const
	{
		return !(*this == aRight);
	}

}