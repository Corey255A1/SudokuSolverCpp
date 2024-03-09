/*
* WunderVision 2024
*/
#include "SudokuValueEmojiRange.h"
#include "SudokuValueEmoji.h"
SudokuValueEmojiRange::SudokuValueEmojiRange(const std::vector<std::wstring>& emojis) : m_invalid{ 0 },
m_emojis{ emojis },
m_count{ emojis.size() - 1 }
{
	m_invalidEmoji = m_emojis[m_invalid];
	m_beginEmoji = m_emojis[m_invalid + 1];
	m_endEmoji = m_emojis[m_count];
}

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::getMin() const { return makeValue(m_invalid + 1); }
std::unique_ptr<SudokuValue>SudokuValueEmojiRange::getMax() const { return makeValue(m_count); }
size_t SudokuValueEmojiRange::getCount() const { return m_count; }

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::getNext(const SudokuValue* value) const
{
	return makeValue(SudokuValueEmoji::castTo(value)->getValue() + 1);
}

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::getPrevious(const SudokuValue* value) const
{
	return makeValue(SudokuValueEmoji::castTo(value)->getValue() - 1);
}

bool SudokuValueEmojiRange::isDefault(const SudokuValue* value) const
{
	return SudokuValueEmoji::castTo(value)->getValue() == m_invalid;
}

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::makeDefault() const
{
	return makeValue(m_invalid);
}

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::parseStream(std::wstringstream& stream) const
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

std::unique_ptr<SudokuValue> SudokuValueEmojiRange::makeValue(int index) const
{
	if (index >= m_emojis.size()) {
		return makeDefault();
	}
	return std::make_unique<SudokuValueEmoji>(shared_from_this(), index, m_emojis[index]);
}