#pragma once

#include <iostream>
#include "vehicle.h"

using namespace std;

class Car : public Vehicle {
public:
    Car(const string& licensePlate) : Vehicle(licensePlate, VehicleType::CAR) {}
};