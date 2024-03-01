#include "SudokuBacktrack.h"
#include <stdexcept>

SudokuValue SudokuBacktrack::getNextValidValue(const std::set<SudokuValue>& validValues, SudokuValue currentValue)
{
	for (const SudokuValue& validValue : validValues)
	{
		if (validValue > currentValue)
		{
			return validValue;
		}
	}
	return SudokuCell::DEFAULT_CELL;
}

SudokuBacktrack::SudokuBacktrack(std::shared_ptr<SudokuBoard> board):
	m_board(board),
	m_currentRow(0),
	m_currentColumn(0)
{
}

void SudokuBacktrack::backTrack()
{
	do {
		m_currentColumn -= 1;
		if (m_currentColumn < 0)
		{
			m_currentRow -= 1;
			m_currentColumn = m_board->size() - 1;
		}
		if (m_currentRow < 0) { throw std::runtime_error("Invalid Board"); }
	} while (m_board->getCell(m_currentColumn, m_currentRow).isReadOnly());
}

void SudokuBacktrack::reset() {
	m_currentRow = 0;
	m_currentColumn = 0;
	for (int row = 0; row < m_board->size(); row++)
	{
		for (int column = 0; column < m_board->size(); column++) 
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
	if (m_currentRow >= m_board->size()) { return true; }

	if (m_currentColumn < m_board->size())
	{
		SudokuCell& cell = m_board->getCell(m_currentColumn, m_currentRow);
		if (cell.isReadOnly())
		{
			m_currentColumn++;
			return false;
		}
		const auto& cellValue = cell.value();
		std::set<SudokuValue> validValues = m_board->getValidValues(m_currentColumn, m_currentRow);
		if (validValues.size() == 0)
		{
			cell.clear();
			backTrack();
			return false;
		}

		if (cell.isValid())
		{
			SudokuValue nextValue = getNextValidValue(validValues, cell.value());
			if (nextValue == SudokuCell::DEFAULT_CELL)
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
			cell.setValue(*validValues.begin());
		}
		m_currentColumn++;
	}
	else 
	{
		m_currentColumn = 0;
		m_currentRow++;
	}

	return m_currentRow >= m_board->size();

}


bool SudokuBacktrack::solve()
{
	reset();
	try {
		while (!takeStep()) {}
	}
	catch (std::exception e) {
		return false;
	}

	return true;
}