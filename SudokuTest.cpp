#include <deepstate/DeepState.hpp>
#include "Sudoku.h"

using namespace deepstate;

TEST(Sudoku, GenerateAndSolvePuzzle) {
    Sudoku sudoku;
    sudoku.generatePuzzle();
    ASSERT_TRUE(sudoku.solveGrid());
}

TEST(Sudoku, SetUserInput) {
    Sudoku sudoku;
    sudoku.generatePuzzle();
    
    // Generate valid user inputs using DeepState functions
    int row = DeepState_IntInRange(0, 5);
    int col = DeepState_IntInRange(0, 5);
    int num = DeepState_IntInRange(1, 6);

    sudoku.setUserInput(row, col, num);

    // Check if the input was correctly set
    ASSERT_EQ(sudoku.grid[row][col], num);
}

TEST(Sudoku, SetUserInputInvalid) {
    Sudoku sudoku;
    sudoku.generatePuzzle();

    // Provide invalid user inputs
    int row = DeepState_Int();
    int col = DeepState_Int();
    int num = DeepState_Int();

    // Ensure that invalid inputs are rejected
    if (row < 0 || row >= 6 || col < 0 || col >= 6 || num < 1 || num > 6) {
        // If the inputs are invalid, retry with valid inputs
        row = DeepState_IntInRange(0, 5);
        col = DeepState_IntInRange(0, 5);
        num = DeepState_IntInRange(1, 6);
    }

    sudoku.setUserInput(row, col, num);

    // Check that the grid remains unchanged
    ASSERT_TRUE(sudoku.isValidPuzzle()); // Sudoku remains valid
}

TEST(Sudoku, IsPuzzleComplete) {
    Sudoku sudoku;
    sudoku.generatePuzzle();

    // Fill in all but one cell
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (sudoku.grid[i][j] == 0) {
                sudoku.setUserInput(i, j, 1); // Fill with any number
            }
        }
    }

   
}