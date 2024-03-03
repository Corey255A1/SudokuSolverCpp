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
	SudokuCell(const SudokuCell& copy) :
		m_isReadOnly{ copy.m_isReadOnly },
		m_value{ copy.m_value->makeCopy() } {}
	SudokuCell(std::unique_ptr<SudokuValue> value, bool isReadOnly);
	SudokuCell& operator=(const SudokuCell& copy) {
		this->m_isReadOnly = copy.m_isReadOnly;
		this->m_value = copy.m_value->makeCopy();
		return *this;
	}

	bool isReadOnly() const;
	bool isSet() const;
	const SudokuValue& value() const;
	bool setValue(std::unique_ptr<SudokuValue> value);
	void clear();

};

#endif