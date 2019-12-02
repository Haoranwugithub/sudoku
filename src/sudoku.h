#include <iostream>
#include <cstring>

class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator ==(const int (*otherGrid)[9]) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%3][i/3] != otherGrid[i%3][i/3]) {
                return false;
            }
        }
        return true;
    }

    bool operator ==(const Sudoku & other) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%3][i/3] != other.grid[i%3][i/3]) {
                return false;
            }
        }
        return true;
    }

    int get(int i, int j) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j];
        }

        return -1;
    }

    int set(int i, int j, int val) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j] = val;
        }
        return -1;
    }
    bool isEmpty(int grid[9][9], int &row, int &col){
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 9; col++) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    void print() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                printf(" [%d] ", get(i, j));
                if (j == 8) {
                    printf("\n");
                }
            }
        }
    }
    bool UsedInRow(int grid[9][9], int row, int val){
        for (int col = 0; col < 9; col++) {
            if (grid[row][col] == val) {
                return true;
            }
        }
        return false;
    }

    bool UsedInCol(int grid[9][9], int col, int val){
        for (int row = 0; row < 9; row++) {
            if (grid[row][col] == val) {
                return true;
            }
        }
        return false;
    }

    bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int val){
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (grid[row + boxStartRow][col + boxStartCol] == val) {
                    return true;
                }
            }
        }
        return false;

    }

    bool legal(int grid[9][9], int row, int col, int val){
        if(UsedInRow(grid, row, val)){
            return false;
        }

        if(UsedInCol(grid, col, val)){
            return false;
        }

        if(UsedInBox(grid, row - row%3 ,col - col%3, val)){
            return false;
        }

        if(!(grid[row][col]==0)){
            return false;
        }
        return true;}


    bool _solve(int grid[9][9]) {
        int row, col;

        if (!isEmpty(grid, row, col)) {
            return true;
        }

        for (int val = 0; val < 9; val++){
            if (!UsedInRow(grid, row, val+1) &&
                !UsedInCol(grid, col, val+1) &&
                !UsedInBox(grid, row - row % 3 ,col - col % 3, val+1) &&
                grid[row][col] == 0){
                grid[row][col] = val+1;
            if (_solve(grid)) {
                    return true;
                }
                grid[row][col] = 0;
            }
        }
        return false;
    }

    bool solve() {
        // homework
        _solve(grid);
        return true;
    }


};
//got idea from https://bokjan.com/2016/12/backtracking-sudoku.html
//and https://www.geeksforgeeks.org/check-key-present-cpp-map-unordered_map/
