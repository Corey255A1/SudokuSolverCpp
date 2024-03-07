/*
* WunderVision 2024
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "SudokuFileReader.h"
#include "SudokuValueIntRange.h"
#include "SudokuValueEmojiRange.h"
#include <locale>
#include <codecvt>
std::unique_ptr<SudokuBoard> SudokuFileReader::read(const std::string& filePath)
{
	const std::locale utf8Locale
                = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
            
	std::wifstream sudokuFile(filePath, std::ios::binary);
	sudokuFile.imbue(utf8Locale);
	if (!sudokuFile.is_open()) { throw std::runtime_error("Sudoku File could not be opened"); }

	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
	//std::wstring utfContents = converter.from_bytes(fileContents.str());
	
	std::wstring line;
	if (!std::getline(sudokuFile, line)) { throw std::runtime_error("Not a valid Sudoku File"); }
	int sudokuSize = (line.length() + 1) / 2; // account for spaces
	std::wcout << "board size:" << sudokuSize << std::endl << line << std::endl;
	auto intValues = std::make_shared<SudokuValueIntRange>(-1, 1, sudokuSize);

	std::vector<std::wstring> emojis = {
		L"🤖", L"😀", L"😃", L"😄", L"😁", L"😆", L"😛", L"😝", L"😜", L"🤪"
	};
	auto emojiValues = std::make_shared<SudokuValueEmojiRange>(emojis);

	//std::unique_ptr<SudokuBoard> board = std::make_unique<SudokuBoard>(emojiValues);
	std::unique_ptr<SudokuBoard> board = std::make_unique<SudokuBoard>(intValues);
	
	int row = 0;
	processLine(*emojiValues, line, row, board.get());
	while (std::getline(sudokuFile, line) && row < sudokuSize-2)
	{
		std::wcout << line << std::endl;
		row += 1;
		processLine(*emojiValues, line, row, board.get());
	}
	return board;
}

void SudokuFileReader::processLine(const SudokuValueRange& values, const std::wstring& line, int rowIndex, SudokuBoard* board)
{
	std::wstringstream stream(line);
	int columnIndex = -1;
	while(!stream.eof()){
		columnIndex++;
		auto value = values.parseStream(stream);
		if(value->isDefault()){ continue; }
		board->setCellValue(columnIndex, rowIndex, std::move(value));
		board->setCellReadOnly(columnIndex, rowIndex, true);
	}
}
