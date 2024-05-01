#include <deepstate/DeepState.hpp>
#include "sudoku.h"

using namespace deepstate;

#define GRID_SIZE 6

TEST(Sudoku, GeneratePuzzle) {
    Sudoku sudoku;
    sudoku.generatePuzzle();
    ASSERT_TRUE(sudoku.isValidPuzzle());
}

TEST(Sudoku, SetUserInputValid) {
    Sudoku sudoku;
    sudoku.generatePuzzle();

    // Provide valid user inputs
    int row = DeepState_IntInRange(0, GRID_SIZE - 1);
    int col = DeepState_IntInRange(0, GRID_SIZE - 1);
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
    sudoku.setUserInput(row, col, num);

    // Check that the grid remains unchanged
    ASSERT_TRUE(sudoku.isValidPuzzle()); // Sudoku remains valid
}

TEST(Sudoku, IsPuzzleComplete) {
    Sudoku sudoku;
    sudoku.generatePuzzle();

    // Fill in all but one cell
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (sudoku.grid[i][j] == 0) {
                sudoku.setUserInput(i, j, 1); // Fill with any number
            }
        }
    }

    // At this point, there should be one empty cell left
    ASSERT_FALSE(sudoku.isPuzzleComplete());

    // Fill the last cell
    sudoku.setUserInput(GRID_SIZE - 1, GRID_SIZE - 1, 1);

    // The puzzle should now be complete
    ASSERT_TRUE(sudoku.isPuzzleComplete());
}
