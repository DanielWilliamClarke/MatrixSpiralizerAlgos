#include "pch.h"

#include <numeric>
#include "../MrMoCoTest/MatrixStringifier.h"

using mrmoco::MatrixStringifier;

/**
 * This is test suite is assert that the anticlockwise spiral traversal algorithm
 * implemented inside the Matrix Stringifier class works is able to traverse any size matrix
 */

namespace mrmocotest
{
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

	void ValidateStringification(std::vector<int> exepectedIntOutput, char* output, int totalArraySize)
	{
		std::string expectedStringValue = std::accumulate(exepectedIntOutput.begin(), exepectedIntOutput.end(), std::string(),
			[=](const std::string& a, int b) -> std::string {
			return a + (a.length() > 0 ? "," : "") + std::to_string(b);
		});

		std::ostringstream buffer;
		for (int i = 0; i < totalArraySize; i++)
		{
			if (i % 2 != 0)
			{
				buffer << output[i];
				continue;
			}
			buffer << static_cast<int>(output[i]);
		}

		ASSERT_EQ(expectedStringValue, buffer.str());
	}

	void ValidateSpiralizardMatrixSorting(char* output, int rowCount, int colCount, int totalArraySize)
	{
		auto totalValues = rowCount * colCount;
		std::vector<int> exepectedIntOutput(totalValues);
		mrmocotest::IncrementGenerator generator(0);
		std::generate(exepectedIntOutput.begin(), exepectedIntOutput.end(), generator);

		std::vector<int> actualOutputValues;
		for (int i = 0; i < totalArraySize; i += 2)
		{
			actualOutputValues.push_back(static_cast<int>(output[i]));
		}
		ASSERT_EQ(exepectedIntOutput, actualOutputValues);
		ASSERT_TRUE(std::is_sorted(actualOutputValues.begin(), actualOutputValues.end()));
		ValidateStringification(exepectedIntOutput, output, totalArraySize);
	}

	int CalculateCharArraySize(int rowCount, int colCount)
	{
		return ((rowCount * colCount) * 2) - 1;
	}
}

TEST(MatrixStringifierTest, OriginalTestData3x4MatrixCanBeSpiralised)
{
	MatrixStringifier ms;
	const auto rowCount = 3;
	const auto colCount = 4;

	/* Matrix data given in the question paper 
	   here with illustation of expected traversal */

	int matrix[rowCount][colCount] = {
		/*S*/       /*<----v--v------------*/
		/*|>*/ { 2, /*|*/  3, 4,  8 }, /*<^*/
		/*|>*/ { 5, /*v>*/ 7, 9, 12 }, /*<|*/
		/*|*/       /*--------^*/	    /*|*/
		/*v>*/ { 1,	       0, 6, 10 }   /*|*/
  		/*-----------------^--^--^-------->*/	
	};      

	/**
	 * Note. not exactly 100% about the commas, we must initialise 
	 * the char array before it can be passed in, so I would assume 
	 * that the added length from the commas needs factoring in
	 *
	 * From the ps. on the question 
	 *	- outBuffer is guaranteed to be valid and large enough to hold all of the data.
	 * I would infer that the char array must already be large enough to start with.
	 *
	 * I had a look at strlen() but if use incorrectly could make algorithm 0(n^2)
	 * I tried to make the outputBuffer resize dynamically but was not able to find
	 * clear time complexity for the strcpy_s() function 
	 */
	auto totalArraySize = mrmocotest::CalculateCharArraySize(rowCount, colCount);
	auto output = new char[totalArraySize];
	ms.StringifyMatrix(*matrix, rowCount, colCount, output);

	std::vector<int> exepectedIntOutput{ 
		2, 5, 1, // down
		0, 6, 10, // right
		12, 8, // up
		4, 3, // left
		7, // down
		9 // right
	};
	mrmocotest::ValidateStringification(exepectedIntOutput, output, totalArraySize);
	delete[] output;
}

TEST(MatrixStringifierTest, 5x5MatrixSpiralCanGenerateSortedArray)
{
	MatrixStringifier ms;
	const auto rowCount = 5;
	const auto colCount = 5;
	int matrix[rowCount][colCount] = {
		{ 1, 16, 15, 14, 13 },
		{ 2, 17, 24, 23, 12 },
		{ 3, 18, 25, 22, 11 },
		{ 4, 19, 20, 21, 10 },
		{ 5, 6,  7,  8,  9 }
	};

	auto totalArraySize = mrmocotest::CalculateCharArraySize(rowCount, colCount);
	auto output = new char[totalArraySize];
	ms.StringifyMatrix(*matrix, rowCount, colCount, output);
	mrmocotest::ValidateSpiralizardMatrixSorting(output, rowCount, colCount, totalArraySize);
	delete[] output;
}

TEST(MatrixStringifierTest, 2x3MatrixSpiralCanGenerateSortedArray)
{
	MatrixStringifier ms;
	const auto rowCount = 2;
	const auto colCount = 3;
	int matrix[rowCount][colCount] = {
		{ 1, 6, 5 },
		{ 2, 3, 4 },
	};

	auto totalArraySize = mrmocotest::CalculateCharArraySize(rowCount, colCount);
	auto output = new char[totalArraySize];
	ms.StringifyMatrix(*matrix, rowCount, colCount, output);
	mrmocotest::ValidateSpiralizardMatrixSorting(output, rowCount, colCount, totalArraySize);
	delete[] output;
}

TEST(MatrixStringifierTest, 7x7MatrixSpiralCanGenerateSortedArray)
{
	MatrixStringifier ms;
	const auto rowCount = 7;
	const auto colCount = 7;
	int matrix[rowCount][colCount] = {
		{ 1, 24, 23, 22, 21, 20, 19 },
		{ 2, 25, 40, 39, 38, 37, 18 },
		{ 3, 26, 41, 48, 47, 36, 17 },
		{ 4, 27, 42, 49, 46, 35, 16 },
		{ 5, 28, 43, 44, 45, 34, 15 },
		{ 6, 29, 30, 31, 32, 33, 14 },
		{ 7,  8,  9, 10, 11, 12, 13 },
	};

	auto totalArraySize = mrmocotest::CalculateCharArraySize(rowCount, colCount);
	auto output = new char[totalArraySize];
	ms.StringifyMatrix(*matrix, rowCount, colCount, output);
	mrmocotest::ValidateSpiralizardMatrixSorting(output, rowCount, colCount, totalArraySize);
	delete[] output;
}

TEST(MatrixStringifierTest, 10x3NonSquareSpiralCanGenerateSortedArray)
{
	MatrixStringifier ms;
	const auto rowCount = 10;
	const auto colCount = 3;
	int matrix[rowCount][colCount] = {
		{ 1,  22, 21 },
		{ 2,  23, 20 },
		{ 3,  24, 19 },
		{ 4,  25, 18 },
		{ 5,  26, 17 },
		{ 6,  27, 16 },
		{ 7,  28, 15 },
		{ 8,  29, 14 },
		{ 9,  30, 13 },
		{ 10, 11, 12 }
	};

	auto totalArraySize = mrmocotest::CalculateCharArraySize(rowCount, colCount);
	auto output = new char[totalArraySize];
	ms.StringifyMatrix(*matrix, rowCount, colCount, output);
	mrmocotest::ValidateSpiralizardMatrixSorting(output, rowCount, colCount, totalArraySize);
	delete[] output;
}