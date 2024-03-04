# CMakeList.txt : CMake project for SudokuSolver, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (SudokuSolver "SudokuSolver.cpp" "SudokuSolver.h" "SudokuFileReader.cpp" "SudokuFileReader.h" "SudokuBoard.cpp" "SudokuBoard.h" "SudokuCell.cpp" "SudokuCell.h" "SudokuBacktrack.cpp" "SudokuValue.h" "SudokuValue.cpp" "SudokuValueInt.h" "SudokuValueInt.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SudokuSolver PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
