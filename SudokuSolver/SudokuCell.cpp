/*
 * WunderVision 2024
 */
#include "SudokuCell.h"
#include "SudokuValueRange.h"

SudokuCell::SudokuCell(std::shared_ptr<SudokuValue> value, bool isReadOnly) : 
	m_value(std::move(value)),
	m_isReadOnly(isReadOnly) {}

SudokuCell::SudokuCell(const SudokuCell &copy) : 
	m_isReadOnly{copy.m_isReadOnly},
    m_value{copy.m_value->makeCopy()} {}

SudokuCell &SudokuCell::operator=(const SudokuCell &copy)
{
	this->m_isReadOnly = copy.m_isReadOnly;
	this->m_value = copy.m_value->makeCopy();
	return *this;
}

bool SudokuCell::isReadOnly() const
{
	return m_isReadOnly;
}

bool SudokuCell::isSet() const
{
	return !m_value->isDefault();
}

const std::shared_ptr<SudokuValue> &SudokuCell::value() const
{
	return m_value;
}

bool SudokuCell::setValue(std::shared_ptr<SudokuValue> value)
{
	if (m_isReadOnly)
	{
		return false;
	}
	m_value = value;
	return true;
}

void SudokuCell::clear()
{
	if (m_isReadOnly)
	{
		return;
	}
	m_value = m_value->getValueRange()->getDefault();
}
