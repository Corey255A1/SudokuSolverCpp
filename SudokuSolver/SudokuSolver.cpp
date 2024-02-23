/*
* WunderVision 2024
* A Simple Sudoku Solver. Using backtrack as the basis for the solving
* 1) Read a Sudoku board from a file
*  a) X is the empty cell
*
*/

#include "SudokuSolver.h"
#include "SudokuFileReader.h"
#include <algorithm>
using namespace std;

int getNextValue(const std::set<int>& validValues, int currentValue)
{
	for (int validValue : validValues)
	{
		if (validValue > currentValue)
		{
			return validValue;
		}
	}
	return -1;
}

void printBoard(const std::unique_ptr<SudokuBoard>& board) 
{
	std::cout << "\n";
	for (int row = 0; row < board->size(); row++)
	{
		for (int column = 0; column < board->size(); column++)
		{
			std::cout << board->getCell(column, row).value() << " ";
		}
		std::cout << "\n";
	}
}
int main()
{
	std::unique_ptr<SudokuBoard> board = SudokuFileReader::read("D:\\Documents\\CodeProjects\\SudokuSolver\\SudokuSolver\\sudoku_test.txt");

	for (int row = 0; row < board->size(); row++)
	{
		for (int column = 0; column < board->size(); column++)
		{
			std::cout << board->getCell(column, row).value() << " ";
		}
		std::cout << "\n";
	}

	for (int row = 0; row < board->size(); row++)
	{
		int column = 0;
		while(column < board->size())
		{
			SudokuCell& cell = board->getCell(column, row);
			if (cell.isReadOnly()) 
			{
				column++;
				continue; 
			}
			int cellValue = cell.value();
			std::set<int> validValues = board->getValidValues(column, row);
			if (validValues.size() == 0) 
			{
				cell.clear();
				do {
					column -= 1;
					if (column < 0) {
						row -= 1;
						column = board->size() - 1;
					}
				} while (board->getCell(column, row).isReadOnly());
				printBoard(board);
				continue;
			}

			if (cell.isValid())
			{				
				int nextValue = getNextValue(validValues, cell.value());
				if (nextValue == -1)
				{
					cell.clear();
					do {						
						column -= 1;
						if (column < 0) {
							row -= 1;
							column = board->size() - 1;
						}
					} while (board->getCell(column, row).isReadOnly());
					printBoard(board);
					continue;
				}
				else
				{
					cell.setValue(nextValue);
				}
			}
			else 
			{
				cell.setValue(*validValues.begin());
			}
			column++;
			printBoard(board);
		}
		std::cout << "\n";
	}



	return 0;
}
