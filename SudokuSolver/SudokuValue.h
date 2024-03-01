#include <iostream>
#include <functional>

class SudokuValue
{
private:
    static const int INVALID = -1;
    int m_value;

public:
    SudokuValue();
    SudokuValue(int value);
    int getValue() const { return m_value; }

    int operator()(const SudokuValue &value)
    {
        return value.m_value;
    }

    bool operator()(const SudokuValue &left, const SudokuValue &right)
    {
        return left == right;
    }

    friend bool operator==(const SudokuValue &left, const SudokuValue &right)
    {
        return left.m_value == right.m_value;
    }

    friend bool operator!=(const SudokuValue &left, const SudokuValue &right)
    {
        return !(left == right);
    }

    friend bool operator<(const SudokuValue &left, const SudokuValue &right)
    {
        return left.m_value < right.m_value;
    }

    friend bool operator>(const SudokuValue &left, const SudokuValue &right)
    {
        return right.m_value < left.m_value;
    }

    friend bool operator<=(const SudokuValue &left, const SudokuValue &right)
    {
        return !(left > right);
    }

    friend bool operator>=(const SudokuValue &left, const SudokuValue &right)
    {
        return !(left < right);
    }

    friend std::ostream& operator<<(std::ostream &os, const SudokuValue &dt)
    {
        os << dt.m_value;
        return os;
    }
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