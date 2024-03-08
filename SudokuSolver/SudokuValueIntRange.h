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
    SudokuValueIntRange(int invalid, int min, int max) : m_invalid(invalid),
                                                         m_count{static_cast<size_t>(max - min + 1)},
                                                         m_min{min},
                                                         m_max{max}
    {
    }

    virtual std::unique_ptr<SudokuValue> getMin() const { return makeValue(m_min); }
    virtual std::unique_ptr<SudokuValue> getMax() const { return makeValue(m_max); }
    virtual size_t getCount() const { return m_count; }

    virtual std::unique_ptr<SudokuValue> getNext(const SudokuValue *value) const
    {
        return makeValue(SudokuValueInt::castTo(value)->getValue() + 1);
    }

    virtual std::unique_ptr<SudokuValue> getPrevious(const SudokuValue *value) const
    {
        return makeValue(SudokuValueInt::castTo(value)->getValue() - 1);
    }

    virtual bool isDefault(const SudokuValue *value) const
    {
        return SudokuValueInt::castTo(value)->getValue() == m_invalid;
    }

    virtual std::unique_ptr<SudokuValue> makeDefault() const
    { 
        return makeValue(m_invalid); 
    }

    std::unique_ptr<SudokuValue> makeValue(int value) const 
    {
        if(value > m_max){
            return makeDefault();
        }
        return std::make_unique<SudokuValueInt>(shared_from_this(), value); 
    }
    

    virtual std::unique_ptr<SudokuValue> parseStream(std::wstringstream& stream) const
    {
        std::wstring charValue;
        auto pos = stream.tellg();
        stream >> charValue;
        if(charValue == L"x")
        {
            return makeDefault();
        }
        stream.seekg(pos);
        int value = 0;
        stream >> value;
        if(value <= 0 || value > m_max)
        {
            return makeDefault();
        }
        return makeValue(value);
    }
};
#endif