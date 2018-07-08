#include "pch.h"

#include <vector>

#include "../MrMoCoTest/IRandomNumberSource.h"
#include "../MrMoCoTest/RandomNumberMersenneSource.h"
#include "../MrMoCoTest/IRandomNumberSorterOutput.h"
#include "../MrMoCoTest/RandomNumberSorter.h"

using mrmoco::IRandomNumberSource;
using mrmoco::RandomNumberMersenneSource;
using mrmoco::IRandomNumberSorterOutput;
using mrmoco::RandomNumberSorter;

namespace mrmocotest
{
	class TestableRandomNumberSorterOutput : public IRandomNumberSorterOutput
	{
	public:
		TestableRandomNumberSorterOutput() = default;
		~TestableRandomNumberSorterOutput() = default;
		void Output(std::vector<int> sortedValues) override
		{
			values = sortedValues;
		}
		std::vector<int> GetValues() const
		{
			return values;
		}
	private:
		std::vector<int> values;
	};

	class TestableRandomNumberSource : public IRandomNumberSource
	{
	public:
		TestableRandomNumberSource(std::vector<int> values)
			: values(values)
		{};
		~TestableRandomNumberSource() = default;
		std::vector<int> Generate(int n) const override
		{
			return values;
		}
	private:
		std::vector<int> values;
	};

	struct IncrementGenerator
	{
		int current;
		int increment;
		IncrementGenerator(int start, int increment = 1) : current(start), increment(increment) {}
		int operator() ()
		{
			return current += increment;
		}
	};

	void ValidateSorting (std::shared_ptr<TestableRandomNumberSorterOutput> controllableOutput) {
		/* Ensure that the remainder values are decreasing */
		/* Create a list of the remainders from the sorted data */
		auto outputValues = controllableOutput->GetValues();
		std::vector<int> remainders;
		std::transform(outputValues.begin(), outputValues.end(), std::back_inserter(remainders), [=](int value) -> int {
			return value % 11;
		});

		/* Ensure that the last value in the vector is the smallest */
		ASSERT_EQ(remainders.back(), *std::min_element(remainders.begin(), remainders.end()));

		/* The is_sorted function can only check if values are ascending so reverse the remainders vector */
		std::vector<int> reverseRemainders(remainders);
		std::reverse(reverseRemainders.begin(), reverseRemainders.end());
		ASSERT_TRUE(std::is_sorted(reverseRemainders.begin(), reverseRemainders.end()));
	}
}

TEST(RandomNumberSorterTest, SmallDataSetIsSortedByARemainderOfEleven)
{
	/* Generate a vector incrementing to 1000 */
	auto totalValues = 10;
	std::vector<int> values(totalValues);
	mrmocotest::IncrementGenerator generator(0);
	std::generate(values.begin(), values.end(), generator);

	/* With this design we are able control the input and output
	 of the values from the algorithm by seperating concerns
	 given the constraints of having a method returning void */

	auto controllableSource = std::make_shared<mrmocotest::TestableRandomNumberSource>(values);
	auto controllableOutput = std::make_shared<mrmocotest::TestableRandomNumberSorterOutput>();
	RandomNumberSorter(controllableSource, controllableOutput).PrintRndByEleven(totalValues);

	/* expect that the values vector will be reversed as values elements approach 11 */
	std::reverse(values.begin(), values.end());
	ASSERT_EQ(values, controllableOutput->GetValues());
}

TEST(RandomNumberSorterTest, ElementsOrderPresevedIfAllElementsAreMultiplesOfEleven)
{
	/* Generate a vector of multiples of 11 */
	auto totalValues = 1000;
	std::vector<int> values(totalValues);
	mrmocotest::IncrementGenerator generator(0, 11);
	std::generate(values.begin(), values.end(), generator);

	auto controllableSource = std::make_shared<mrmocotest::TestableRandomNumberSource>(values);
	auto controllableOutput = std::make_shared<mrmocotest::TestableRandomNumberSorterOutput>();
	RandomNumberSorter(controllableSource, controllableOutput).PrintRndByEleven(totalValues);

	/* If all values are multiples of 11 then the vector should be left unchanged */
	ASSERT_EQ(values, controllableOutput->GetValues());
}

TEST(RandomNumberSorterTest, ElementsAreSortedByARemainderOfEleven)
{
	auto totalValues = 1000;
	std::vector<int> values(totalValues);
	mrmocotest::IncrementGenerator generator (0);
	std::generate(values.begin(), values.end(), generator);

	auto controllableSource = std::make_shared<mrmocotest::TestableRandomNumberSource>(values);
	auto controllableOutput = std::make_shared<mrmocotest::TestableRandomNumberSorterOutput>();
	RandomNumberSorter(controllableSource, controllableOutput).PrintRndByEleven(totalValues);
	mrmocotest::ValidateSorting(controllableOutput);
}

TEST(RandomNumberSorterTest, RandomNumbersAreSortedByARemainderOfEleven)
{
	auto totalValues = 1000;
	auto controllableSource = std::make_shared<RandomNumberMersenneSource>();
	auto controllableOutput = std::make_shared<mrmocotest::TestableRandomNumberSorterOutput>();
	RandomNumberSorter(controllableSource, controllableOutput).PrintRndByEleven(totalValues);
	mrmocotest::ValidateSorting(controllableOutput);
}