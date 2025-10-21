#pragma once

#include <iostream>
#include <string>

using namespace std;

enum class Symbol {
    X,
    O,
    E
};

class Player {
    string name;
    Symbol symbol;

public:
    Player(string& name, Symbol symbol) : name(name), symbol(symbol) {}

    string getName() {
        return name;
    }

    Symbol getSymbol() {
        return symbol;
    }
};