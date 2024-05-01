// Sudoku_main.cpp

#include <iostream>
#include "sudoku.h"

int main()
{
    Sudoku sudoku;
    sudoku.generatePuzzle();
    std::cout << "Generated Sudoku Puzzle:" << std::endl;
    sudoku.printGrid();
    std::cout << std::endl;

    int row, col, num;
    while (!sudoku.isPuzzleComplete())
    {
        std::cout << "Enter row, column, and number (0-5) to fill in the Sudoku puzzle (Example: 0 0 5): ";
        std::cin >> row >> col >> num;
        sudoku.setUserInput(row, col, num);
        std::cout << "Updated Sudoku Puzzle:" << std::endl;
        sudoku.printGrid();
    }

    std::cout << "Congratulations! You solved the Sudoku puzzle." << std::endl;
    return 0;
}