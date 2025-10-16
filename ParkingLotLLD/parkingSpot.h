#pragma once
#include <iostream>
#include <mutex>
#include "vehicle.h"
#include "vehicleType.h"

using namespace std;

class ParkingSpot {
    int spotNumber;
    VehicleType vehicleType;
    Vehicle* parkedVehicle;        // use pointer to represent presence/absence
    mutable mutex mtx;

public:
    ParkingSpot(int spotNumber, VehicleType vehicleType)
        : spotNumber(spotNumber),
          vehicleType(vehicleType),
          parkedVehicle(nullptr) {}

    int getSpotNumber() const {
        return spotNumber;
    }

    VehicleType getVehicleType() const {
        return vehicleType;
    }

    // Expose a const pointer (no copy)
    const Vehicle* getParkedVehicle() const {
        return parkedVehicle;
    }

    // Sets the parked vehicle pointer; caller owns the object lifetime
    void setParkedVehicle(Vehicle* v) {
        lock_guard<mutex> lock(mtx);
        parkedVehicle = v;
    }

    bool isAvailable() const {
        lock_guard<mutex> lock(mtx);
        return parkedVehicle == nullptr;
    }

    void parkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr) {
            throw invalid_argument("Vehicle pointer is null");
        }

        lock_guard<mutex> lock(mtx);
        if (parkedVehicle == nullptr && vehicle->getType() == vehicleType) {
            parkedVehicle = vehicle;
            return;
        }
        throw invalid_argument("Invalid vehicle type or spot not available");
    }

    void unparkVehicle() {
        lock_guard<mutex> lock(mtx);
        parkedVehicle = nullptr;
    }

    ~ParkingSpot() {
        delete parkedVehicle;
    }
};
