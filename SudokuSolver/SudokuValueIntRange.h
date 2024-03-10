/*
 * WunderVision 2024
 * A range of sequential integers that can start and end really anywhere
 */
#ifndef HSudokuValueIntRange
#define HSudokuValueIntRange
#include "SudokuValue.h"
#include "SudokuValueRange.h"

#include <map>

class SudokuValueIntRange : public SudokuValueRange
{
private:
	int m_invalid;
	size_t m_count;
	int m_min;
	int m_max;
	std::map<int, std::shared_ptr<SudokuValue>> m_values;
	std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> m_valueSet;

public:
	SudokuValueIntRange();
	void setRange(int invalid, int min, int max);
	virtual std::shared_ptr<SudokuValue> getMin() const;
	virtual std::shared_ptr<SudokuValue> getMax() const;
	virtual size_t getCount() const;
	virtual std::shared_ptr<SudokuValue> getNext(const SudokuValue *value) const;
	virtual std::shared_ptr<SudokuValue> getPrevious(const SudokuValue *value) const;
	virtual bool isDefault(const SudokuValue *value) const;
	virtual std::unique_ptr<SudokuValue> makeDefault() const;
	virtual std::shared_ptr<SudokuValue> getDefault() const;
	std::unique_ptr<SudokuValue> makeValue(int value) const;
	std::shared_ptr<SudokuValue> getValue(int value) const;
	virtual std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> getValueSet() const;
	virtual std::shared_ptr<SudokuValue> parseStream(std::wstringstream &stream) const;
};
#endif