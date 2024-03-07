/*
* WunderVision 2024
* Read Sudoku Board from a file and generate a Sudoku Board Class
*/

#include <string>
#include <memory>
#include "SudokuBoard.h"
#include "SudokuValueRange.h"
#ifndef HSudokuFileReader
#define HSudokuFileReader
class SudokuFileReader {
private:
	static void processLine(const SudokuValueRange& values, const std::wstring& line, int row, SudokuBoard* board);
public:
	static std::unique_ptr<SudokuBoard> read(const std::string& filePath);
};
#endif