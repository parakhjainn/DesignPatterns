#pragma once
#include <string>
#include <vector>
#include "player.h"
using namespace std;

class Team {
private:
    string name;
    string teamId;
    vector<Player> players;

public:
    // Getters
    string getName() const {
        return name;
    }

    string getTeamId() const {
        return teamId;
    }

    vector<Player> getPlayers() const {
        return players;
    }

    // Setters
    void setName(const string& n) {
        name = n;
    }

    void setTeamId(const string& id) {
        teamId = id;
    }

    void setPlayers(const vector<Player>& p) {
        players = p;
    }
};