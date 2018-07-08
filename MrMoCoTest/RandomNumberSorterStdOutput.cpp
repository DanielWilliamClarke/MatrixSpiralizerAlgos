#include "RandomNumberSorterStdOutput.h"

#include <iostream>
#include <string>
#include <numeric>

using namespace mrmoco;

void RandomNumberSorterStdOutput::Output(std::vector<int> values)
{
	/* generate a stringified vector as printing each vector element will be slower */
	std::string stringified = std::accumulate(values.begin(), values.end(), std::string(),
		[=](const std::string& a, int b) -> std::string {
		return a + (a.length() > 0 ? ", " : "") + std::to_string(b);
	});

	std::cout << stringified << std::endl;
}