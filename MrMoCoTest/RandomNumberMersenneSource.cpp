#include "RandomNumberMersenneSource.h"

#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

using namespace mrmoco;

std::vector<int> RandomNumberMersenneSource::Generate(int n) const
{
	/* Create device and apply random number engine */
	std::random_device randomDevice;
	std::mt19937 mersenne_engine(randomDevice());
	/* Set distribution of number between 1 and 1000 */
	std::uniform_int_distribution<int> dist(1, 1e3);
	auto generator = std::bind(dist, mersenne_engine);
	/* Create vector and reserve as many spaces as required */
	std::vector<int> randomNumberArray(n);
	/* Fill vector with random numbers */
	std::generate(randomNumberArray.begin(), randomNumberArray.end(), generator);
	return randomNumberArray;
}