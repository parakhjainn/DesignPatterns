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
    Player(const string& name, Symbol symbol) : name(name), symbol(symbol) {}

    string getName() const {
        return name;
    }

    Symbol getSymbol() const {
        return symbol;
    }
};