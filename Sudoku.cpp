// sudoku.cpp
#include "Sudoku.h"

Sudoku::Sudoku()
{
    grid = std::vector<std::vector<int>>(6, std::vector<int>(6, 0));
}

bool Sudoku::isSafe(int row, int col, int num)
{
    // Check row
    for (int i = 0; i < grid.size(); ++i)
    {
        if (grid[row][i] == num)
        {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < grid.size(); ++i)
    {
        if (grid[i][col] == num)
        {
            return false;
        }
    }

    // Check subgrid (2x3 in this case)
    int subgridRowStart = row - row % 2;
    int subgridColStart = col - col % 3;
    for (int i = subgridRowStart; i < subgridRowStart + 2; ++i)
    {
        for (int j = subgridColStart; j < subgridColStart + 3; ++j)
        {
            if (grid[i][j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::fillGrid()
{
    // Find empty position
    int row = -1, col = -1;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1)
        {
            break;
        }
    }

    // If no empty position found, Sudoku grid is filled
    if (row == -1)
    {
        return true;
    }

    // Try placing numbers 1 to 6 at empty position
    std::vector<int> nums{1, 2, 3, 4, 5, 6};
    std::random_shuffle(nums.begin(), nums.end()); // Shuffle the numbers
    for (int num : nums)
    {
        if (isSafe(row, col, num))
        {
            grid[row][col] = num;
            if (fillGrid())
            {
                return true;
            }
            grid[row][col] = 0; // Backtrack if placing num doesn't lead to solution
        }
    }

    // No number can be placed at empty position
    return false;
}

bool Sudoku::solveGrid()
{
    // Find empty position
    int row = -1, col = -1;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1)
        {
            break;
        }
    }

    // If no empty position found, Sudoku grid is solved
    if (row == -1)
    {
        return true;
    }

    // Try placing numbers 1 to 6 at empty position
    for (int num = 1; num <= 6; ++num)
    {
        if (isSafe(row, col, num))
        {
            grid[row][col] = num;
            if (solveGrid())
            {
                return true;
            }
            grid[row][col] = 0; // Backtrack if placing num doesn't lead to solution
        }
    }

    // No number can be placed at empty position
    return false;
}

void Sudoku::removeCells(int numCellsToRemove)
{
    srand(time(0));
    while (numCellsToRemove > 0)
    {
        int row = rand() % grid.size();
        int col = rand() % grid[0].size();
        if (grid[row][col] != 0)
        {
            grid[row][col] = 0;
            numCellsToRemove--;
        }
    }
}

bool Sudoku::isValidPuzzle()
{
    Sudoku tempGrid;
    tempGrid.grid = grid;

    if (tempGrid.solveGrid())
    {
        return true;
    }
    return false;
}

void Sudoku::generatePuzzle()
{
    // Fill grid with random numbers from 1 to 6
    srand(time(0));
    fillGrid();

    // Remove some cells to make it a puzzle
    removeCells(10); // Adjust the number of cells to remove as desired
}

void Sudoku::printGridLine()
{
    std::cout << "------------------" << std::endl;
}

void Sudoku::printGrid()
{
    printGridLine();
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] != 0)
            {
                std::cout << grid[i][j] << " ";
            }
            else
            {
                std::cout << "  ";
            }
            if ((j + 1) % 3 == 0)
            {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if ((i + 1) % 2 == 0 && i != grid.size() - 1)
        {
            printGridLine();
        }
    }
    printGridLine();
}

void Sudoku::solvePuzzle()
{
    if (isValidPuzzle())
    {
        if (solveGrid())
        {
            std::cout << "Sudoku Puzzle Solved:" << std::endl;
            printGrid();
        }
        else
        {
            std::cout << "No solution exists for the Sudoku puzzle." << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid Sudoku puzzle. Cannot be solved." << std::endl;
    }
}

void Sudoku::setUserInput(int row, int col, int num)
{
    if (isInputValid(row, col, num))
    {
        if (!isNumberValidForCell(row, col, num))
        {
            std::cout << "Invalid number! Please enter a different number." << std::endl;
            return;
        }
        if (grid[row][col] == 0)
        {
            grid[row][col] = num;
        }
        else
        {
            std::cout << "Invalid input! Number already exist in the position. Please provide valid row & column" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid input! Please provide valid row (0-5), column (0-5), and number (1-6)." << std::endl;
    }
}

bool Sudoku::isInputValid(int row, int col, int num)
{
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || num < 1 || num > 6)
    {
        return false;
    }
    return true;
}

bool Sudoku::isPuzzleComplete()
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::isNumberValidForCell(int row, int col, int num)
{
    if (!isNumberPresentInRow(row, num) && !isNumberPresentInCol(col, num) &&
        !isNumberPresentInSubgrid(row, col, num))
    {
        return true;
    }
    return false;
}

bool Sudoku::isNumberPresentInRow(int row, int num)
{
    for (int j = 0; j < grid[row].size(); ++j)
    {
        if (grid[row][j] == num)
        {
            return true;
        }
    }
    return false;
}

bool Sudoku::isNumberPresentInCol(int col, int num)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        if (grid[i][col] == num)
        {
            return true;
        }
    }
    return false;
}

bool Sudoku::isNumberPresentInSubgrid(int row, int col, int num)
{
    int subgridRowStart = row - row % 2;
    int subgridColStart = col - col % 3;
    for (int i = subgridRowStart; i < subgridRowStart + 2; ++i)
    {
        for (int j = subgridColStart; j < subgridColStart + 3; ++j)
        {
            if (grid[i][j] == num)
            {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::isPuzzleSolved()
{
    // Check if every cell is filled and each number is valid in its row, column, and subgrid
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            // If any cell is empty or its number is not valid, the puzzle is not solved
            if (grid[i][j] == 0 || !isNumberValidForCell(i, j, grid[i][j]))
            {
                return false;
            }
        }
    }
    return true; // If all cells are filled and each number is valid, the puzzle is solved
}

/*
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
*/