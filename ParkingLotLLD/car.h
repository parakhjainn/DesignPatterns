#pragma once

#include<iostream>
#include "vehicle.h"
#include "vehicleType.h"

using namespace std;

class Car : public Vehicle {
public:
    Car(const string& licensePlate) : Vehicle(licensePlate, VehicleType::CAR) {}
};