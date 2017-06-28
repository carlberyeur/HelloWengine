#pragma once

#include <vector>

namespace cu
{
	template <typename T>
	class CVector : public std::vector<T>
	{
	public:
		CVector();
		CVector(size_t aSize);
		CVector(size_t aSize, const T& aObject);
		CVector(const std::initializer_list<T>& aInitializerList);
		CVector(const std::vector<T>& aVector);
		CVector(T* aBegin, T* aEnd);
		~CVector();

		void Add();
		void AddChunk(const void* aData, const size_t aByteSize);

		void Remove(const T& aElement);
		void RemoveCyclic(const T& aElement);
		void RemoveAtIndex(const size_t aIndex);
		void RemoveCyclicAtIndex(const size_t aIndex);
		void DeleteAll();

		T* TryGet(const size_t aIndex);
		const T* TryGet(const size_t aIndex) const;

		bool HasIndex(const size_t aIndex) const;
		size_t Find(const T& aElement) const;

		template<typename SizeType>
		T& At(const SizeType aIndex);

		template<typename SizeType>
		const T& At(const SizeType aIndex) const;

		template<typename SizeType>
		SizeType Size() const;

		template<typename SizeType = size_t>
		SizeType ByteSize() const;

		static const size_t FoundNone = static_cast<size_t>(-1);
	};

	template<typename T>
	inline CVector<T>::CVector()
		: std::vector<T>()
	{
	}

	template<typename T>
	inline CVector<T>::CVector(size_t aSize)
		: std::vector<T>(aSize)
	{
	}

	template<typename T>
	inline CVector<T>::CVector(size_t aSize, const T& aObject)
		: std::vector<T>(aSize, aObject)
	{
	}

	template<typename T>
	inline CVector<T>::CVector(const std::initializer_list<T>& aInitializerList)
		: std::vector<T>(aInitializerList)
	{
	}

	template<typename T>
	inline CVector<T>::CVector(const std::vector<T>& aVector)
		: std::vector<T>(aVector)
	{
	}

	template<typename T>
	inline CVector<T>::CVector(T* aBegin, T* aEnd)
		: std::vector<T>(aBegin, aEnd)
	{
	}

	template<typename T>
	inline CVector<T>::~CVector()
	{
	}

	template<typename T>
	inline void CVector<T>::Add()
	{
		T t;
		push_back(std::move(t));
	}

	template<typename T>
	inline void CVector<T>::AddChunk(const void* aData, const size_t aByteSize)
	{
		static_assert(std::is_trivially_copyable<T>(), "Element type is not trivially copyable");

		size_t newSize = aByteSize / sizeof(T);
		resize(newSize);
		memcpy(data(), aData, aByteSize);
	}

	template<typename T>
	inline void CVector<T>::Remove(const T& aElement)
	{
		size_t index = Find(aElement);
		if (index != FoundNone)
		{
			RemoveAtIndex(index);
		}
	}

	template<typename T>
	inline void CVector<T>::RemoveCyclic(const T& aElement)
	{
		size_t index = Find(aElement);
		if (index != FoundNone)
		{
			RemoveCyclicAtIndex(index);
		}
	}
	
	template<typename T>
	inline void CVector<T>::RemoveAtIndex(const size_t aIndex)
	{
		erase(begin() + aIndex);
	}
	
	template<typename T>
	inline void CVector<T>::RemoveCyclicAtIndex(const size_t aIndex)
	{
		if (size() > 1)
		{
			at(aIndex) = std::move(at(size() - 1));
		}

		pop_back();
	}

	template<typename T>
	inline void CVector<T>::DeleteAll()
	{
		for (size_t i = 0; i < size(); ++i)
		{
			delete at(i);
		}

		clear();
	}

	template<typename T>
	inline T* CVector<T>::TryGet(const size_t aIndex)
	{
		if (HasIndex(aIndex))
		{
			return &at(aIndex);
		}

		return nullptr;
	}

	template<typename T>
	inline const T* CVector<T>::TryGet(const size_t aIndex) const
	{
		if (HasIndex(aIndex))
		{
			return &at(aIndex);
		}

		return nullptr;
	}

	template<typename T>
	inline bool CVector<T>::HasIndex(const size_t aIndex) const
	{
		return aIndex < size();
	}

	template<typename T>
	inline size_t CVector<T>::Find(const T& aElement) const
	{
		for (size_t i = 0; i < size(); ++i)
		{
			if (at(i) == aElement)
			{
				return i;
			}
		}

		return FoundNone;
	}

	template<typename T>
	template<typename SizeType>
	inline T& CVector<T>::At(const SizeType aIndex)
	{
		return at(static_cast<size_t>(aIndex));
	}

	template<typename T>
	template<typename SizeType>
	inline const T& CVector<T>::At(const SizeType aIndex) const
	{
		return at(static_cast<size_t>(aIndex));
	}

	template<typename T>
	template<typename SizeType>
	inline SizeType CVector<T>::Size() const
	{
		return static_cast<SizeType>(size());
	}

	template<typename T>
	template<typename SizeType>
	inline SizeType CVector<T>::ByteSize() const
	{
		return static_cast<SizeType>(size() * sizeof(T));
	}
}