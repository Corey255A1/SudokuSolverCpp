/*
* WunderVision 2024
* Define the possible range of values for a sudoku cell
*/
#ifndef HSudokuValueRange
#define HSudokuValueRange
#include <memory>
class SudokuValue;
class SudokuValueRange : public std::enable_shared_from_this<SudokuValueRange> {
public:
    virtual const SudokuValue& getMin() const = 0;
    virtual const SudokuValue& getMax() const = 0;
    virtual size_t getCount() const = 0;
    virtual std::unique_ptr<SudokuValue> getNext(const SudokuValue& value) const = 0;
    virtual std::unique_ptr<SudokuValue> getPrevious(const SudokuValue& value) const = 0;
    virtual bool isDefault(const SudokuValue& value) const = 0;
    virtual std::unique_ptr<SudokuValue> makeDefault() const = 0;
};
#endif