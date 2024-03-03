/*
* WunderVision 2024
*/
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

	std::shared_ptr<SudokuValueIntRange> values = std::make_shared<SudokuValueIntRange>(-1, 1, line.length());
	std::unique_ptr<SudokuBoard> board = std::make_unique<SudokuBoard>(values);
	
	int row = 0;
	processLine(*values, line, row, board.get());
	while (std::getline(sudokuFile, line))
	{
		std::cout << line << "\n";
		row += 1;
		processLine(*values, line, row, board.get());
	}
	return board;
}

void SudokuFileReader::processLine(const SudokuValueIntRange& values, const std::string& line, int rowIndex, SudokuBoard* board)
{
	for (int columnIndex = 0; columnIndex < line.length(); columnIndex++)
	{
		if (line[columnIndex] == 'x') { continue; }
		int cellValue = line[columnIndex] - '0';

		board->setCellValue(columnIndex, rowIndex, values.makeValue(cellValue));
		board->setCellReadOnly(columnIndex, rowIndex, true);
	}
}
