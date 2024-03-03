/*
* WunderVision 2024
*/
#include "SudokuBoard.h"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
size_t SudokuBoard::findBoxSize(size_t size) {
	if (size < 4) { return -1; }
	if (size == 4) { return 2; }

	size_t squareCheck = 3;
	size_t square = static_cast<size_t>(pow(squareCheck, 2));
	while (square < size) {
		squareCheck += 1;
		square = static_cast<size_t>(pow(squareCheck, 2));
	}

	return square == size ? squareCheck : 0;
}

SudokuBoard::SudokuBoard(std::shared_ptr<SudokuValueRange> values) :
	m_size{ values->getCount() },
	m_boxSize{ SudokuBoard::findBoxSize(m_size) },
	m_valueRange{ values }
{
	if (m_boxSize == 0) { throw std::invalid_argument("Invalid Sudoku Size"); }

	size_t multiDimension = static_cast<size_t>(pow(m_size, 2));
	for (size_t i = 0; i < multiDimension; i++) {
		m_board.push_back(SudokuCell(m_valueRange->makeDefault(), false));
	}
}

void SudokuBoard::checkAndThrow(size_t column, size_t row)
{
	if (column >= m_size || row >= m_size) { throw std::invalid_argument("Out of range"); }
}

size_t SudokuBoard::getSize() const {
	return m_size;
}

void SudokuBoard::setCellValue(size_t column, size_t row, const SudokuValue& value)
{
	checkAndThrow(column, row);
	m_board[row * m_size + column].setValue(value);
}

void SudokuBoard::setCellReadOnly(size_t column, size_t row, bool isReadOnly)
{
	checkAndThrow(column, row);
	SudokuCell& oldCell = m_board[row * m_size + column];
	m_board[row * m_size + column] = SudokuCell(oldCell.value(), isReadOnly);
}

SudokuCell& SudokuBoard::getCell(size_t column, size_t row)
{
	return m_board[row * m_size + column];
}

std::shared_ptr<SudokuValueRange> SudokuBoard::getValueDefinition() const { 
	return m_valueRange; 
}

std::set<SudokuValue> SudokuBoard::getValidValues(size_t column, size_t row)
{
	checkAndThrow(column, row);
	std::set<SudokuValue> validValues;
	// Getting closer to generic value range
	for (SudokuValue value = m_valueRange->getMin(); value <= m_valueRange->getMax(); value++) {
		validValues.insert(value); 
	}

	auto cell = getCell(column, row);
	if (cell.isSet())
	{
		auto valueIterator = validValues.find(cell.value());
		if (valueIterator != validValues.end())
		{
			validValues.erase(valueIterator);
		}
	}


	// Check Row
	for (int columnSearch = 0; columnSearch < m_size; columnSearch++) {
		if (columnSearch == column) { continue; }

		auto cell = getCell(columnSearch, row);
		if (!cell.isSet()) { continue; }


		auto valueIterator = validValues.find(cell.value());
		if (valueIterator == validValues.end()) { continue; }

		validValues.erase(valueIterator);
	}

	if (validValues.size() == 0) { return validValues; }

	// Check Column
	for (int rowSearch = 0; rowSearch < m_size; rowSearch++) {
		if (rowSearch == row) { continue; }

		auto cell = getCell(column, rowSearch);
		if (!cell.isSet()) { continue; }

		auto valueIterator = validValues.find(cell.value());
		if (valueIterator == validValues.end()) { continue; }

		validValues.erase(valueIterator);
	}

	if (validValues.size() == 0) { return validValues; }

	// Check Box
	size_t boxRowStart = (row / m_boxSize) * m_boxSize;
	size_t boxRowEnd = boxRowStart + m_boxSize;
	size_t boxColumnStart = (column / m_boxSize) * m_boxSize;
	size_t boxColumnEnd = boxColumnStart + m_boxSize;

	for (size_t rowSearch = boxRowStart; rowSearch < boxRowEnd; rowSearch++)
	{
		for (size_t columnSearch = boxColumnStart; columnSearch < boxColumnEnd; columnSearch++)
		{
			if (rowSearch == row && columnSearch == column) { continue; }
			auto cell = getCell(columnSearch, rowSearch);
			if (!cell.isSet()) { continue; }

			auto valueIterator = validValues.find(cell.value());
			if (valueIterator == validValues.end()) { continue; }

			validValues.erase(valueIterator);
		}
	}

	return validValues;
}

bool SudokuBoard::isValid()
{
	std::vector<std::unordered_set<SudokuValue>> rows(m_size);
	std::vector<std::unordered_set<SudokuValue>> columns(m_size);
	std::vector<std::unordered_set<SudokuValue>> boxes(m_size);

	for (size_t row = 0; row < m_size; row++) {
		for (size_t column = 0; column < m_size; column++) {
			auto cell = getCell(column, row);
			if (!cell.isSet()) { continue; }

			size_t boxIndex = (row / m_boxSize) * m_boxSize + (column / m_boxSize);

			auto rowItr = rows[row].find(cell.value());
			auto columnItr = columns[column].find(cell.value());
			auto boxItr = boxes[boxIndex].find(cell.value());

			if (rowItr != rows[row].end() ||
				columnItr != columns[column].end() ||
				boxItr != boxes[boxIndex].end()) {
				return false;
			}

			rows[row].insert(cell.value());
			columns[column].insert(cell.value());
			boxes[boxIndex].insert(cell.value());
		}
	}
	return true;
}

std::string SudokuBoard::toString()
{
	std::stringstream stringify;
	for (int row = 0; row < m_size; row++)
	{
		for (int column = 0; column < m_size; column++)
		{
			stringify << getCell(column, row).value() << " ";
		}
		stringify << "\n";
	}
	return stringify.str();
}

std::string SudokuBoard::toStringOnlyEntries()
{
	std::stringstream stringify;
	for (int row = 0; row < m_size; row++)
	{
		for (int column = 0; column < m_size; column++)
		{
			auto& cell = getCell(column, row);
			if (cell.isReadOnly()) { continue; }

			stringify << cell.value() << " ";
		}
		stringify << "\n";
	}
	return stringify.str();
}
