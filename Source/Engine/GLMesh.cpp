#include "stdafx.h"
#include "GLMesh.h"

#include "OpenGLFramework.h"
#include "VertexStructs.h"

namespace wendy
{
	CGLMesh::CGLMesh()
		: myVertexCount(0)
		, myIndexCount(0)
		, myVertexArrayID(0u)
		, myVertexBufferID(0u)
		, myIndexBufferID(0u)
	{
	}

	CGLMesh::CGLMesh(CGLMesh&& aTemporary) noexcept
		: myVertexCount(aTemporary.myVertexCount)
		, myIndexCount(aTemporary.myIndexCount)
		, myVertexArrayID(aTemporary.myVertexArrayID)
		, myVertexBufferID(aTemporary.myVertexBufferID)
		, myIndexBufferID(aTemporary.myIndexBufferID)
	{
		aTemporary.myVertexCount = 0;
		aTemporary.myIndexCount = 0;
		aTemporary.myVertexArrayID = 0;
		aTemporary.myVertexBufferID = 0;
		aTemporary.myIndexBufferID = 0;
	}

	CGLMesh::~CGLMesh()
	{
		Destroy();
	}

	CGLMesh& CGLMesh::operator=(CGLMesh&& aTemporary) noexcept
	{
		Destroy();

		myVertexCount = aTemporary.myVertexCount;
		myIndexCount = aTemporary.myIndexCount;
		myVertexArrayID = aTemporary.myVertexArrayID;
		myVertexBufferID = aTemporary.myVertexBufferID;
		myIndexBufferID = aTemporary.myIndexBufferID;

		aTemporary.myVertexCount = 0;
		aTemporary.myIndexCount = 0;
		aTemporary.myVertexArrayID = 0;
		aTemporary.myVertexBufferID = 0;
		aTemporary.myIndexBufferID = 0;

		return *this;
	}

	bool CGLMesh::Init(const int aVertexSize, const int aVertexCount, const void* aVertices, const cu::CVector<uint32_t>& aIndices, const cu::CVector<SVertexAttributeInfo>& aAttributeInfos)
	{
		myVertexCount = aVertexCount;
		myIndexCount = aIndices.Size<int>();

		glGenVertexArrays(1, &myVertexArrayID);
		glBindVertexArray(myVertexArrayID);

		glGenBuffers(1, &myVertexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, myVertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, myVertexCount * aVertexSize, aVertices, GL_STATIC_DRAW);

		for (std::uint32_t i = 0; i < aAttributeInfos.Size<std::uint32_t>(); ++i)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, aAttributeInfos[i].count, GL_FLOAT, false, aVertexSize, aAttributeInfos[i].offsetptr);
		}

		glGenBuffers(1, &myIndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, myIndexCount * sizeof(uint32_t), aIndices.data(), GL_STATIC_DRAW);

		return true;
	}

	void CGLMesh::Draw()
	{
		glBindVertexArray(myVertexArrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIndexBufferID);
		glDrawElements(GL_TRIANGLES, myIndexCount, GL_UNSIGNED_INT, nullptr);
	}

	void CGLMesh::Destroy()
	{
		if (myVertexBufferID != 0)
		{
			glDisableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &myVertexBufferID);
			myVertexBufferID = 0;
		}

		if (myIndexBufferID != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glDeleteBuffers(1, &myIndexBufferID);
			myIndexBufferID = 0;
		}

		if (myVertexArrayID != 0)
		{
			glBindVertexArray(0);
			glDeleteVertexArrays(1, &myVertexArrayID);
			myVertexArrayID = 0;
		}
	}
}
