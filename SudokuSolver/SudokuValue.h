/*
* WunderVision 2024
* Eventually.. I want this to be generic.. not tied to Int
*/
#include <iostream>
#include <functional>
#include "SudokuValueRange.h"
#ifndef HSudokuValue
#define HSudokuValue
class SudokuValue
{
private:
    std::shared_ptr<const SudokuValueRange> m_values;
    int m_value;

public:
    SudokuValue(std::shared_ptr<const SudokuValueRange> values, int value);
    int getValue() const { return m_value; }
    bool isDefault() const;
    std::unique_ptr<SudokuValue> makeCopy() const { 
        return std::make_unique<SudokuValue>(m_values, m_value); 
    }
    std::shared_ptr<const SudokuValueRange> getValueDefinition() const { return m_values; }

    SudokuValue& operator=(const SudokuValue& copy);
    SudokuValue operator++(int inc);
    SudokuValue& operator++();
    SudokuValue operator--(int dec);
    SudokuValue& operator--();
    int operator()(const SudokuValue& value);
    bool operator()(const SudokuValue& left, const SudokuValue& right);
    friend bool operator==(const SudokuValue& left, const SudokuValue& right);
    friend bool operator!=(const SudokuValue& left, const SudokuValue& right);
    friend bool operator<(const SudokuValue& left, const SudokuValue& right);
    friend bool operator>(const SudokuValue& left, const SudokuValue& right);
    friend bool operator<=(const SudokuValue& left, const SudokuValue& right);
    friend bool operator>=(const SudokuValue& left, const SudokuValue& right);
    friend std::ostream& operator<<(std::ostream& os, const SudokuValue& dt);
};

template<>
struct std::hash<SudokuValue>
{
    size_t operator()(const SudokuValue& value) const
    {
        return value.getValue();
    }
};

template<>
struct std::equal_to<SudokuValue>
{
    bool operator()(const SudokuValue& left, const SudokuValue& right) const
    {
        return left == right;
    }
};
#endif