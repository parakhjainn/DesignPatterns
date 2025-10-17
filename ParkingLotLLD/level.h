#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include "vehicle.h"
#include "vehicleType.h"
#include "parkingSpot.h"

using namespace std;

class Level {
    int floor;
    vector<unique_ptr<ParkingSpot>> parkingSpots;  // Changed to unique_ptr
    mutex mtx;
    
    static const char* toString(VehicleType t) {
        switch (t) {
            case VehicleType::BIKE: return "BIKE";
            case VehicleType::CAR: return "CAR";
            case VehicleType::TRUCK: return "TRUCK";
        }
        return "UNKNOWN";
    }
    
public:
    Level(int floor, int numSpots) : floor(floor) {
        parkingSpots.reserve(3 * numSpots);
        
        // Bike spots
        for (int i = 0; i < numSpots; ++i) {
            parkingSpots.push_back(make_unique<ParkingSpot>(i + 1, VehicleType::BIKE));
        }
        
        // Car spots
        for (int i = numSpots; i < 2 * numSpots; ++i) {
            parkingSpots.push_back(make_unique<ParkingSpot>(i + 1, VehicleType::CAR));
        }
        
        // Truck spots (commented out)
        // for (int i = 2 * numSpots; i < 3 * numSpots; ++i) {
        //     parkingSpots.push_back(make_unique<ParkingSpot>(i + 1, VehicleType::TRUCK));
        // }
    }
    
    bool parkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr) return false;
        
        lock_guard<mutex> lock(mtx);
        for (auto& spot : parkingSpots) {
            try {
                if (spot->isAvailable() && spot->getVehicleType() == vehicle->getType()) {
                    spot->parkVehicle(vehicle);
                    return true;
                }
            } catch (const exception& e) {
                continue;
            }
        }
        return false;
    }
    
    bool unparkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr) return false;
        
        lock_guard<mutex> lock(mtx);
        for (auto& spot : parkingSpots) {
            if (!spot->isAvailable() && spot->getParkedVehicle() == vehicle) {
                spot->unparkVehicle();
                return true;
            }
        }
        return false;
    }
    
    void displayAvailability() {
        lock_guard<mutex> lock(mtx);
        cout << "\n";
        for (auto& spot : parkingSpots) {
            if(spot->isAvailable()) {
                cout << "Parking Spot " << spot->getSpotNumber() 
                    << " is available for type " << toString(spot->getVehicleType());
            }
            else {
                cout << "Parking Spot " << spot->getSpotNumber() 
                    << " is occupied by vechile " << spot->getParkedVehicle()->getLicensePlate();
            }
            cout << "\n";
        }
    }
};
