#pragma once

#include "IRandomNumberSorterOutput.h"

namespace mrmoco
{
	class RandomNumberSorterStdOutput : public IRandomNumberSorterOutput
	{
	public:
		RandomNumberSorterStdOutput() = default;
		virtual ~RandomNumberSorterStdOutput() = default;
		void Output(std::vector<int> values) override;
	};
}