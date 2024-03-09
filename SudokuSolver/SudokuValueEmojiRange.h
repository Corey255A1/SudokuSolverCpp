/*
 * WunderVision 2024
 */
#ifndef HSudokuValueEmojiRange
#define HSudokuValueEmojiRange
#include "SudokuValueRange.h"
#include "SudokuValueEmoji.h"
#include <unordered_map>
class SudokuValueEmojiRange : public SudokuValueRange
{
private:
	std::vector<std::wstring> m_emojis;
	std::wstring m_invalidEmoji;
	std::wstring m_beginEmoji;
	std::wstring m_endEmoji;
	int m_invalid;
	size_t m_count;

public:
	SudokuValueEmojiRange(const std::vector<std::wstring>& emojis);
	virtual std::unique_ptr<SudokuValue> getMin() const;
	virtual std::unique_ptr<SudokuValue> getMax() const;
	virtual size_t getCount() const;
	virtual std::unique_ptr<SudokuValue> getNext(const SudokuValue* value) const;
	virtual std::unique_ptr<SudokuValue> getPrevious(const SudokuValue* value) const;
	virtual bool isDefault(const SudokuValue* value) const;
	virtual std::unique_ptr<SudokuValue> makeDefault() const;
	virtual std::unique_ptr<SudokuValue> parseStream(std::wstringstream& stream) const;
	std::unique_ptr<SudokuValue> makeValue(int index) const;
};
#endif