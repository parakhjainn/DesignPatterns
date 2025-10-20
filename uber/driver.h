#pragma once

#include <iostream>
#include <string>
#include "location.h"

using namespace std;

enum class DriverStatus {
    ONLINE,
    OFFLINE,
    IN_RIDE
};

class Driver {
    string id;
    string name;
    string phone;
    Location location;
    string license;
    DriverStatus status;
    // ... more prop like vehicle, etc can be added 

public:
    Driver () {}

    Driver(string id, string name, string phone, string license, Location location, DriverStatus status) {
        this -> id = id;
        this -> name = name;
        this -> phone = phone;
        this -> license = license;
        this -> location = location;
        this -> status = status;
    }


    // Note to myself:
    // Ignore the getters/setters based on discussion with interviewer
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

    string getLicense() {
        return license;
    }

    DriverStatus getStatus() {
        return status;
    }

    void setStatus(DriverStatus status) {
        this -> status = status;
    }

    void updateLocation(Location newLocation) {
        this -> location = newLocation;
    }

};
