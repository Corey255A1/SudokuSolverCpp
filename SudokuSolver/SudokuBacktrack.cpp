/*
* WunderVision 2024
* Use the backtrack algorithm to solve a sudoku board
*/
#include "SudokuBacktrack.h"
#include "SudokuValueRange.h"

#include <stdexcept>

std::shared_ptr<SudokuValue> SudokuBacktrack::getNextValidValue(const std::set<std::shared_ptr<SudokuValue>, SudokuValueLT>& validValues, const SudokuValue* currentValue)
{
	for (const auto& validValue : validValues)
	{
		if (currentValue->lessThan(validValue.get()))
		{
			return validValue;
		}
	}
	return currentValue->getValueRange()->getDefault();
}

SudokuBacktrack::SudokuBacktrack(std::shared_ptr<SudokuBoard> board) :
	m_board(board),
	m_currentRow(0),
	m_currentColumn(0)
{
}

void SudokuBacktrack::backTrack()
{
	do {
		if (m_currentColumn == 0)
		{
			if (m_currentRow == 0)
			{
				throw std::runtime_error("Invalid Board");
			}
			m_currentRow -= 1;
			m_currentColumn = m_board->getSize();
		}
		m_currentColumn -= 1;
	} while (m_board->getCell(m_currentColumn, m_currentRow).isReadOnly());
}

void SudokuBacktrack::reset() {
	m_currentRow = 0;
	m_currentColumn = 0;
	for (int row = 0; row < m_board->getSize(); row++)
	{
		for (int column = 0; column < m_board->getSize(); column++)
		{
			SudokuCell& cell = m_board->getCell(column, row);
			if (!cell.isReadOnly())
			{
				cell.clear();
			}
		}
	}
}

bool SudokuBacktrack::takeStep()
{
	if (m_currentRow >= m_board->getSize()) { return true; }

	if (m_currentColumn < m_board->getSize())
	{
		SudokuCell& cell = m_board->getCell(m_currentColumn, m_currentRow);
		if (cell.isReadOnly())
		{
			m_currentColumn++;
			return false;
		}
		const auto& cellValue = cell.value();


		std::set<std::shared_ptr<SudokuValue>, SudokuValueLT> validValues = m_board->getValidValues(m_currentColumn, m_currentRow);
		if (validValues.size() == 0)
		{
			cell.clear();
			backTrack();
			return false;
		}

		if (cell.isSet())
		{
			auto nextValue = getNextValidValue(validValues, cell.value().get());
			if (nextValue->isDefault())
			{
				cell.clear();
				backTrack();
				return false;
			}
			else
			{
				cell.setValue(nextValue);
			}
		}
		else
		{
			cell.setValue(*(validValues.begin()));
		}
		m_currentColumn++;
	}
	else
	{
		m_currentColumn = 0;
		m_currentRow++;
	}

	return m_currentRow >= m_board->getSize();

}


bool SudokuBacktrack::solve(std::wostream* output)
{
	reset();
	try {
		if (output != nullptr)
		{
			auto& outputRef = *output;
			outputRef << "\x1b[2J\x1b[?25l";
			while (!takeStep()) {
				outputRef << "\x1b[0;0H";
				outputRef << m_board->toString();
			}
			outputRef << "\x1b[2J\x1b[?25h";
		}
		else 
		{
			while (!takeStep()) {}
		}

	}
	catch (std::exception e) {
		return false;
	}

	return true;
}