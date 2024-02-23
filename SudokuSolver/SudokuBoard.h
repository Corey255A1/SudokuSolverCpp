#include <set>
#include <vector>
#include "SudokuCell.h"
class SudokuBoard {
private:
	std::vector<SudokuCell> m_board;
	int m_size;
	int m_boxSize;
	void checkAndThrow(int column, int row);
public:
	static int findBoxSize(int size);
	SudokuBoard(int size);
	int size() const;

	void setCell(int column, int row, const SudokuCell& cell);
	SudokuCell& getCell(int column, int row);

	std::set<int> getValidValues(int column, int row);

};