#pragma once
#include "Frustum.h"

namespace cu
{
	struct SSphere;

	class Camera
	{
	public:
		Camera();
		~Camera();

		void Init(const float aFov, const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar);
		void InitOrthographic(const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar);

		void ReInit(const float aFov, const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar);
		void ReInitOrthoGraphic(const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar);
		void ReInit(const Matrix44f& aProjection, const Matrix44f& aTransformation);

		void SetTransformation(const Matrix44f& aTransformation);
		const Vector3f& GetPosition() const;
		void SetPosition(const Vector3f& aPosition);

		void LookAt(const Vector3f& aPosition);
		void Roll(const float aAngle);
		void Pitch(const float aAngle);
		void Yaw(const float aAngle);

		bool IsInside(const SSphere& aSphere) const;
		Vector2f GetProjectionSize() const;

		inline const Matrix44f& GetTransformation() const;
		inline const Matrix44f& GetTransformationInverse() const;
		inline const Matrix44f& GetProjection() const;
		inline const Matrix44f& GetProjectionInverse() const;

		inline float GetProjectionWidth() const;
		inline float GetProjectionHeight() const;
		inline float GetFar() const;
		inline float GetNear() const;
		inline float GetFOV() const;

	private:
		Matrix44f myTransformation;
		Matrix44f myProjection;
		Matrix44f myProjectionInverse;

		CFrustum myFrustum;

		float myWidth;
		float myHeight;
		float myNear;
		float myFar;
		float myFOV;
	};

	const Matrix44f& Camera::GetTransformation() const
	{
		return myTransformation;
	}

	const Matrix44f& Camera::GetTransformationInverse() const
	{
		return myTransformation.GetFastInverse();
	}

	const Matrix44f& Camera::GetProjection() const
	{
		return myProjection;
	}

	const Matrix44f& Camera::GetProjectionInverse() const
	{
		return myProjectionInverse;
	}

	inline float Camera::GetProjectionWidth() const
	{
		return myWidth;
	}

	inline float Camera::GetProjectionHeight() const
	{
		return myHeight;
	}

	inline float Camera::GetNear() const
	{
		return myNear;
	}

	inline float Camera::GetFar() const
	{
		return myFar;
	}

	inline float Camera::GetFOV() const
	{
		return myFOV;
	}
}
