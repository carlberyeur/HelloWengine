#include "stdafx.h"
#include "Camera.h"
#include "Intersection.h"

namespace cu
{
	Camera::Camera()
		: myWidth(0.f)
		, myHeight(0.f)
		, myNear(0.f)
		, myFar(0.f)
		, myFOV(0.f)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Init(const float aFov, const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar)
	{
		myProjection = Matrix44f::CreateProjectionMatrixLH(aNear, aFar, aProjectionWidth, aProjectionHeight, aFov);
		myProjectionInverse = myProjection.GetInverse();

		myFrustum.SetFrustum(myProjectionInverse);

		myFar = aFar;
		myNear = aNear;
		myFOV = aFov;

		myWidth = aProjectionWidth;
		myHeight = aProjectionHeight;
	}

	void Camera::InitOrthographic(const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar)
	{
		myProjection = myProjection.CreateOrthogonalProjectionMatrixLH(aNear, aFar, aProjectionWidth, aProjectionHeight);
		myProjectionInverse = myProjection.GetInverse();

		myFrustum.SetFrustum(myProjectionInverse);

		myFar = aFar;
		myNear = aNear;

		myWidth = aProjectionWidth;
		myHeight = aProjectionHeight;
	}

	void Camera::ReInit(const float aFov, const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar)
	{
		Init(aFov, aProjectionWidth, aProjectionHeight, aNear, aFar);
	}

	void Camera::ReInitOrthoGraphic(const float aProjectionWidth, const float aProjectionHeight, const float aNear, const float aFar)
	{
		InitOrthographic(aProjectionWidth, aProjectionHeight, aNear, aFar);
		myFOV = 0.f;
	}

	void Camera::ReInit(const Matrix44f& aProjection, const Matrix44f& aTransformation)
	{
		myProjection = aProjection;
		myTransformation = aTransformation;
		myProjectionInverse = aProjection.GetInverse();
		myFrustum.SetFrustum(myProjectionInverse);
	}

	void Camera::SetTransformation(const Matrix44f& aTransformation)
	{
		myTransformation = aTransformation;
	}

	const Vector3f& Camera::GetPosition() const
	{
		return myTransformation.myPosition;
	}

	void Camera::SetPosition(const Vector3f& aPosition)
	{
		myTransformation.myPosition = aPosition;
	}

	void Camera::LookAt(const Vector3f& aPosition)
	{
		myTransformation.LookAt(aPosition);
	}

	void Camera::Roll(const float aAngle)
	{
		myTransformation = myTransformation.CreateRotateAroundZ(aAngle) * myTransformation;
	}

	void Camera::Pitch(const float aAngle)
	{
		myTransformation = myTransformation.CreateRotateAroundX(aAngle) * myTransformation;
	}

	void Camera::Yaw(const float aAngle)
	{
		myTransformation = myTransformation.CreateRotateAroundY(aAngle) * myTransformation;
	}

	bool Camera::IsInside(const SSphere& aSphere) const
	{
		Matrix44f inverse = GetTransformationInverse();
		SSphere sphere = aSphere;
		sphere.position = aSphere.position * inverse;
		return myFrustum.IsInside(sphere);
	}

	Vector2f Camera::GetProjectionSize() const
	{
		return Vector2f(myWidth, myHeight);
	}
}
