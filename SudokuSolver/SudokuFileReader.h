/*
* WunderVision 2024
* Read Sudoku Board from a file and generate a Sudoku Board Class
*/

#include <string>
#include <memory>
#include "SudokuBoard.h"

#ifndef HSudokuFileReader
#define HSudokuFileReader
class SudokuFileReader {
private:
	static void processLine(const std::string& line, int row, std::unique_ptr<SudokuBoard>& board);
public:
	static std::unique_ptr<SudokuBoard> read(const std::string& filePath);
};
#endif