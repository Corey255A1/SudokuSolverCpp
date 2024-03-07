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
#include <locale>
void getInteractiveFilePath(std::string& filePath) {
	std::wcout << L"Sudoku File path: ";
	std::getline(std::cin, filePath);
}
int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "");
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
				std::wcout << L"Sudoku Board is not valid\n";
				if (isInteractive) {
					getInteractiveFilePath(filePath);
					continue;
				}
				break;
			}
			SudokuBacktrack backTrack(board);
			if (!backTrack.solve()) {
				std::wcout << L"Sudoku Board could not be solved" << std::endl;
			}
			std::wcout << std::endl << L"-- Solution Found! --" << std::endl;
			std::wcout << board->toString();
			std::wcout << L"--Enter These Values--\n" << board->toStringOnlyEntries();
		}
		catch (std::exception e) {
			std::wcerr << e.what() << std::endl;
		}

		if (!isInteractive) { break; }
		getInteractiveFilePath(filePath);
	}

	std::wcout << L"Have a good day!" << std::endl;
	return 0;
}
