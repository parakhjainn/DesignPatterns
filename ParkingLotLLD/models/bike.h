#pragma once

#include <iostream>
#include "vehicle.h"

using namespace std;

class Bike : public Vehicle {
public:
    Bike(const string& licensePlate) : Vehicle(licensePlate, VehicleType::BIKE) {}
};