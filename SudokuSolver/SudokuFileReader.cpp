/*
 * WunderVision 2024
 */
#include "SudokuFileReader.h"
#include "SudokuValueIntRange.h"
#include "SudokuValueEmojiRange.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <algorithm>

// Because files may have different line endings and getline might not match the line ending type
void trim(std::wstring &stringToTrim)
{
	stringToTrim.erase(std::remove(stringToTrim.begin(), stringToTrim.end(), L'\r'), stringToTrim.end());
	stringToTrim.erase(std::remove(stringToTrim.begin(), stringToTrim.end(), L'\n'), stringToTrim.end());
}

bool getlineTrim(std::wifstream &stream, std::wstring &line)
{
	bool isEnd = std::getline(stream, line).eof();
	trim(line);
	return !isEnd;
}

void SudokuFileReader::getBoxSize(std::wifstream &stream, int &width, int &height)
{
	stream >> width >> height;
	std::wstring endOfLine;
	std::getline(stream, endOfLine);
}

size_t SudokuFileReader::getBoardSize(std::wifstream &stream)
{
	std::streampos startPos = stream.tellg();
	size_t size = 0;
	std::wstring line;
	getlineTrim(stream, line);
	std::wstringstream characterStream(line);
	while (!characterStream.eof())
	{
		std::wstring character;
		characterStream >> character;
		size++;
	}
	stream.seekg(startPos);
	return size;
}

std::vector<std::wstring> SudokuFileReader::getEmojiList(std::wifstream &stream)
{
	// L"🤖", L"😀", L"😃", L"😄", L"😁", L"😆", L"😛", L"😝", L"😜", L"🤪"
	std::vector<std::wstring> emojis;
	std::wstring characterLine;
	getlineTrim(stream, characterLine);
	std::wstringstream characterStream(characterLine);
	while (!characterStream.eof())
	{
		std::wstring character;
		characterStream >> character;
		emojis.push_back(character);
	}
	return emojis;
}

void SudokuFileReader::processHeader(std::wifstream &stream, SudokuFileReader::Header &header)
{
	while (!stream.eof())
	{
		wchar_t unicodeChar;
		std::streampos startPos = stream.tellg();
		stream >> unicodeChar;
		if (unicodeChar == L'B')
		{
			getBoxSize(stream, header.boxWidth, header.boxHeight);
		}
		else if (unicodeChar == L'U')
		{
			auto range = std::make_shared<SudokuValueEmojiRange>();
			range->setRange(getEmojiList(stream));
			header.valueTypeRange = range;
		}
		else
		{
			stream.seekg(startPos);
			break;
		}
	}
}

void SudokuFileReader::processLine(SudokuBoard &board, const std::wstring &line, int rowIndex)
{
	std::wstringstream stream(line);
	auto &values = board.getValueRange();
	int columnIndex = 0;
	while (!stream.eof() && columnIndex < board.getSize())
	{
		auto value = values->parseStream(stream);
		if (!value->isDefault())
		{
			board.setCellValue(columnIndex, rowIndex, value);
			board.setCellReadOnly(columnIndex, rowIndex, true);
		}
		columnIndex++;
	}
}

std::unique_ptr<SudokuBoard> SudokuFileReader::read(const std::string &filePath)
{
#ifdef _WINDOWS
	std::locale utf8Locale = std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>());
#else
	std::locale utf8Locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
#endif

	std::wifstream sudokuFile(filePath, std::ios::binary);
	sudokuFile.imbue(utf8Locale);
	if (!sudokuFile.is_open())
	{
		throw std::runtime_error("Sudoku File could not be opened");
	}

	// std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
	// std::wstring utfContents = converter.from_bytes(fileContents.str());

	SudokuFileReader::Header header;
	processHeader(sudokuFile, header);

	if (!header.valueTypeRange)
	{
		int sudokuSize = getBoardSize(sudokuFile);
		if (sudokuSize == 0)
		{
			throw std::runtime_error("Invalid Board Size");
		}

		auto range = std::make_shared<SudokuValueIntRange>();
		range->setRange(-1, 1, sudokuSize);
		header.valueTypeRange = range;
	}

	std::unique_ptr<SudokuBoard> board = std::make_unique<SudokuBoard>(header.valueTypeRange, header.boxWidth, header.boxHeight);

	std::wstring line;
	int row = 0;
	bool hasMoreRows = true;
	while (hasMoreRows && row < header.valueTypeRange->getCount())
	{
		hasMoreRows = getlineTrim(sudokuFile, line);
		processLine(*board, line, row);
		row += 1;
	}
	return board;
}
