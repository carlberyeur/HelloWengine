#pragma once

namespace cu
{
	template<typename Ret, typename... Args>
	class CBaseFunction
	{
	public:
		CBaseFunction() {}
		virtual ~CBaseFunction() {}

		virtual Ret Call(Args&&... aArgs) = 0;
		virtual CBaseFunction* Copy() const = 0;
		virtual int Size() const = 0;
	};

	template <typename RealType, typename Ret, typename... Args>
	class CEraserFunction : public CBaseFunction<Ret, Args...>
	{
	public:
		CEraserFunction(RealType aFunctionObject);
		~CEraserFunction() {}

		CEraserFunction& operator=(RealType aFunctionObject);

		virtual Ret Call(Args&&... aArgs) override;
		virtual CBaseFunction<Ret, Args...>* Copy() const override;
		virtual int Size() const override;

	private:
		RealType myFunctionObject;
	};

	template <typename RealType, typename Ret, typename... Args>
	CEraserFunction<RealType, Ret, Args...>::CEraserFunction(RealType aFunctionObject)
		: myFunctionObject(aFunctionObject)
	{
	}

	template<typename RealType, typename Ret, typename... Args>
	inline CEraserFunction<RealType, Ret, Args...>& CEraserFunction<RealType, Ret, Args...>::operator=(RealType aFunctionObject)
	{
		myFunctionObject = aFunctionObject;
		return *this;
	}

	template<typename RealType, typename Ret, typename... Args>
	Ret CEraserFunction<RealType, Ret, Args...>::Call(Args&&... aArgs)
	{
		return myFunctionObject(std::forward<Args>(aArgs)...);
	}

	template<typename RealType, typename Ret, typename... Args>
	inline CBaseFunction<Ret, Args...>* CEraserFunction<RealType, Ret, Args...>::Copy() const
	{
		return new CEraserFunction(*this);
	}

	template<typename RealType, typename Ret, typename... Args>
	inline int CEraserFunction<RealType, Ret, Args...>::Size() const
	{
		return sizeof(CEraserFunction);
	}

	template<typename Ret, typename... Args>
	class CFunction
	{
	public:
		CFunction();
		CFunction(std::nullptr_t);
		CFunction(const CFunction& aCopy);
		CFunction(CFunction&& aTemporary);
		~CFunction();

		Ret operator()(Args...);

		CFunction& operator=(const CFunction& aCopy);
		CFunction& operator=(CFunction&& aTemporary);
		CFunction& operator=(std::nullptr_t);

		template<typename T>
		CFunction(T aFunction);

		template<typename T>
		CFunction& operator=(T aFunction);

		bool operator==(std::nullptr_t) const;
		bool operator!=(std::nullptr_t) const;
		bool operator!() const;
		operator bool() const;

	private:
		template<typename T>
		void Create(T aFunction);
		void Destroy();

		CBaseFunction<Ret, Args...>* myFunctionObject;
	};

	template<typename Ret, typename... Args>
	CFunction<Ret, Args...>::CFunction()
		: myFunctionObject(nullptr)
	{
	}

	template<typename Ret, typename... Args>
	inline CFunction<Ret, Args...>::CFunction(std::nullptr_t)
		: myFunctionObject(nullptr)
	{
	}

	template<typename Ret, typename... Args>
	inline CFunction<Ret, Args...>::CFunction(const CFunction& aCopy)
		: myFunctionObject(nullptr)
	{
		if (aCopy.myFunctionObject)
		{
			myFunctionObject = aCopy.myFunctionObject->Copy();
		}
	}

	template<typename Ret, typename... Args>
	inline CFunction<Ret, Args...>::CFunction(CFunction&& aTemporary)
		: myFunctionObject(aTemporary.myFunctionObject)
	{
		aTemporary.myFunctionObject = nullptr;
	}

	template<typename Ret, typename... Args>
	CFunction<Ret, Args...>::~CFunction()
	{
		Destroy();
	}

	template<typename Ret, typename... Args>
	inline Ret CFunction<Ret, Args...>::operator()(Args... aArgs)
	{
		return myFunctionObject->Call(std::forward<Args>(aArgs)...);
	}

	template<typename Ret, typename... Args>
	inline CFunction<Ret, Args...>& CFunction<Ret, Args...>::operator=(const CFunction& aCopy)
	{
		Destroy();
		if (aCopy.myFunctionObject)
		{
			myFunctionObject = aCopy.myFunctionObject->Copy();
		}
		return *this;
	}

	template<typename Ret, typename... Args>
	inline CFunction<Ret, Args...>& CFunction<Ret, Args...>::operator=(CFunction&& aTemporary)
	{
		Destroy();
		if (aTemporary.myFunctionObject)
		{
			myFunctionObject = aTemporary.myFunctionObject;
			aTemporary.myFunctionObject = nullptr;
		}
		return *this;
	}

	template<typename Ret, typename... Args>
	inline CFunction<Ret, Args...>& CFunction<Ret, Args...>::operator=(std::nullptr_t)
	{
		Destroy();
		return *this;
	}

	template<typename Ret, typename... Args>
	inline bool CFunction<Ret, Args...>::operator==(std::nullptr_t) const
	{
		return myFunctionObject == nullptr;
	}

	template<typename Ret, typename... Args>
	inline bool CFunction<Ret, Args...>::operator!=(std::nullptr_t) const
	{
		return myFunctionObject != nullptr;
	}

	template<typename Ret, typename... Args>
	inline bool CFunction<Ret, Args...>::operator!() const
	{
		return myFunctionObject == nullptr;
	}

	template<typename Ret, typename... Args>
	inline CFunction<Ret, Args...>::operator bool() const
	{
		return myFunctionObject != nullptr;
	}

	template<typename Ret, typename... Args>
	template<typename T>
	inline CFunction<Ret, Args...>::CFunction(T aFunction)
	{
		Create(aFunction);
	}

	template<typename Ret, typename... Args>
	template<typename T>
	inline CFunction<Ret, Args...>& CFunction<Ret, Args...>::operator=(T aFunction)
	{
		Destroy();
		Create(aFunction);
		return *this;
	}

	template<typename Ret, typename... Args>
	template<typename T>
	inline void CFunction<Ret, Args...>::Create(T aFunction)
	{
		myFunctionObject = new CEraserFunction<T, Ret, Args...>(aFunction);
	}

	template<typename Ret, typename... Args>
	inline void CFunction<Ret, Args...>::Destroy()
	{
		if (myFunctionObject)
		{
			delete myFunctionObject;
			myFunctionObject = nullptr;
		}
	}
}
