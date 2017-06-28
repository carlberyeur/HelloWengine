#pragma once

namespace cu
{
	template<typename T, typename SizeType = std::size_t>
	class CSynchronizer
	{
	public:
		CSynchronizer();
		CSynchronizer(const CSynchronizer& aCopy) = delete;
		~CSynchronizer();

		inline const T& At(const SizeType aIndex);
		inline void Write(const T& aObject);
		inline SizeType ReadSize() const;

		inline const T& operator[](const SizeType aIndex);
		inline void operator <<(const T& aObject);
		inline SizeType operator!() const;

		inline void SwapWrite();
		inline void SwapRead();
		inline void ClearWrite();
		inline void ClearAll();

	private:
		std::array<cu::CVector<T>, 3> myBuffers;

		std::mutex mySwapMutex;

		std::uint8_t myWriteTo;
		std::uint8_t myReadFrom;
		std::uint8_t myFreeBuffer;

		std::atomic_bool myHasFresh;

		static const SizeType BufferSize = 512;
	};

	template<typename T, typename SizeType>
	inline void CSynchronizer<T, SizeType>::ClearAll()
	{
		for (size_t i = 0; i < myBuffers.size(); ++i)
		{
			myBuffers[i].DeleteAll();
		}
	}

	template<typename T, typename SizeType>
	inline CSynchronizer<T, SizeType>::CSynchronizer()
	{
		myBuffers[0].reserve(BufferSize);
		myBuffers[1].reserve(BufferSize);
		myBuffers[2].reserve(BufferSize);

		myWriteTo = 0;
		myReadFrom = 1;
		myFreeBuffer = 2;

		myHasFresh = false;
	}

	template<typename T, typename SizeType>
	inline CSynchronizer<T, SizeType>::~CSynchronizer()
	{
		ClearAll();
	}

	template<typename T, typename SizeType>
	inline const T& CSynchronizer<T, SizeType>::At(const SizeType aIndex)
	{
		return myBuffers[myReadFrom][aIndex];
	}

	template<typename T, typename SizeType>
	inline void CSynchronizer<T, SizeType>::Write(const T& aObject)
	{
		myBuffers[myWriteTo].push_back(aObject);
	}

	template<typename T, typename SizeType>
	inline SizeType CSynchronizer<T, SizeType>::ReadSize() const
	{
		return myBuffers[myReadFrom].Size<SizeType>();
	}

	template<typename T, typename SizeType>
	const T& CSynchronizer<T, SizeType>::operator[](const SizeType aIndex)
	{
		return At(aIndex);
	}

	template<typename T, typename SizeType>
	inline void CSynchronizer<T, SizeType>::operator<<(const T& aObject)
	{
		Write(aObject);
	}

	template<typename T, typename SizeType>
	inline SizeType CSynchronizer<T, SizeType>::operator!() const
	{
		return ReadSize();
	}

	template<typename T, typename SizeType>
	inline void CSynchronizer<T, SizeType>::SwapWrite()
	{
		mySwapMutex.lock();

		std::uint8_t lastFree = myFreeBuffer;
		myFreeBuffer = myWriteTo;
		myWriteTo = lastFree;

		myHasFresh = true;

		mySwapMutex.unlock();

		ClearWrite();

	}

	template<typename T, typename SizeType>
	inline void CSynchronizer<T, SizeType>::SwapRead()
	{
		if (!myHasFresh)
		{
			return;
		}

		mySwapMutex.lock();

		myHasFresh = false;

		std::uint8_t lastFree = myFreeBuffer;
		myFreeBuffer = myReadFrom;
		myReadFrom = lastFree;

		mySwapMutex.unlock();
	}

	template<typename T, typename SizeType>
	inline void CSynchronizer<T, SizeType>::ClearWrite()
	{
		myBuffers[myWriteTo].DeleteAll();
	}
}
