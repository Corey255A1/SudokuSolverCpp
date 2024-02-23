/*
* WunderVision 2024
* A Simple Sudoku Solver. Using backtrack as the basis for the solving
* 1) Read a Sudoku board from a file
*  a) X is the empty cell
*
*/

#include "SudokuSolver.h"
#include "SudokuFileReader.h"
#include "SudokuBacktrack.h"

int main()
{
	std::shared_ptr<SudokuBoard> board = std::move(SudokuFileReader::read("D:\\Documents\\CodeProjects\\SudokuSolver\\SudokuSolver\\sudoku_test.txt"));
	SudokuBacktrack backTrack(board);
	if (!backTrack.solve()) {
		std::cout << "Sudoku Board could not be solved.\n";
	}
	std::cout << board->toString();
	return 0;
}
