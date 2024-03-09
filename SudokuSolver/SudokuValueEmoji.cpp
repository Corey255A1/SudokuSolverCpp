/*
* WunderVision 2024
* an Emoji/String based SudokuValue
*/

#include "SudokuValueEmoji.h"
#include <exception>
const SudokuValueEmoji& SudokuValueEmoji::castTo(const SudokuValue& value) {
	const auto* sudokuValue = dynamic_cast<const SudokuValueEmoji*>(&value);
	if (sudokuValue == nullptr) { throw std::runtime_error("Invalid Sudoku Value Cast: To Int"); }
	return *sudokuValue;
}

const SudokuValueEmoji* SudokuValueEmoji::castTo(const SudokuValue* value) {
	const auto* sudokuValue = dynamic_cast<const SudokuValueEmoji*>(value);
	if (sudokuValue == nullptr) { throw std::runtime_error("Invalid Sudoku Value Cast: To Int"); }
	return sudokuValue;
}

bool SudokuValueEmoji::equals(const SudokuValue* right) const {
	return m_value == castTo(right)->m_value;
}

bool SudokuValueEmoji::lessThan(const SudokuValue* right) const {
	return m_value < castTo(right)->m_value;
}

bool SudokuValueEmoji::lessThanOrEqual(const SudokuValue* right) const {
	return m_value <= castTo(right)->m_value;
}

std::unique_ptr<SudokuValue> SudokuValueEmoji::makeCopy() const {
	return std::make_unique<SudokuValueEmoji>(m_values, m_value, m_emoji);
}

std::ostream& SudokuValueEmoji::outToStream(std::ostream& stream) const {
	stream << m_value;
	return stream;
}

std::wostream& SudokuValueEmoji::outToStream(std::wostream& stream) const {
	stream << m_emoji;
	return stream;
}