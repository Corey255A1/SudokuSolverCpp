/*
* WunderVision 2024
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <algorithm>

#include "SudokuFileReader.h"
#include "SudokuValueIntRange.h"
#include "SudokuValueEmojiRange.h"


// Because files may have different line endings and getline might not match the line ending type
void trim(std::wstring& stringToTrim) {
	stringToTrim.erase(std::remove(stringToTrim.begin(), stringToTrim.end(), L'\r'), stringToTrim.end());
	stringToTrim.erase(std::remove(stringToTrim.begin(), stringToTrim.end(), L'\n'), stringToTrim.end());
}
bool getlineTrim(std::wifstream& stream, std::wstring& line) {
	bool isEnd = std::getline(stream, line).eof();
	trim(line);
	return !isEnd;
}

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
	int boxWidth = 0;
	int boxHeight = 0;
	auto startPos = sudokuFile.tellg();
	if(unicodeChar == L'B'){
		sudokuFile >> boxWidth >> boxHeight;
		getlineTrim(sudokuFile, line);
		startPos = sudokuFile.tellg();
		sudokuFile >> unicodeChar;
	}
	bool unicodeMode = false;
	if(unicodeChar == L'U'){
		std::vector<std::wstring> emojis;
		// L"🤖", L"😀", L"😃", L"😄", L"😁", L"😆", L"😛", L"😝", L"😜", L"🤪"
		
		std::wstring characterLine;
		getlineTrim(sudokuFile, characterLine);
		std::wstringstream characterStream(characterLine);
		while(!characterStream.eof())
		{
			std::wstring character;
			characterStream >> character;
			emojis.push_back(character);
		}
		valueTypeRange = std::make_shared<SudokuValueEmojiRange>(emojis);
		sudokuSize = emojis.size() - 1;
		if (!getlineTrim(sudokuFile, line)) { throw std::runtime_error("Not a valid Sudoku File"); }
	} 
	else
	{
		sudokuFile.seekg(startPos);
		if (!getlineTrim(sudokuFile, line)) { throw std::runtime_error("Not a valid Sudoku File"); }
		std::wstringstream characterStream(line);
		while(!characterStream.eof())
		{
			std::wstring character;
			characterStream >> character;
			sudokuSize++;
		}
		valueTypeRange = std::make_shared<SudokuValueIntRange>(-1, 1, sudokuSize);
	}
	
	std::wcout << "Board Size: " << sudokuSize << std::endl << line << std::endl;
	std::unique_ptr<SudokuBoard> board = std::make_unique<SudokuBoard>(valueTypeRange, boxWidth, boxHeight);

	int row = 0;
	bool hasMoreRows = true;
	processLine(*valueTypeRange, line, row, board.get());
	while (hasMoreRows && row < sudokuSize-1)
	{
		row += 1;
		std::wcout << line << std::endl;
		hasMoreRows = getlineTrim(sudokuFile, line);
		processLine(*valueTypeRange, line, row, board.get());
	}
	std::wcout << "Done Reading" << std::endl;
	return board;
}

void SudokuFileReader::processLine(const SudokuValueRange& values, const std::wstring& line, int rowIndex, SudokuBoard* board)
{
	std::wstringstream stream(line);
	int columnIndex = 0;
	while(!stream.eof() && columnIndex < board->getSize()){
		auto value = values.parseStream(stream);
		if (!value->isDefault()) {
			board->setCellValue(columnIndex, rowIndex, std::move(value));
			board->setCellReadOnly(columnIndex, rowIndex, true);
		}
		columnIndex++;
	}
}
