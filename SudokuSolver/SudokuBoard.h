#include <vector>
#include "SudokuCell.h"
class SudokuBoard {
private:
	std::vector<SudokuCell> m_board;
	int m_size;
public:
	SudokuBoard(int size);
	void setCell(int x, int y, const SudokuCell& cell);
};