#pragma once

namespace cu
{
	using WorkFunction = std::function<void(void)>;
	using ConditionFunction = std::function<bool(void)>;

	class CWork
	{
	public:
		CWork();
		CWork(CWork&& aTemporary) noexcept;
		CWork(const WorkFunction& aFunction, const ConditionFunction& aIsCompleteCondition = nullptr);
		~CWork();

		CWork& operator=(CWork&& aTemporary) noexcept;

		void DoWork();
		bool IsComplete() const;

		void SetName(const std::string& aName);
		void SetName(std::string&& aName);
		const std::string& GetName() const;

		CWork(const CWork&) = delete;
		CWork& operator=(const CWork&) = delete;

	private:
		WorkFunction mySweatAndTears;
		ConditionFunction myIsComplete;
		std::string myName;
	};
}
