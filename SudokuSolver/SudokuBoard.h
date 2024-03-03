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
	std::shared_ptr<SudokuValueRange> m_valueRange;
	std::vector<SudokuCell> m_board;
	size_t m_size;
	size_t m_boxSize;
	void checkAndThrow(size_t column, size_t row);
public:
	static size_t findBoxSize(size_t size);
	SudokuBoard(std::shared_ptr<SudokuValueRange> values);
	size_t getSize() const;
	bool isValid();
	void setCellValue(size_t column, size_t row, const SudokuValue& value);
	void setCellReadOnly(size_t column, size_t row, bool isReadOnly);
	SudokuCell& getCell(size_t column, size_t row);
	std::set<SudokuValue> getValidValues(size_t column, size_t row);
	std::shared_ptr<SudokuValueRange> getValueDefinition() const;
	std::string toString();
	std::string toStringOnlyEntries();
};
#endif