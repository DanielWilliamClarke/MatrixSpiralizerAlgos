#pragma once

#include <memory>

namespace mrmoco
{
	class IRandomNumberSource;
	class IRandomNumberSorterOutput;
	class RandomNumberSorter
	{
	public:
		RandomNumberSorter(std::shared_ptr<IRandomNumberSource> source, std::shared_ptr<IRandomNumberSorterOutput> output);
		virtual ~RandomNumberSorter() = default;
		void PrintRndByEleven(int n) const;
	private:
		std::shared_ptr<IRandomNumberSource> source;
		std::shared_ptr<IRandomNumberSorterOutput> output;
		const int sortCoefficient;
	};
}