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

void getInteractiveFilePath(std::string& filePath) {
	std::cout << "Sudoku File path: ";
	std::getline(std::cin, filePath);
}
int main(int argc, char** argv)
{
	std::string filePath;
	bool isInteractive = false;
	if (argc >= 2) {
		filePath.assign(argv[1]);
	}
	else {
		getInteractiveFilePath(filePath);
		isInteractive = true;
	}

	while (!filePath.empty()) {
		try {
			std::shared_ptr<SudokuBoard> board = std::move(SudokuFileReader::read(filePath));

			if(!board->isValid()){
				std::cout << "Sudoku Board is not valid\n";
				if (isInteractive) {
					getInteractiveFilePath(filePath);
					continue;
				}
				break;
			}
			SudokuBacktrack backTrack(board);
			if (!backTrack.solve()) {
				std::cout << "Sudoku Board could not be solved.\n";
			}
			std::cout << board->toString();
			std::cout << "--Enter These Values--\n" << board->toStringOnlyEntries();
		}
		catch (std::exception e) {
			std::cerr << e.what() << std::endl;
		}

		if (!isInteractive) { break; }
		getInteractiveFilePath(filePath);
	}

	std::cout << "Have a good day!" << std::endl;
	return 0;
}
