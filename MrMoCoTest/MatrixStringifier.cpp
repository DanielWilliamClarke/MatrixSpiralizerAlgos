#include "MatrixStringifier.h"

using namespace mrmoco;

MatrixStringifier::MatrixStringifier()
	: directions({
		{ 0, 1 }, // down
		{ 1, 0 }, // right
		{ 0, -1 }, // left
		{ -1, 0 } // up
		})
{}

/**
 * A way to tackle this anticlockwise spiral travesal algorithm is to
 * think of the matrix like an onion, and traverse around the perimeter
 * of each matrix layer, then move inward to the next layer, until the center is reached
 * in this algorithm we reach the center when we have iterated rows * columns (plus delimiters) times
 * Please view MatrixStringifierTest for unit tests
 */

void MatrixStringifier::StringifyMatrix(int* matrix, int rows, int columns, char* outBuffer) const
{
	/* Create initial traveral indices */
	auto rowIndex = 0, colIndex = 0, dirIndex = 0;

	/* Create initial traversal limits */
	auto rootLimit = 0, columnLimit = rows - 1, rowLimit = columns - 1;

	/* There will always be one less comma than there are elements in the matrix */
	auto totalArraySize = ((rows * columns) * 2) - 1;
	for (int currentIteration = 0; currentIteration < totalArraySize; currentIteration++)
	{
		/* If an odd index then add a comma */
		if (currentIteration % 2 != 0)
		{
			outBuffer[currentIteration] = ',';
			continue;
		}

		/* GET PHASE */
		/* Push value into the output buffer */
		auto matrixValue = matrix[colIndex * columns + rowIndex];
		outBuffer[currentIteration] = static_cast<int>(matrixValue);

		/* STEERING PHASE */
		auto checkColIndex = colIndex + directions[dirIndex][1];
		auto checkRowIndex = rowIndex + directions[dirIndex][0];

		/* Check if we have not hit any spiral boundries */
		if (directions[dirIndex][1] && (checkColIndex <= rootLimit || checkColIndex >= columnLimit) ||
			directions[dirIndex][0] && (checkRowIndex <= rootLimit || checkRowIndex >= rowLimit))
		{
			dirIndex++;
			if (dirIndex == directions.size())
			{
				/* Move direction index back to start */
				dirIndex = 0;
				/* Set new spiral boundries and root position */
				rootLimit++; columnLimit--; rowLimit--;
				/* We cannot traverse to the root as it has now moved, so we must change direction */
				checkColIndex = colIndex + directions[dirIndex][1];
				checkRowIndex = rowIndex + directions[dirIndex][0];
			}
		}

		/* MOVEMENT PHASE */
		/**
		 * If inside the boundries the check indices are valid
		 * otherwise we must recalculate them
		 */
		if (checkColIndex >= rootLimit && checkColIndex <= columnLimit)
		{
			colIndex = checkColIndex;
		}
		else
		{
			colIndex = colIndex + directions[dirIndex][1];
			/* Force update row check as we may have to change direction */
			checkRowIndex = rowIndex + directions[dirIndex][0];
		}

		if (checkRowIndex >= rootLimit && checkRowIndex <= rowLimit)
		{
			rowIndex = checkRowIndex;
		}
		else
		{
			rowIndex = rowIndex + directions[dirIndex][0];
		}
	}
}