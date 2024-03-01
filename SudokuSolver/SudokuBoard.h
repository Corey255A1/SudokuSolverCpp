/*
* WunderVision 2024
* Contains all the Sudoku Cells and provides functions for getting
* data about the board state
*/

#include <set>
#include <vector>
#include <string>
#include "SudokuCell.h"

#ifndef HSudokuBoard
#define HSudokuBoard
class SudokuBoard {
private:
	std::vector<SudokuCell> m_board;
	int m_size;
	int m_boxSize;
	void checkAndThrow(int column, int row);
public:
	static int findBoxSize(int size);
	SudokuBoard(int size);
	int size() const;
	bool isValid();
	void setCell(int column, int row, const SudokuCell& cell);
	SudokuCell& getCell(int column, int row);
	std::set<SudokuValue> getValidValues(int column, int row);

	std::string toString();
	std::string toStringOnlyEntries();
};
#endif