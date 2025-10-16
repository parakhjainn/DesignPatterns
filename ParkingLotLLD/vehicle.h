#pragma once
#include<string>
#include "vehicleType.h"

using namespace std;

class Vehicle {
    string licensePlate;
    VehicleType type;
public:
    Vehicle(string licensePlate, VehicleType type) : licensePlate(licensePlate), type(type) {}
  
    VehicleType getType() const { return type; }

    string getLicensePlate() const { return licensePlate; }

    virtual ~Vehicle() = default;
};