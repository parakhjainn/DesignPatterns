#pragma once

#include <mutex>
#include <stdexcept>
#include "vehicle.h"
#include "vehicleType.h"

using namespace std;

class ParkingSpot {
    int spotNumber;
    VehicleType vehicleType;
    Vehicle* parkedVehicle; // Non-owning pointer
    mutable mutex mtx;
    
public:
    ParkingSpot(int spotNumber, VehicleType vehicleType)
        : spotNumber(spotNumber),
          vehicleType(vehicleType),
          parkedVehicle(nullptr) {}
    
    // Explicitly delete copy operations (mutex is non-copyable)
    ParkingSpot(const ParkingSpot&) = delete;
    ParkingSpot& operator=(const ParkingSpot&) = delete;
    
    // Allow move operations
    ParkingSpot(ParkingSpot&& other) noexcept
        : spotNumber(other.spotNumber),
          vehicleType(other.vehicleType),
          parkedVehicle(other.parkedVehicle),
          mtx() {
        other.parkedVehicle = nullptr;
    }
    
    ParkingSpot& operator=(ParkingSpot&& other) noexcept {
        if (this != &other) {
            spotNumber = other.spotNumber;
            vehicleType = other.vehicleType;
            parkedVehicle = other.parkedVehicle;
            other.parkedVehicle = nullptr;
        }
        return *this;
    }
    
    int getSpotNumber() const {
        return spotNumber;
    }
    
    VehicleType getVehicleType() const {
        return vehicleType;
    }
    
    const Vehicle* getParkedVehicle() const {
        return parkedVehicle;
    }
    
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
};
