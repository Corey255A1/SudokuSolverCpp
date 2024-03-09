/*
* WunderVision 2024
* an Integer based SudokuValue
*/
#ifndef HSudokuValueInt
#define HSudokuValueInt
#include "SudokuValue.h"
class SudokuValueInt : public SudokuValue
{
private:
	int m_value;

public:
	SudokuValueInt(std::shared_ptr<const SudokuValueRange> values, int value) :SudokuValue(values), m_value(value) {}
	static const SudokuValueInt& castTo(const SudokuValue& value);
	static const SudokuValueInt* castTo(const SudokuValue* value);
	int getValue() const { return m_value; }
	virtual size_t getHash() const { return getValue(); }
	bool isDefault() const { return m_values->isDefault(this); }
	virtual bool equals(const SudokuValue* right) const;
	virtual bool lessThan(const SudokuValue* right) const;
	virtual bool lessThanOrEqual(const SudokuValue* right) const;
	virtual std::ostream& outToStream(std::ostream& stream) const;
	virtual std::wostream& outToStream(std::wostream& stream) const;
	virtual std::unique_ptr<SudokuValue> makeCopy() const;
	std::shared_ptr<const SudokuValueRange> getValueRange() const { return m_values; }

};
#endif