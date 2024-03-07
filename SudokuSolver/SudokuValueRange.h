/*
* WunderVision 2024
* Define the possible range of values for a sudoku cell
*/
#ifndef HSudokuValueRange
#define HSudokuValueRange
#include <memory>
#include <vector>
#include <unordered_set>
#include <sstream>
class SudokuValue;
class SudokuValueRange : public std::enable_shared_from_this<SudokuValueRange> {
public:
    virtual std::unique_ptr<SudokuValue> getMin() const = 0;
    virtual std::unique_ptr<SudokuValue> getMax() const = 0;
    virtual size_t getCount() const = 0;
    virtual std::unique_ptr<SudokuValue> getNext(const SudokuValue* value) const = 0;
    virtual std::unique_ptr<SudokuValue> getPrevious(const SudokuValue* value) const = 0;
    virtual bool isDefault(const SudokuValue* value) const = 0;
    virtual std::unique_ptr<SudokuValue> makeDefault() const = 0;
    virtual std::unique_ptr<SudokuValue> parseStream(std::wstringstream& stream) const = 0;
};
#endif