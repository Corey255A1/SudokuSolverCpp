/*
* WunderVision 2024
*/
#include "SudokuValueEmojiRange.h"
#include "SudokuValueEmoji.h"
SudokuValueEmojiRange::SudokuValueEmojiRange() :
	m_invalid{ 0 },
	m_count{ 0 }
{}

void SudokuValueEmojiRange::setRange(const std::vector<std::wstring>& emojis) {
	m_values.clear();
	m_valueSet.clear();
	m_count = emojis.size() - 1;
	m_emojis = emojis;
	m_values[m_invalid] = std::make_shared<SudokuValueEmoji>(shared_from_this(), m_invalid, emojis[m_invalid]);
	for (int i = 1; i < emojis.size(); i++) {
		m_values[i] = std::make_shared<SudokuValueEmoji>(shared_from_this(), i, emojis[i]);
		m_valueSet.insert(m_values[i]);
	}
}

std::shared_ptr<SudokuValue> SudokuValueEmojiRange::getMin() const { return getValue(m_invalid + 1); }
std::shared_ptr<SudokuValue> SudokuValueEmojiRange::getMax() const { return getValue(m_count); }
size_t SudokuValueEmojiRange::getCount() const { return m_count; }

std::shared_ptr<SudokuValue> SudokuValueEmojiRange::getNext(const SudokuValue* value) const
{
	return getValue(SudokuValueEmoji::castTo(value)->getValue() + 1);
}

std::shared_ptr<SudokuValue> SudokuValueEmojiRange::getPrevious(const SudokuValue* value) const
{
	return getValue(SudokuValueEmoji::castTo(value)->getValue() - 1);
}

bool SudokuValueEmojiRange::isDefault(const SudokuValue* value) const
{
	return SudokuValueEmoji::castTo(value)->getValue() == m_invalid;
}

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::makeDefault() const
{
	return makeValue(m_invalid);
}

std::shared_ptr<SudokuValue> SudokuValueEmojiRange::getDefault() const
{
	return getValue(m_invalid);
}

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::makeValue(int index) const
{
	if (index > m_count || index == m_invalid)
	{
		return std::make_unique<SudokuValueEmoji>(shared_from_this(), index, m_emojis[m_invalid]);
	}
	return std::make_unique<SudokuValueEmoji>(shared_from_this(), index, m_emojis[index]);
}

std::shared_ptr<SudokuValue> SudokuValueEmojiRange::getValue(int index) const
{
	if (index > m_count || index == m_invalid)
	{
		return m_values.at(m_invalid);
	}
	return m_values.at(index);
}

std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> SudokuValueEmojiRange::getValueSet() const
{
	return m_valueSet;
}

std::shared_ptr<SudokuValue> SudokuValueEmojiRange::parseStream(std::wstringstream& stream) const
{
	std::wstring emojiValue;
	stream >> emojiValue;
	auto emojiItr = std::find(m_emojis.begin(), m_emojis.end(), emojiValue);
	if (emojiItr == m_emojis.end())
	{
		return makeDefault();
	}
	if (emojiItr == m_emojis.begin())
	{
		return makeDefault();
	}

	int index = emojiItr - m_emojis.begin();
	return makeValue(index);
}