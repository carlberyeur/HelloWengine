#pragma once

namespace pulp
{
	class CGLUniformBuffer
	{
	public:
		CGLUniformBuffer();
		CGLUniformBuffer(const int aLocation);
		CGLUniformBuffer(const CGLUniformBuffer& aCopy) = default;
		~CGLUniformBuffer();

		template <typename T>
		void SetData(const T& aType);

	private:
		int myLocation;
	};
}
