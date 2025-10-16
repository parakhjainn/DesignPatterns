#pragma once

#include<iostream>
#include <vector>
#include "level.h"
#include "vehicle.h"

using namespace std;

class ParkingLot {
    vector<Level> levels;

    // private constructor to achieve Singleton
    ParkingLot() {}

    // method to get the instance to allow singleton

public:

    static ParkingLot& getInstance() {
        static ParkingLot instance;
        return instance;
    }
    
    void addLevel(Level level) {
        levels.emplace_back(level);
    }

    bool parkVehicle(Vehicle* vehicle) {
        for(auto& level: levels) {
            if(level.parkVehicle(vehicle)) {
                cout << "Vehicle parked successfully\n";
                return true;
            }
        }

        cout << "No spots available\n";
        return false;
    }

    bool unparkVehicle(Vehicle* vehicle) {
        for(auto& level: levels) {
            if(level.unparkVehicle(vehicle)) {
                cout << "Vehicle unparked\n";
                return true;
            }
        }

        return false;
    }

    void displayAvailability() {
        for(auto& level: levels) {
            level.displayAvailability();
        }
    }
};