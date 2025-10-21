#pragma once

#include <vector>
#include "player.h"

using namespace std;

class Board {
    int size;
    int maxMoves;
    int moves;
    vector<vector<Symbol>> grid;

    // Helper method to convert Symbol to char for display
    char symbolToChar(Symbol s) {
        if (s == Symbol::X) return 'X';
        if (s == Symbol::O) return 'O';
        return ' ';
    }

public:
    Board() {}

    Board(int size) : size(size), maxMoves(size * size), moves(0) {
        grid.resize(size, vector<Symbol>(size, Symbol::E));
    }

    void playMove(int row, int col, Symbol symbol) {
        if (row < 0 || col < 0 || row >= size || col >= size || grid[row][col] != Symbol::E) {
            throw invalid_argument("Invalid move");
        }
        grid[row][col] = symbol;
        moves++;
    }

    void printBoard() {
        cout << "\nCurrent Board:\n";
        
        // Print top border
        for (int j = 0; j < size; j++) {
            cout << "----";
        }
        cout << "-\n";

        // Print grid with borders
        for (int i = 0; i < size; i++) {
            cout << "| ";
            for (int j = 0; j < size; j++) {
                cout << symbolToChar(grid[i][j]) << " | ";
            }
            cout << "\n";
            
            // Print horizontal separator
            for (int j = 0; j < size; j++) {
                cout << "----";
            }
            cout << "-\n";
        }
        cout << endl;
    }

    bool isGameOver() {
        return moves == maxMoves;
    }

    bool isWinner() {
        cout << "Checking for winner..." << endl;

        // row check
        for (int i = 0; i < size; i++) {
            bool match = true;
            for (int j = 1; j < size; j++) {
                if (grid[i][j] == Symbol::E || grid[i][j] != grid[i][j - 1]) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }

        // col check
        for (int i = 0; i < size; i++) {
            bool match = true;
            for (int j = 1; j < size; j++) {
                if (grid[j][i] == Symbol::E || grid[j][i] != grid[j - 1][i]) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }

        // positive diagonal (0,0 - 1,1)
        int i = 1;
        int j = 1;
        bool match = true;
        while (i < size && j < size) {
            if (grid[i][j] == Symbol::E || grid[i][j] != grid[i - 1][j - 1]) {
                match = false;
                break;
            }
            i++;
            j++;
        }
        if (match) return true;

        // neg diagonal (0, size-1) -> (1, size-2)
        i = 1;
        j = size - 2;
        match = true;

        while (i < size && j >= 0) {
            if (grid[i][j] == Symbol::E || grid[i][j] != grid[i - 1][j + 1]) {
                match = false;
                break;
            }
            i++;
            j--;
        }

        return match;
    }
};
