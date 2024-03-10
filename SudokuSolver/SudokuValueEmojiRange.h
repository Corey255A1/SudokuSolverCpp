/*
 * WunderVision 2024
 * Range of values based on what was going to be originally emojis, but
 * can actually be any range of strings
 */
#ifndef HSudokuValueEmojiRange
#define HSudokuValueEmojiRange
#include "SudokuValueRange.h"

#include <vector>
#include <map>

class SudokuValueEmojiRange : public SudokuValueRange
{
private:
	std::vector<std::wstring> m_emojis;
	std::map<int, std::shared_ptr<SudokuValue>> m_values;
	std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> m_valueSet;
	std::wstring m_invalidEmoji;
	std::wstring m_beginEmoji;
	std::wstring m_endEmoji;
	int m_invalid;
	size_t m_count;

public:
	SudokuValueEmojiRange();
	void setRange(const std::vector<std::wstring> &emojis);
	virtual std::shared_ptr<SudokuValue> getMin() const;
	virtual std::shared_ptr<SudokuValue> getMax() const;
	virtual size_t getCount() const;
	virtual std::shared_ptr<SudokuValue> getNext(const SudokuValue *value) const;
	virtual std::shared_ptr<SudokuValue> getPrevious(const SudokuValue *value) const;
	virtual bool isDefault(const SudokuValue *value) const;
	virtual std::unique_ptr<SudokuValue> makeDefault() const;
	virtual std::shared_ptr<SudokuValue> getDefault() const;
	std::unique_ptr<SudokuValue> makeValue(int index) const;
	std::shared_ptr<SudokuValue> getValue(int index) const;
	virtual std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> getValueSet() const;
	virtual std::shared_ptr<SudokuValue> parseStream(std::wstringstream &stream) const;
};
#endif