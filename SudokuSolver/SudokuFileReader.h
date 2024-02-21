#include <string>
#include "SudokuBoard.h"
class SudokuFileReader {
public:
	static SudokuBoard read(const std::string filePath);

};