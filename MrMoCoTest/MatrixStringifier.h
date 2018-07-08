#pragma once
#include <vector>

namespace mrmoco
{
	class MatrixStringifier
	{
	public:
		MatrixStringifier();
		virtual ~MatrixStringifier() = default;
		void StringifyMatrix(int* matrix, int rows, int columns, char* outBuffer) const;
	private:
		const std::vector<std::vector<int>> directions;
	};
}
