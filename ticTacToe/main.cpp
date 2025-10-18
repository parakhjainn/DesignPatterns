#include "gameService.h"

using namespace std;

int main() {
    int size;
    cout << "Enter board size: ";
    cin >> size;
    cin.ignore(); // consume newline

    string player1Name;
    cout << "Enter player 1 name: ";
    getline(cin, player1Name);
    Player player1(player1Name, Symbol::X);

    string player2Name;
    cout << "Enter player 2 name: ";
    getline(cin, player2Name);
    Player player2(player2Name, Symbol::O);

    Game game(size, {player1, player2});
    game.playGame();

    return 0;
}
