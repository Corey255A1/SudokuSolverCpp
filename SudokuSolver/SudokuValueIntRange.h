/*
 * WunderVision 2024
 */
#ifndef HSudokuValueIntRange
#define HSudokuValueIntRange
#include "SudokuValueRange.h"
#include "SudokuValueInt.h"
class SudokuValueIntRange : public SudokuValueRange
{
private:
    int m_invalid;
    size_t m_count;
    int m_min;
    int m_max;

public:
    SudokuValueIntRange(int invalid, int min, int max);
    virtual std::unique_ptr<SudokuValue> getMin() const;
    virtual std::unique_ptr<SudokuValue> getMax() const;
    virtual size_t getCount() const;
    virtual std::unique_ptr<SudokuValue> getNext(const SudokuValue* value) const;
    virtual std::unique_ptr<SudokuValue> getPrevious(const SudokuValue* value) const;
    virtual bool isDefault(const SudokuValue* value) const;
    virtual std::unique_ptr<SudokuValue> makeDefault() const;
    virtual std::unique_ptr<SudokuValue> parseStream(std::wstringstream& stream) const;
    std::unique_ptr<SudokuValue> makeValue(int value) const;
};
#endif