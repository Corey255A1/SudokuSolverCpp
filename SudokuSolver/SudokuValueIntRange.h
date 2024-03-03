/*
* WunderVision 2024
*/
#include "SudokuValueRange.h"
#ifndef HSudokuValueIntRange
#define HSudokuValueIntRange
class SudokuValueIntRange : public SudokuValueRange {
private:
    int m_invalid;
    size_t m_count;
    int m_min;
    int m_max;
public:
    SudokuValueIntRange(int invalid, int min, int max) :
        m_invalid(invalid),
        m_count{ static_cast<size_t>(max - min + 1) },
        m_min{min},
        m_max{max}
    {}

    virtual const SudokuValue& getMin() const { return SudokuValue(shared_from_this(), m_min); }
    virtual const SudokuValue& getMax() const { return SudokuValue(shared_from_this(), m_max); }
    virtual size_t getCount() const { return m_count; }
    virtual std::unique_ptr<SudokuValue> getNext(const SudokuValue& value) const { return std::make_unique<SudokuValue>(shared_from_this(), value.getValue() + 1); }
    virtual std::unique_ptr<SudokuValue> getPrevious(const SudokuValue& value) const { return std::make_unique<SudokuValue>(shared_from_this(), value.getValue() - 1); }
    virtual bool isDefault(const SudokuValue& value) const { return value.getValue() == m_invalid; }
    virtual std::unique_ptr<SudokuValue> makeDefault() const { return std::make_unique<SudokuValue>(shared_from_this(), m_invalid); }
    std::unique_ptr<SudokuValue> makeValue(int value) const { return std::make_unique<SudokuValue>(shared_from_this(), value); }
};
#endif