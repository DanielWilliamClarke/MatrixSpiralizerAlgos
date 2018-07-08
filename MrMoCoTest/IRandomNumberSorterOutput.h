#pragma once

#include <vector>

namespace mrmoco
{
	class IRandomNumberSorterOutput
	{
	public:
		virtual ~IRandomNumberSorterOutput() = default;
		virtual void Output(std::vector<int> values) = 0;
	};
}