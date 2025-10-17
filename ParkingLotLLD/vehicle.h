#pragma once

#include <string>
#include "vehicleType.h"

using namespace std;

class Vehicle {
    string licensePlate;
    VehicleType type;
public:
    Vehicle(const string licensePlate, VehicleType type) : licensePlate(licensePlate), type(type) {}
  
    VehicleType getType() {
        return type; 
    }

    string getLicensePlate() { 
        return licensePlate; 
    }

    virtual ~Vehicle() = default;
};