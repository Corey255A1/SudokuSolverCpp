/*
* WunderVision 2024
* Each Cell in a board has a value, and whether or not that value can be modified to solve the game
*/

#ifndef HSudokuCell
#define HSudokuCell
#include "SudokuValue.h"
class SudokuCell {
private:
	bool m_isReadOnly;
	std::unique_ptr<SudokuValue> m_value;

public:
	SudokuCell(const SudokuCell& copy);
	SudokuCell(std::unique_ptr<SudokuValue> value, bool isReadOnly);
	SudokuCell& operator=(const SudokuCell& copy);

	bool isReadOnly() const;
	bool isSet() const;
	const std::unique_ptr<SudokuValue>& value() const;
	bool setValue(std::unique_ptr<SudokuValue> value);
	void clear();
};

#endif