/*
* WunderVision 2024
* an Integer based SudokuValue
*/

#include "SudokuValueInt.h"
#include <exception>
const SudokuValueInt& SudokuValueInt::castTo(const SudokuValue& value) {
    const auto* sudokuValueInt = dynamic_cast<const SudokuValueInt*>(&value);
    if (sudokuValueInt == nullptr) { throw std::runtime_error("Invalid Sudoku Value Cast: To Int"); }
    return *sudokuValueInt;
}

const SudokuValueInt* SudokuValueInt::castTo(const SudokuValue* value) {
    const auto* sudokuValueInt = dynamic_cast<const SudokuValueInt*>(value);
    if (sudokuValueInt == nullptr) { throw std::runtime_error("Invalid Sudoku Value Cast: To Int"); }
    return sudokuValueInt;
}

bool SudokuValueInt::equals(const SudokuValue* right) const {
    return m_value == castTo(right)->m_value;
}

bool SudokuValueInt::lessThan(const SudokuValue* right) const {
    return m_value < castTo(right)->m_value;
}

bool SudokuValueInt::lessThanOrEqual(const SudokuValue* right) const {
    return m_value <= castTo(right)->m_value;
}

std::unique_ptr<SudokuValue> SudokuValueInt::makeCopy() const {
    return std::make_unique<SudokuValueInt>(m_values, m_value);
}

std::ostream& SudokuValueInt::outToStream(std::ostream& stream) const {
    stream << m_value;
    return stream;
}

std::wostream& SudokuValueInt::outToStream(std::wostream& stream) const {
    stream << m_value;
    return stream;
}