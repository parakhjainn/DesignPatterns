#pragma once

#include <mutex>
#include "vehicle.h"
#include "vehicleType.h"

using namespace std;

class ParkingSpot {
    int spotNumber;
    VehicleType vehicleType;
    Vehicle* parkedVehicle; // Non-owning pointer
    mutex mtx;
    
public:
    ParkingSpot(int spotNumber, VehicleType vehicleType)
        : spotNumber(spotNumber),
          vehicleType(vehicleType),
          parkedVehicle(nullptr) {}
    
    int getSpotNumber() {
        return spotNumber;
    }
    
    VehicleType getVehicleType() {
        return vehicleType;
    }
    
    Vehicle* getParkedVehicle() {
        return parkedVehicle;
    }
    
    void setParkedVehicle(Vehicle* v) {
        lock_guard<mutex> lock(mtx);
        parkedVehicle = v;
    }
    
    bool isAvailable() {
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
};
