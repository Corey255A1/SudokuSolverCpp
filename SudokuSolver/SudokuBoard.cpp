#include "SudokuBoard.h"
#include <cmath>
SudokuBoard::SudokuBoard(int size) :
	m_size{ size }
{
	int multiDimension = pow(size, 2);
	for (int i = 0; i < multiDimension; i++) {
		m_board.push_back(SudokuCell());
	}
}

int SudokuBoard::size() const {
	return m_size;
}

void SudokuBoard::setCell(int column, int row, const SudokuCell& cell)
{
	if (column < 0 || row < 0 || column >= m_size || row >= m_size) { throw "Out of range"; }

	m_board[row * m_size + column] = cell;
}

SudokuCell& SudokuBoard::getCell(int column, int row)
{
	if (column < 0 || row < 0 || column >= m_size || row >= m_size) { throw "Out of range"; }

	return m_board[row * m_size + column];
}
