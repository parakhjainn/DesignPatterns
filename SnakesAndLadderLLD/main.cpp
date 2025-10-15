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
    int getHead() const { return head; }
    int getTail() const { return tail; }
};

class Ladder {
    int bottom;
    int top;
public:
    Ladder(int bottom, int top) : bottom(bottom), top(top) {}
    int getBottom() const { return bottom; }
    int getTop() const { return top; }
};

class Player {
    string name;
    int position;
public:
    Player(string name, int position) : name(std::move(name)), position(position) {}
    const string& getName() const { return name; }
    int getPosition() const { return position; }
    void setPosition(int pos) { position = pos; }
};

class Board {
    int size;
    unordered_map<int, int> snakesMap;
    unordered_map<int, int> laddersMap;
public:
    Board(int size, const vector<Snake>& snakes, const vector<Ladder>& ladders)
        : size(size) {
        for (const auto& s : snakes) {
            snakesMap[s.getHead()] = s.getTail();
        }
        for (const auto& l : ladders) {
            laddersMap[l.getBottom()] = l.getTop();
        }
    }

    int getSize() const { return size; }

    int makeMove(int initialPosition, int moveBy) const {
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
    Game(Board board, Dice dice, const vector<Player>& players, int currentPlayer)
        : players(players),
          currentPlayerIndex(currentPlayer),
          board(std::move(board)),
          dice(std::move(dice)) {}

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

            currentPlayerIndex = (currentPlayerIndex + 1) % static_cast<int>(players.size());
        }
    }

    bool isGameOver() const {
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
    ladders.emplace_back(10, 60);
    ladders.emplace_back(2, 85);
    ladders.emplace_back(10, 80);

    Dice dice(6);
    Board board(100, snakes, ladders);
    Game game(board, dice, players, 0);
    game.playGame();

    return 0;
}
