#pragma once
#include <vector>

#include "IRandomNumberSource.h"

namespace mrmoco
{
	class RandomNumberMersenneSource : public IRandomNumberSource
	{
	public:
		RandomNumberMersenneSource() = default;
		virtual ~RandomNumberMersenneSource() = default;
		std::vector<int> Generate(int n) const override;
	};
}