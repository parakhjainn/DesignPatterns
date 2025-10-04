#pragma once // To ensure the header is included only once during compilation
#include <string>
using namespace std;

class Innings {
private:
    string currentOver;
    string currentBall;
    string currentRunRate;
    string currentScore;
    string wickets;

public:
    // Getters
    string getCurrentOver() const {
        return currentOver;
    }

    string getCurrentBall() const {
        return currentBall;
    }

    string getCurrentRunRate() const {
        return currentRunRate;
    }

    string getCurrentScore() const {
        return currentScore;
    }

    string getWickets() const {
        return wickets;
    }

    // Setters
    void setCurrentOver(const string& over) {
        currentOver = over;
    }

    void setCurrentBall(const string& ball) {
        currentBall = ball;
    }

    void setCurrentRunRate(const string& runRate) {
        currentRunRate = runRate;
    }

    void setCurrentScore(const string& score) {
        currentScore = score;
    }

    void setWickets(const string& wkt) {
        wickets = wkt;
    }
};