#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include <stdexcept>
#include "vehicle.h"
#include "vehicleType.h"
#include "parkingSpot.h"

using namespace std;

class Level {
    int floor;
    vector<ParkingSpot> parkingSpots;
    mutex mtx;

    static const char* toString(VehicleType t) {
        switch (t) {
            case VehicleType::BIKE:  return "BIKE";
            case VehicleType::CAR:   return "CAR";
            case VehicleType::TRUCK: return "TRUCK";
        }
        return "UNKNOWN";
    }

public:
    Level(int floor, int numSpots) : floor(floor) {
        parkingSpots.reserve(3 * numSpots);
        // bike
        for (int i = 0; i < numSpots; ++i) {
            parkingSpots.emplace_back(i + 1, VehicleType::BIKE);
        }
        // cars
        for (int i = numSpots; i < 2 * numSpots; ++i) {
            parkingSpots.emplace_back(i + 1, VehicleType::CAR);
        }
        // truck
        // for (int i = 2 * numSpots; i < 3 * numSpots; ++i) {
        //     parkingSpots.emplace_back(i + 1, VehicleType::TRUCK);
        // }
    }

    bool parkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr) return false;
        lock_guard<mutex> lock(mtx);
        for (auto& spot : parkingSpots) {
            try {
                spot.parkVehicle(vehicle);
                return true;
            } catch (const exception&) {
                // spot not compatible or occupied; try next
            }
        }
        cout << "No spots available\n";
        return false;
    }

    // Unparks the specific vehicle pointer if found
    bool unparkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr) return false;
        lock_guard<mutex> lock(mtx);
        for (auto& spot : parkingSpots) {
            const Vehicle* parked = spot.getParkedVehicle();
            if (parked != nullptr && parked == vehicle) {
                spot.unparkVehicle();
                return true;
            }
        }
        return false;
    }

    void displayAvailability() {
        lock_guard<mutex> lock(mtx);
        for (auto& spot : parkingSpots) {
            if (spot.isAvailable()) {
                cout << "Parking Spot " << spot.getSpotNumber()
                          << " is available for type " << toString(spot.getVehicleType())
                          << "\n";
            } else {
                const Vehicle* v = spot.getParkedVehicle();
                cout << "Parking Spot " << spot.getSpotNumber()
                     << " is occupied by vehicle " << v->getLicensePlate() << "\n";
            }
        }
    }
};
