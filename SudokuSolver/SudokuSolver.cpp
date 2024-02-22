/*
* WunderVision 2024
* A Simple Sudoku Solver. Using backtrack as the basis for the solving
* 1) Read a Sudoku board from a file
*  a) X is the empty cell
* 
*/

#include "SudokuSolver.h"
#include "SudokuFileReader.h"
using namespace std;

int main()
{
	std::unique_ptr<SudokuBoard> board = SudokuFileReader::read("D:\\Documents\\CodeProjects\\SudokuSolver\\SudokuSolver\\sudoku_test.txt");

	for (int row = 0; row < board->size(); row++)
	{
		for (int column = 0; column < board->size(); column++)
		{
			std::cout << board->getCell(column, row).value() << " ";
		}
		std::cout << "\n";
	}

	return 0;
}
