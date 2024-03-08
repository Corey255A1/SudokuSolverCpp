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
#ifdef _WINDOWS
	std::locale utf8Locale = std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>());
#else
	std::locale utf8Locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
#endif
	
            
	std::wifstream sudokuFile(filePath, std::ios::binary);
	sudokuFile.imbue(utf8Locale);
	if (!sudokuFile.is_open()) { throw std::runtime_error("Sudoku File could not be opened"); }

	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
	//std::wstring utfContents = converter.from_bytes(fileContents.str());
	
	std::wstring line;
	std::shared_ptr<SudokuValueRange> valueTypeRange;
	int sudokuSize = 0;

	wchar_t unicodeChar;
	sudokuFile >> unicodeChar;
	bool unicodeMode = false;
	if(unicodeChar == L'U'){
		std::vector<std::wstring> emojis;
		// L"🤖", L"😀", L"😃", L"😄", L"😁", L"😆", L"😛", L"😝", L"😜", L"🤪"
		
		std::wstring characterLine;
		std::getline(sudokuFile, characterLine);
		std::wstringstream characterStream(characterLine);
		while(!characterStream.eof()){
			std::wstring character;
			characterStream >> character;
			if (character.empty()) { continue; }
			emojis.push_back(character);
		}
		valueTypeRange = std::make_shared<SudokuValueEmojiRange>(emojis);
		sudokuSize = emojis.size() - 1;
		if (!std::getline(sudokuFile, line)) { throw std::runtime_error("Not a valid Sudoku File"); }
	} 
	else
	{
		sudokuFile.seekg(0);
		if (!std::getline(sudokuFile, line)) { throw std::runtime_error("Not a valid Sudoku File"); }
		sudokuSize = (line.length() + 1) / 2; // account for spaces
		valueTypeRange = std::make_shared<SudokuValueIntRange>(-1, 1, sudokuSize);
	}
	
	std::wcout << "Board Size: " << sudokuSize << std::endl << line << std::endl;
	std::unique_ptr<SudokuBoard> board = std::make_unique<SudokuBoard>(valueTypeRange);

	int row = 0;
	processLine(*valueTypeRange, line, row, board.get());
	while (std::getline(sudokuFile, line) && row < sudokuSize-1)
	{
		std::wcout << line << std::endl;
		row += 1;
		processLine(*valueTypeRange, line, row, board.get());
	}
	std::wcout << "Done Reading" << std::endl;
	return board;
}

void SudokuFileReader::processLine(const SudokuValueRange& values, const std::wstring& line, int rowIndex, SudokuBoard* board)
{
	std::wstringstream stream(line);
	int columnIndex = -1;
	while(!stream.eof() && columnIndex < board->getSize()){
		columnIndex++;
		auto value = values.parseStream(stream);
		if(value->isDefault()){ continue; }
		board->setCellValue(columnIndex, rowIndex, std::move(value));
		board->setCellReadOnly(columnIndex, rowIndex, true);
	}
}
