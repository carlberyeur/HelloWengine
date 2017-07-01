#pragma once

namespace wendy
{
	typedef struct MeshID_t* MeshID;
	typedef struct ConstantBufferID_t* ConstantBufferID;
	typedef struct TextureID_t* TextureID;

	class CBaseRenderer;

	class CModel
	{
	public:
		CModel();
		CModel(const CModel& aCopy) = default;
		~CModel();

		bool Init(const MeshID aMesh, const TextureID aTexture, const ConstantBufferID aTransformationBuffer);
		void Render(CBaseRenderer& aRenderer);

		inline const cu::Matrix44f& GetTransformation() const;
		inline const cu::Vector3f& GetPosition() const;
		inline void SetTransformation(const cu::Matrix44f& aTransformation);
		inline void SetPosition(const cu::Vector3f& aPosition);

	private:
		//CBoundingSphere myBoundingSphere
		cu::Matrix44f myTransformation;

		MeshID myMesh;
		ConstantBufferID myTransformationBuffer;
		TextureID myTexture;
	};

	inline const cu::Matrix44f& CModel::GetTransformation() const
	{
		return myTransformation;
	}

	inline const cu::Vector3f& CModel::GetPosition() const
	{
		return myTransformation.myPosition;
	}

	inline void CModel::SetTransformation(const cu::Matrix44f& aTransformation)
	{
		myTransformation = aTransformation;
	}

	inline void CModel::SetPosition(const cu::Vector3f& aPosition)
	{
		myTransformation.myPosition = aPosition;
	}
}
