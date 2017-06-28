#include "stdafx.h"
#include "Work.h"

#define that_(boolean_expression) (boolean_expression)
#define _exist

namespace cu
{
	CWork::CWork()
	{
	}

	CWork::CWork(CWork&& aTemporary) noexcept
		: mySweatAndTears(std::move(aTemporary.mySweatAndTears))
		, myIsComplete(std::move(aTemporary.myIsComplete))
		, myName(std::move(aTemporary.myName))
	{
		assert(that_(mySweatAndTears)_exist);
	}

	CWork::CWork(const WorkFunction& aFunction, const ConditionFunction& aIsCompleteCondition)
		: mySweatAndTears(aFunction)
		, myIsComplete(aIsCompleteCondition)
	{
		assert(that_(mySweatAndTears)_exist);
	}

	CWork::~CWork()
	{
	}

	CWork& CWork::operator=(CWork&& aTemporary) noexcept
	{
		mySweatAndTears = std::move(aTemporary.mySweatAndTears);
		myIsComplete = std::move(aTemporary.myIsComplete);
		myName = std::move(aTemporary.myName);

		return *this;
	}

	void CWork::DoWork()
	{
		assert(that_(mySweatAndTears)_exist);

		if (mySweatAndTears)
		{
			mySweatAndTears();
		}
	}

	bool CWork::IsComplete() const
	{
		if (myIsComplete)
		{
			return myIsComplete();
		}

		return true;
	}

	void CWork::SetName(const std::string& aName)
	{
		myName = aName;
	}

	void CWork::SetName(std::string&& aName)
	{
		myName = std::move(aName);
	}

	const std::string& CWork::GetName() const
	{
		return myName;
	}
}
