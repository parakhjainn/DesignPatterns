#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <utility>
#include "level.h"
#include "vehicle.h"

using namespace std;

class ParkingLot {
    vector<unique_ptr<Level>> levels;
    
    // Private constructor for Singleton
    ParkingLot() {}
    
public:
    // Singleton instance
    static ParkingLot& getInstance() {
        static ParkingLot instance;
        return instance;
    }
    
    // Delete copy constructor and assignment operator
    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;
    
    void addLevel(unique_ptr<Level> level) {
        levels.push_back(std::move(level));
    }
    
    bool parkVehicle(Vehicle* vehicle) {
        for(auto& level : levels) {
            if(level->parkVehicle(vehicle)) {
                cout << "Vehicle parked successfully\n";
                return true;
            }
        }
        cout << "No spots available\n";
        return false;
    }
    
    bool unparkVehicle(Vehicle* vehicle) {
        for(auto& level : levels) {
            if(level->unparkVehicle(vehicle)) {
                cout << "Vehicle unparked\n";
                return true;
            }
        }
        return false;
    }
    
    void displayAvailability() {
        for(auto& level : levels) {
            level->displayAvailability();
        }
    }
};
