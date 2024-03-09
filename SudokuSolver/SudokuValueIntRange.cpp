#include "SudokuValueIntRange.h"
#include "SudokuValueInt.h"
SudokuValueIntRange::SudokuValueIntRange(int invalid, int min, int max) : 
	m_invalid(invalid),
	m_count{ static_cast<size_t>(max - min + 1) },
	m_min{ min },
	m_max{ max }
{
}

std::unique_ptr<SudokuValue> SudokuValueIntRange::getMin() const { return makeValue(m_min); }
std::unique_ptr<SudokuValue>SudokuValueIntRange::getMax() const { return makeValue(m_max); }
size_t SudokuValueIntRange::getCount() const { return m_count; }

std::unique_ptr<SudokuValue> SudokuValueIntRange::getNext(const SudokuValue* value) const
{
	return makeValue(SudokuValueInt::castTo(value)->getValue() + 1);
}

std::unique_ptr<SudokuValue> SudokuValueIntRange::getPrevious(const SudokuValue* value) const
{
	return makeValue(SudokuValueInt::castTo(value)->getValue() - 1);
}

bool SudokuValueIntRange::isDefault(const SudokuValue* value) const
{
	return SudokuValueInt::castTo(value)->getValue() == m_invalid;
}

std::unique_ptr<SudokuValue> SudokuValueIntRange::makeDefault() const
{
	return makeValue(m_invalid);
}

std::unique_ptr<SudokuValue> SudokuValueIntRange::makeValue(int value) const
{
	if (value > m_max) {
		return makeDefault();
	}
	return std::make_unique<SudokuValueInt>(shared_from_this(), value);
}


std::unique_ptr<SudokuValue> SudokuValueIntRange::parseStream(std::wstringstream& stream) const
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