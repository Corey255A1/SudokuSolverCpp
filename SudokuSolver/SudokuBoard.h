#include <vector>
#include "SudokuCell.h"
class SudokuBoard {
private:
	std::vector<SudokuCell> m_board;
	int m_size;
public:
	SudokuBoard(int size);
	int size() const;

	void setCell(int column, int row, const SudokuCell& cell);
	SudokuCell& getCell(int column, int row);

};