/*
 * WunderVision 2024
 * A complex Sudoku Solver
 * It can read in more than just numbers,
 * it can parse boards made of emojis and
 * process boards that are different sizes than 9x9
 */

#include "SudokuSolver.h"
#include "SudokuFileReader.h"
#include "SudokuBacktrack.h"

#include <iostream>
#include <locale>
#include <chrono>
#ifdef _WINDOWS
#include <fcntl.h>
#include <io.h>
#endif

void getInteractiveFilePath(std::string &filePath)
{
	std::wcout << L"Sudoku File path: ";
	std::getline(std::cin, filePath);
}

int main(int argc, char **argv)
{
	std::setlocale(LC_ALL, "");
#ifdef _WINDOWS
	_setmode(_fileno(stdout), _O_U16TEXT);
	//_setmode(_fileno(stdin), _O_U16TEXT);
#endif
	std::string filePath;
	bool isInteractive = false;
	std::wostream *verboseOutput = nullptr;
	if (argc >= 2)
	{
		for (int argIndex = 1; argIndex < argc; argIndex++)
		{
			if (std::string(argv[argIndex]) == "-v")
			{
				verboseOutput = &std::wcout;
			}
			else
			{
				filePath.assign(argv[argIndex]);
			}
		}
	}
	else
	{
		getInteractiveFilePath(filePath);
		isInteractive = true;
	}

	while (!filePath.empty())
	{
		try
		{
			std::shared_ptr<SudokuBoard> board = std::move(SudokuFileReader::read(filePath));
			std::wcout << board->toString();
			if (!board->isValid())
			{
				std::wcout << L"Sudoku Board is not valid\n";
				if (isInteractive)
				{
					getInteractiveFilePath(filePath);
					continue;
				}
				break;
			}
			SudokuBacktrack backTrack(board);
			std::wcout << L"Looking for solution..." << std::endl;
			auto startTime = std::chrono::high_resolution_clock::now();
			if (!backTrack.solve(verboseOutput))
			{
				std::wcout << L"Sudoku Board could not be solved" << std::endl;
			}
			auto endTime = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			double seconds = static_cast<double>(duration.count()) / 1000000.0;
			std::wcout << std::endl
					   << L"-- Solution Found in " << seconds << L"s!! --" << std::endl;
			std::wcout << board->toString();
			std::wcout << L"--Enter These Values--\n"
					   << board->toStringOnlyEntries();
		}
		catch (std::exception e)
		{
			std::wcerr << e.what() << std::endl;
		}

		if (!isInteractive)
		{
			break;
		}
		getInteractiveFilePath(filePath);
	}

	std::wcout << L"Have a good day!" << std::endl;
	return 0;
}
