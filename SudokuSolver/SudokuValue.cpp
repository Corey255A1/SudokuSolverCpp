/*
 * WunderVision 2024
 */
#include "SudokuValue.h"
#include "SudokuValueIntRange.h"

SudokuValue::SudokuValue(std::shared_ptr<const SudokuValueRange> values) : m_values{values}
{
}

bool SudokuValue::isDefault() const
{
	return m_values->isDefault(this);
}

std::shared_ptr<const SudokuValueRange> SudokuValue::getValueRange() const
{
	return m_values;
}