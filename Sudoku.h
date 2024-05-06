// Sudoku.h
#ifndef SUDOKU_H
#define SUDOKU_H

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>

class Sudoku
{
public:
    std::vector<std::vector<int>> grid;
    std::chrono::steady_clock::time_point startTime;
    bool isSafe(int row, int col, int num);
    bool fillGrid();
    bool solveGrid();
    bool isValidPuzzle();
    void removeCells(int numCellsToRemove);
    bool isInputValid(int row, int col, int num);
    bool isNumberPresentInRow(int row, int num);
    bool isNumberPresentInCol(int col, int num);
    bool isNumberPresentInSubgrid(int row, int col, int num);
    void printGridLine();


    Sudoku();
    void generatePuzzle();
    void printGrid();
    void solvePuzzle();
    bool isPuzzleComplete();
    void setUserInput(int row, int col, int num);
    bool isPuzzleSolved();
    bool isNumberValidForCell(int row, int col, int num);
    void startTimer();
    void stopTimer();
    double getElapsedTime();
    
};

#endif