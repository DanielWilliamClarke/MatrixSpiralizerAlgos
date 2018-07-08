#include <iostream>
#include <memory>
#include <sstream>

#include "../MrMoCoTest/MatrixStringifier.h"
using mrmoco::MatrixStringifier;

#include "../MrMoCoTest/RandomNumberMersenneSource.h"
#include "../MrMoCoTest/RandomNumberSorterStdOutput.h"
#include "../MrMoCoTest/RandomNumberSorter.h"
using mrmoco::RandomNumberMersenneSource;
using mrmoco::RandomNumberSorterStdOutput;
using mrmoco::RandomNumberSorter;

namespace mrmococonsole
{
	void PrintMatrixSprial(int totalArraySize, char* output) 
	{
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
		std::cout << buffer.str() << std::endl;
	}

	void PerformTraversal(int *matrix, int row, int column) {
		MatrixStringifier ms;
		auto totalArraySize = ((row * column) * 2) - 1;
		auto output = new char[totalArraySize];
		ms.StringifyMatrix(matrix, row, column, output);
		mrmococonsole::PrintMatrixSprial(totalArraySize, output);
		delete[] output;
	}

	void Question2() 
	{
		std::cout 
			<< "Question 2" << std::endl << std::endl 
			<< "Write a O(n) function with the following signature that, given a matrix of integers" << std::endl
			<< "builds a string with the entries of that matrix appended in anticlockwise order." << std::endl;

		std::cout << std::endl << "3 x 4 matrix should print values are shown in question paper" << std::endl;
		const auto rowCountSmall = 3;
		const auto colCountSmall = 4;
		int smallMatrix[rowCountSmall][colCountSmall] = {
			{ 2, 3, 4, 8 },
			{ 5, 7, 9, 12 },
			{ 1, 0, 6, 10 }
		};
		PerformTraversal(*smallMatrix, rowCountSmall, colCountSmall);
	
		std::cout << std::endl << "7 x 7 matrix should print values in order" << std::endl;
		const auto rowCountLarge = 7;
		const auto colCountLarge = 7;
		int largeMatrix[rowCountLarge][colCountLarge] = {
			{ 1, 24, 23, 22, 21, 20, 19 },
			{ 2, 25, 40, 39, 38, 37, 18 },
			{ 3, 26, 41, 48, 47, 36, 17 },
			{ 4, 27, 42, 49, 46, 35, 16 },
			{ 5, 28, 43, 44, 45, 34, 15 },
			{ 6, 29, 30, 31, 32, 33, 14 },
			{ 7,  8,  9, 10, 11, 12, 13 },
		};
		PerformTraversal(*largeMatrix, rowCountLarge, colCountLarge);

		std::cout << std::endl << "Please See attached unit tests for further validation (MatrixStringifierTest)" << std::endl;
	}

	void Question3()
	{
		std::cout
			<< "Question 3" << std::endl << std::endl 
			<< "Using the Standard Library and C++(03, 11 or 14) write a function with the following" << std::endl
			<< "signature that generates a list of random numbers between 1 and 1000, sort them" << std::endl
			<< "comparing the remainder of a division by 11 and starting from the bigger reminder," << std::endl
			<< "and print them on the standard output." << std::endl;

		auto totalValues = 1000;
		std::cout << std::endl << totalValues << " Sorted Elements" << std::endl;
		auto controllableSource = std::make_shared<RandomNumberMersenneSource>();
		auto controllableOutput = std::make_shared<RandomNumberSorterStdOutput>();
		RandomNumberSorter(controllableSource, controllableOutput).PrintRndByEleven(totalValues);
		std::cout << std::endl << "Please See attached unit tests for further validation (RandomNumberSorterTest)" << std::endl;
	}
}

int main()
{
	mrmococonsole::Question2();
	std::cout << std::endl;
	mrmococonsole::Question3();
	return 0;
}