/*
* WunderVision 2024
* Define the possible range of values for a sudoku cell
*/
#include <memory>
#ifndef HSudokuValueRange
#define HSudokuValueRange
class SudokuValue;
class SudokuValueRange : public std::enable_shared_from_this<SudokuValueRange> {
public:
    virtual SudokuValue getMin() const = 0;
    virtual SudokuValue getMax() const = 0;
    virtual size_t getCount() const = 0;
    virtual SudokuValue getNext(const SudokuValue& value) const = 0;
    virtual SudokuValue getPrevious(const SudokuValue& value) const = 0;
    virtual bool isDefault(const SudokuValue& value) const = 0;
    virtual SudokuValue makeDefault() const = 0;
};
#endif