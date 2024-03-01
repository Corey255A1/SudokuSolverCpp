#include "SudokuFileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
std::unique_ptr<SudokuBoard> SudokuFileReader::read(const std::string& filePath)
{
	std::ifstream sudokuFile(filePath);
	if (!sudokuFile.is_open()) { throw std::runtime_error("Sudoku File could not be opened"); }

	std::string line;
	if (!std::getline(sudokuFile, line)) { throw std::runtime_error("Not a valid Sudoku File"); }
	std::cout << line << "\n";

	std::unique_ptr<SudokuBoard> board;
	board = std::make_unique<SudokuBoard>(static_cast<int>(line.length()));

	int row = 0;
	processLine(line, row, board);
	while (std::getline(sudokuFile, line))
	{
		std::cout << line << "\n";
		row += 1;
		processLine(line, row, board);
	}
	return board;
}

void SudokuFileReader::processLine(const std::string& line, int rowIndex, std::unique_ptr<SudokuBoard>& board)
{
	for (int columnIndex = 0; columnIndex < line.length(); columnIndex++)
	{
		if (line[columnIndex] == 'x') { continue; }
		int cellValue = line[columnIndex] - '0';

		board->setCell(columnIndex, rowIndex, SudokuCell(SudokuValue(cellValue), true));
	}
}
