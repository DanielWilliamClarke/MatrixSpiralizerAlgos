#pragma once

#include <vector>

namespace mrmoco
{
	class IRandomNumberSource
	{
	public:
		virtual ~IRandomNumberSource() = default;
		virtual std::vector<int> Generate(int n) const = 0;
	};
}