#pragma once

#include "board.h"

using namespace std;

class Game {
private:
    Board board;
    vector<Player> players;
    int currentPlayer;

public:
    Game(int size, const vector<Player>& players) 
        : board(size), players(players), currentPlayer(0) {}

    void playGame() {
        // Print initial empty board
        board.printBoard();
        
        while (!board.isGameOver()) {
            while (true) {
                Player player = players[currentPlayer];
                cout << player.getName() << "'s turn (" 
                         << (player.getSymbol() == Symbol::X ? "X" : "O") << ")" << endl;
                int row, col;
                cout << "Enter row (0-based): ";
                cin >> row;
                cout << "Enter col (0-based): ";
                cin >> col;
                
                try {
                    board.playMove(row, col, player.getSymbol());
                } catch (const invalid_argument& e) {
                    cout << "Invalid move, try again." << endl;
                    continue; // don't change player
                }
                
                // Print board after successful move
                board.printBoard();
                
                if (board.isWinner()) {
                    cout << player.getName() << " wins!" << endl;
                    return;
                }
                currentPlayer = (currentPlayer + 1) % players.size();
                break;
            }
        }
        cout << "Game over! It's a draw." << endl;
    }
};
