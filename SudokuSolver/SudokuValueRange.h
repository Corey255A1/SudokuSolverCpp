/*
* WunderVision 2024
* Base class to Define the possible range of values for a sudoku cell
*/
#ifndef HSudokuValueRange
#define HSudokuValueRange
#include <memory>
#include <sstream>
#include <set>
#include "SudokuValue.h"
class SudokuValueRange : public std::enable_shared_from_this<SudokuValueRange> {
public:
	virtual std::shared_ptr<SudokuValue> getMin() const = 0;
	virtual std::shared_ptr<SudokuValue> getMax() const = 0;
	virtual size_t getCount() const = 0;
	virtual std::shared_ptr<SudokuValue> getNext(const SudokuValue* value) const = 0;
	virtual std::shared_ptr<SudokuValue> getPrevious(const SudokuValue* value) const = 0;
	virtual bool isDefault(const SudokuValue* value) const = 0;
	virtual std::unique_ptr<SudokuValue> makeDefault() const = 0;
	virtual std::shared_ptr<SudokuValue> getDefault() const = 0;
	virtual std::shared_ptr<SudokuValue> parseStream(std::wstringstream& stream) const = 0;
	virtual std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> getValueSet() const = 0;
};
#endif