// 1

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Movie {
    // use encapsulation to protect the internal state of the object
    string id;
    string title;
    string genre;
    int minDuration;

public:
    Movie(string id, string title, string genre, int minDuration) {
        this -> id = id;
        this -> title = title;
        this -> genre = genre;
        this -> minDuration = minDuration;
    }

    string getId() {
        return id;
    }

    string getTitle() {
        return title;
    }

    int getMinDuration() {
        return minDuration;
    }
};