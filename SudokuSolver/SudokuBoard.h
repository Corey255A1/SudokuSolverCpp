/*
* WunderVision 2024
* Contains all the Sudoku Cells and provides functions for getting
* data about the board state
*/

#ifndef HSudokuBoard
#define HSudokuBoard
#include <set>
#include <vector>
#include <string>
#include "SudokuCell.h"

class SudokuBoard {
private:
	std::shared_ptr<SudokuValueRange> m_valueRange;
	std::vector<SudokuCell> m_board;
	size_t m_size;
	size_t m_boxWidth;
	size_t m_boxHeight;
	void checkAndThrow(size_t column, size_t row);
public:
	static size_t findBoxSize(size_t size);
	SudokuBoard(std::shared_ptr<SudokuValueRange> values, size_t boxWidth = 0, size_t boxHeight = 0);
	size_t getSize() const;
	bool isValid();
	void setCellValue(size_t column, size_t row, std::shared_ptr<SudokuValue> value);
	void setCellReadOnly(size_t column, size_t row, bool isReadOnly);
	SudokuCell& getCell(size_t column, size_t row);
	std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> getValidValues(size_t column, size_t row);
	const std::shared_ptr<SudokuValueRange>& getValueRange() const;
	std::wstring toString();
	std::wstring toStringOnlyEntries();
};
#endif