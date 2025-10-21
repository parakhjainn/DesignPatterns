#pragma once

#include <vector>
#include <iostream>
#include "models/vehicle.h"
#include "level.h"

using namespace std;

class ParkingLot {
    vector<Level*> levels;
    
    // Private constructor for Singleton
    ParkingLot() {}
    
public:
    // Singleton instance
    static ParkingLot& getInstance() {
        static ParkingLot instance;
        return instance;
    }
    
    // Delete copy constructor and assignment operator
    ParkingLot(ParkingLot&) = delete;
    ParkingLot& operator=(ParkingLot&) = delete;
    
    void addLevel(Level* level) {
        levels.push_back(level); 
    }
    
    bool parkVehicle(Vehicle* vehicle) {
        cout << "\n";
        for(auto& level : levels) {
            if(level -> parkVehicle(vehicle)) {
                cout << "Vehicle parked successfully\n";
                return true;
            }
        }
        cout << "No spots available\n";
        return false;
    }
    
    bool unparkVehicle(Vehicle* vehicle) {
        cout << "\n";
        for(auto& level : levels) {
            if(level -> unparkVehicle(vehicle)) {
                cout << "Vehicle unparked\n";
                return true;
            }
        }
        return false;
    }
    
    void displayAvailability() {
        for(auto& level : levels) {
            level -> displayAvailability();
        }
    }

    ~ParkingLot() {
        for(auto& l : levels) {
            delete l;
        }
    }
};
