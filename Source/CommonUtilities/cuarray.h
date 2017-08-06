#pragma once
#include <array>

namespace cu
{
	template <typename T, size_t SIZE>
	class CArray : public std::array<T, SIZE>
	{
	public:
		CArray();
		CArray(const T& aObject);
		CArray(const std::initializer_list<T>& aInitializerList);
		CArray(const std::array<T, SIZE>& aArray);

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
	
	template<typename T, size_t SIZE>
	inline CArray<T, SIZE>::CArray()
	{
	}

	template<typename T, size_t SIZE>
	inline CArray<T, SIZE>::CArray(const T& aObject)
	{
		this->fill(aObject);
	}

	template<typename T, size_t SIZE>
	inline CArray<T, SIZE>::CArray(const std::initializer_list<T>& aInitializerList)
	{
		size_t i = 0;
		for (const T& object : aInitializerList)
		{
			if (i >= SIZE)
			{
				break;
			}

			this->at(i++) = object;
		}
	}
	
	template<typename T, size_t SIZE>
	inline CArray<T, SIZE>::CArray(const std::array<T, SIZE>& aArray)
		: std::array<T, SIZE>(aArray)
	{
	}

	template<typename T, size_t SIZE>
	inline size_t CArray<T, SIZE>::Find(const T& aElement) const
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			if (this->at(i) == aElement)
			{
				return i;
			}
		}

		return FoundNone;
	}

	template<typename T, size_t SIZE>
	template<typename SizeType>
	inline T& CArray<T, SIZE>::At(const SizeType aIndex)
	{
		return this->at(static_cast<size_t>(aIndex));
	}

	template<typename T, size_t SIZE>
	template<typename SizeType>
	inline const T& CArray<T, SIZE>::At(const SizeType aIndex) const
	{
		return this->at(static_cast<size_t>(aIndex));
	}

	template<typename T, size_t SIZE>
	template<typename SizeType>
	inline SizeType CArray<T, SIZE>::Size() const
	{
		return static_cast<SizeType>(SIZE);
	}

	template<typename T, size_t SIZE>
	template<typename SizeType>
	inline SizeType CArray<T, SIZE>::ByteSize() const
	{
		return static_cast<SizeType>(SIZE * sizeof(T));
	}
}