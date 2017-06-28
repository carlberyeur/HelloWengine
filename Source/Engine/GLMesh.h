#pragma once

namespace wendy
{
	struct SVertexAttributeInfo;
	
	class CGLMesh
	{
	public:
		CGLMesh();
		CGLMesh(const CGLMesh& aCopy) = delete;
		CGLMesh(CGLMesh&& aTemporary) noexcept;
		~CGLMesh();

		CGLMesh& operator=(CGLMesh&& aTemporary) noexcept;

		bool Init(const int aVertexSize, const int aVertexCount, const void* aVertices, const cu::CVector<uint32_t>& aIndices, const cu::CVector<SVertexAttributeInfo>& aAttributeInfos);
		void Draw();

		inline bool IsInitialized() const;

		template <typename VertexType>
		inline bool Init(const cu::CVector<VertexType>& aVertices, const cu::CVector<uint32_t>& aIndices);

	private:
		void Cleanup();

		std::int32_t myVertexCount;
		std::int32_t myIndexCount;

		std::uint32_t myVertexArrayID;
		std::uint32_t myVertexBufferID;
		std::uint32_t myIndexBufferID;
	};

	inline bool wendy::CGLMesh::IsInitialized() const
	{
		return myVertexCount > 0;
	}

	template<typename VertexType>
	inline bool CGLMesh::Init(const cu::CVector<VertexType>& aVertices, const cu::CVector<uint32_t>& aIndices)
	{
		return Init(sizeof(VertexType), aVertices.Size<int>(), aVertices.data(), aIndices, VertexType::AttributeInfos);
	}
}
