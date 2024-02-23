#include "SudokuBoard.h"
#include <cmath>
#include <iostream>

int SudokuBoard::findBoxSize(int size) {
	if (size < 4) { return -1; }
	if (size == 4) { return 2; }

	int squareCheck = 3;
	int square = pow(squareCheck, 2);
	while (square < size) {
		squareCheck += 1;
		square = pow(squareCheck, 2);
	}

	return square == size ? squareCheck : -1;
}
SudokuBoard::SudokuBoard(int size) :
	m_size{ size },
	m_boxSize { SudokuBoard::findBoxSize(size) }
{
	if (m_boxSize == -1) { throw "Invalid Sudoku Size"; }

	int multiDimension = pow(size, 2);
	for (int i = 0; i < multiDimension; i++) {
		m_board.push_back(SudokuCell());
	}
}

void SudokuBoard::checkAndThrow(int column, int row) 
{
	if (column < 0 || row < 0 || column >= m_size || row >= m_size) { throw "Out of range"; }
}

int SudokuBoard::size() const {
	return m_size;
}

void SudokuBoard::setCell(int column, int row, const SudokuCell& cell)
{
	checkAndThrow(column, row);
	m_board[row * m_size + column] = cell;
}

SudokuCell& SudokuBoard::getCell(int column, int row)
{
	return m_board[row * m_size + column];
}

std::set<int> SudokuBoard::getValidValues(int column, int row)
{
	checkAndThrow(column, row);
	std::set<int> validValues;
	for (int value = 1; value <= m_size; value++) { validValues.insert(value); }

	auto cell = getCell(column, row);
	if (cell.isValid())
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
		if (!cell.isValid()) { continue; }

		
		auto valueIterator = validValues.find(cell.value());
		if (valueIterator == validValues.end()) { continue; }

		validValues.erase(valueIterator);
	}

	if (validValues.size() == 0) { return validValues; }

	// Check Column
	for (int rowSearch = 0; rowSearch < m_size; rowSearch++) {
		if (rowSearch == row) { continue; }

		auto cell = getCell(column, rowSearch);
		if (!cell.isValid()) { continue; }

		auto valueIterator = validValues.find(cell.value());
		if (valueIterator == validValues.end()) { continue; }

		validValues.erase(valueIterator);
	}

	if (validValues.size() == 0) { return validValues; }

	// Check Box
	int boxRowStart = (row / m_boxSize) * m_boxSize;
	int boxRowEnd = boxRowStart + m_boxSize;
	int boxColumnStart = (column / m_boxSize) * m_boxSize;
	int boxColumnEnd = boxColumnStart + m_boxSize;

	for (int rowSearch = boxRowStart; rowSearch < boxRowEnd; rowSearch++) 
	{
		for (int columnSearch = boxColumnStart; columnSearch < boxColumnEnd; columnSearch++) 
		{
			if (rowSearch == row && columnSearch == column) { continue; }
			auto cell = getCell(columnSearch, rowSearch);
			if (!cell.isValid()) { continue; }

			auto valueIterator = validValues.find(cell.value());
			if (valueIterator == validValues.end()) { continue; }

			validValues.erase(valueIterator);
		}
	}

	return validValues;
}
