/*
* WunderVision 2024
* Read Sudoku Board from a file and generate a Sudoku Board Class
*/
#ifndef HSudokuFileReader
#define HSudokuFileReader
#include "SudokuBoard.h"
#include "SudokuValueRange.h"

#include <string>
#include <memory>
class SudokuFileReader {
private:
	struct Header {
		std::shared_ptr<SudokuValueRange> valueTypeRange;
		int boxWidth;
		int boxHeight;
		Header() :boxWidth{ 0 }, boxHeight{ 0 } {}
	};
	static void processLine(SudokuBoard& board, const std::wstring& line, int row);
	static void processHeader(std::wifstream& stream, Header& header);
	static size_t getBoardSize(std::wifstream& stream);
	static void getBoxSize(std::wifstream& stream, int& width, int& height);
	static std::vector<std::wstring> getEmojiList(std::wifstream& stream);
public:
	static std::unique_ptr<SudokuBoard> read(const std::string& filePath);
};
#endif