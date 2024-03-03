/*
* WunderVision 2024
*/
#include "SudokuCell.h"

SudokuCell::SudokuCell(SudokuValue value, bool isReadOnly) :
	m_value(value),
	m_isReadOnly(isReadOnly)
{
}

bool SudokuCell::isReadOnly() const
{
	return m_isReadOnly;
}

bool SudokuCell::isSet() const
{
	return !m_value.isDefault();
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

void SudokuCell::clear()
{
	if (m_isReadOnly) { return; }
	m_value = m_value.getValueDefinition()->makeDefault();
}
