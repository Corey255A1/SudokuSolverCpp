/*
 * WunderVision 2024
 */
#include "SudokuBoard.h"
#include "SudokuValueRange.h"

#include <cmath>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

size_t SudokuBoard::findBoxSize(size_t size)
{
	if (size < 4)
	{
		return -1;
	}
	if (size == 4)
	{
		return 2;
	}

	size_t squareCheck = 3;
	size_t square = static_cast<size_t>(pow(squareCheck, 2));
	while (square < size)
	{
		squareCheck += 1;
		square = static_cast<size_t>(pow(squareCheck, 2));
	}

	return square == size ? squareCheck : 0;
}

SudokuBoard::SudokuBoard(std::shared_ptr<SudokuValueRange> values, size_t boxWidth, size_t boxHeight) :
	m_size{values->getCount()},
	m_valueRange{values},
	m_boxWidth{boxWidth},
	m_boxHeight{boxHeight}
{
	if (m_size == 0)
	{
		throw std::invalid_argument("Invalid Sudoku Size");
	}

	if (m_boxWidth == 0 || m_boxHeight == 0)
	{
		size_t square = SudokuBoard::findBoxSize(m_size);
		if (square == 0)
		{
			throw std::invalid_argument("Invalid Sudoku Size");
		}
		m_boxWidth = square;
		m_boxHeight = square;
	}

	if (m_boxWidth * m_boxHeight != m_size)
	{
		throw std::invalid_argument("Invalid Sudoku Box Size");
	}

	size_t multiDimension = static_cast<size_t>(pow(m_size, 2));
	for (size_t i = 0; i < multiDimension; i++)
	{
		m_board.push_back(SudokuCell(m_valueRange->getDefault(), false));
	}
}

void SudokuBoard::checkAndThrow(size_t column, size_t row)
{
	if (column >= m_size || row >= m_size)
	{
		throw std::invalid_argument("Out of range");
	}
}

size_t SudokuBoard::getSize() const
{
	return m_size;
}

void SudokuBoard::setCellValue(size_t column, size_t row, std::shared_ptr<SudokuValue> value)
{
	checkAndThrow(column, row);
	m_board[row * m_size + column].setValue(value);
}

void SudokuBoard::setCellReadOnly(size_t column, size_t row, bool isReadOnly)
{
	checkAndThrow(column, row);
	SudokuCell &oldCell = m_board[row * m_size + column];
	m_board[row * m_size + column] = SudokuCell(oldCell.value()->makeCopy(), isReadOnly);
}

SudokuCell &SudokuBoard::getCell(size_t column, size_t row)
{
	return m_board[row * m_size + column];
}

const std::shared_ptr<SudokuValueRange> &SudokuBoard::getValueRange() const
{
	return m_valueRange;
}

std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> SudokuBoard::getValidValues(size_t column, size_t row)
{
	checkAndThrow(column, row);
	auto validValues = m_valueRange->getValueSet();

	const SudokuCell &cell = getCell(column, row);
	if (cell.isSet())
	{
		auto valueIterator = validValues.find(cell.value());
		if (valueIterator != validValues.end())
		{
			validValues.erase(valueIterator);
		}
	}

	// Check Row
	for (int columnSearch = 0; columnSearch < m_size; columnSearch++)
	{
		if (columnSearch == column)
		{
			continue;
		}

		SudokuCell &cell = getCell(columnSearch, row);
		if (!cell.isSet())
		{
			continue;
		}

		auto valueIterator = validValues.find(cell.value());
		if (valueIterator == validValues.end())
		{
			continue;
		}

		validValues.erase(valueIterator);
	}

	if (validValues.size() == 0)
	{
		return validValues;
	}
	// Check Column
	for (int rowSearch = 0; rowSearch < m_size; rowSearch++)
	{
		if (rowSearch == row)
		{
			continue;
		}

		SudokuCell &cell = getCell(column, rowSearch);
		if (!cell.isSet())
		{
			continue;
		}

		auto valueIterator = validValues.find(cell.value());
		if (valueIterator == validValues.end())
		{
			continue;
		}

		validValues.erase(valueIterator);
	}

	if (validValues.size() == 0)
	{
		return validValues;
	}
	// Check Box
	size_t boxRowStart = (row / m_boxHeight) * m_boxHeight;
	size_t boxRowEnd = boxRowStart + m_boxHeight;

	size_t boxColumnStart = (column / m_boxWidth) * m_boxWidth;
	size_t boxColumnEnd = boxColumnStart + m_boxWidth;

	for (size_t rowSearch = boxRowStart; rowSearch < boxRowEnd; rowSearch++)
	{
		for (size_t columnSearch = boxColumnStart; columnSearch < boxColumnEnd; columnSearch++)
		{
			if (rowSearch == row && columnSearch == column)
			{
				continue;
			}
			SudokuCell &cell = getCell(columnSearch, rowSearch);
			if (!cell.isSet())
			{
				continue;
			}

			auto valueIterator = validValues.find(cell.value());
			if (valueIterator == validValues.end())
			{
				continue;
			}

			validValues.erase(valueIterator);
		}
	}
	return validValues;
}

bool SudokuBoard::isValid()
{
	std::vector<std::unordered_set<std::shared_ptr<SudokuValue>, SudokuValueOps, SudokuValueOps>> rows(m_size);
	std::vector<std::unordered_set<std::shared_ptr<SudokuValue>, SudokuValueOps, SudokuValueOps>> columns(m_size);
	std::vector<std::unordered_set<std::shared_ptr<SudokuValue>, SudokuValueOps, SudokuValueOps>> boxes(m_size);
	for (size_t row = 0; row < m_size; row++)
	{
		for (size_t column = 0; column < m_size; column++)
		{
			SudokuCell &cell = getCell(column, row);
			if (!cell.isSet())
			{
				continue;
			}

			size_t boxIndex = (row / m_boxHeight) * m_boxHeight + (column / m_boxWidth);

			auto rowItr = rows[row].find(cell.value());
			auto columnItr = columns[column].find(cell.value());
			auto boxItr = boxes[boxIndex].find(cell.value());

			if (rowItr != rows[row].end() ||
				columnItr != columns[column].end() ||
				boxItr != boxes[boxIndex].end())
			{
				return false;
			}

			rows[row].insert(cell.value());
			columns[column].insert(cell.value());
			boxes[boxIndex].insert(cell.value());
		}
	}
	return true;
}

std::wstring SudokuBoard::toString()
{
	std::wstringstream stringify;
	for (int row = 0; row < m_size; row++)
	{
		for (int column = 0; column < m_size; column++)
		{
			stringify << *getCell(column, row).value() << " ";
		}
		stringify << "\n";
	}
	return stringify.str();
}

std::wstring SudokuBoard::toStringOnlyEntries()
{
	std::wstringstream stringify;
	for (int row = 0; row < m_size; row++)
	{
		for (int column = 0; column < m_size; column++)
		{
			SudokuCell &cell = getCell(column, row);
			if (cell.isReadOnly())
			{
				continue;
			}

			stringify << *cell.value() << " ";
		}
		stringify << "\n";
	}
	return stringify.str();
}
