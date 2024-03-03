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
	SudokuValue m_value;

public:
	SudokuCell(SudokuValue value, bool isReadOnly);

	bool isReadOnly() const;
	bool isSet() const;
	SudokuValue value() const;
	bool setValue(SudokuValue value);
	void clear();

};

#endif