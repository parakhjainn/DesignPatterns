// 2

#include <iostream>
#include <vector>
#include <string>
#include "show.h"

using namespace std;

class Show;

class Theatre {
    string id;
    string name;
    string location;
    vector<Show*> shows;

public:
    Theatre(String id, String name, String location) {
        this -> id = id;
        this -> name = name;
        this -> location = location;
    }

    void addShow(Show* show) {
        shows.add(show);
    }

};