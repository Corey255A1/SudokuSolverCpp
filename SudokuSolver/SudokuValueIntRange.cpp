#include "SudokuValueIntRange.h"
#include "SudokuValueInt.h"
SudokuValueIntRange::SudokuValueIntRange() : 
	m_invalid{0}, m_count{ 0 },
	m_min{ 0 }, m_max{ 0 }
{}

void SudokuValueIntRange::setRange(int invalid, int min, int max) {
	if (max <= min) { throw std::runtime_error("Invalid Int range"); }
	m_values.clear();
	m_valueSet.clear();
	m_invalid = invalid;
	m_min = min;
	m_max = max;
	m_count = static_cast<size_t>(max - min + 1);

	for (int i = m_min; i <= m_max; i++) {
		m_values[i] = std::make_shared<SudokuValueInt>(shared_from_this(), i);
		m_valueSet.insert(m_values[i]);
	}

	m_values[invalid] = std::make_shared<SudokuValueInt>(shared_from_this(), invalid);
}

std::shared_ptr<SudokuValue> SudokuValueIntRange::getMin() const { return getValue(m_min); }
std::shared_ptr<SudokuValue> SudokuValueIntRange::getMax() const { return getValue(m_max); }
size_t SudokuValueIntRange::getCount() const { return m_count; }

std::shared_ptr<SudokuValue> SudokuValueIntRange::getNext(const SudokuValue* value) const
{
	return getValue(SudokuValueInt::castTo(value)->getValue() + 1);
}

std::shared_ptr<SudokuValue> SudokuValueIntRange::getPrevious(const SudokuValue* value) const
{
	return getValue(SudokuValueInt::castTo(value)->getValue() - 1);
}

bool SudokuValueIntRange::isDefault(const SudokuValue* value) const
{
	return SudokuValueInt::castTo(value)->getValue() == m_invalid;
}

std::unique_ptr<SudokuValue> SudokuValueIntRange::makeDefault() const
{
	return makeValue(m_invalid);
}

std::shared_ptr<SudokuValue> SudokuValueIntRange::getDefault() const
{
	return getValue(m_invalid);
}

std::unique_ptr<SudokuValue> SudokuValueIntRange::makeValue(int value) const
{
	if (value < m_min || value > m_max || value == m_invalid) {
		return std::make_unique<SudokuValueInt>(shared_from_this(), m_invalid);
	}
	return std::make_unique<SudokuValueInt>(shared_from_this(), value);
}


std::shared_ptr<SudokuValue> SudokuValueIntRange::getValue(int value) const
{
	if (value < m_min || value > m_max || value == m_invalid) {
		return m_values.at(m_invalid);
	}
	return m_values.at(value);
}

std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> SudokuValueIntRange::getValueSet() const
{
	return m_valueSet;
}

std::shared_ptr<SudokuValue> SudokuValueIntRange::parseStream(std::wstringstream& stream) const
{
	std::wstring charValue;
	auto pos = stream.tellg();
	stream >> charValue;
	if (charValue == L"x")
	{
		return makeDefault();
	}
	stream.seekg(pos);
	int value = 0;
	stream >> value;
	if (value <= 0 || value > m_max)
	{
		return makeDefault();
	}
	return makeValue(value);
}