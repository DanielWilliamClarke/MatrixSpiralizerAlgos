#include "RandomNumberSorter.h"

#include <algorithm>

#include "IRandomNumberSource.h"
#include "IRandomNumberSorterOutput.h"

using namespace mrmoco;

RandomNumberSorter::RandomNumberSorter(std::shared_ptr<IRandomNumberSource> source, std::shared_ptr<IRandomNumberSorterOutput> output)
	: source(source), output(output), sortCoefficient(11)
{}

/* Please view RandomNumberSorterTest for unit tests */

void RandomNumberSorter::PrintRndByEleven(int n) const
{
	auto values = source->Generate(n);

	std::sort(values.begin(), values.end(),	[&](int a, int b) -> bool {
		auto aRemainder = a % sortCoefficient;
		auto bRemainder = b % sortCoefficient;
		return aRemainder > bRemainder;
	});
	
	output->Output(values);
}