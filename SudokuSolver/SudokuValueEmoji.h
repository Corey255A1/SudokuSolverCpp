/*
 * WunderVision 2024
 * an Integer based SudokuValue
 */
#ifndef HSudokuValueEmoji
#define HSudokuValueEmoji
#include "SudokuValue.h"
#include "SudokuValueRange.h"

class SudokuValueEmoji : public SudokuValue
{
private:
	int m_value;
	std::wstring m_emoji;

public:
	SudokuValueEmoji(std::shared_ptr<const SudokuValueRange> values, int value, const std::wstring &emoji) : 
		SudokuValue(values), 
		m_value{value}, 
		m_emoji{emoji} {}
	static const SudokuValueEmoji &castTo(const SudokuValue &value);
	static const SudokuValueEmoji *castTo(const SudokuValue *value);
	int getValue() const { return m_value; }
	virtual size_t getHash() const { return getValue(); }
	bool isDefault() const { return m_values->isDefault(this); }
	virtual bool equals(const SudokuValue *right) const;
	virtual bool lessThan(const SudokuValue *right) const;
	virtual bool lessThanOrEqual(const SudokuValue *right) const;
	virtual std::ostream &outToStream(std::ostream &stream) const;
	virtual std::wostream &outToStream(std::wostream &stream) const;
	virtual std::unique_ptr<SudokuValue> makeCopy() const;
	std::shared_ptr<const SudokuValueRange> getValueRange() const { return m_values; }
};
#endif