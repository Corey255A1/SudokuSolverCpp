#include <string>
#include <memory>
#include "SudokuBoard.h"

class SudokuFileReader {
private:
	static void processLine(const std::string& line, int row, std::unique_ptr<SudokuBoard>& board);
public:
	static std::unique_ptr<SudokuBoard> read(const std::string& filePath);
};