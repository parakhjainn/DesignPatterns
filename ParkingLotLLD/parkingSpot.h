#pragma once

#include "models/vehicle.h"

using namespace std;

class ParkingSpot {
    int spotNumber;
    VehicleType vehicleType;
    Vehicle* parkedVehicle; // Non-owning pointer
    
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
        parkedVehicle = v;
    }
    
    bool isAvailable() {
        return parkedVehicle == nullptr;
    }
    
    void parkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr) {
            throw invalid_argument("Vehicle pointer is null");
        }
        
        if (parkedVehicle == nullptr && vehicle->getType() == vehicleType) {
            parkedVehicle = vehicle;
            return;
        }
        
        throw invalid_argument("Invalid vehicle type or spot not available");
    }
    
    void unparkVehicle() {
        parkedVehicle = nullptr;
    }
};
