#include "SudokuCell.h"

SudokuCell::SudokuCell() :
	SudokuCell(DEFAULT_CELL, false)
{
}
SudokuCell::SudokuCell(int value, bool isReadOnly) :
	m_value(value),
	m_isReadOnly(isReadOnly)
{
}

bool SudokuCell::isReadOnly() const
{
	return m_isReadOnly;
}

int SudokuCell::value() const
{
	return m_value;
}

bool SudokuCell::setValue(int value)
{
	if (m_isReadOnly) { return false; }
	m_value = value;
	return true;
}
