/*
* WunderVision 2024
*/
#include "SudokuValueRange.h"
#ifndef HSudokuValueIntRange
#define HSudokuValueIntRange
class SudokuValueIntRange : public SudokuValueRange {
private:
    int m_invalid;
    int m_min;
    int m_max;
public:
    SudokuValueIntRange(int invalid, int min, int max) : m_invalid(invalid), m_min(min), m_max(max) {}
    virtual SudokuValue getMin() const { return SudokuValue(shared_from_this(), m_min); }
    virtual SudokuValue getMax() const { return SudokuValue(shared_from_this(), m_max); }
    virtual size_t getCount() const { return (m_max - m_min) + 1; }
    virtual SudokuValue getNext(const SudokuValue& value) const { return SudokuValue(shared_from_this(), value.getValue() + 1); }
    virtual SudokuValue getPrevious(const SudokuValue& value) const { return SudokuValue(shared_from_this(), value.getValue() - 1); }
    virtual bool isDefault(const SudokuValue& value) const { return value.getValue() == m_invalid; }
    virtual SudokuValue makeDefault() const { return SudokuValue(shared_from_this(), m_invalid); }
    SudokuValue makeValue(int value) const { return SudokuValue(shared_from_this(), value); }
};
#endif