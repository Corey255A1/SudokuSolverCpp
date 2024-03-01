/*
* WunderVision 2024
* Iterate through and check each valid value in the non readonly
* cells until it reaches the end or throws an error
*/

#include <memory>
#include "SudokuBoard.h"

#ifndef HSudokuBacktrack
#define HSudokuBacktrack
class SudokuBacktrack {
private:
	std::shared_ptr<SudokuBoard> m_board;
	int m_currentRow;
	int m_currentColumn;

	void backTrack();
	static SudokuValue getNextValidValue(const std::set<SudokuValue>& validValues, SudokuValue currentValue);
public:
	SudokuBacktrack(std::shared_ptr<SudokuBoard> board);
	bool solve();
	bool takeStep();
	void reset();
};
#endif