#pragma once

#include <iostream>
#include "location.h"

using namespace std;

class Rider {
    string id;
    string name;
    string phone; 
    Location location;

public:
    Rider() {}

    Rider(string id, string name, string phone, Location location) {
        this -> id = id;
        this -> name = name;
        this -> phone = phone;
        this -> location = location;
    }

    string getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getPhone() {
        return phone;
    }

    Location getLocation() {
        return location;
    }

    void updateLocation(Location newLocation) {
        this -> location = newLocation;
    }

};