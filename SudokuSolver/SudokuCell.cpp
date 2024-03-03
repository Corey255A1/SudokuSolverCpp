/*
* WunderVision 2024
*/
#include "SudokuCell.h"

SudokuCell::SudokuCell(std::unique_ptr<SudokuValue> value, bool isReadOnly) :
	m_value(std::move(value)),
	m_isReadOnly(isReadOnly)
{
}

bool SudokuCell::isReadOnly() const
{
	return m_isReadOnly;
}

bool SudokuCell::isSet() const
{
	return !m_value->isDefault();
}

const SudokuValue& SudokuCell::value() const
{
	return *m_value;
}

bool SudokuCell::setValue(std::unique_ptr<SudokuValue> value)
{
	if (m_isReadOnly) { return false; }
	m_value = std::move(value);
	return true;
}

void SudokuCell::clear()
{
	if (m_isReadOnly) { return; }
	m_value = m_value->getValueDefinition()->makeDefault();
}
