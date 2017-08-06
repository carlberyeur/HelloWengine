#pragma once

namespace cu
{
	struct SSphere;
}

namespace wendy
{
	typedef struct MeshID_t* MeshID;
	typedef struct ConstantBufferID_t* ConstantBufferID;
	typedef struct TextureID_t* TextureID;
	typedef struct SurfaceID_t* SurfaceID;

	class CBaseRenderer;

	class CModel
	{
	public:
		CModel();
		CModel(const CModel& aCopy) = default;
		~CModel();

		bool Init(const MeshID aMesh, const /*TextureID*/SurfaceID aTexture, const ConstantBufferID aTransformationBuffer, const ConstantBufferID aAlbedoBuffer);
		void Render(CBaseRenderer& aRenderer);

		cu::SSphere GetBoundingSphere() const;

		inline const cu::Matrix44f& GetTransformation() const;
		inline const cu::Vector3f& GetPosition() const;
		inline cu::Matrix44f& GetTransformation();
		inline cu::Vector3f& GetPosition();
		inline cu::Vector4f& GetPosition4();

		inline void SetTransformation(const cu::Matrix44f& aTransformation);
		inline void SetPosition(const cu::Vector3f& aPosition);
		inline void SetPosition(const float aX, const float aY, const float aZ);

	private:
		cu::Matrix44f myTransformation;

		MeshID myMesh;
		ConstantBufferID myTransformationBuffer;
		/*TextureID*/SurfaceID myTexture;
		ConstantBufferID myAlbedoBuffer;

		float myRadius;
	};

	inline const cu::Matrix44f& CModel::GetTransformation() const
	{
		return myTransformation;
	}

	inline cu::Matrix44f& CModel::GetTransformation()
	{
		return myTransformation;
	}

	inline const cu::Vector3f& CModel::GetPosition() const
	{
		return myTransformation.myPosition;
	}

	inline cu::Vector3f& CModel::GetPosition()
	{
		return myTransformation.myPosition;
	}

	inline cu::Vector4f& CModel::GetPosition4()
	{
		return myTransformation.myPosition4;
	}

	inline void CModel::SetTransformation(const cu::Matrix44f& aTransformation)
	{
		myTransformation = aTransformation;
	}

	inline void CModel::SetPosition(const cu::Vector3f& aPosition)
	{
		myTransformation.myPosition = aPosition;
	}

	inline void CModel::SetPosition(const float aX, const float aY, const float aZ)
	{
		myTransformation.myPosition.Set(aX, aY, aZ);
	}
}
