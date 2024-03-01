/*
* WunderVision 2024
* Each Cell in a board has a value, and whether or not that value can be modified to solve the game
*/

#ifndef HSudokuCell
#define HSudokuCell
#include "SudokuValue.h"
class SudokuCell {
private:
	SudokuValue m_value;
	bool m_isReadOnly;
public:
	/*
	Deleted copy assignment operator
	An implicitly-declared or explicitly-defaulted(since C++11) copy assignment operator for class T 
	is undefined(until C++11)defined as deleted(since C++11) if any of the following conditions is satisfied:
	T has a non-static data member of a const-qualified non-class type (or possibly multi-dimensional array thereof).
	*/
	static const SudokuValue DEFAULT_CELL;
	SudokuCell();
	SudokuCell(SudokuValue value, bool isReadOnly);

	bool isReadOnly() const;
	bool isValid() const;
	SudokuValue value() const;
	bool setValue(SudokuValue value);
	void clear();

};

#endif