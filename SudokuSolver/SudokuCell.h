/*
* WunderVision 2024
* Each Cell in a board has a value, and whether or not that value can be modified to solve the game
*/
class SudokuCell {
private:
	int m_value;
	bool m_isReadOnly;
public:
	/*
	Deleted copy assignment operator
	An implicitly-declared or explicitly-defaulted(since C++11) copy assignment operator for class T 
	is undefined(until C++11)defined as deleted(since C++11) if any of the following conditions is satisfied:
	T has a non-static data member of a const-qualified non-class type (or possibly multi-dimensional array thereof).
	*/
	static const int DEFAULT_CELL = -1;
	SudokuCell();
	SudokuCell(int value, bool isReadOnly);

	bool isReadOnly() const;
	bool isValid() const;
	int value() const;
	bool setValue(int value);
	void clear();
};