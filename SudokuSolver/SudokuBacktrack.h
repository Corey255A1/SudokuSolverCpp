/*
* WunderVision 2024
* Iterate through and check each valid value in the non readonly
* cells until it reaches the end or throws an error
*/
#ifndef HSudokuBacktrack
#define HSudokuBacktrack
#include "SudokuBoard.h"

#include <memory>

class SudokuBacktrack {
private:
	std::shared_ptr<SudokuBoard> m_board;
	size_t m_currentRow;
	size_t m_currentColumn;

	void backTrack();
	static std::shared_ptr<SudokuValue> getNextValidValue(const std::set<std::shared_ptr<SudokuValue>, SudokuValueLT>& validValues, const SudokuValue* currentValue);
public:
	SudokuBacktrack(std::shared_ptr<SudokuBoard> board);
	bool solve();
	bool takeStep();
	void reset();
};
#endif