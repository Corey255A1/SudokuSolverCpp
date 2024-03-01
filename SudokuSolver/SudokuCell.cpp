#include "SudokuCell.h"
const SudokuValue SudokuCell::DEFAULT_CELL = SudokuValue();

SudokuCell::SudokuCell() :
	SudokuCell(DEFAULT_CELL, false)
{
}
SudokuCell::SudokuCell(SudokuValue value, bool isReadOnly) :
	m_value(value),
	m_isReadOnly(isReadOnly)
{
}

bool SudokuCell::isReadOnly() const
{
	return m_isReadOnly;
}

bool SudokuCell::isValid() const 
{
	return m_value != DEFAULT_CELL;
}

SudokuValue SudokuCell::value() const
{
	return m_value;
}

bool SudokuCell::setValue(SudokuValue value)
{
	if (m_isReadOnly) { return false; }
	m_value = value;
	return true;
}

void SudokuCell::clear() {
	setValue(DEFAULT_CELL);
}
