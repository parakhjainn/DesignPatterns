#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Dice {
    int size;

public:
    Dice(int size) : size(size) {}
    int rollDice() {
        return rand() % size + 1; // 1..size
    }
};

class Snake {
    int head;
    int tail;

public:
    Snake(int head, int tail) : head(head), tail(tail) {}

    int getHead() { 
        return head; 
    }
    
    int getTail() { 
        return tail; 
    }
};

class Ladder {
    int bottom;
    int top;

public:
    Ladder(int bottom, int top) : bottom(bottom), top(top) {}
    
    int getBottom() { 
        return bottom; 
    }
    
    int getTop() { 
        return top; 
    }
};

class Player {
    string name;
    int position;

public:
    Player(string name, int position) : name(name), position(position) {}

    string& getName() { 
        return name; 
    }

    int getPosition() { 
        return position; 
    }
    
    void setPosition(int pos) {
        position = pos; 
    }
};

class Board {
    int size;
    unordered_map<int, int> snakesMap;
    unordered_map<int, int> laddersMap;

public:
    Board(int size, vector<Snake>& snakes, vector<Ladder>& ladders) : size(size) {
        for (auto& s : snakes) {
            snakesMap[s.getHead()] = s.getTail();
        }
        for (auto& l : ladders) {
            laddersMap[l.getBottom()] = l.getTop();
        }
    }

    int getSize() { 
        return size; 
    }

    int makeMove(int initialPosition, int moveBy) {
        int newPosition = initialPosition + moveBy;

        if (newPosition > size) return initialPosition;

        auto sIt = snakesMap.find(newPosition);
        if (sIt != snakesMap.end()) return sIt->second;

        auto lIt = laddersMap.find(newPosition);
        if (lIt != laddersMap.end()) return lIt->second;

        return newPosition;
    }
};

class Game {
    vector<Player> players;
    int currentPlayerIndex;
    Board board;
    Dice dice;

public:
    Game(Board board, Dice dice, vector<Player>& players, int currentPlayer)
        : players(players),
          currentPlayerIndex(currentPlayer),
          board(board),
          dice(dice) {}

    void playGame() {
        cout << "Game Started" << endl;

        while (true) {
            Player& player = players[currentPlayerIndex];

            int initialPosition = player.getPosition();
            int moveBy = dice.rollDice();
            int newPosition = board.makeMove(initialPosition, moveBy);

            cout << player.getName() << " made a move to " << newPosition << endl;

            player.setPosition(newPosition);

            if (isGameOver()) {
                cout << player.getName() << " won" << endl;
                break;
            }

            currentPlayerIndex = (currentPlayerIndex + 1) % (int)(players.size());
        }
    }

    bool isGameOver() {
        return players[currentPlayerIndex].getPosition() == board.getSize();
    }
};

int main() {
    vector<Player> players;
    players.emplace_back("Ronaldo", 0);
    players.emplace_back("Messi", 0);

    vector<Snake> snakes;
    snakes.emplace_back(55, 40);
    snakes.emplace_back(99, 30);
    snakes.emplace_back(70, 35);

    vector<Ladder> ladders;
    ladders.emplace_back(7, 60);
    ladders.emplace_back(2, 85);
    ladders.emplace_back(10, 80);

    Dice dice(6);
    Board board(100, snakes, ladders);
    Game game(board, dice, players, 0);

    game.playGame();

    return 0;
}
