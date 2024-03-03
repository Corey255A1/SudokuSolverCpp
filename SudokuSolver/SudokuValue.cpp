/*
* WunderVision 2024
*/
#include "SudokuValue.h"

SudokuValue::SudokuValue(std::shared_ptr<const SudokuValueRange> values, int value) :
	m_value{ value },
	m_values{ values }
{}

bool SudokuValue::isDefault() const {
	return m_values->isDefault(*this);
}

SudokuValue& SudokuValue::operator=(const SudokuValue& copy) {
	m_value = copy.m_value;
	return *this;
}

SudokuValue SudokuValue::operator++(int inc) {
	SudokuValue previous(*this);
	++(*this);
	return previous;
}

SudokuValue& SudokuValue::operator++() {
	m_value = m_values->getNext(*this)->getValue();
	return *this;
}

SudokuValue SudokuValue::operator--(int dec) {
	SudokuValue previous(*this);
	--(*this);
	return previous;
}

SudokuValue& SudokuValue::operator--() {
	m_value = m_values->getPrevious(*this)->getValue();
	return *this;
}

int SudokuValue::operator()(const SudokuValue& value)
{
	return value.m_value;
}

bool SudokuValue::operator()(const SudokuValue& left, const SudokuValue& right)
{
	return left == right;
}

bool operator==(const SudokuValue& left, const SudokuValue& right)
{
	return left.m_value == right.m_value;
}

bool operator!=(const SudokuValue& left, const SudokuValue& right)
{
	return !(left == right);
}

bool operator<(const SudokuValue& left, const SudokuValue& right)
{
	return left.m_value < right.m_value;
}

bool operator>(const SudokuValue& left, const SudokuValue& right)
{
	return right.m_value < left.m_value;
}

bool operator<=(const SudokuValue& left, const SudokuValue& right)
{
	return !(left > right);
}

bool operator>=(const SudokuValue& left, const SudokuValue& right)
{
	return !(left < right);
}

std::ostream& operator<<(std::ostream& os, const SudokuValue& dt)
{
	os << dt.m_value;
	return os;
}