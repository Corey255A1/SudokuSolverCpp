#include "SudokuBoard.h"
#include <cmath>
SudokuBoard::SudokuBoard(int size) :
	m_size{ size },
	m_board(pow(m_size, 2)) // Future multidimension idea
{
}

void SudokuBoard::setCell(int x, int y, const SudokuCell& cell)
{
	if (x < 0 || y < 0 || x >= m_size || y >= m_size) { return; }

	m_board[y * m_size + x] = cell;
}

